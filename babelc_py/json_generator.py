"""JSON generator: per-type rendering and variant sanity checks."""

from __future__ import annotations

import re
from dataclasses import dataclass

from pymonad.maybe import Just, Maybe

from babelc_py.ipc_generator import _lookup_type
from babelc_py.jinja_env import build_guard_name, create_env
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


# ---------------------------------------------------------------------------
# Header orchestration
# ---------------------------------------------------------------------------

_CONTAINER_RE = re.compile(r"\bstd::(vector|list|array|map)<")
_OPTIONAL_RE = re.compile(r"\b(std|boost)::optional<")
_VARIANT_RE = re.compile(r"\b(std|boost)::variant<")


def _referenced_strings(cu: CompilationUnit) -> list[str]:
    """Type spellings that can occur in JSON-relevant (non-interface) types."""
    out: list[str] = []
    for s in cu.structs:
        out.extend(f.type_name for f in s.fields)
    out.extend(a.target_type for a in cu.aliases)
    out.extend(c.element_type for c in cu.containers)
    out.extend(p.pointee_type for p in cu.pointers)
    for v in cu.variants:
        out.extend(v.alternatives)
    return out


def used_features(cu: CompilationUnit) -> tuple[list[str], list[str], list[str]]:
    """Return (container kinds, optional flavours, variant flavours) in use."""
    texts = _referenced_strings(cu)
    kinds = {f"std::{c.container_kind}" for c in cu.containers if c.container_kind != "optional"}
    optionals = {c.optional_kind for c in cu.containers if c.optional_kind}
    variants = {v.variant_kind for v in cu.variants}
    for t in texts:
        kinds.update(f"std::{m}" for m in _CONTAINER_RE.findall(t))
        optionals.update(_OPTIONAL_RE.findall(t))
        variants.update(_VARIANT_RE.findall(t))
    return sorted(kinds), sorted(optionals), sorted(variants)


def render_json_header(output_path: str) -> callable:
    """Curried bind step: render the .json.h header.

    Reads ctx["compilation_unit"] and ctx["cpp_std"] (default 20).
    Adds ctx["rendered_output"], ctx["output_path"], and variant warnings.
    """

    def do_render(ctx: dict) -> Maybe:
        try:
            cu: CompilationUnit = ctx["compilation_unit"]
            cpp_std = ctx.get("cpp_std", 20)
            kinds, optionals, variants = used_features(cu)

            if cpp_std < 17 and "std" in (*optionals, *variants):
                return Maybe(
                    value="std::optional/std::variant require --cpp-std 17 or later",
                    monoid=False,
                )

            warnings = list(ctx.get("validation_warnings", []))
            errors: list[str] = []
            for v in cu.variants:
                w, e = check_variant(v, cu)
                warnings.extend(w)
                errors.extend(e)
            if errors:
                return Maybe(value="\n".join(errors), monoid=False)

            types = [*cu.enums, *cu.structs]
            rendered = (
                create_env()
                .get_template("json_header.h.j2")
                .render(
                    guard_name=build_guard_name(output_path),
                    header_path=cu.header_path,
                    cpp_std=cpp_std,
                    kinds=kinds,
                    optional_adapters=optionals,
                    variant_adapters=variants,
                    type_declarations=[render_declaration(t, cpp_std) for t in types],
                    type_implementations=[render_implementation(t, cpp_std) for t in types],
                )
            )
            return Just(
                {
                    **ctx,
                    "rendered_output": rendered,
                    "output_path": output_path,
                    "validation_warnings": warnings,
                }
            )
        except Exception as e:
            return Maybe(value=f"Failed to render JSON header: {e}", monoid=False)

    return do_render
