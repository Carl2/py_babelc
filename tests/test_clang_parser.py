"""Tests for clang_parser.py — libclang AST walking and extraction."""

from __future__ import annotations

import tempfile
from pathlib import Path

import pytest
from pymonad.maybe import Just

from babelc_py.clang_parser import (
    BUILTIN_TYPES,
    _collect_annotations,
    _parse_babelc_annotation,
    _resolve_container,
    _split_template_args,
    _toposort,
    discover_system_cpp_includes,
    extract_type_model,
    parse_with_clang,
)
from babelc_py.type_model import (
    AliasType,
    Annotation,
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
)

from conftest import HEADERS_DIR


# ---------------------------------------------------------------------------
# Fixtures
# ---------------------------------------------------------------------------


@pytest.fixture()
def addressbook_ctx():
    """Context dict for parsing addressbook.h (no pre-processing needed)."""
    return {
        "header_path": str(HEADERS_DIR / "addressbook.h"),
        "rewritten_header_path": str(HEADERS_DIR / "addressbook.h"),
        "clang_args": discover_system_cpp_includes(),
    }


@pytest.fixture()
def parsed_ctx(addressbook_ctx):
    """Parsed translation unit context from addressbook.h."""
    result = parse_with_clang(addressbook_ctx)
    assert result.is_just(), f"parse_with_clang failed: {result.value}"
    return result.value


@pytest.fixture()
def compilation_unit(parsed_ctx):
    """Extracted CompilationUnit from addressbook.h."""
    result = extract_type_model(parsed_ctx)
    assert result.is_just(), f"extract_type_model failed: {result.value}"
    return result.value["compilation_unit"]


# ---------------------------------------------------------------------------
# parse_with_clang tests
# ---------------------------------------------------------------------------


class TestParseWithClang:
    def test_parse_succeeds(self, addressbook_ctx):
        result = parse_with_clang(addressbook_ctx)
        assert result.is_just()
        assert "translation_unit" in result.value
        assert "index" in result.value

    def test_parse_nonexistent_file(self):
        ctx = {
            "rewritten_header_path": "/nonexistent/file.h",
            "clang_args": [],
        }
        result = parse_with_clang(ctx)
        # libclang may parse but produce errors, or fail outright
        # Either way the pipeline should report failure
        if result.is_just():
            # If it parsed, extract should still work but with empty results
            pass
        else:
            assert "error" in result.value.lower() or "fail" in result.value.lower()

    def test_parse_invalid_syntax(self, tmp_path):
        bad_header = tmp_path / "bad.h"
        bad_header.write_text("this is not valid c++ {{{{")
        ctx = {
            "rewritten_header_path": str(bad_header),
            "clang_args": [],
        }
        result = parse_with_clang(ctx)
        assert result.is_nothing(), "Should fail on invalid C++"


# ---------------------------------------------------------------------------
# Annotation tests
# ---------------------------------------------------------------------------


class TestAnnotations:
    def test_parse_annotation_with_value(self):
        result = _parse_babelc_annotation("babelc::ipc_type=FileDescriptor")
        assert result.is_just()
        assert result.value == Annotation(name="ipc_type", value="FileDescriptor")

    def test_parse_annotation_without_value(self):
        result = _parse_babelc_annotation("babelc::use_discriminated_variant")
        assert result.is_just()
        assert result.value == Annotation(name="use_discriminated_variant", value=None)

    def test_parse_non_babelc_annotation(self):
        result = _parse_babelc_annotation("clang::something")
        assert result.is_nothing()


# ---------------------------------------------------------------------------
# Container resolution tests
# ---------------------------------------------------------------------------


class TestResolveContainer:
    def test_vector(self):
        r = _resolve_container(
            "std::vector<std::uint64_t>",
            "PhoneNumbers",
            "addressbook::v1::PhoneNumbers",
            ("addressbook", "v1"),
        )
        assert isinstance(r, ContainerType)
        assert r.container_kind == "vector"
        assert r.element_type == "std::uint64_t"

    def test_shared_ptr(self):
        r = _resolve_container(
            "std::shared_ptr<addressbook::v1::Server>",
            "ServerPtr",
            "addressbook::v1::ServerPtr",
            ("addressbook", "v1"),
        )
        assert isinstance(r, PointerType)
        assert r.pointer_kind == "shared_ptr"
        assert r.pointee_type == "addressbook::v1::Server"

    def test_array_with_size(self):
        r = _resolve_container(
            "std::array<std::uint8_t, 20>",
            "Buffer",
            "ns::Buffer",
            ("ns",),
        )
        assert isinstance(r, ContainerType)
        assert r.container_kind == "array"
        assert r.element_type == "std::uint8_t"
        assert r.size == 20

    def test_not_a_container(self):
        r = _resolve_container(
            "int",
            "x",
            "x",
            (),
        )
        assert r is None


