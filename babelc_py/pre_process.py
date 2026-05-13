"""Attribute syntax rewriter: [[babelc::X]] -> [[clang::annotate(...)]]."""

import re
import tempfile
from pathlib import Path
from typing import Callable

from pymonad.maybe import Just, Maybe, Nothing


BABELC_ATTR_RE = re.compile(
    r"\[\[babelc::"  # opening [[ and namespace
    r"(\w+)"  # capture group 1: attribute name
    r'(?:\("([^"]*)"\))?'  # optional: capture group 2: string argument (without quotes)
    r"\]\]"  # closing ]]
)

# Match interface_name annotation on struct closing: } [[babelc::interface_name("X")]];
# Captures: the struct name is not available here, but the dbus name is.
INTERFACE_NAME_RE = re.compile(
    r"\}\s*\[\[babelc::interface_name\(\"([^\"]*)\"\)\]\]\s*;"
)


def _replace_attr(match: re.Match) -> str:
    """Replace a single babelc attribute match with clang::annotate form."""
    name = match.group(1)
    value = match.group(2)
    if value is not None:
        return f'[[clang::annotate("babelc::{name}={value}")]]'
    else:
        return f'[[clang::annotate("babelc::{name}")]]'


def _extract_interface_names(content: str) -> dict[str, str]:
    """Extract interface_name annotations and the preceding struct name.

    Returns a dict mapping struct_name -> dbus_interface_name.
    Searches for patterns like:
        struct Foo { ... } [[babelc::interface_name("x.y.z")]];
    """
    # Find all } [[babelc::interface_name("X")]]; and work backwards to find struct name
    result = {}
    for m in INTERFACE_NAME_RE.finditer(content):
        dbus_name = m.group(1)
        # Search backwards from the match to find the struct name
        preceding = content[: m.start()]
        # Find the last 'struct NAME' before this closing brace
        struct_match = re.search(r"struct\s+(\w+)\s*\{", preceding[::-1])
        # Actually search forward through all struct defs and take the last one
        struct_matches = list(re.finditer(r"struct\s+(\w+)", preceding))
        if struct_matches:
            result[struct_matches[-1].group(1)] = dbus_name
    return result


def rewrite_babelc_attributes(ctx: dict) -> Maybe:
    """Rewrite [[babelc::X]] attributes to [[clang::annotate(...)]].

    Reads ctx["header_path"], writes a temp file with rewritten content.
    Adds ctx["rewritten_header_path"] pointing to the temp file.
    Adds ctx["interface_names"] mapping struct names to custom dbus names.
    Returns Just(ctx) on success, Maybe(value=error, monoid=False) on failure.
    """
    header_path = Path(ctx["header_path"])

    try:
        content = header_path.read_text()
    except Exception as e:
        return Maybe(value=f"Could not read {header_path}: {e}", monoid=False)

    # Extract interface_name annotations before rewriting
    interface_names = _extract_interface_names(content)

    # Remove interface_name annotations (they can't be applied as clang::annotate on types)
    rewritten = INTERFACE_NAME_RE.sub("};", content)

    # Rewrite remaining babelc attributes to clang::annotate
    rewritten, count = BABELC_ATTR_RE.subn(_replace_attr, rewritten)

    ctx = dict(ctx)
    ctx["interface_names"] = interface_names

    if count == 0 and not interface_names:
        ctx["rewritten_header_path"] = str(header_path)
        return Just(ctx)

    try:
        tmp = tempfile.NamedTemporaryFile(mode="w", suffix=".h", delete=False)
        tmp.write(rewritten)
        tmp.close()
    except Exception as e:
        return Maybe(value=f"Could not write temp file: {e}", monoid=False)

    ctx["rewritten_header_path"] = tmp.name

    # Add original header's directory as -I so includes still resolve
    original_dir = str(header_path.parent.resolve())
    clang_args = list(ctx.get("clang_args", []))
    if f"-I{original_dir}" not in clang_args and original_dir not in clang_args:
        clang_args.extend(["-I", original_dir])
    ctx["clang_args"] = clang_args

    return Just(ctx)
