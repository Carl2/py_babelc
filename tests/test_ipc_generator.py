"""Tests for ipc_generator.py — unit tests with synthetic types + integration."""

from __future__ import annotations

import textwrap

import jinja2
import pytest

from babelc_py.ipc_generator import (
    EnrichedContainer,
    EnrichedField,
    EnrichedInterface,
    EnrichedMethod,
    EnrichedParam,
    EnrichedStruct,
    _build_guard_name,
    _collect_container_kinds,
    _create_jinja_env,
    _dbus_interface_name_filter,
    _enrich_container,
    _enrich_field,
    _enrich_interface,
    _enrich_struct,
    _guard_macro,
    _is_complicated_field,
    _ns_close_filter,
    _ns_open_filter,
    _qualified_filter,
    ipc_template_type,
    render_ipc_header,
)
from babelc_py.type_model import (
    AliasType,
    CompilationUnit,
    ContainerType,
    EnumType,
    Enumerator,
    Field,
    InterfaceType,
    Method,
    Parameter,
    StructType,
)


# ---------------------------------------------------------------------------
# Fixture: a minimal addressbook-like compilation unit
# ---------------------------------------------------------------------------


@pytest.fixture
def addressbook_cu() -> CompilationUnit:
    """Minimal addressbook CU for unit tests."""
    sex_enum = EnumType(
        name="Sex",
        qualified_name="addressbook::v1::Sex",
        namespace=("addressbook", "v1"),
        underlying_type="std::uint8_t",
        enumerators=(
            Enumerator(name="Unknown", value=0),
            Enumerator(name="Male", value=1),
            Enumerator(name="Female", value=2),
            Enumerator(name="Neither", value=3),
        ),
        annotations=(),
    )

    phone_numbers_cont = ContainerType(
        name="PhoneNumbers",
        qualified_name="addressbook::v1::PhoneNumbers",
        namespace=("addressbook", "v1"),
        container_kind="vector",
        element_type="std::uint64_t",
    )

    person_struct = StructType(
        name="Person",
        qualified_name="addressbook::v1::Person",
        namespace=("addressbook", "v1"),
        fields=(
            Field(name="itsName", type_name="std::string"),
            Field(name="itsSex", type_name="addressbook::v1::Sex"),
            Field(name="itsPhoneNumbers", type_name="addressbook::v1::PhoneNumbers"),
        ),
        annotations=(),
    )

    server_iface = InterfaceType(
        name="Server",
        qualified_name="addressbook::v1::Server",
        namespace=("addressbook", "v1"),
        methods=(
            Method(
                name="add",
                return_type="void",
                parameters=(
                    Parameter(
                        name="thePerson",
                        type_name="addressbook::v1::Person",
                        is_const=True,
                        is_ref=True,
                    ),
                ),
                is_pure_virtual=True,
            ),
        ),
        annotations=(),
    )

    phone_alias = AliasType(
        name="PhoneNumbers",
        qualified_name="addressbook::v1::PhoneNumbers",
        namespace=("addressbook", "v1"),
        target_type="std::vector<std::uint64_t>",
        annotations=(),
    )

    return CompilationUnit(
        header_path="/test/addressbook.h",
        namespaces=("addressbook::v1",),
        enums=(sex_enum,),
        structs=(person_struct,),
        interfaces=(server_iface,),
        aliases=(phone_alias,),
        containers=(phone_numbers_cont,),
        pointers=(),
        variants=(),
    )


# ---------------------------------------------------------------------------
# Filter unit tests
# ---------------------------------------------------------------------------


class TestFilters:
    def test_guard_macro(self):
        assert _guard_macro("addressbook::v1::Sex") == "ADDRESSBOOK__V1__SEX"

    def test_guard_macro_leading_colons(self):
        assert _guard_macro("::addressbook::v1::Sex") == "__ADDRESSBOOK__V1__SEX"

    def test_qualified_filter_with_obj(self, addressbook_cu):
        enum = addressbook_cu.enums[0]
        assert _qualified_filter(enum) == "::addressbook::v1::Sex"

    def test_qualified_filter_string(self):
        assert _qualified_filter("addressbook::v1::Sex") == "::addressbook::v1::Sex"

    def test_ns_open(self, addressbook_cu):
        enum = addressbook_cu.enums[0]
        assert _ns_open_filter(enum) == "namespace addressbook::v1 {"

    def test_ns_close(self, addressbook_cu):
        enum = addressbook_cu.enums[0]
        assert _ns_close_filter(enum) == "}"

    def test_dbus_interface_name(self, addressbook_cu):
        iface = addressbook_cu.interfaces[0]
        assert _dbus_interface_name_filter(iface) == "addressbook.v1.Server"

    def test_build_guard_name(self):
        result = _build_guard_name("/tmp/babelc_ref/addressbook.ipc.h")
        assert result.startswith("__")
        assert result.endswith("__")
        assert "ADDRESSBOOK" in result


