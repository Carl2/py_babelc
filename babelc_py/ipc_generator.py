"""Jinja2 template rendering for IPC header generation.

This module implements the code generation layer that takes a validated
CompilationUnit and produces a complete .ipc.h file using Jinja2 templates.

All public functions follow the functional-python style: curried where
configuration is needed, returning Maybe values for pipeline composition.
"""

from __future__ import annotations

import re
from dataclasses import dataclass
from pathlib import Path
from typing import Any

import jinja2
from pymonad.maybe import Just, Maybe

from babelc_py.type_model import (
    AliasType,
    CompilationUnit,
    ContainerType,
    EnumType,
    Field,
    InterfaceType,
    Method,
    Parameter,
    StructType,
    VariantType,
)


# ---------------------------------------------------------------------------
# Enriched dataclasses (carry computed rendering data alongside model types)
# ---------------------------------------------------------------------------


@dataclass(frozen=True)
class EnrichedField:
    """A struct field with pre-computed wire type and read/write expressions."""

    name: str
    type_name: str
    wire_type: str
    is_complicated: bool
    read_expr: str
    write_expr: str


@dataclass(frozen=True)
class EnrichedParam:
    """A method parameter with pre-computed type info for rendering."""

    name: str
    type_name: str
    type_qualified: str
    is_const: bool
    is_ref: bool
    is_complicated: bool
    initializer: str  # e.g. "{}" or ""


@dataclass(frozen=True)
class EnrichedMethod:
    """A method with pre-computed rendering data."""

    name: str
    return_type: str
    return_type_str: str
    has_return: bool
    params_enriched: tuple[EnrichedParam, ...]
    params_signature: str
    params_forward: str
    read_block: str
    write_return_block: str
    client_write_block: str
    client_read_return_block: str
    vtable_signature: str
    vtable_signal_signature: str
    has_enum_params: bool


@dataclass(frozen=True)
class EnrichedContainer:
    """A container with pre-computed rendering data."""

    name: str
    qualified_name: str
    namespace: tuple[str, ...]
    container_kind: str
    element_type: str
    element_type_qualified: str
    is_simple_element: bool
    element_read_expr: str
    element_write_expr: str


@dataclass(frozen=True)
class EnrichedStruct:
    """A struct with pre-computed field rendering data."""

    name: str
    qualified_name: str
    namespace: tuple[str, ...]
    fields_enriched: tuple[EnrichedField, ...]
    simple_read_fields: tuple[EnrichedField, ...]
    complicated_read_fields: tuple[EnrichedField, ...]
    simple_write_fields: tuple[EnrichedField, ...]
    complicated_write_fields: tuple[EnrichedField, ...]
    has_enum_fields: bool


@dataclass(frozen=True)
class EnrichedInterface:
    """An interface with pre-computed method rendering data."""

    name: str
    qualified_name: str
    namespace: tuple[str, ...]
    methods_enriched: tuple[EnrichedMethod, ...]
    all_methods_void: bool
    has_complicated_params: bool
    vtable_uses_boolean: bool
    dbus_name: str  # explicit D-Bus interface name (from annotation or derived)


# ---------------------------------------------------------------------------
# Type resolution helpers
# ---------------------------------------------------------------------------


def _lookup_type(type_name: str, cu: CompilationUnit) -> Any:
    """Look up a type by name in the compilation unit."""
    for enum in cu.enums:
        if enum.qualified_name == type_name or enum.name == type_name:
            return enum
    for struct in cu.structs:
        if struct.qualified_name == type_name or struct.name == type_name:
            return struct
    for cont in cu.containers:
        if cont.qualified_name == type_name or cont.name == type_name:
            return cont
    for alias in cu.aliases:
        if alias.qualified_name == type_name or alias.name == type_name:
            return alias
    for variant in cu.variants:
        if variant.qualified_name == type_name or variant.name == type_name:
            return variant
    return None


def _is_enum(type_name: str, cu: CompilationUnit) -> bool:
    resolved = _lookup_type(type_name, cu)
    return isinstance(resolved, EnumType)


def _is_struct(type_name: str, cu: CompilationUnit) -> bool:
    resolved = _lookup_type(type_name, cu)
    return isinstance(resolved, StructType)


def _is_container(type_name: str, cu: CompilationUnit) -> bool:
    resolved = _lookup_type(type_name, cu)
    return isinstance(resolved, ContainerType)


