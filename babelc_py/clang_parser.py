"""libclang AST walking and extraction."""

from __future__ import annotations

import glob as globmod
import re
from pathlib import Path
from typing import Callable

from clang.cindex import (
    Cursor,
    CursorKind,
    Diagnostic,
    Index,
    TranslationUnit,
    TypeKind,
)
from pymonad.maybe import Just, Maybe, Nothing

from babelc_py.type_model import (
    AliasType,
    Annotation,
    BuiltinType,
    CompilationUnit,
    ContainerType,
    EnumType,
    Enumerator,
    Field,
    InterfaceType,
    Method,
    Parameter,
    PointerType,
    StructType,
    VariantType,
)

# ---------------------------------------------------------------------------
# Built-in types (hardcoded, not discovered from AST)
# ---------------------------------------------------------------------------

BUILTIN_TYPES: dict[str, BuiltinType] = {
    "std::uint8_t": BuiltinType(name="std::uint8_t"),
    "std::uint16_t": BuiltinType(name="std::uint16_t"),
    "std::uint32_t": BuiltinType(name="std::uint32_t"),
    "std::uint64_t": BuiltinType(name="std::uint64_t"),
    "std::int8_t": BuiltinType(name="std::int8_t"),
    "std::int16_t": BuiltinType(name="std::int16_t"),
    "std::int32_t": BuiltinType(name="std::int32_t"),
    "std::int64_t": BuiltinType(name="std::int64_t"),
    "bool": BuiltinType(name="bool"),
    "float": BuiltinType(name="float"),
    "double": BuiltinType(name="double"),
    "std::string": BuiltinType(name="std::string"),
    "void": BuiltinType(name="void"),
}

# Regex for extracting std::array size from spelling, e.g. "std::array<uint8_t, 20>"
_ARRAY_SIZE_RE = re.compile(r",\s*(\d+)\s*>")


# ---------------------------------------------------------------------------
# System include path discovery
# ---------------------------------------------------------------------------


def discover_system_cpp_includes() -> list[str]:
    """Discover system C++ include paths needed by pip-installed libclang.

    The pip ``clang`` package bundles its own libclang.so but often resolves
    GCC installation paths incorrectly (e.g. selecting GCC 14 which may
    lack C++ headers).  This function finds the right paths and returns
    clang-compatible ``-isystem`` / ``-nostdinc++`` arguments.

    Returns an empty list if discovery is not needed or fails.
    """
    # Find highest GCC version that actually has C++ headers
    gcc_cpp_dirs = sorted(
        Path(p).parent for p in globmod.glob("/usr/include/c++/*/cstdint")
    )
    if not gcc_cpp_dirs:
        return []

    gcc_dir = gcc_cpp_dirs[-1]  # highest version
    version = gcc_dir.name

    # Architecture-specific dir
    arch_dir = Path(f"/usr/include/x86_64-linux-gnu/c++/{version}")

    # Find a clang resource include dir (for stddef.h etc.)
    clang_resource_dirs = sorted(
        Path(p).parent
        for p in globmod.glob("/usr/lib/llvm-*/lib/clang/*/include/stddef.h")
    )

    args = ["-nostdinc++", "-isystem", str(gcc_dir)]
    if arch_dir.is_dir():
        args += ["-isystem", str(arch_dir)]
    if clang_resource_dirs:
        args += ["-isystem", str(clang_resource_dirs[-1])]
    return args


# ---------------------------------------------------------------------------
# Pipeline step 1: parse_with_clang
# ---------------------------------------------------------------------------


def parse_with_clang(ctx: dict) -> Maybe:
    """Parse a rewritten header with libclang.

    Reads ctx["rewritten_header_path"] and optional ctx["clang_args"].
    On success adds ctx["translation_unit"] and ctx["index"].
    """
    try:
        index = Index.create()
        tu = index.parse(
            ctx["rewritten_header_path"],
            args=["-std=c++20", "-x", "c++"] + ctx.get("clang_args", []),
            options=(
                TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD
                | TranslationUnit.PARSE_SKIP_FUNCTION_BODIES
            ),
        )
        errors = [d for d in tu.diagnostics if d.severity >= Diagnostic.Error]
        if errors:
            msg = "; ".join(str(e) for e in errors)
            return Maybe(value=f"Clang parse errors: {msg}", monoid=False)
        return Just({**ctx, "translation_unit": tu, "index": index})
    except Exception as e:
        return Maybe(value=f"Failed to parse: {e}", monoid=False)


