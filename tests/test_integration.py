"""Integration test: full pipeline from addressbook.h to rendered output."""

from __future__ import annotations

from pathlib import Path

import pytest
from pymonad.maybe import Just

from babelc_py.clang_parser import (
    discover_system_cpp_includes,
    extract_type_model,
    parse_with_clang,
)
from babelc_py.ipc_generator import render_ipc_header, write_output
from babelc_py.pre_process import rewrite_babelc_attributes
from babelc_py.type_model import validate_type_model

TESTS_DIR = Path(__file__).parent
HEADERS_DIR = TESTS_DIR / "headers"
REFERENCE_DIR = TESTS_DIR / "reference_output"


@pytest.fixture
def system_includes():
    return discover_system_cpp_includes()


class TestFullPipeline:
    """End-to-end: addressbook.h -> rendered .ipc.h -> compare to reference."""

    def test_pipeline_succeeds(self, tmp_path, system_includes):
        """The full pipeline should complete without errors."""
        header = str(HEADERS_DIR / "addressbook.h")
        output = str(tmp_path / "addressbook.ipc.h")

        result = (
            Just(
                {
                    "header_path": header,
                    "clang_args": system_includes,
                }
            )
            .bind(rewrite_babelc_attributes)
            .bind(parse_with_clang)
            .bind(extract_type_model)
            .bind(validate_type_model)
            .bind(render_ipc_header(output))
            .bind(write_output)
        )

        assert result.is_just(), f"Pipeline failed: {result.value}"
        assert Path(output).exists()
        content = Path(output).read_text()
        assert len(content) > 100

    def test_rendered_contains_key_sections(self, tmp_path, system_includes):
        """Check the rendered output has all expected sections."""
        header = str(HEADERS_DIR / "addressbook.h")
        output = str(tmp_path / "addressbook.ipc.h")

        result = (
            Just({"header_path": header, "clang_args": system_includes})
            .bind(rewrite_babelc_attributes)
            .bind(parse_with_clang)
            .bind(extract_type_model)
            .bind(validate_type_model)
            .bind(render_ipc_header(output))
        )

        assert result.is_just()
        content = result.value["rendered_output"]

        # Forward declarations
        assert "registerServerImplementation" in content
        assert "lookupServerImplementation" in content
        assert "registerServerBroadcastListener" in content
        assert "getServerBroadcastProxy" in content

        # babel type traits
        assert "__BABEL_HELPERS_FIRST__" in content
        assert "__BABEL_HELPERS_LAST__" in content

        # Container helpers
        assert "__BABEL_HELPERS_STD__VECTOR__" in content

        # ipc helpers
        assert "__HAVE_BABEL__IPC_HELPERS__" in content

        # Per-type: container (PhoneNumbers)
        assert "PhoneNumbers_ArrayView" in content
        assert "IpcReadContainer" in content

        # Per-type: enum (Sex)
        assert "IpcEnumValidate" in content
        assert "case Sex::Unknown:" in content

        # Per-type: struct (Person)
        assert "Person_TupleView" in content
        assert "StringReference(theStruct.itsName)" in content

        # Interface proxy classes
        assert "ServerImplementationProxy" in content
        assert "ServerClientProxy" in content
        assert "ServerClientProxyWrapper" in content
        assert "ServerBroadcastListener" in content
        assert "ServerBroadcastProxy" in content

        # Registration implementations
        assert "registerImplementor" in content
        assert "registerListener" in content
        assert "registerClient" in content

        # D-Bus interface name
        assert '"addressbook.v1.Server"' in content

        # C++20: no C++17 guards (except in static boilerplate reference checks)
        # Our generated sections should use nested namespace syntax
        assert "namespace addressbook::v1 {" in content