def _is_variant(type_name: str, cu: CompilationUnit) -> bool:
    resolved = _lookup_type(type_name, cu)
    return isinstance(resolved, VariantType)


def _get_enum(type_name: str, cu: CompilationUnit) -> EnumType | None:
    resolved = _lookup_type(type_name, cu)
    return resolved if isinstance(resolved, EnumType) else None


def _resolve_alias_target(type_name: str, cu: CompilationUnit) -> str:
    """Resolve a type alias to its target, returning the original if not an alias."""
    for alias in cu.aliases:
        if alias.qualified_name == type_name or alias.name == type_name:
            return alias.target_type
    return type_name


def _is_string(type_name: str) -> bool:
    return type_name in ("std::string", "string")


def _is_bool(type_name: str) -> bool:
    return type_name == "bool"


def _is_complicated_field(type_name: str, cu: CompilationUnit) -> bool:
    """True if a field with this type requires a separate IpcRead/WriteContainer call."""
    if _is_struct(type_name, cu):
        return True
    if _is_container(type_name, cu):
        return True
    if _is_variant(type_name, cu):
        return True
    # Check if it resolves to a container via alias
    target = _resolve_alias_target(type_name, cu)
    if target != type_name:
        return _is_complicated_field(target, cu)
    return False


# ---------------------------------------------------------------------------
# Wire type mapping (ipc_template_type / ipc_value_type)
# ---------------------------------------------------------------------------


def ipc_template_type(type_name: str, cu: CompilationUnit) -> str:
    """Map a C++ type to its TupleView/ArrayView template argument."""
    if _is_string(type_name):
        return "const char *"
    if _is_bool(type_name):
        return "Boolean"
    enum = _get_enum(type_name, cu)
    if enum is not None:
        return enum.underlying_type
    if _is_struct(type_name, cu):
        qn = _qualified_name_for(type_name, cu)
        return f"{qn}_TupleView<Boolean,IpcPolicy>"
    if _is_container(type_name, cu):
        qn = _qualified_name_for(type_name, cu)
        return qn
    # For containers resolved via alias
    resolved = _lookup_type(type_name, cu)
    if isinstance(resolved, ContainerType):
        return (
            resolved.qualified_name
            if resolved.qualified_name.startswith("::")
            else "::" + resolved.qualified_name
        )
    return type_name


def _qualified_name_for(type_name: str, cu: CompilationUnit) -> str:
    """Get the qualified name (with :: prefix) for a type."""
    resolved = _lookup_type(type_name, cu)
    if resolved is not None:
        qn = resolved.qualified_name
        if not qn.startswith("::"):
            return "::" + qn
        return qn
    # Don't prefix std:: types — they are already qualified
    if type_name.startswith("std::"):
        return type_name
    # Don't prefix primitive/builtin types
    if type_name in (
        "bool",
        "char",
        "int",
        "float",
        "double",
        "void",
        "short",
        "long",
        "unsigned",
        "signed",
    ):
        return type_name
    if not type_name.startswith("::"):
        return "::" + type_name
    return type_name


# ---------------------------------------------------------------------------
# Read/write expression generation
# ---------------------------------------------------------------------------


def _read_expr_for_field(
    field_name: str, type_name: str, struct_qn: str, cu: CompilationUnit
) -> str:
    """Generate the read expression for a struct field."""
    if _is_string(type_name):
        return f"&babel::ipc::StringReference(theStruct.{field_name})"
    if _is_bool(type_name):
        return f"&babel::ipc::BooleanReference<Boolean>(theStruct.{field_name})"
    enum = _get_enum(type_name, cu)
    if enum is not None:
        eqn = _qualified_name_for(type_name, cu)
        ns = "::".join(enum.namespace)
        return (
            f"&babel::ipc::EnumReference<\n"
            f"                {eqn},\n"
            f"                {_qualified_name_for_ns(enum.namespace)}::IpcEnumValidate\n"
            f"            >(theStruct.{field_name}, theErrorString )"
        )
    if _is_complicated_field(type_name, cu):
        qn = _qualified_name_for(type_name, cu)
        ns = _namespace_for(type_name, cu)
        return (
            f"{ns}::IpcReadContainer<IpcPolicy, typename IpcPolicy::Boolean>(\n"
            f"            theMessage,\n"
            f"            theStruct.{field_name}\n"
            f"        );"
        )
    # Simple passthrough
    return f"&theStruct.{field_name}"