# ---------------------------------------------------------------------------
# Annotation helpers
# ---------------------------------------------------------------------------


def _parse_babelc_annotation(annotation: str) -> Maybe:
    """Parse 'babelc::name=value' or 'babelc::name' into Annotation."""
    if not annotation.startswith("babelc::"):
        return Nothing
    rest = annotation[len("babelc::") :]
    if "=" in rest:
        name, value = rest.split("=", 1)
        return Just(Annotation(name=name, value=value))
    return Just(Annotation(name=rest))


def _collect_annotations(cursor: Cursor) -> tuple[Annotation, ...]:
    """Collect babelc annotations from ANNOTATE_ATTR children."""
    annotations: list[Annotation] = []
    for child in cursor.get_children():
        if child.kind == CursorKind.ANNOTATE_ATTR:
            result = _parse_babelc_annotation(child.displayname)
            if result.is_just():
                annotations.append(result.value)
    return tuple(annotations)


# ---------------------------------------------------------------------------
# Type resolution helpers
# ---------------------------------------------------------------------------


def _qualified_name(name: str, namespace: tuple[str, ...]) -> str:
    """Compose a fully qualified name from namespace stack and short name."""
    if namespace:
        return "::".join(namespace) + "::" + name
    return name


def _resolve_type_spelling(spelling: str) -> str:
    """Normalise a clang type spelling to a canonical form.

    Strips leading '::' prefix and normalises whitespace around angle brackets.
    """
    s = spelling.lstrip(":")
    # Normalise "type < " to "type<"
    s = re.sub(r"\s*<\s*", "<", s)
    s = re.sub(r"\s*>\s*", ">", s)
    s = re.sub(r"\s*,\s*", ", ", s)
    return s


def _extract_array_size(spelling: str) -> int | None:
    """Extract the integer size from a std::array<T, N> spelling."""
    m = _ARRAY_SIZE_RE.search(spelling)
    if m:
        return int(m.group(1))
    return None


def _resolve_container(
    spelling: str,
    name: str,
    qualified: str,
    namespace: tuple[str, ...],
) -> ContainerType | PointerType | VariantType | None:
    """Try to resolve a type spelling to a container/pointer/variant.

    Returns the appropriate type object or None if not a recognised pattern.
    """
    canonical = _resolve_type_spelling(spelling)

    # Varying-length containers
    for prefix, kind in [
        ("std::vector<", "vector"),
        ("std::list<", "list"),
    ]:
        if canonical.startswith(prefix):
            inner = canonical[len(prefix) : -1]
            return ContainerType(
                name=name,
                qualified_name=qualified,
                namespace=namespace,
                container_kind=kind,
                element_type=inner,
            )

    # Fixed array
    if canonical.startswith("std::array<"):
        inner_full = canonical[len("std::array<") : -1]
        # element type is everything before the last comma
        last_comma = inner_full.rfind(",")
        element = inner_full[:last_comma].strip() if last_comma != -1 else inner_full
        size = _extract_array_size(canonical)
        return ContainerType(
            name=name,
            qualified_name=qualified,
            namespace=namespace,
            container_kind="array",
            element_type=element,
            size=size,
        )

    # Map
    if canonical.startswith("std::map<"):
        inner_full = canonical[len("std::map<") : -1]
        # Split on first comma for key, rest is value
        first_comma = inner_full.find(",")
        if first_comma != -1:
            element = inner_full[first_comma + 1 :].strip()
        else:
            element = inner_full
        return ContainerType(
            name=name,
            qualified_name=qualified,
            namespace=namespace,
            container_kind="map",
            element_type=element,
        )

    # Optional
    for prefix, kind in [
        ("boost::optional<", "optional"),
        ("std::optional<", "optional"),
    ]:
        if canonical.startswith(prefix):
            inner = canonical[len(prefix) : -1]
            return ContainerType(
                name=name,
                qualified_name=qualified,
                namespace=namespace,
                container_kind=kind,
                element_type=inner,
            )

    # Smart pointers
    for prefix, kind in [
        ("std::shared_ptr<", "shared_ptr"),
        ("std::unique_ptr<", "unique_ptr"),
    ]:
        if canonical.startswith(prefix):
            inner = canonical[len(prefix) : -1]
            return PointerType(
                name=name,
                qualified_name=qualified,
                namespace=namespace,
                pointer_kind=kind,
                pointee_type=inner,
            )

    # Variants
    for prefix, vkind in [
        ("boost::variant<", "boost"),
        ("std::variant<", "std"),
    ]:
        if canonical.startswith(prefix):
            inner = canonical[len(prefix) : -1]
            # Split alternatives on top-level commas (not inside angle brackets)
            alternatives = _split_template_args(inner)
            return VariantType(
                name=name,
                qualified_name=qualified,
                namespace=namespace,
                variant_kind=vkind,
                alternatives=tuple(alternatives),
                annotations=(),
            )

    return None


