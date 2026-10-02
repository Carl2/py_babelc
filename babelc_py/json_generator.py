"""JSON generator: per-type rendering and variant sanity checks."""

from __future__ import annotations

from dataclasses import dataclass

from babelc_py.ipc_generator import _lookup_type
from babelc_py.jinja_env import create_env
from babelc_py.type_model import (
    CompilationUnit,
    ContainerType,
    EnumType,
    PointerType,
    StructType,
    VariantType,
)

JSON_CATEGORIES: tuple[str, ...] = ("null", "boolean", "number", "string", "array", "object")
_NUMBER_BUILTINS = frozenset({"float", "double", "long double"})
_STRING_NAMES = frozenset({"std::string", "string", "std::wstring", "wstring"})


@dataclass(frozen=True)
class JsonField:
    """A struct field prepared for the JSON struct template."""

    name: str
    required: bool
    req_index: int
    pad: str


@dataclass(frozen=True)
class JsonStruct:
    """A struct prepared for the JSON struct template."""

    name: str
    qualified_name: str
    namespace: tuple[str, ...]
    fields: tuple[JsonField, ...]


def prepare_struct(struct: StructType) -> JsonStruct:
    """Compute required/optional flags, required indices and label padding."""
    width = max((len(f.name) for f in struct.fields), default=0)
    fields: list[JsonField] = []
    index = 0
    for f in struct.fields:
        required = f.default_value is None
        fields.append(
            JsonField(
                name=f.name,
                required=required,
                req_index=index if required else -1,
                pad=" " * (width - len(f.name)),
            )
        )
        index += 1 if required else 0
    return JsonStruct(struct.name, struct.qualified_name, struct.namespace, tuple(fields))


def _render(template: str, macro: str, obj: object, cpp_std: int) -> str:
    module = create_env().get_template(template).make_module()
    return getattr(module, macro)(obj, cpp_std)


def render_declaration(type_obj: EnumType | StructType, cpp_std: int = 20) -> str:
    """Render the JSON declaration block of an enum or struct."""
    if isinstance(type_obj, EnumType):
        return _render("json_enum.j2", "declaration", type_obj, cpp_std)
    return _render("json_struct.j2", "declaration", prepare_struct(type_obj), cpp_std)


def render_implementation(type_obj: EnumType | StructType, cpp_std: int = 20) -> str:
    """Render the JSON implementation block of an enum or struct."""
    if isinstance(type_obj, EnumType):
        return _render("json_enum.j2", "implementation", type_obj, cpp_std)
    return _render("json_struct.j2", "implementation", prepare_struct(type_obj), cpp_std)


# ---------------------------------------------------------------------------
# Variant sanity check (the original JSON generator emits no variant code)
# ---------------------------------------------------------------------------


def json_categories(type_name: str, cu: CompilationUnit, _seen: frozenset[str] = frozenset()) -> frozenset[str]:
    """Return the JSON value categories a C++ type can be serialised as."""
    if type_name in _seen:
        return frozenset()
    seen = _seen | {type_name}
    if type_name == "bool":
        return frozenset({"boolean"})
    if type_name in _STRING_NAMES:
        return frozenset({"string"})
    resolved = _lookup_type(type_name, cu)
    if resolved is None:
        return frozenset({"number"})
    if hasattr(resolved, "target_type"):
        return json_categories(resolved.target_type, cu, seen)
    if isinstance(resolved, EnumType):
        return frozenset({"string" if resolved.enumerators else "number"})
    if isinstance(resolved, StructType):
        return frozenset({"object" if resolved.fields else "null"})
    if isinstance(resolved, ContainerType):
        if resolved.container_kind == "map":
            return frozenset({"object"})
        if resolved.container_kind == "optional":
            return json_categories(resolved.element_type, cu, seen) | {"null"}
        return frozenset({"array"})
    if isinstance(resolved, PointerType):
        return json_categories(resolved.pointee_type, cu, seen) | {"null"}
    return frozenset()


def check_variant(variant: VariantType, cu: CompilationUnit) -> tuple[list[str], list[str]]:
    """Return (warnings, errors) for a variant, mirroring the original generator."""
    warnings: list[str] = []
    errors: list[str] = []
    by_category: dict[str, list[str]] = {}
    for alt in variant.alternatives:
        for cat in json_categories(alt, cu):
            by_category.setdefault(cat, []).append(alt)
    collided = False
    for cat, alts in sorted(by_category.items()):
        if len(alts) > 1:
            collided = True
            for alt in alts:
                warnings.append(
                    f"{variant.qualified_name}: alternative {alt} collides with other"
                    f" alternatives in JSON category '{cat}'"
                )
    if collided:
        errors.append(f"{variant.qualified_name}: variant is ambiguous in JSON")
    intentional = any(a.name == "intentionally_incomplete_variant" for a in variant.annotations)
    complete = all(c in by_category for c in JSON_CATEGORIES)
    if not complete and not intentional:
        missing = [c for c in JSON_CATEGORIES if c not in by_category]
        warnings.append(
            f"{variant.qualified_name}: variant cannot hold JSON {', '.join(missing)};"
            " mark with intentionally_incomplete_variant to silence"
        )
    if complete and intentional:
        warnings.append(
            f"{variant.qualified_name}: redundant intentionally_incomplete_variant attribute"
        )
    return warnings, errors
