"""Frozen dataclasses representing the C++ type model, plus validation."""

from __future__ import annotations

from dataclasses import dataclass

from pymonad.maybe import Just, Maybe


@dataclass(frozen=True)
class Annotation:
    """A [[babelc::*]] attribute attached to a type."""

    name: str
    value: str | None = None


@dataclass(frozen=True)
class Enumerator:
    """A single enumerator within an enum."""

    name: str
    value: int | None = None


@dataclass(frozen=True)
class BuiltinType:
    """A recognized built-in or standard library primitive."""

    name: str


@dataclass(frozen=True)
class Field:
    """A field within a struct."""

    name: str
    type_name: str
    default_value: str | None = None


@dataclass(frozen=True)
class Parameter:
    """A method parameter."""

    name: str
    type_name: str
    is_const: bool
    is_ref: bool


@dataclass(frozen=True)
class Method:
    """A method on an interface."""

    name: str
    return_type: str
    parameters: tuple[Parameter, ...]
    is_pure_virtual: bool
    is_const: bool = False


@dataclass(frozen=True)
class EnumType:
    """An enum type extracted from a C++ header."""

    name: str
    qualified_name: str
    namespace: tuple[str, ...]
    underlying_type: str
    enumerators: tuple[Enumerator, ...]
    annotations: tuple[Annotation, ...]


@dataclass(frozen=True)
class StructType:
    """A plain aggregate struct (non-interface)."""

    name: str
    qualified_name: str
    namespace: tuple[str, ...]
    fields: tuple[Field, ...]
    annotations: tuple[Annotation, ...]


@dataclass(frozen=True)
class InterfaceType:
    """An abstract class with pure virtual methods."""

    name: str
    qualified_name: str
    namespace: tuple[str, ...]
    methods: tuple[Method, ...]
    annotations: tuple[Annotation, ...]


@dataclass(frozen=True)
class AliasType:
    """A using or typedef declaration."""

    name: str
    qualified_name: str
    namespace: tuple[str, ...]
    target_type: str
    annotations: tuple[Annotation, ...]


@dataclass(frozen=True)
class ContainerType:
    """A recognized container type (vector, array, list, map, optional)."""

    name: str
    qualified_name: str
    namespace: tuple[str, ...]
    container_kind: str
    element_type: str
    size: int | None = None


@dataclass(frozen=True)
class PointerType:
    """A smart pointer wrapper."""

    name: str
    qualified_name: str
    namespace: tuple[str, ...]
    pointer_kind: str
    pointee_type: str


@dataclass(frozen=True)
class VariantType:
    """A std::variant or boost::variant type."""

    name: str
    qualified_name: str
    namespace: tuple[str, ...]
    variant_kind: str
    alternatives: tuple[str, ...]
    annotations: tuple[Annotation, ...]


@dataclass(frozen=True)
class CompilationUnit:
    """Top-level container for everything extracted from one header file."""

    header_path: str
    namespaces: tuple[str, ...]
    enums: tuple[EnumType, ...]
    structs: tuple[StructType, ...]
    interfaces: tuple[InterfaceType, ...]
    aliases: tuple[AliasType, ...]
    containers: tuple[ContainerType, ...]
    pointers: tuple[PointerType, ...]
    variants: tuple[VariantType, ...]


# ---------------------------------------------------------------------------
# Validation constants
# ---------------------------------------------------------------------------

FIXED_WIDTH_INTEGER_TYPES: frozenset[str] = frozenset(
    {
        "std::uint8_t",
        "std::uint16_t",
        "std::uint32_t",
        "std::uint64_t",
        "std::int8_t",
        "std::int16_t",
        "std::int32_t",
        "std::int64_t",
        "uint8_t",
        "uint16_t",
        "uint32_t",
        "uint64_t",
        "int8_t",
        "int16_t",
        "int32_t",
        "int64_t",
    }
)

DISALLOWED_BARE_TYPES: frozenset[str] = frozenset(
    {
        "char",
        "signed char",
        "unsigned char",
        "wchar_t",
        "signed wchar_t",
        "unsigned wchar_t",
        "short",
        "signed short",
        "unsigned short",
        "int",
        "signed int",
        "unsigned int",
        "long",
        "signed long",
        "unsigned long",
        "long int",
        "signed long int",
        "unsigned long int",
        "long long",
        "signed long long",
        "unsigned long long",
        "long long int",
        "signed long long int",
        "unsigned long long int",
        "size_t",
        "std::size_t",
        "ssize_t",
        "std::ssize_t",
        "ptrdiff_t",
        "std::ptrdiff_t",
        "nullptr_t",
        "std::nullptr_t",
    }
)


@dataclass(frozen=True)
class ValidationResult:
    """A single validation finding."""

    rule_id: str
    severity: str  # "error" or "warning"
    type_name: str  # fully qualified name of the offending type
    message: str


# ---------------------------------------------------------------------------
# Individual validators
# ---------------------------------------------------------------------------