def _split_template_args(args_str: str) -> list[str]:
    """Split a comma-separated template argument list respecting nesting."""
    result: list[str] = []
    depth = 0
    current: list[str] = []
    for ch in args_str:
        if ch == "<":
            depth += 1
            current.append(ch)
        elif ch == ">":
            depth -= 1
            current.append(ch)
        elif ch == "," and depth == 0:
            result.append("".join(current).strip())
            current = []
        else:
            current.append(ch)
    if current:
        result.append("".join(current).strip())
    return result


# ---------------------------------------------------------------------------
# Type-specific extractors
# ---------------------------------------------------------------------------


def _extract_enum(cursor: Cursor, namespace: tuple[str, ...]) -> Maybe:
    """Extract an EnumType from an ENUM_DECL cursor."""
    try:
        name = cursor.spelling
        qualified = _qualified_name(name, namespace)
        annotations = _collect_annotations(cursor)

        # Underlying type
        underlying = cursor.enum_type.spelling
        underlying = _resolve_type_spelling(underlying)

        # Enumerators
        enumerators: list[Enumerator] = []
        for child in cursor.get_children():
            if child.kind == CursorKind.ENUM_CONSTANT_DECL:
                enumerators.append(
                    Enumerator(name=child.spelling, value=child.enum_value)
                )

        return Just(
            EnumType(
                name=name,
                qualified_name=qualified,
                namespace=namespace,
                underlying_type=underlying,
                enumerators=tuple(enumerators),
                annotations=annotations,
            )
        )
    except Exception as e:
        return Maybe(
            value=f"Failed to extract enum {cursor.spelling}: {e}",
            monoid=False,
        )


def _extract_struct_or_interface(cursor: Cursor, namespace: tuple[str, ...]) -> Maybe:
    """Extract a StructType or InterfaceType from a STRUCT_DECL/CLASS_DECL."""
    try:
        name = cursor.spelling
        if not name:
            return Nothing  # anonymous struct, skip
        qualified = _qualified_name(name, namespace)
        annotations = _collect_annotations(cursor)

        fields: list[Field] = []
        methods: list[Method] = []
        has_pure_virtual = False

        for child in cursor.get_children():
            if child.kind == CursorKind.FIELD_DECL:
                field_type = _resolve_type_spelling(child.type.spelling)
                # Check for default value via tokens
                default_val = _extract_default_value(child)
                fields.append(
                    Field(
                        name=child.spelling,
                        type_name=field_type,
                        default_value=default_val,
                    )
                )
            elif child.kind == CursorKind.CXX_METHOD:
                if child.is_pure_virtual_method():
                    has_pure_virtual = True
                    params = _extract_parameters(child)
                    ret_type = _resolve_type_spelling(child.result_type.spelling)
                    methods.append(
                        Method(
                            name=child.spelling,
                            return_type=ret_type,
                            parameters=tuple(params),
                            is_pure_virtual=True,
                            is_const=child.is_const_method(),
                        )
                    )

        if has_pure_virtual:
            return Just(
                InterfaceType(
                    name=name,
                    qualified_name=qualified,
                    namespace=namespace,
                    methods=tuple(methods),
                    annotations=annotations,
                )
            )
        return Just(
            StructType(
                name=name,
                qualified_name=qualified,
                namespace=namespace,
                fields=tuple(fields),
                annotations=annotations,
            )
        )
    except Exception as e:
        return Maybe(
            value=f"Failed to extract struct/interface {cursor.spelling}: {e}",
            monoid=False,
        )