def _write_expr_for_field(field_name: str, type_name: str, cu: CompilationUnit) -> str:
    """Generate the write expression for a struct field."""
    if _is_string(type_name):
        return f"theStruct.{field_name}.c_str()"
    if _is_bool(type_name):
        return f"static_cast<Boolean>(theStruct.{field_name})"
    enum = _get_enum(type_name, cu)
    if enum is not None:
        return f"static_cast<{enum.underlying_type}>(theStruct.{field_name})"
    if _is_complicated_field(type_name, cu):
        ns = _namespace_for(type_name, cu)
        return (
            f"{ns}::IpcWriteContainer<IpcPolicy, typename IpcPolicy::Boolean>(\n"
            f"            theMessage,\n"
            f"            theStruct.{field_name}\n"
            f"        );"
        )
    # Simple passthrough
    return f"theStruct.{field_name}"


def _namespace_for(type_name: str, cu: CompilationUnit) -> str:
    """Get the '::ns1::ns2' namespace prefix for a type."""
    resolved = _lookup_type(type_name, cu)
    if resolved is not None and hasattr(resolved, "namespace"):
        return _qualified_name_for_ns(resolved.namespace)
    return ""


def _qualified_name_for_ns(namespace: tuple[str, ...]) -> str:
    """Turn ('addressbook', 'v1') into '::addressbook::v1'."""
    if namespace:
        return "::" + "::".join(namespace)
    return ""


# ---------------------------------------------------------------------------
# Enrichment: containers
# ---------------------------------------------------------------------------


def _enrich_container(cont: ContainerType, cu: CompilationUnit) -> EnrichedContainer:
    """Add rendering data to a ContainerType."""
    element_qn = _qualified_name_for(cont.element_type, cu)
    is_simple = not _is_complicated_field(cont.element_type, cu)

    # For complicated elements, generate per-element read/write
    if is_simple:
        element_read = ""
        element_write = ""
    else:
        ns = _namespace_for(cont.element_type, cu)
        element_read = (
            f"{ns}::IpcReadContainer<IpcPolicy, typename IpcPolicy::Boolean>(\n"
            f"                theMessage,\n"
            f"                theElement\n"
            f"            );"
        )
        element_write = (
            f"{ns}::IpcWriteContainer<IpcPolicy, typename IpcPolicy::Boolean>(\n"
            f"                theMessage,\n"
            f"                theElement\n"
            f"            );"
        )

    return EnrichedContainer(
        name=cont.name,
        qualified_name=cont.qualified_name,
        namespace=cont.namespace,
        container_kind=cont.container_kind,
        element_type=cont.element_type,
        element_type_qualified=element_qn,
        is_simple_element=is_simple,
        element_read_expr=element_read,
        element_write_expr=element_write,
    )


# ---------------------------------------------------------------------------
# Enrichment: structs
# ---------------------------------------------------------------------------


def _enrich_field(field: Field, struct_qn: str, cu: CompilationUnit) -> EnrichedField:
    """Add rendering data to a Field."""
    # Bug 2 fix: For container-typed fields in _TupleView, babelc uses the raw
    # qualified name (e.g. ::ns::PhoneNumbers) not the _ArrayView form.
    if _is_container(field.type_name, cu):
        wire = _qualified_name_for(field.type_name, cu)
    else:
        wire = ipc_template_type(field.type_name, cu)
    complicated = _is_complicated_field(field.type_name, cu)
    read = _read_expr_for_field(field.name, field.type_name, struct_qn, cu)
    write = _write_expr_for_field(field.name, field.type_name, cu)
    return EnrichedField(
        name=field.name,
        type_name=field.type_name,
        wire_type=wire,
        is_complicated=complicated,
        read_expr=read,
        write_expr=write,
    )


def _enrich_struct(struct: StructType, cu: CompilationUnit) -> EnrichedStruct:
    """Add rendering data to a StructType."""
    enriched = tuple(_enrich_field(f, struct.qualified_name, cu) for f in struct.fields)
    simple_r = tuple(f for f in enriched if not f.is_complicated)
    complicated_r = tuple(f for f in enriched if f.is_complicated)
    has_enum = any(_is_enum(f.type_name, cu) for f in struct.fields)

    return EnrichedStruct(
        name=struct.name,
        qualified_name=struct.qualified_name,
        namespace=struct.namespace,
        fields_enriched=enriched,
        simple_read_fields=simple_r,
        complicated_read_fields=complicated_r,
        simple_write_fields=simple_r,
        complicated_write_fields=complicated_r,
        has_enum_fields=has_enum,
    )