# ---------------------------------------------------------------------------
# Type mapping unit tests
# ---------------------------------------------------------------------------


class TestTypeMapping:
    def test_string_maps_to_const_char_ptr(self, addressbook_cu):
        assert ipc_template_type("std::string", addressbook_cu) == "const char *"

    def test_bool_maps_to_boolean(self, addressbook_cu):
        assert ipc_template_type("bool", addressbook_cu) == "Boolean"

    def test_enum_maps_to_underlying(self, addressbook_cu):
        result = ipc_template_type("addressbook::v1::Sex", addressbook_cu)
        assert result == "std::uint8_t"

    def test_struct_maps_to_tuple_view(self, addressbook_cu):
        result = ipc_template_type("addressbook::v1::Person", addressbook_cu)
        assert "Person_TupleView<Boolean,IpcPolicy>" in result

    def test_passthrough_builtin(self, addressbook_cu):
        assert ipc_template_type("std::uint64_t", addressbook_cu) == "std::uint64_t"


# ---------------------------------------------------------------------------
# Complicated field classification
# ---------------------------------------------------------------------------


class TestFieldClassification:
    def test_struct_is_complicated(self, addressbook_cu):
        assert _is_complicated_field("addressbook::v1::Person", addressbook_cu)

    def test_container_is_complicated(self, addressbook_cu):
        assert _is_complicated_field("addressbook::v1::PhoneNumbers", addressbook_cu)

    def test_string_is_not_complicated(self, addressbook_cu):
        assert not _is_complicated_field("std::string", addressbook_cu)

    def test_enum_is_not_complicated(self, addressbook_cu):
        assert not _is_complicated_field("addressbook::v1::Sex", addressbook_cu)

    def test_builtin_is_not_complicated(self, addressbook_cu):
        assert not _is_complicated_field("std::uint64_t", addressbook_cu)


# ---------------------------------------------------------------------------
# Enrichment tests
# ---------------------------------------------------------------------------


class TestEnrichment:
    def test_enrich_container_simple(self, addressbook_cu):
        cont = addressbook_cu.containers[0]  # PhoneNumbers
        enriched = _enrich_container(cont, addressbook_cu)
        assert enriched.is_simple_element
        assert enriched.container_kind == "vector"

    def test_enrich_struct_fields(self, addressbook_cu):
        struct = addressbook_cu.structs[0]  # Person
        enriched = _enrich_struct(struct, addressbook_cu)
        assert len(enriched.fields_enriched) == 3
        # itsName and itsSex are simple, itsPhoneNumbers is complicated
        assert len(enriched.simple_read_fields) == 2
        assert len(enriched.complicated_read_fields) == 1
        assert enriched.has_enum_fields

    def test_enrich_interface(self, addressbook_cu):
        iface = addressbook_cu.interfaces[0]  # Server
        enriched = _enrich_interface(iface, addressbook_cu, {})
        assert enriched.all_methods_void
        assert len(enriched.methods_enriched) == 1
        method = enriched.methods_enriched[0]
        assert method.name == "add"
        assert not method.has_return

    def test_enrich_field_wire_types(self, addressbook_cu):
        struct = addressbook_cu.structs[0]
        enriched = _enrich_struct(struct, addressbook_cu)
        wire_types = [f.wire_type for f in enriched.fields_enriched]
        assert wire_types[0] == "const char *"  # itsName (string)
        assert wire_types[1] == "std::uint8_t"  # itsSex (enum)
        # itsPhoneNumbers — container, stays as-is for tuple view
        assert "PhoneNumbers" in wire_types[2]


# ---------------------------------------------------------------------------
# Container kinds
# ---------------------------------------------------------------------------


