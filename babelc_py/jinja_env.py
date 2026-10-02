"""Jinja2 environment and filters shared by the IPC and JSON generators."""

from __future__ import annotations

import re

from typing import Any

import jinja2


def guard_macro(name: str) -> str:
    """Qualified name to a guard fragment: '::a::b::C' -> 'A_B_C'.

    Never contains '__' or a leading underscore (both reserved in C++).
    """
    return re.sub(r"_+", "_", name.replace("::", "_")).strip("_").upper()


def qualified(obj: Any) -> str:
    """Jinja2 filter: return '::ns1::ns2::Name'."""
    qn = obj.qualified_name if hasattr(obj, "qualified_name") else str(obj)
    return qn if qn.startswith("::") else "::" + qn


def ns_open(obj: Any) -> str:
    """Jinja2 filter: emit 'namespace a::b {' (C++20)."""
    ns = obj.namespace if hasattr(obj, "namespace") else ()
    if ns:
        return f"namespace {'::'.join(ns)} {{"
    return "namespace {"


def ns_close(obj: Any) -> str:
    """Jinja2 filter: emit closing brace (C++20 = single brace)."""
    return "}"


def build_guard_name(output_path: str) -> str:
    """Build an include guard macro name from the output path."""
    name = re.sub(r"[^A-Za-z0-9]+", "_", output_path).strip("_").upper()
    return name if not name[:1].isdigit() else f"G_{name}"


def create_env(**extra_filters: Any) -> jinja2.Environment:
    """Create the shared Jinja2 environment; extra_filters are generator-specific."""
    env = jinja2.Environment(
        loader=jinja2.PackageLoader("babelc_py", "templates"),
        keep_trailing_newline=True,
        trim_blocks=True,
        lstrip_blocks=True,
    )
    env.filters.update(
        guard_macro=guard_macro,
        qualified=qualified,
        ns_open=ns_open,
        ns_close=ns_close,
        **extra_filters,
    )
    return env