def _extract_parameters(method_cursor: Cursor) -> list[Parameter]:
    """Extract parameters from a CXX_METHOD cursor."""
    params: list[Parameter] = []
    for child in method_cursor.get_children():
        if child.kind == CursorKind.PARM_DECL:
            ptype = child.type
            is_ref = ptype.kind == TypeKind.LVALUEREFERENCE
            if is_ref:
                pointee = ptype.get_pointee()
                is_const = pointee.is_const_qualified()
                type_spelling = _resolve_type_spelling(pointee.spelling)
                if is_const:
                    type_spelling = type_spelling.removeprefix("const ")
            else:
                is_const = ptype.is_const_qualified()
                type_spelling = _resolve_type_spelling(ptype.spelling)
                if is_const:
                    type_spelling = type_spelling.removeprefix("const ")
            params.append(
                Parameter(
                    name=child.spelling,
                    type_name=type_spelling,
                    is_const=is_const,
                    is_ref=is_ref,
                )
            )
    return params


def _extract_default_value(field_cursor: Cursor) -> str | None:
    """Extract default value from a field cursor, if present.

    Checks for children that are not ANNOTATE_ATTR (which indicate an
    initializer expression).
    """
    for child in field_cursor.get_children():
        if child.kind not in (
            CursorKind.ANNOTATE_ATTR,
            CursorKind.UNEXPOSED_ATTR,
        ):
            # There is an initializer — extract from tokens
            tokens = list(child.get_tokens())
            if tokens:
                return " ".join(t.spelling for t in tokens)
    return None


def _extract_alias(cursor: Cursor, namespace: tuple[str, ...]) -> Maybe:
    """Extract an AliasType from a TYPEDEF_DECL or TYPE_ALIAS_DECL."""
    try:
        name = cursor.spelling
        qualified = _qualified_name(name, namespace)
        annotations = _collect_annotations(cursor)
        target = _resolve_type_spelling(cursor.underlying_typedef_type.spelling)
        return Just(
            AliasType(
                name=name,
                qualified_name=qualified,
                namespace=namespace,
                target_type=target,
                annotations=annotations,
            )
        )
    except Exception as e:
        return Maybe(
            value=f"Failed to extract alias {cursor.spelling}: {e}",
            monoid=False,
        )


# ---------------------------------------------------------------------------
# Main AST walk
# ---------------------------------------------------------------------------


def _is_from_main_file(cursor: Cursor, main_file: str) -> bool:
    """Check whether a cursor originates from the main input file."""
    loc = cursor.location
    if loc.file is None:
        return False
    return loc.file.name == main_file


def _walk_cursor(
    cursor: Cursor,
    namespace: tuple[str, ...],
    main_file: str,
    result: dict,
) -> None:
    """Recursively walk the AST, collecting types into result dict.

    result is mutated in place with lists: enums, structs, interfaces,
    aliases, containers, pointers, variants.
    """
    for child in cursor.get_children():
        if not _is_from_main_file(child, main_file):
            continue

        if child.kind == CursorKind.NAMESPACE:
            ns_name = child.spelling
            _walk_cursor(child, namespace + (ns_name,), main_file, result)

        elif child.kind == CursorKind.ENUM_DECL:
            r = _extract_enum(child, namespace)
            if r.is_just():
                result["enums"].append(r.value)

        elif child.kind in (CursorKind.STRUCT_DECL, CursorKind.CLASS_DECL):
            # Skip forward declarations (no definition)
            if not child.is_definition():
                continue
            r = _extract_struct_or_interface(child, namespace)
            if r.is_just():
                val = r.value
                if isinstance(val, InterfaceType):
                    result["interfaces"].append(val)
                else:
                    result["structs"].append(val)

        elif child.kind in (
            CursorKind.TYPEDEF_DECL,
            CursorKind.TYPE_ALIAS_DECL,
        ):
            r = _extract_alias(child, namespace)
            if r.is_just():
                alias = r.value
                result["aliases"].append(alias)
                # Also resolve to container/pointer/variant if applicable
                resolved = _resolve_container(
                    alias.target_type,
                    alias.name,
                    alias.qualified_name,
                    alias.namespace,
                )
                if resolved is not None:
                    if isinstance(resolved, ContainerType):
                        result["containers"].append(resolved)
                    elif isinstance(resolved, PointerType):
                        result["pointers"].append(resolved)
                    elif isinstance(resolved, VariantType):
                        # Carry annotations from alias to variant
                        resolved = VariantType(
                            name=resolved.name,
                            qualified_name=resolved.qualified_name,
                            namespace=resolved.namespace,
                            variant_kind=resolved.variant_kind,
                            alternatives=resolved.alternatives,
                            annotations=alias.annotations,
                        )
                        result["variants"].append(resolved)