class TestContainerKinds:
    def test_collect_kinds(self, addressbook_cu):
        kinds = _collect_container_kinds(addressbook_cu)
        assert "std::vector" in kinds


# ---------------------------------------------------------------------------
# Template rendering tests (render individual template fragments)
# ---------------------------------------------------------------------------


class TestTemplateRendering:
    @pytest.fixture
    def env(self):
        return _create_jinja_env()

    def test_babel_helpers_renders(self, env):
        tpl = env.get_template("babel_helpers.j2")
        output = tpl.render()
        assert "__BABEL_HELPERS_FIRST__" in output
        assert "is_supported_ptr_helper" in output
        assert "namespace babel {" in output
        # No C++17 guards
        assert "#if __cplusplus" not in output

    def test_container_helpers_renders(self, env):
        tpl = env.get_template("container_helpers.j2")
        output = tpl.render(kind="std::vector")
        assert "__BABEL_HELPERS_STD__VECTOR__" in output
        assert "is_supported_container_helper<std::vector<T>>" in output
        assert "#include <vector>" in output

    def test_container_helpers_map(self, env):
        tpl = env.get_template("container_helpers.j2")
        output = tpl.render(kind="std::map")
        assert "is_map_container_helper" in output

    def test_container_helpers_array(self, env):
        tpl = env.get_template("container_helpers.j2")
        output = tpl.render(kind="std::array")
        assert "is_fixed_container_helper" in output

    def test_babel_helpers_last_renders(self, env):
        tpl = env.get_template("babel_helpers_last.j2")
        output = tpl.render()
        assert "__BABEL_HELPERS_LAST__" in output
        assert "is_supported_container" in output

    def test_helpers_renders(self, env):
        tpl = env.get_template("helpers.j2")
        output = tpl.render()
        assert "__HAVE_BABEL__IPC_HELPERS__" in output
        assert "BooleanReference" in output
        assert "EnumReference" in output
        assert "StringReference" in output
        assert "ArrayReference" in output
        assert "namespace babel::ipc {" in output
        # No C++17 guards
        assert "#if __cplusplus" not in output

    def test_enum_declaration(self, env, addressbook_cu):
        tpl = env.get_template("enum.j2")
        enum = addressbook_cu.enums[0]
        output = tpl.module.declaration(enum)
        assert "IpcEnumValidate" in output
        assert "__attribute__((weak))" in output
        assert "namespace addressbook::v1 {" in output

    def test_enum_implementation(self, env, addressbook_cu):
        tpl = env.get_template("enum.j2")
        enum = addressbook_cu.enums[0]
        output = tpl.module.implementation(enum)
        assert "switch (theValue)" in output
        assert "case Sex::Unknown:" in output
        assert "case Sex::Male:" in output
        assert "case Sex::Female:" in output
        assert "case Sex::Neither:" in output
        assert "not valid for ::addressbook::v1::Sex" in output


# ---------------------------------------------------------------------------
# Full render pipeline test (unit level — uses synthetic CU)
# ---------------------------------------------------------------------------


class TestRenderPipeline:
    def test_render_produces_output(self, addressbook_cu, tmp_path):
        output_file = str(tmp_path / "addressbook.ipc.h")
        ctx = {"compilation_unit": addressbook_cu}
        result = render_ipc_header(output_file)(ctx)
        assert result.is_just()
        rendered = result.value["rendered_output"]
        # Check major sections present
        assert "#ifndef" in rendered
        assert "#define" in rendered
        assert "#endif" in rendered
        assert '#include "' in rendered
        assert "registerServerImplementation" in rendered
        assert "lookupServerImplementation" in rendered
        assert "ServerImplementationProxy" in rendered
        assert "ServerClientProxy" in rendered
        assert "ServerClientProxyWrapper" in rendered
        # Broadcast variants since all methods void
        assert "ServerBroadcastListener" in rendered
        assert "ServerBroadcastProxy" in rendered
        assert "registerServerBroadcastListener" in rendered
        assert "getServerBroadcastProxy" in rendered
        # Enum
        assert "IpcEnumValidate" in rendered
        # Container
        assert "PhoneNumbers_ArrayView" in rendered
        assert "IpcReadContainer" in rendered
        assert "IpcWriteContainer" in rendered
        # Struct
        assert "Person_TupleView" in rendered
        # Helpers
        assert "is_supported_ptr_helper" in rendered
        assert "BooleanReference" in rendered
