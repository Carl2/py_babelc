"""Tests for pre_process.py — babelc attribute rewriter."""

import os
import tempfile
from pathlib import Path

import pytest
from pymonad.maybe import Just

from babelc_py.pre_process import (
    BABELC_ATTR_RE,
    _replace_attr,
    rewrite_babelc_attributes,
)

from conftest import HEADERS_DIR


# ---------------------------------------------------------------------------
# Regex unit tests
# ---------------------------------------------------------------------------


class TestRegex:
    """Test BABELC_ATTR_RE matching and _replace_attr substitution."""

    def test_attr_with_string_arg(self):
        text = '[[babelc::ipc_type("FileDescriptor")]]'
        assert (
            BABELC_ATTR_RE.sub(_replace_attr, text)
            == '[[clang::annotate("babelc::ipc_type=FileDescriptor")]]'
        )

    def test_attr_without_arg(self):
        text = "[[babelc::use_discriminated_variant]]"
        assert (
            BABELC_ATTR_RE.sub(_replace_attr, text)
            == '[[clang::annotate("babelc::use_discriminated_variant")]]'
        )

    def test_attr_without_arg_incomplete_variant(self):
        text = "[[babelc::intentionally_incomplete_variant]]"
        assert (
            BABELC_ATTR_RE.sub(_replace_attr, text)
            == '[[clang::annotate("babelc::intentionally_incomplete_variant")]]'
        )

    def test_no_match(self):
        text = "struct Foo { int x; };"
        assert BABELC_ATTR_RE.sub(_replace_attr, text) == text

    def test_multiple_attrs_different_lines(self):
        text = (
            '[[babelc::ipc_type("FileDescriptor")]]\n'
            "[[babelc::use_discriminated_variant]]\n"
        )
        expected = (
            '[[clang::annotate("babelc::ipc_type=FileDescriptor")]]\n'
            '[[clang::annotate("babelc::use_discriminated_variant")]]\n'
        )
        assert BABELC_ATTR_RE.sub(_replace_attr, text) == expected

    def test_attr_in_enum_context(self):
        text = (
            'enum struct FD : std::int32_t [[babelc::ipc_type("FileDescriptor")]] {};'
        )
        expected = 'enum struct FD : std::int32_t [[clang::annotate("babelc::ipc_type=FileDescriptor")]] {};'
        assert BABELC_ATTR_RE.sub(_replace_attr, text) == expected

    def test_attr_in_using_context(self):
        text = (
            "using Event = boost::variant<A, B> [[babelc::use_discriminated_variant]];"
        )
        expected = 'using Event = boost::variant<A, B> [[clang::annotate("babelc::use_discriminated_variant")]];'
        assert BABELC_ATTR_RE.sub(_replace_attr, text) == expected


# ---------------------------------------------------------------------------
# Pipeline step tests
# ---------------------------------------------------------------------------


class TestRewriteBabelcAttributes:
    """Test rewrite_babelc_attributes pipeline step."""

    def _write_tmp_header(self, tmp_path: Path, content: str) -> Path:
        header = tmp_path / "test.h"
        header.write_text(content)
        return header

    def test_no_attrs_pass_through(self, tmp_path):
        header = self._write_tmp_header(tmp_path, "struct Foo { int x; };")
        ctx = {"header_path": str(header), "clang_args": []}
        result = rewrite_babelc_attributes(ctx)

        assert result.is_just()
        assert result.value["rewritten_header_path"] == str(header)

    def test_rewrite_creates_temp_file(self, tmp_path):
        content = '[[babelc::ipc_type("FileDescriptor")]]'
        header = self._write_tmp_header(tmp_path, content)
        ctx = {"header_path": str(header), "clang_args": []}
        result = rewrite_babelc_attributes(ctx)

        assert result.is_just()
        rewritten_path = result.value["rewritten_header_path"]
        assert rewritten_path != str(header)
        assert Path(rewritten_path).exists()

        rewritten_content = Path(rewritten_path).read_text()
        assert (
            '[[clang::annotate("babelc::ipc_type=FileDescriptor")]]'
            in rewritten_content
        )

        # Cleanup
        os.unlink(rewritten_path)

    def test_rewrite_adds_include_path(self, tmp_path):
        content = "[[babelc::use_discriminated_variant]]"
        header = self._write_tmp_header(tmp_path, content)
        ctx = {"header_path": str(header), "clang_args": []}
        result = rewrite_babelc_attributes(ctx)

        assert result.is_just()
        clang_args = result.value["clang_args"]
        assert "-I" in clang_args
        assert str(tmp_path.resolve()) in clang_args

        os.unlink(result.value["rewritten_header_path"])

    def test_does_not_mutate_original_ctx(self, tmp_path):
        content = "[[babelc::use_discriminated_variant]]"
        header = self._write_tmp_header(tmp_path, content)
        original_ctx = {"header_path": str(header), "clang_args": ["-std=c++20"]}
        result = rewrite_babelc_attributes(original_ctx)

        assert result.is_just()
        assert "rewritten_header_path" not in original_ctx
        assert len(original_ctx["clang_args"]) == 1

        os.unlink(result.value["rewritten_header_path"])

    def test_file_not_found(self):
        ctx = {"header_path": "/nonexistent/path.h", "clang_args": []}
        result = rewrite_babelc_attributes(ctx)

        assert result.is_nothing()
        assert "Could not read" in result.value

    def test_pipeline_integration(self, tmp_path):
        content = '[[babelc::ipc_type("Foo")]]\n[[babelc::use_discriminated_variant]]'
        header = self._write_tmp_header(tmp_path, content)
        ctx = {"header_path": str(header), "clang_args": [], "output_path": "/dev/null"}

        result = Just(ctx).bind(rewrite_babelc_attributes)

        assert result.is_just()
        assert "rewritten_header_path" in result.value
        assert result.value["output_path"] == "/dev/null"

        rewritten = Path(result.value["rewritten_header_path"]).read_text()
        assert '[[clang::annotate("babelc::ipc_type=Foo")]]' in rewritten
        assert '[[clang::annotate("babelc::use_discriminated_variant")]]' in rewritten

        os.unlink(result.value["rewritten_header_path"])

    def test_full_file_addressbook_pass_through(self):
        """addressbook.h has no babelc attrs — should pass through unchanged."""
        header = HEADERS_DIR / "addressbook.h"
        if not header.exists():
            pytest.skip("addressbook.h fixture not available")

        ctx = {"header_path": str(header), "clang_args": []}
        result = rewrite_babelc_attributes(ctx)

        assert result.is_just()
        assert result.value["rewritten_header_path"] == str(header)