# ---------------------------------------------------------------------------
# Enrichment: interfaces
# ---------------------------------------------------------------------------


def _enrich_param(param: Parameter, cu: CompilationUnit) -> EnrichedParam:
    """Add rendering data to a Parameter."""
    qn = _qualified_name_for(param.type_name, cu)
    complicated = _is_complicated_field(param.type_name, cu)
    init = ""

    return EnrichedParam(
        name=param.name,
        type_name=param.type_name,
        type_qualified=qn,
        is_const=param.is_const,
        is_ref=param.is_ref,
        is_complicated=complicated,
        initializer=init,
    )


def _method_params_signature(method: Method, cu: CompilationUnit) -> str:
    """Generate 'const Type &name, ...' parameter signature."""
    parts = []
    for p in method.parameters:
        qn = _qualified_name_for(p.type_name, cu)
        if p.is_ref and p.is_const:
            parts.append(f"const {qn} &{p.name}")
        elif p.is_ref:
            parts.append(f"{qn} &{p.name}")
        elif p.is_const:
            parts.append(f"const {qn} {p.name}")
        else:
            parts.append(f"{qn} {p.name}")
    return ", ".join(parts)


def _method_params_forward(method: Method) -> str:
    """Generate 'name1, name2, ...' forwarding list."""
    return ", ".join(p.name for p in method.parameters)


def _read_ref_for_param(p: Parameter, cu: CompilationUnit) -> str:
    """Generate the reference expression for reading a param in getMessageArguments."""
    if _is_string(p.type_name):
        return f"&babel::ipc::StringReference({p.name})"
    if _is_bool(p.type_name):
        return f"&babel::ipc::BooleanReference<typename IpcPolicy::Boolean>({p.name})"
    enum = _get_enum(p.type_name, cu)
    if enum is not None:
        eqn = _qualified_name_for(p.type_name, cu)
        ns = _qualified_name_for_ns(enum.namespace)
        return (
            f"&babel::ipc::EnumReference<\n"
            f"                    {eqn},\n"
            f"                    {ns}::IpcEnumValidate\n"
            f"                >({p.name}, theErrorString )"
        )
    # Builtin numeric
    return f"&{p.name}"


def _write_expr_for_param(p: Parameter, cu: CompilationUnit) -> str:
    """Generate the write expression for a param in appendMessageArguments."""
    if _is_string(p.type_name):
        return f"{p.name}.c_str()"
    if _is_bool(p.type_name):
        return f"static_cast<Boolean>({p.name})"
    enum = _get_enum(p.type_name, cu)
    if enum is not None:
        return f"static_cast<{enum.underlying_type}>({p.name})"
    # Builtin numeric
    return p.name


def _has_enum_params(method: Method, cu: CompilationUnit) -> bool:
    """True if any param is an enum type."""
    return any(_get_enum(p.type_name, cu) is not None for p in method.parameters)


def _method_read_block(method: Method, cu: CompilationUnit) -> str:
    """Generate the deserialization block for method arguments in ImplementationProxy.

    Groups consecutive simple params into batched getMessageArguments calls.
    Emits IpcReadContainer for complicated params.
    Adds theErrorString handling if any enum params exist.
    """
    if not method.parameters:
        return ""

    has_enum = _has_enum_params(method, cu)
    lines: list[str] = []

    if has_enum:
        lines.append("            std::string theErrorString;")
        lines.append("")

    # Process params in order, grouping simple ones
    i = 0
    params = method.parameters
    while i < len(params):
        p = params[i]
        if _is_complicated_field(p.type_name, cu):
            # Emit IpcReadContainer for this param
            ns = _namespace_for(p.type_name, cu)
            lines.append(
                f"            {ns}::IpcReadContainer<IpcPolicy, typename IpcPolicy::Boolean>(\n"
                f"                theArguments,\n"
                f"                {p.name}\n"
                f"            );"
            )
            i += 1
        else:
            # Collect consecutive simple params
            simple_group: list[Parameter] = []
            while i < len(params) and not _is_complicated_field(
                params[i].type_name, cu
            ):
                simple_group.append(params[i])
                i += 1
            # Emit batched getMessageArguments
            refs = [_read_ref_for_param(sp, cu) for sp in simple_group]
            lines.append("            IpcPolicy::getMessageArguments(")
            lines.append("                theArguments,")
            for j, ref in enumerate(refs):
                comma = "," if j < len(refs) - 1 else ""
                lines.append(f"                {ref}{comma}")
            lines.append("            );")

    if has_enum:
        lines.append("")
        lines.append(
            "            if (!theErrorString.empty()) { throw std::invalid_argument( theErrorString ); };"
        )

    return "\n".join(lines)