def validate_enums(cu: CompilationUnit) -> list[ValidationResult]:
    """V001, V002: enum underlying type checks."""
    results: list[ValidationResult] = []
    for enum in cu.enums:
        if not enum.underlying_type:
            results.append(
                ValidationResult(
                    rule_id="V001",
                    severity="error",
                    type_name=enum.qualified_name,
                    message="Enum must have an explicit underlying type",
                )
            )
        elif enum.underlying_type not in FIXED_WIDTH_INTEGER_TYPES:
            results.append(
                ValidationResult(
                    rule_id="V002",
                    severity="error",
                    type_name=enum.qualified_name,
                    message=f"Enum underlying type '{enum.underlying_type}' "
                    f"is not a fixed-width integer",
                )
            )
    return results


def validate_interfaces(cu: CompilationUnit) -> list[ValidationResult]:
    """V003, V004, V005, V006, V014: interface method checks."""
    results: list[ValidationResult] = []
    for iface in cu.interfaces:
        fqn = iface.qualified_name
        if not iface.methods:
            results.append(
                ValidationResult(
                    rule_id="V014",
                    severity="error",
                    type_name=fqn,
                    message="Interface must have at least one method",
                )
            )
        for method in iface.methods:
            method_fqn = f"{fqn}::{method.name}"
            if not method.is_pure_virtual:
                results.append(
                    ValidationResult(
                        rule_id="V003",
                        severity="error",
                        type_name=method_fqn,
                        message="Interface method must be pure virtual",
                    )
                )
            if method.is_const:
                results.append(
                    ValidationResult(
                        rule_id="V004",
                        severity="error",
                        type_name=method_fqn,
                        message="Interface method must be non-const",
                    )
                )
            if method.return_type.endswith("*") or method.return_type.endswith("&"):
                results.append(
                    ValidationResult(
                        rule_id="V005",
                        severity="error",
                        type_name=method_fqn,
                        message=f"Interface method must return by value, "
                        f"not '{method.return_type}'",
                    )
                )
            for param in method.parameters:
                if param.is_ref and not param.is_const:
                    results.append(
                        ValidationResult(
                            rule_id="V006",
                            severity="error",
                            type_name=method_fqn,
                            message=f"Parameter '{param.name}' must be by value "
                            f"or const reference, not non-const reference",
                        )
                    )
    return results


def validate_structs(cu: CompilationUnit) -> list[ValidationResult]:
    """V008, V009: struct field type checks."""
    known_types = _collect_known_type_names(cu)
    results: list[ValidationResult] = []
    for struct in cu.structs:
        for field in struct.fields:
            if field.type_name.endswith("*"):
                results.append(
                    ValidationResult(
                        rule_id="V009",
                        severity="error",
                        type_name=struct.qualified_name,
                        message=f"Field '{field.name}' is a raw pointer "
                        f"(type '{field.type_name}')",
                    )
                )
            elif not _type_is_known(field.type_name, known_types):
                results.append(
                    ValidationResult(
                        rule_id="V008",
                        severity="error",
                        type_name=struct.qualified_name,
                        message=f"Field '{field.name}' has unresolvable type "
                        f"'{field.type_name}'",
                    )
                )
    return results


def validate_attributes(cu: CompilationUnit) -> list[ValidationResult]:
    """V011, V012, V013: babelc attribute target checks."""
    results: list[ValidationResult] = []

    # V011: ipc_type only on enums
    enum_names = frozenset(e.qualified_name for e in cu.enums)
    for struct in cu.structs:
        for ann in struct.annotations:
            if ann.name == "ipc_type":
                results.append(
                    ValidationResult(
                        rule_id="V011",
                        severity="error",
                        type_name=struct.qualified_name,
                        message="ipc_type attribute can only be applied to enum types",
                    )
                )
    for iface in cu.interfaces:
        for ann in iface.annotations:
            if ann.name == "ipc_type":
                results.append(
                    ValidationResult(
                        rule_id="V011",
                        severity="error",
                        type_name=iface.qualified_name,
                        message="ipc_type attribute can only be applied to enum types",
                    )
                )
    for alias in cu.aliases:
        for ann in alias.annotations:
            if ann.name == "ipc_type":
                # Check if the alias resolves to an enum
                if alias.qualified_name not in enum_names:
                    results.append(
                        ValidationResult(
                            rule_id="V011",
                            severity="error",
                            type_name=alias.qualified_name,
                            message="ipc_type attribute can only be applied to enum types",
                        )
                    )

    # V012, V013: use_discriminated_variant only on variants
    variant_names = frozenset(v.qualified_name for v in cu.variants)
    for variant in cu.variants:
        for ann in variant.annotations:
            if ann.name == "use_discriminated_variant":
                # V013: warn if no alternatives share types (unnecessary)
                if len(variant.alternatives) == len(set(variant.alternatives)):
                    results.append(
                        ValidationResult(
                            rule_id="V013",
                            severity="warning",
                            type_name=variant.qualified_name,
                            message="use_discriminated_variant is unnecessary — "
                            "no alternative types are ambiguous",
                        )
                    )

    for struct in cu.structs:
        for ann in struct.annotations:
            if ann.name == "use_discriminated_variant":
                results.append(
                    ValidationResult(
                        rule_id="V012",
                        severity="error",
                        type_name=struct.qualified_name,
                        message="use_discriminated_variant can only be applied "
                        "to variant types",
                    )
                )
    for iface in cu.interfaces:
        for ann in iface.annotations:
            if ann.name == "use_discriminated_variant":
                results.append(
                    ValidationResult(
                        rule_id="V012",
                        severity="error",
                        type_name=iface.qualified_name,
                        message="use_discriminated_variant can only be applied "
                        "to variant types",
                    )
                )
    for enum in cu.enums:
        for ann in enum.annotations:
            if ann.name == "use_discriminated_variant":
                results.append(
                    ValidationResult(
                        rule_id="V012",
                        severity="error",
                        type_name=enum.qualified_name,
                        message="use_discriminated_variant can only be applied "
                        "to variant types",
                    )
                )

    return results


