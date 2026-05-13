"""IPC correctness verification: py_babelc vs babelc reference output."""

from __future__ import annotations

import re
from pathlib import Path

import pytest
from pymonad.maybe import Just

from babelc_py.clang_parser import (
    discover_system_cpp_includes,
    extract_type_model,
    parse_with_clang,
)
from babelc_py.ipc_generator import render_ipc_header
from babelc_py.pre_process import rewrite_babelc_attributes
from babelc_py.type_model import validate_type_model

TESTS_DIR = Path(__file__).parent
HEADERS_DIR = TESTS_DIR / "headers"
REFERENCE_DIR = TESTS_DIR / "reference_output"


def normalise(text: str) -> str:
    """Normalise generated output for semantic comparison.

    Handles:
    - Include guard replacement (top-level #ifndef/#define)
    - Original header include path replacement
    - C++17 compatibility guard stripping (keep only C++20 variant)
    - Guard macro double-underscore normalisation
    - Trailing whitespace stripping
    - Blank line collapsing (max 2 consecutive)
    - Whitespace alignment collapsing (interior runs of spaces)
    - Empty parens normalisation: (  ) -> ()
    """
    lines = text.splitlines()
    result: list[str] = []
    i = 0

    while i < len(lines):
        line = lines[i]

        # Strip C++17 guard blocks: skip from #if __cplusplus < 201700L to #else,
        # keep lines after #else until #endif (which we also skip)
        if line.strip() == "#if __cplusplus < 201700L":
            # Skip lines until #else
            j = i + 1
            while j < len(lines) and lines[j].strip() != "#else":
                j += 1
            # Skip the #else line itself
            j += 1
            # Now keep lines until #endif
            while j < len(lines) and lines[j].strip() != "#endif":
                result.append(lines[j])
                j += 1
            # Skip the #endif
            i = j + 1
            continue

        result.append(line)
        i += 1

    text = "\n".join(result)

    # Normalise multi-line method signatures into single line
    # babelc splits params across lines; py_babelc keeps on one line
    # Pattern: "void name(\n  param1,\n  param2\n) override {"
    # Only match if line contains ") override {" or ") {" on closing line
    def _collapse_signatures(txt: str) -> str:
        result_lines: list[str] = []
        lines_list = txt.split("\n")
        idx = 0
        while idx < len(lines_list):
            ln = lines_list[idx]
            # Detect start of multi-line signature: line ends with "(" and no ")" on same line
            # Must look like a method declaration (has type + name before the paren)
            stripped = ln.rstrip()
            if (
                stripped.endswith("(")
                and ")" not in ln
                and ("override" not in ln)
                and (") override" not in ln)
            ):
                # Peek ahead to see if this looks like a method sig or call
                peek = idx + 1
                is_method_sig = False
                while peek < len(lines_list) and peek < idx + 10:
                    if (
                        ") override" in lines_list[peek]
                        or ") {" in lines_list[peek]
                        or lines_list[peek].strip() in (");", ");,")
                    ):
                        is_method_sig = True
                        break
                    peek_stripped = lines_list[peek].strip()
                    if peek_stripped.endswith(");"):
                        is_method_sig = True
                        break
                    if ")" in lines_list[peek] and "{" not in lines_list[peek]:
                        # standalone ) line — check next
                        pass
                    peek += 1

                if is_method_sig:
                    sig_parts = [stripped]
                    idx += 1
                    while idx < len(lines_list) and ")" not in lines_list[idx]:
                        sig_parts.append(lines_list[idx].strip())
                        idx += 1
                    if idx < len(lines_list):
                        sig_parts.append(lines_list[idx].strip())
                        idx += 1
                    combined = " ".join(sig_parts)
                    # Collapse interior spaces but preserve leading indent
                    leading = combined[: len(combined) - len(combined.lstrip())]
                    collapsed_inner = re.sub(r"  +", " ", combined.lstrip())
                    result_lines.append(leading + collapsed_inner)
                else:
                    result_lines.append(ln)
                    idx += 1
            else:
                result_lines.append(ln)
                idx += 1
        return "\n".join(result_lines)

    text = _collapse_signatures(text)

    # Normalise top-level include guard
    text = re.sub(
        r"#ifndef\s+__[A-Za-z0-9_]+__\s*\n#define\s+__[A-Za-z0-9_]+__",
        "#ifndef __GUARD__\n#define __GUARD__",
        text,
        count=1,
    )

    # Normalise header include path
    text = re.sub(r'#include ".*\.h"', '#include "HEADER"', text, count=1)

    # Normalise guard macro double-underscore: collapse runs of 3+ underscores to 2
    text = re.sub(r"_{3,}", "__", text)

    # Normalise empty parens: (  ) -> () and ( ) -> ()
    text = re.sub(r"\(\s+\)", "()", text)

    # Normalise interior whitespace alignment (collapse multiple spaces to one,
    # but preserve leading indentation)
    def _collapse_interior_spaces(line: str) -> str:
        stripped = line.lstrip()
        indent = line[: len(line) - len(stripped)]
        # Collapse runs of 2+ spaces to single space in the non-indent part
        collapsed = re.sub(r"  +", " ", stripped)
        return indent + collapsed

    lines = text.splitlines()
    lines = [_collapse_interior_spaces(ln).rstrip() for ln in lines]
    text = "\n".join(lines)

    # Collapse multiple consecutive blank lines to exactly one
    text = re.sub(r"\n{2,}", "\n", text)

    return text


# ---------------------------------------------------------------------------
# Test corpus
# ---------------------------------------------------------------------------

CORPUS = [
    ("addressbook.h", "addressbook.ipc.h", []),
    ("device_status.h", "device_status.ipc.h", []),
    ("counter.h", "counter.ipc.h", []),
    ("echo_service.h", "echo_service.ipc.h", []),
    ("diagnostics.h", "diagnostics.ipc.h", []),
]


@pytest.fixture(scope="session")
def system_includes():
    return discover_system_cpp_includes()


@pytest.mark.parametrize("header,reference,extra_args", CORPUS)
def test_ipc_matches_babelc(header, reference, extra_args, tmp_path, system_includes):
    """py_babelc output must match babelc reference after normalisation."""
    header_path = str(HEADERS_DIR / header)
    output_path = str(tmp_path / reference)
    ref_path = REFERENCE_DIR / reference

    result = (
        Just({"header_path": header_path, "clang_args": system_includes + extra_args})
        .bind(rewrite_babelc_attributes)
        .bind(parse_with_clang)
        .bind(extract_type_model)
        .bind(validate_type_model)
        .bind(render_ipc_header(output_path))
    )

    assert result.is_just(), f"Pipeline failed for {header}: {result}"

    actual = normalise(result.value["rendered_output"])
    expected = normalise(ref_path.read_text())

    if actual != expected:
        # Write both to tmp for manual inspection
        (tmp_path / "actual_normalised.txt").write_text(actual)
        (tmp_path / "expected_normalised.txt").write_text(expected)
        # Show first difference
        actual_lines = actual.splitlines()
        expected_lines = expected.splitlines()
        for i, (a, e) in enumerate(zip(actual_lines, expected_lines)):
            if a != e:
                pytest.fail(
                    f"{header}: First diff at line {i + 1}:\n"
                    f"  actual:   {a!r}\n"
                    f"  expected: {e!r}"
                )
        if len(actual_lines) != len(expected_lines):
            pytest.fail(
                f"{header}: Length differs: {len(actual_lines)} vs {len(expected_lines)}"
            )