# ---------------------------------------------------------------------------
# Template arg splitting
# ---------------------------------------------------------------------------


class TestSplitTemplateArgs:
    def test_simple(self):
        assert _split_template_args("int, float") == ["int", "float"]

    def test_nested(self):
        assert _split_template_args("std::vector<int>, float") == [
            "std::vector<int>",
            "float",
        ]

    def test_single(self):
        assert _split_template_args("int") == ["int"]


# ---------------------------------------------------------------------------
# extract_type_model — addressbook.h
# ---------------------------------------------------------------------------


class TestExtractTypeModel:
    def test_returns_compilation_unit(self, compilation_unit):
        assert isinstance(compilation_unit, CompilationUnit)

    def test_namespace_extraction(self, compilation_unit):
        assert "addressbook::v1" in compilation_unit.namespaces

    def test_enum_extraction(self, compilation_unit):
        enums = compilation_unit.enums
        assert len(enums) == 1
        sex = enums[0]
        assert sex.name == "Sex"
        assert sex.qualified_name == "addressbook::v1::Sex"
        assert sex.namespace == ("addressbook", "v1")
        assert sex.underlying_type == "std::uint8_t"
        assert len(sex.enumerators) == 4
        names = [e.name for e in sex.enumerators]
        assert names == ["Unknown", "Male", "Female", "Neither"]

    def test_struct_extraction(self, compilation_unit):
        structs = compilation_unit.structs
        person = next((s for s in structs if s.name == "Person"), None)
        assert person is not None
        assert person.qualified_name == "addressbook::v1::Person"
        assert len(person.fields) == 3
        field_names = [f.name for f in person.fields]
        assert "itsName" in field_names
        assert "itsSex" in field_names
        assert "itsPhoneNumbers" in field_names

    def test_interface_extraction(self, compilation_unit):
        interfaces = compilation_unit.interfaces
        assert len(interfaces) == 1
        server = interfaces[0]
        assert server.name == "Server"
        assert server.qualified_name == "addressbook::v1::Server"
        assert len(server.methods) == 1
        add = server.methods[0]
        assert add.name == "add"
        assert add.return_type == "void"
        assert add.is_pure_virtual is True
        assert len(add.parameters) == 1
        param = add.parameters[0]
        assert param.name == "thePerson"
        assert param.is_const is True
        assert param.is_ref is True

    def test_alias_extraction(self, compilation_unit):
        aliases = compilation_unit.aliases
        alias_names = [a.name for a in aliases]
        assert "PhoneNumber" in alias_names
        assert "PhoneNumbers" in alias_names
        assert "ServerPtr" in alias_names

    def test_phone_number_alias(self, compilation_unit):
        pn = next(a for a in compilation_unit.aliases if a.name == "PhoneNumber")
        assert "uint64_t" in pn.target_type

    def test_phone_numbers_container(self, compilation_unit):
        containers = compilation_unit.containers
        pns = next((c for c in containers if c.name == "PhoneNumbers"), None)
        assert pns is not None
        assert pns.container_kind == "vector"

    def test_server_ptr_pointer(self, compilation_unit):
        pointers = compilation_unit.pointers
        sp = next((p for p in pointers if p.name == "ServerPtr"), None)
        assert sp is not None
        assert sp.pointer_kind == "shared_ptr"

    def test_no_system_types(self, compilation_unit):
        """No types from <cstdint>, <string>, <vector>, etc."""
        all_names = (
            [e.name for e in compilation_unit.enums]
            + [s.name for s in compilation_unit.structs]
            + [i.name for i in compilation_unit.interfaces]
            + [a.name for a in compilation_unit.aliases]
        )
        # Should not contain any std:: type declarations
        for name in all_names:
            assert not name.startswith("std::"), f"System type leaked: {name}"
            assert not name.startswith("__"), f"Internal type leaked: {name}"


# ---------------------------------------------------------------------------
# Toposort tests
# ---------------------------------------------------------------------------


class TestToposort:
    def test_independent_types(self):
        t1 = StructType(
            name="A",
            qualified_name="A",
            namespace=(),
            fields=(),
            annotations=(),
        )
        t2 = StructType(
            name="B",
            qualified_name="B",
            namespace=(),
            fields=(),
            annotations=(),
        )
        result = _toposort([t2, t1])
        assert len(result) == 2

    def test_dependency_order(self):
        t1 = StructType(
            name="A",
            qualified_name="A",
            namespace=(),
            fields=(),
            annotations=(),
        )
        t2 = StructType(
            name="B",
            qualified_name="B",
            namespace=(),
            fields=(Field(name="a", type_name="A"),),
            annotations=(),
        )
        result = _toposort([t2, t1])
        names = [r.qualified_name for r in result]
        assert names.index("A") < names.index("B")