def _method_client_write_block(method: Method, cu: CompilationUnit) -> str:
    """Generate the serialization block for method arguments in ClientProxy.

    Groups consecutive simple params into batched appendMessageArguments calls.
    Emits IpcWriteContainer for complicated params.
    """
    if not method.parameters:
        return ""

    lines: list[str] = []

    # Process params in order, grouping simple ones
    i = 0
    params = method.parameters
    while i < len(params):
        p = params[i]
        if _is_complicated_field(p.type_name, cu):
            # Emit IpcWriteContainer for this param
            ns = _namespace_for(p.type_name, cu)
            lines.append(
                f"            {ns}::IpcWriteContainer<IpcPolicy, typename IpcPolicy::Boolean>(\n"
                f"                theIpcMessage,\n"
                f"                {p.name}\n"
                f"            );"
            )
            i += 1
        else:
            # Collect consecutive simple params
            simple_group: list[Parameter] = []
            while i < len(params) and not _is_complicated_field(
                params[i].type_name, cu
            ):
                simple_group.append(params[i])
                i += 1
            # Emit batched appendMessageArguments
            exprs = [_write_expr_for_param(sp, cu) for sp in simple_group]
            lines.append("            IpcPolicy::appendMessageArguments(")
            lines.append("                theIpcMessage,")
            for j, expr in enumerate(exprs):
                comma = "," if j < len(exprs) - 1 else ""
                lines.append(f"                {expr}{comma}")
            lines.append("            );")

    return "\n".join(lines)


def _vtable_signature(method: Method, cu: CompilationUnit) -> str:
    """Generate vtable type signature: 'RetIpcType, Arg1IpcType, Arg2IpcType, ...'

    Pattern: addMethod< RetIpcType, ArgTypes... >
    If no args: addMethod< RetIpcType, void >
    If void return with args: addMethod< void, ArgTypes... >
    """
    param_types = [ipc_template_type(p.type_name, cu) for p in method.parameters]
    args_part = ", ".join(param_types) if param_types else "void"

    if method.return_type == "void":
        ret_part = "void"
    else:
        ret_part = ipc_template_type(method.return_type, cu)

    return f"{ret_part}, {args_part}"


def _vtable_signal_signature(method: Method, cu: CompilationUnit) -> str:
    """Generate signal vtable type signature: 'Arg1IpcType, Arg2IpcType, ...'

    Signals have no return type — only the parameter types are listed.
    """
    param_types = [ipc_template_type(p.type_name, cu) for p in method.parameters]
    return ", ".join(param_types) if param_types else "void"


def _write_return_expr(method: Method, cu: CompilationUnit) -> str:
    """Generate the expression to serialize the return value in ImplementationProxy.

    This is the argument to IpcPolicy::appendMessageArguments that serializes
    the return value of theProxy.methodName(args...).
    """
    call = f"theProxy.{method.name}({_method_params_forward(method)})"
    rt = method.return_type

    if _is_string(rt):
        return f"{call}.c_str()"
    enum = _get_enum(rt, cu)
    if enum is not None:
        return f"static_cast<{enum.underlying_type}>({call})"
    if _is_bool(rt):
        return f"static_cast<Boolean>({call})"
    # Builtin numeric types
    return call


def _write_return_block(method: Method, cu: CompilationUnit) -> str:
    """Generate the write_return_block for ImplementationProxy static handler."""
    if method.return_type == "void":
        return ""
    expr = _write_return_expr(method, cu)
    return (
        f"            IpcPolicy::appendMessageArguments(\n"
        f"                theReturnValue,\n"
        f"                {expr}\n"
        f"            );\n"
    )