def validate_no_bare_types(cu: CompilationUnit) -> list[ValidationResult]:
    """V010: reject bare C types in struct fields and interface methods."""
    results: list[ValidationResult] = []

    for struct in cu.structs:
        for field in struct.fields:
            if field.type_name in DISALLOWED_BARE_TYPES:
                results.append(
                    ValidationResult(
                        rule_id="V010",
                        severity="error",
                        type_name=struct.qualified_name,
                        message=f"Field '{field.name}' uses disallowed bare type "
                        f"'{field.type_name}'",
                    )
                )

    for iface in cu.interfaces:
        for method in iface.methods:
            method_fqn = f"{iface.qualified_name}::{method.name}"
            if method.return_type in DISALLOWED_BARE_TYPES:
                results.append(
                    ValidationResult(
                        rule_id="V010",
                        severity="error",
                        type_name=method_fqn,
                        message=f"Return type '{method.return_type}' is a "
                        f"disallowed bare type",
                    )
                )
            for param in method.parameters:
                if param.type_name in DISALLOWED_BARE_TYPES:
                    results.append(
                        ValidationResult(
                            rule_id="V010",
                            severity="error",
                            type_name=method_fqn,
                            message=f"Parameter '{param.name}' uses disallowed "
                            f"bare type '{param.type_name}'",
                        )
                    )

    return results


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------


def _collect_known_type_names(cu: CompilationUnit) -> frozenset[str]:
    """Collect all type names known within the compilation unit."""
    names: set[str] = set()
    # Builtins
    names.update(
        {
            "std::uint8_t",
            "std::uint16_t",
            "std::uint32_t",
            "std::uint64_t",
            "std::int8_t",
            "std::int16_t",
            "std::int32_t",
            "std::int64_t",
            "bool",
            "float",
            "double",
            "std::string",
            "void",
        }
    )
    for enum in cu.enums:
        names.add(enum.qualified_name)
        names.add(enum.name)
    for struct in cu.structs:
        names.add(struct.qualified_name)
        names.add(struct.name)
    for iface in cu.interfaces:
        names.add(iface.qualified_name)
        names.add(iface.name)
    for alias in cu.aliases:
        names.add(alias.qualified_name)
        names.add(alias.name)
    for container in cu.containers:
        names.add(container.qualified_name)
        names.add(container.name)
    for pointer in cu.pointers:
        names.add(pointer.qualified_name)
        names.add(pointer.name)
    for variant in cu.variants:
        names.add(variant.qualified_name)
        names.add(variant.name)
    return frozenset(names)


def _type_is_known(type_name: str, known: frozenset[str]) -> bool:
    """Check if a type name resolves to a known type."""
    return type_name in known


# ---------------------------------------------------------------------------
# Pipeline step: validate_type_model
# ---------------------------------------------------------------------------


def validate_type_model(ctx: dict) -> Maybe:
    """Validate the extracted CompilationUnit.

    Reads ctx["compilation_unit"].
    Returns Just(ctx) if valid.
    Returns Maybe(value="error description", monoid=False) on first fatal error.

    Warnings are collected in ctx["validation_warnings"] (list of strings).
    """
    cu = ctx["compilation_unit"]
    results = (
        validate_enums(cu)
        + validate_interfaces(cu)
        + validate_structs(cu)
        + validate_attributes(cu)
        + validate_no_bare_types(cu)
    )
    errors = [r for r in results if r.severity == "error"]
    warnings = [r for r in results if r.severity == "warning"]

    if errors:
        msg = "\n".join(f"[{e.rule_id}] {e.type_name}: {e.message}" for e in errors)
        return Maybe(value=f"Validation failed:\n{msg}", monoid=False)

    return Just(
        {
            **ctx,
            "validation_warnings": [
                f"[{w.rule_id}] {w.type_name}: {w.message}" for w in warnings
            ],
        }
    )