def _collect_namespaces(result: dict) -> tuple[str, ...]:
    """Collect all unique namespace paths from extracted types."""
    ns_set: set[tuple[str, ...]] = set()
    for category in ("enums", "structs", "interfaces", "aliases"):
        for t in result[category]:
            if t.namespace:
                ns_set.add(t.namespace)
    return tuple("::".join(ns) for ns in sorted(ns_set))


# ---------------------------------------------------------------------------
# Dependency ordering
# ---------------------------------------------------------------------------


def _type_references(type_obj: object) -> set[str]:
    """Collect fully qualified type names referenced by a type object."""
    refs: set[str] = set()
    if isinstance(type_obj, StructType):
        for f in type_obj.fields:
            refs.add(f.type_name)
    elif isinstance(type_obj, InterfaceType):
        for m in type_obj.methods:
            refs.add(m.return_type)
            for p in m.parameters:
                refs.add(p.type_name)
    elif isinstance(type_obj, AliasType):
        refs.add(type_obj.target_type)
    elif isinstance(type_obj, ContainerType):
        refs.add(type_obj.element_type)
    elif isinstance(type_obj, PointerType):
        refs.add(type_obj.pointee_type)
    elif isinstance(type_obj, VariantType):
        for alt in type_obj.alternatives:
            refs.add(alt)
    return refs


def _toposort(types: list, name_attr: str = "qualified_name") -> list:
    """Topological sort of types by their dependency references.

    Types with no dependencies come first. Cycles are broken arbitrarily.
    """
    name_to_type = {getattr(t, name_attr): t for t in types}
    name_to_refs = {
        getattr(t, name_attr): _type_references(t) & set(name_to_type.keys())
        for t in types
    }

    sorted_names: list[str] = []
    visited: set[str] = set()
    visiting: set[str] = set()  # cycle detection

    def visit(name: str) -> None:
        if name in visited:
            return
        if name in visiting:
            # Cycle — break it by just adding
            return
        visiting.add(name)
        for dep in name_to_refs.get(name, set()):
            visit(dep)
        visiting.discard(name)
        visited.add(name)
        sorted_names.append(name)

    for name in name_to_type:
        visit(name)

    return [name_to_type[n] for n in sorted_names]


# ---------------------------------------------------------------------------
# Pipeline step 2: extract_type_model
# ---------------------------------------------------------------------------


def extract_type_model(ctx: dict) -> Maybe:
    """Walk the clang AST and build a CompilationUnit.

    Reads ctx["translation_unit"]. On success adds ctx["compilation_unit"].
    """
    try:
        tu = ctx["translation_unit"]
        main_file = tu.spelling

        result: dict[str, list] = {
            "enums": [],
            "structs": [],
            "interfaces": [],
            "aliases": [],
            "containers": [],
            "pointers": [],
            "variants": [],
        }

        _walk_cursor(tu.cursor, (), main_file, result)

        # Dependency ordering for structs, aliases, containers
        result["enums"] = _toposort(result["enums"])
        result["structs"] = _toposort(result["structs"])
        result["aliases"] = _toposort(result["aliases"])

        cu = CompilationUnit(
            header_path=ctx.get("header_path", main_file),
            namespaces=_collect_namespaces(result),
            enums=tuple(result["enums"]),
            structs=tuple(result["structs"]),
            interfaces=tuple(result["interfaces"]),
            aliases=tuple(result["aliases"]),
            containers=tuple(result["containers"]),
            pointers=tuple(result["pointers"]),
            variants=tuple(result["variants"]),
        )

        return Just({**ctx, "compilation_unit": cu})
    except Exception as e:
        return Maybe(value=f"Failed to extract type model: {e}", monoid=False)