def _client_read_return_block(method: Method, cu: CompilationUnit) -> str:
    """Generate the client-side return deserialization block."""
    if method.return_type == "void":
        return ""
    rt = method.return_type
    rt_qn = _qualified_name_for(rt, cu)

    lines: list[str] = []

    enum = _get_enum(rt, cu)
    if enum is not None:
        ns = _qualified_name_for_ns(enum.namespace)
        lines.append("")
        lines.append("            std::string theErrorString;")
        lines.append("")
        lines.append("            IpcPolicy::getMessageArguments(")
        lines.append("                theMessageReturnValue,")
        lines.append(f"                &babel::ipc::EnumReference<")
        lines.append(f"                    {rt_qn},")
        lines.append(f"                    {ns}::IpcEnumValidate")
        lines.append(f"                >(theIpcReturnValue, theErrorString )")
        lines.append("            );")
        lines.append("")
        lines.append(
            "            if (!theErrorString.empty()) { throw std::invalid_argument( theErrorString ); };"
        )
    elif _is_string(rt):
        lines.append("")
        lines.append("            IpcPolicy::getMessageArguments(")
        lines.append("                theMessageReturnValue,")
        lines.append("                &babel::ipc::StringReference(theIpcReturnValue)")
        lines.append("            );")
    elif _is_bool(rt):
        lines.append("")
        lines.append("            IpcPolicy::getMessageArguments(")
        lines.append("                theMessageReturnValue,")
        lines.append(
            "                &babel::ipc::BooleanReference<Boolean>(theIpcReturnValue)"
        )
        lines.append("            );")
    else:
        # Builtin numeric
        lines.append("")
        lines.append("            IpcPolicy::getMessageArguments(")
        lines.append("                theMessageReturnValue,")
        lines.append("                &theIpcReturnValue")
        lines.append("            );")

    lines.append("")
    lines.append("            return theIpcReturnValue;")

    return "\n".join(lines)


def _enrich_method(method: Method, cu: CompilationUnit) -> EnrichedMethod:
    """Add rendering data to a Method."""
    params_enriched = tuple(_enrich_param(p, cu) for p in method.parameters)
    has_return = method.return_type != "void"

    return EnrichedMethod(
        name=method.name,
        return_type=method.return_type,
        return_type_str=method.return_type
        if method.return_type == "void"
        else _qualified_name_for(method.return_type, cu),
        has_return=has_return,
        params_enriched=params_enriched,
        params_signature=_method_params_signature(method, cu),
        params_forward=_method_params_forward(method),
        read_block=_method_read_block(method, cu),
        write_return_block=_write_return_block(method, cu),
        client_write_block=_method_client_write_block(method, cu),
        client_read_return_block=_client_read_return_block(method, cu),
        vtable_signature=_vtable_signature(method, cu),
        vtable_signal_signature=_vtable_signal_signature(method, cu),
        has_enum_params=_has_enum_params(method, cu),
    )


def _enrich_interface(
    iface: InterfaceType, cu: CompilationUnit, interface_names: dict[str, str]
) -> EnrichedInterface:
    """Add rendering data to an InterfaceType."""
    methods = tuple(_enrich_method(m, cu) for m in iface.methods)
    all_void = all(m.return_type == "void" for m in iface.methods)

    # Use explicit interface_name annotation if available, else derive from namespace
    dbus_name = interface_names.get(
        iface.name, ".".join(list(iface.namespace) + [iface.name])
    )

    has_complicated = any(
        _is_complicated_field(p.type_name, cu)
        for m in iface.methods
        for p in m.parameters
    )
    # vtable_uses_boolean: true if any param maps to Boolean in vtable sig
    # (bool params → Boolean, struct params → _TupleView<Boolean,IpcPolicy>)
    vtable_boolean = any(
        _is_bool(p.type_name) or _is_struct(p.type_name, cu)
        for m in iface.methods
        for p in m.parameters
    )
    return EnrichedInterface(
        name=iface.name,
        qualified_name=iface.qualified_name,
        namespace=iface.namespace,
        methods_enriched=methods,
        all_methods_void=all_void,
        has_complicated_params=has_complicated,
        vtable_uses_boolean=vtable_boolean,
        dbus_name=dbus_name,
    )


# ---------------------------------------------------------------------------
# Jinja2 filters
# ---------------------------------------------------------------------------


