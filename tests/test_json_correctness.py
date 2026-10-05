"""JSON correctness: py_babelc vs original babelc reference output (block-set diff)."""

from __future__ import annotations

import os
import re
import shutil
import subprocess
from pathlib import Path

import pytest
from pymonad.maybe import Just

from babelc_py.clang_parser import (
    discover_system_cpp_includes,
    extract_type_model,
    parse_with_clang,
)
from babelc_py.json_generator import render_json_header
from babelc_py.pre_process import cleanup_temp_files, rewrite_babelc_attributes
from babelc_py.type_model import validate_type_model

TESTS_DIR = Path(__file__).parent
HEADERS_DIR = TESTS_DIR / "headers"
REFERENCE_DIR = TESTS_DIR / "reference_output"

_CPP17_RE = re.compile(r"#if __cplusplus < 201700L\n.*?\n#else\n(.*?)#endif\n", re.DOTALL)
_GUARD_RE = re.compile(r"#(ifndef|define)\s+(\w+)")
_SPLIT_RE = re.compile(r"(?=#ifndef(?:HAVE_|BABEL_HELPERS)\w+#define)")


def _guard(m: re.Match) -> str:
    name = re.sub(r"_+", "_", m.group(2)).strip("_")
    name = re.sub(r"^(HAVE_(?:BOOST|STD)_(?:OPTIONAL|VARIANT))_JSON_", r"\1_", name)
    return f"#{m.group(1)} {name}"


def blocks(text: str) -> list[str]:
    """Split output into whitespace-insensitive guarded blocks (order-insensitive)."""
    text = _CPP17_RE.sub(r"\1", text)
    text = _GUARD_RE.sub(_guard, text)
    # cosmetic: template parameter naming of std::array helpers
    text = re.sub(r"(?:std::)?size_t\s+[SN]\b", "size_t N", text)
    text = re.sub(r"<T,\s*[SN]>", "<T,N>", text)
    text = re.sub(r"\s+", "", text)
    parts = _SPLIT_RE.split(text)
    # Known deviation: the original emits invalid C++ for empty structs
    return sorted(p for p in parts[1:] if "EMPTY_IMPLEMENTATIONS" not in p[:120])


def boost_include() -> str | None:
    """Locate a Boost include dir (env BOOST_INCLUDE_DIR or a conan cache)."""
    env = os.environ.get("BOOST_INCLUDE_DIR")
    if env:
        return env
    for hit in sorted(Path.home().glob(".conan2/p/b/boost*/p/include")):
        if (hit / "boost" / "optional.hpp").exists():
            return str(hit)
    return None


def generate(header: str, cpp_std: int = 20, extra_args: tuple[str, ...] = ()) -> str:
    try:
        result = (
            Just(
                {
                    "header_path": str(HEADERS_DIR / header),
                    "clang_args": discover_system_cpp_includes() + list(extra_args),
                    "cpp_std": cpp_std,
                }
            )
            .bind(rewrite_babelc_attributes)
            .bind(parse_with_clang)
            .bind(extract_type_model)
            .bind(validate_type_model)
            .bind(render_json_header("out.json.h"))
        )
    finally:
        cleanup_temp_files()
    assert not result.is_nothing(), result.value
    return result.value["rendered_output"]


@pytest.mark.parametrize("name", ["addressbook", "json_types"])
def test_blocks_match_reference(name):
    extra: tuple[str, ...] = ()
    if name == "json_types":
        inc = boost_include()
        if inc is None:
            pytest.skip("Boost headers not found (set BOOST_INCLUDE_DIR)")
        extra = (f"-I{inc}",)
    ours = blocks(generate(f"{name}.h", extra_args=extra))
    ref = blocks((REFERENCE_DIR / f"{name}.json.h").read_text())
    missing = [b[:120] for b in ref if b not in ours]
    surplus = [b[:120] for b in ours if b not in ref]
    assert not missing and not surplus, f"missing={missing}\nextra={surplus}"


@pytest.mark.skipif(shutil.which("g++") is None, reason="g++ not available")
@pytest.mark.parametrize("cpp_std", [17, 20])
def test_generated_headers_compile(tmp_path, cpp_std):
    cases = [("addressbook.h", ()), ("json_std_types.h", ())]
    inc = boost_include()
    if inc:
        cases.append(("json_types.h", (f"-I{inc}",)))
    for header, extra in cases:
        out = tmp_path / header.replace(".h", ".json.h")
        text = generate(header, cpp_std, extra).replace(
            f'#include "{HEADERS_DIR / header}"', f'#include "{header}"'
        )
        out.write_text(text)
        src = tmp_path / "t.cpp"
        src.write_text(f'#include "{out.name}"\nint main() {{}}\n')
        cmd = ["g++", f"-std=c++{cpp_std}", "-Wall", "-Wextra", "-Werror", "-fsyntax-only",
               f"-I{HEADERS_DIR}", str(src)]
        if extra:
            cmd.insert(1, extra[0])
        r = subprocess.run(cmd, capture_output=True, text=True)
        assert r.returncode == 0, f"{header}: {r.stderr[:2000]}"


def test_bool_underlying_enum_generates(tmp_path):
    import subprocess, sys
    from pathlib import Path
    hdr = Path(__file__).parent / "headers" / "json_bool_enum.h"
    subprocess.run([sys.executable, "-m", "babelc_py.compat", "-std=gnu++20", "-babelcCompiler=g++",
                    "-babelcForce", "-babelcOutput=Json", f"-babelcDirectory={tmp_path}", str(hdr)], check=True)
    out = (tmp_path / "json_bool_enum.json.h").read_text()
    assert 'CharT,"off"' in out and "static_cast<bool>(theValue)" in out