def _guard_macro(name: str) -> str:
    """Convert a qualified name to an include guard style: '::a::b::C' -> '__A__B__C'."""
    return name.replace("::", "__").upper()


def _qualified_filter(obj: Any) -> str:
    """Jinja2 filter: return '::ns1::ns2::Name'."""
    if hasattr(obj, "qualified_name"):
        qn = obj.qualified_name
    else:
        qn = str(obj)
    if not qn.startswith("::"):
        return "::" + qn
    return qn


def _ns_open_filter(obj: Any) -> str:
    """Jinja2 filter: emit 'namespace a::b {' (C++20)."""
    ns = obj.namespace if hasattr(obj, "namespace") else ()
    if ns:
        return f"namespace {'::'.join(ns)} {{"
    return "namespace {"


def _ns_close_filter(obj: Any) -> str:
    """Jinja2 filter: emit closing brace (C++20 = single brace)."""
    return "}"


def _dbus_interface_name_filter(obj: Any) -> str:
    """Jinja2 filter: return the D-Bus interface name."""
    if hasattr(obj, "dbus_name"):
        return obj.dbus_name
    parts = list(obj.namespace) + [obj.name]
    return ".".join(parts)


# ---------------------------------------------------------------------------
# Container kind detection
# ---------------------------------------------------------------------------


def _collect_container_kinds(cu: CompilationUnit) -> list[str]:
    """Collect unique container kinds used (e.g. 'std::vector')."""
    kinds: set[str] = set()
    for cont in cu.containers:
        kinds.add(f"std::{cont.container_kind}")
    return sorted(kinds)


# ---------------------------------------------------------------------------
# Jinja2 environment setup and rendering
# ---------------------------------------------------------------------------


def _create_jinja_env() -> jinja2.Environment:
    """Create a configured Jinja2 environment."""
    env = jinja2.Environment(
        loader=jinja2.PackageLoader("babelc_py", "templates"),
        keep_trailing_newline=True,
        trim_blocks=True,
        lstrip_blocks=True,
    )
    env.filters["guard_macro"] = _guard_macro
    env.filters["qualified"] = _qualified_filter
    env.filters["ns_open"] = _ns_open_filter
    env.filters["ns_close"] = _ns_close_filter
    env.filters["dbus_interface_name"] = _dbus_interface_name_filter
    return env


def _build_guard_name(output_path: str) -> str:
    """Build an include guard macro name from the output path."""
    # Convert path to uppercase with underscores
    name = output_path.replace("/", "_").replace(".", "_").replace("-", "_")
    return f"__{name.upper()}__"


def render_ipc_header(output_path: str) -> callable:
    """Curried: captures output path, returns a bind-compatible pipeline step.

    Reads ctx["compilation_unit"].
    Returns Just(ctx) with ctx["rendered_output"] added.
    """

    def do_render(ctx: dict) -> Maybe:
        try:
            cu: CompilationUnit = ctx["compilation_unit"]
            env = _create_jinja_env()
            template = env.get_template("ipc_header.h.j2")

            # Enrich types for rendering
            interface_names = ctx.get("interface_names", {})
            enriched_containers = [_enrich_container(c, cu) for c in cu.containers]
            enriched_enums = list(cu.enums)
            enriched_structs = [_enrich_struct(s, cu) for s in cu.structs]
            enriched_interfaces = [
                _enrich_interface(i, cu, interface_names) for i in cu.interfaces
            ]
            container_kinds = _collect_container_kinds(cu)

            rendered = template.render(
                header_path=cu.header_path,
                guard_name=_build_guard_name(output_path),
                enums=enriched_enums,
                structs=enriched_structs,
                containers=enriched_containers,
                interfaces=enriched_interfaces,
                container_kinds_used=container_kinds,
            )

            return Just(
                {**ctx, "rendered_output": rendered, "output_path": output_path}
            )
        except Exception as e:
            return Maybe(value=f"Failed to render IPC header: {e}", monoid=False)

    return do_render


def write_output(ctx: dict) -> Maybe:
    """Pipeline step: write rendered output to file.

    Reads ctx["rendered_output"] and ctx["output_path"].
    Returns Just(ctx) on success.
    """
    try:
        path = Path(ctx["output_path"])
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(ctx["rendered_output"])
        return Just(ctx)
    except Exception as e:
        return Maybe(value=f"Failed to write output: {e}", monoid=False)
