"""Tests for type_model.py — construction, immutability, equality, addressbook fixture, validation."""

import dataclasses

import pytest

from babelc_py.type_model import (
    AliasType,
    Annotation,
    BuiltinType,
    CompilationUnit,
    ContainerType,
    DISALLOWED_BARE_TYPES,
    EnumType,
    Enumerator,
    Field,
    FIXED_WIDTH_INTEGER_TYPES,
    InterfaceType,
    Method,
    Parameter,
    PointerType,
    StructType,
    ValidationResult,
    VariantType,
    validate_attributes,
    validate_enums,
    validate_interfaces,
    validate_no_bare_types,
    validate_structs,
    validate_type_model,
)


# ---------------------------------------------------------------------------
# Construction
# ---------------------------------------------------------------------------


class TestConstruction:
    def test_annotation_with_value(self):
        a = Annotation(name="ipc_type", value="FileDescriptor")
        assert a.name == "ipc_type"
        assert a.value == "FileDescriptor"

    def test_annotation_without_value(self):
        a = Annotation(name="use_discriminated_variant")
        assert a.value is None

    def test_enumerator_with_value(self):
        e = Enumerator(name="Male", value=0)
        assert e.name == "Male"
        assert e.value == 0

    def test_enumerator_without_value(self):
        e = Enumerator(name="Male")
        assert e.value is None

    def test_builtin_type(self):
        b = BuiltinType(name="std::uint8_t")
        assert b.name == "std::uint8_t"

    def test_field_with_default(self):
        f = Field(name="itsName", type_name="std::string", default_value='""')
        assert f.default_value == '""'

    def test_field_without_default(self):
        f = Field(name="itsName", type_name="std::string")
        assert f.default_value is None

    def test_parameter(self):
        p = Parameter(
            name="thePerson",
            type_name="addressbook::v1::Person",
            is_const=True,
            is_ref=True,
        )
        assert p.is_const is True
        assert p.is_ref is True

    def test_method(self):
        m = Method(
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
        )
        assert len(m.parameters) == 1

    def test_enum_type(self):
        e = EnumType(
            name="Sex",
            qualified_name="addressbook::v1::Sex",
            namespace=("addressbook", "v1"),
            underlying_type="std::uint8_t",
            enumerators=(
                Enumerator(name="Male", value=0),
                Enumerator(name="Female", value=1),
            ),
            annotations=(),
        )
        assert len(e.enumerators) == 2

    def test_struct_type(self):
        s = StructType(
            name="Person",
            qualified_name="addressbook::v1::Person",
            namespace=("addressbook", "v1"),
            fields=(
                Field(name="itsName", type_name="std::string"),
                Field(name="itsSex", type_name="addressbook::v1::Sex"),
            ),
            annotations=(),
        )
        assert len(s.fields) == 2

    def test_interface_type(self):
        i = InterfaceType(
            name="Server",
            qualified_name="addressbook::v1::Server",
            namespace=("addressbook", "v1"),
            methods=(
                Method(
                    name="add", return_type="void", parameters=(), is_pure_virtual=True
                ),
            ),
            annotations=(),
        )
        assert len(i.methods) == 1

    def test_alias_type(self):
        a = AliasType(
            name="PhoneNumber",
            qualified_name="addressbook::v1::PhoneNumber",
            namespace=("addressbook", "v1"),
            target_type="std::uint64_t",
            annotations=(),
        )
        assert a.target_type == "std::uint64_t"

    def test_container_type_vector(self):
        c = ContainerType(
            name="PhoneNumbers",
            qualified_name="addressbook::v1::PhoneNumbers",
            namespace=("addressbook", "v1"),
            container_kind="vector",
            element_type="addressbook::v1::PhoneNumber",
        )
        assert c.size is None

    def test_container_type_array(self):
        c = ContainerType(
            name="Bytes",
            qualified_name="ns::Bytes",
            namespace=("ns",),
            container_kind="array",
            element_type="std::uint8_t",
            size=16,
        )
        assert c.size == 16

    def test_pointer_type(self):
        p = PointerType(
            name="ServerPtr",
            qualified_name="ns::ServerPtr",
            namespace=("ns",),
            pointer_kind="shared_ptr",
            pointee_type="ns::Server",
        )
        assert p.pointer_kind == "shared_ptr"

    def test_variant_type(self):
        v = VariantType(
            name="MyVariant",
            qualified_name="ns::MyVariant",
            namespace=("ns",),
            variant_kind="boost",
            alternatives=("ns::A", "ns::B"),
            annotations=(Annotation(name="use_discriminated_variant"),),
        )
        assert len(v.alternatives) == 2
        assert v.variant_kind == "boost"

    def test_compilation_unit_empty(self):
        cu = CompilationUnit(
            header_path="empty.h",
            namespaces=(),
            enums=(),
            structs=(),
            interfaces=(),
            aliases=(),
            containers=(),
            pointers=(),
            variants=(),
        )
        assert cu.header_path == "empty.h"


# ---------------------------------------------------------------------------
# Immutability
# ---------------------------------------------------------------------------


class TestImmutability:
    def test_annotation_frozen(self):
        a = Annotation(name="x")
        with pytest.raises(dataclasses.FrozenInstanceError):
            a.name = "y"  # type: ignore[misc]

    def test_enum_type_frozen(self):
        e = EnumType(
            name="E",
            qualified_name="E",
            namespace=(),
            underlying_type="int",
            enumerators=(),
            annotations=(),
        )
        with pytest.raises(dataclasses.FrozenInstanceError):
            e.name = "F"  # type: ignore[misc]

    def test_struct_type_frozen(self):
        s = StructType(
            name="S", qualified_name="S", namespace=(), fields=(), annotations=()
        )
        with pytest.raises(dataclasses.FrozenInstanceError):
            s.name = "T"  # type: ignore[misc]

    def test_compilation_unit_frozen(self):
        cu = CompilationUnit(
            header_path="x.h",
            namespaces=(),
            enums=(),
            structs=(),
            interfaces=(),
            aliases=(),
            containers=(),
            pointers=(),
            variants=(),
        )
        with pytest.raises(dataclasses.FrozenInstanceError):
            cu.header_path = "y.h"  # type: ignore[misc]


# ---------------------------------------------------------------------------
# Equality
# ---------------------------------------------------------------------------


class TestEquality:
    def test_identical_annotations_equal(self):
        a1 = Annotation(name="x", value="y")
        a2 = Annotation(name="x", value="y")
        assert a1 == a2

    def test_different_annotations_not_equal(self):
        a1 = Annotation(name="x")
        a2 = Annotation(name="y")
        assert a1 != a2

    def test_identical_enum_types_equal(self):
        kwargs = dict(
            name="Sex",
            qualified_name="addressbook::v1::Sex",
            namespace=("addressbook", "v1"),
            underlying_type="std::uint8_t",
            enumerators=(Enumerator(name="Male", value=0),),
            annotations=(),
        )
        assert EnumType(**kwargs) == EnumType(**kwargs)


# ---------------------------------------------------------------------------
# Addressbook fixture
# ---------------------------------------------------------------------------


@pytest.fixture
def addressbook_unit() -> CompilationUnit:
    """Hand-built CompilationUnit for addressbook.h."""
    sex_enum = EnumType(
        name="Sex",
        qualified_name="addressbook::v1::Sex",
        namespace=("addressbook", "v1"),
        underlying_type="std::uint8_t",
        enumerators=(
            Enumerator(name="Male", value=0),
            Enumerator(name="Female", value=1),
        ),
        annotations=(),
    )

    phone_number_alias = AliasType(
        name="PhoneNumber",
        qualified_name="addressbook::v1::PhoneNumber",
        namespace=("addressbook", "v1"),
        target_type="std::uint64_t",
        annotations=(),
    )

    phone_numbers_alias = AliasType(
        name="PhoneNumbers",
        qualified_name="addressbook::v1::PhoneNumbers",
        namespace=("addressbook", "v1"),
        target_type="std::vector<addressbook::v1::PhoneNumber>",
        annotations=(),
    )

    phone_numbers_container = ContainerType(
        name="PhoneNumbers",
        qualified_name="addressbook::v1::PhoneNumbers",
        namespace=("addressbook", "v1"),
        container_kind="vector",
        element_type="addressbook::v1::PhoneNumber",
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

    server_interface = InterfaceType(
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
            Method(
                name="remove",
                return_type="bool",
                parameters=(
                    Parameter(
                        name="theName",
                        type_name="std::string",
                        is_const=True,
                        is_ref=True,
                    ),
                ),
                is_pure_virtual=True,
            ),
        ),
        annotations=(
            Annotation(name="interface_name", value="com.2getthere.addressbook"),
        ),
    )

    return CompilationUnit(
        header_path="addressbook.h",
        namespaces=("addressbook::v1",),
        enums=(sex_enum,),
        structs=(person_struct,),
        interfaces=(server_interface,),
        aliases=(phone_number_alias, phone_numbers_alias),
        containers=(phone_numbers_container,),
        pointers=(),
        variants=(),
    )


class TestAddressbookFixture:
    def test_header_path(self, addressbook_unit: CompilationUnit):
        assert addressbook_unit.header_path == "addressbook.h"

    def test_enum_count(self, addressbook_unit: CompilationUnit):
        assert len(addressbook_unit.enums) == 1
        assert addressbook_unit.enums[0].name == "Sex"

    def test_enum_enumerators(self, addressbook_unit: CompilationUnit):
        sex = addressbook_unit.enums[0]
        assert sex.enumerators[0].name == "Male"
        assert sex.enumerators[1].name == "Female"
        assert sex.underlying_type == "std::uint8_t"

    def test_struct_count(self, addressbook_unit: CompilationUnit):
        assert len(addressbook_unit.structs) == 1
        assert addressbook_unit.structs[0].name == "Person"

    def test_person_fields(self, addressbook_unit: CompilationUnit):
        person = addressbook_unit.structs[0]
        assert len(person.fields) == 3
        assert person.fields[0].name == "itsName"
        assert person.fields[1].name == "itsSex"
        assert person.fields[2].name == "itsPhoneNumbers"

    def test_interface_count(self, addressbook_unit: CompilationUnit):
        assert len(addressbook_unit.interfaces) == 1
        assert addressbook_unit.interfaces[0].name == "Server"

    def test_server_methods(self, addressbook_unit: CompilationUnit):
        server = addressbook_unit.interfaces[0]
        assert len(server.methods) == 2
        assert server.methods[0].name == "add"
        assert server.methods[1].name == "remove"

    def test_server_annotation(self, addressbook_unit: CompilationUnit):
        server = addressbook_unit.interfaces[0]
        assert len(server.annotations) == 1
        assert server.annotations[0].name == "interface_name"
        assert server.annotations[0].value == "com.2getthere.addressbook"

    def test_alias_count(self, addressbook_unit: CompilationUnit):
        assert len(addressbook_unit.aliases) == 2

    def test_container_count(self, addressbook_unit: CompilationUnit):
        assert len(addressbook_unit.containers) == 1
        assert addressbook_unit.containers[0].container_kind == "vector"

    def test_no_pointers_or_variants(self, addressbook_unit: CompilationUnit):
        assert len(addressbook_unit.pointers) == 0
        assert len(addressbook_unit.variants) == 0


# ---------------------------------------------------------------------------
# Validation helpers
# ---------------------------------------------------------------------------


def _empty_cu(**overrides) -> CompilationUnit:
    """Build a minimal CompilationUnit with overrides."""
    defaults = dict(
        header_path="test.h",
        namespaces=(),
        enums=(),
        structs=(),
        interfaces=(),
        aliases=(),
        containers=(),
        pointers=(),
        variants=(),
    )
    defaults.update(overrides)
    return CompilationUnit(**defaults)


def _ctx(cu: CompilationUnit) -> dict:
    return {"compilation_unit": cu}


# ---------------------------------------------------------------------------
# Validation tests
# ---------------------------------------------------------------------------


class TestValidateEnums:
    def test_v001_enum_without_underlying_type(self):
        cu = _empty_cu(
            enums=(
                EnumType(
                    name="Bad",
                    qualified_name="Bad",
                    namespace=(),
                    underlying_type="",
                    enumerators=(Enumerator(name="A"),),
                    annotations=(),
                ),
            )
        )
        results = validate_enums(cu)
        assert len(results) == 1
        assert results[0].rule_id == "V001"

    def test_v002_enum_with_int_underlying(self):
        cu = _empty_cu(
            enums=(
                EnumType(
                    name="Bad",
                    qualified_name="Bad",
                    namespace=(),
                    underlying_type="int",
                    enumerators=(Enumerator(name="A"),),
                    annotations=(),
                ),
            )
        )
        results = validate_enums(cu)
        assert len(results) == 1
        assert results[0].rule_id == "V002"

    def test_valid_enum_passes(self):
        cu = _empty_cu(
            enums=(
                EnumType(
                    name="Good",
                    qualified_name="Good",
                    namespace=(),
                    underlying_type="std::uint8_t",
                    enumerators=(Enumerator(name="A"),),
                    annotations=(),
                ),
            )
        )
        results = validate_enums(cu)
        assert len(results) == 0


class TestValidateInterfaces:
    def test_v014_empty_interface(self):
        cu = _empty_cu(
            interfaces=(
                InterfaceType(
                    name="I",
                    qualified_name="I",
                    namespace=(),
                    methods=(),
                    annotations=(),
                ),
            )
        )
        results = validate_interfaces(cu)
        assert any(r.rule_id == "V014" for r in results)

    def test_v003_non_pure_virtual(self):
        cu = _empty_cu(
            interfaces=(
                InterfaceType(
                    name="I",
                    qualified_name="I",
                    namespace=(),
                    methods=(
                        Method(
                            name="foo",
                            return_type="void",
                            parameters=(),
                            is_pure_virtual=False,
                        ),
                    ),
                    annotations=(),
                ),
            )
        )
        results = validate_interfaces(cu)
        assert any(r.rule_id == "V003" for r in results)

    def test_v004_const_method(self):
        cu = _empty_cu(
            interfaces=(
                InterfaceType(
                    name="I",
                    qualified_name="I",
                    namespace=(),
                    methods=(
                        Method(
                            name="foo",
                            return_type="void",
                            parameters=(),
                            is_pure_virtual=True,
                            is_const=True,
                        ),
                    ),
                    annotations=(),
                ),
            )
        )
        results = validate_interfaces(cu)
        assert any(r.rule_id == "V004" for r in results)

    def test_v005_pointer_return(self):
        cu = _empty_cu(
            interfaces=(
                InterfaceType(
                    name="I",
                    qualified_name="I",
                    namespace=(),
                    methods=(
                        Method(
                            name="get",
                            return_type="Foo *",
                            parameters=(),
                            is_pure_virtual=True,
                        ),
                    ),
                    annotations=(),
                ),
            )
        )
        results = validate_interfaces(cu)
        assert any(r.rule_id == "V005" for r in results)

    def test_v005_reference_return(self):
        cu = _empty_cu(
            interfaces=(
                InterfaceType(
                    name="I",
                    qualified_name="I",
                    namespace=(),
                    methods=(
                        Method(
                            name="get",
                            return_type="Foo &",
                            parameters=(),
                            is_pure_virtual=True,
                        ),
                    ),
                    annotations=(),
                ),
            )
        )
        results = validate_interfaces(cu)
        assert any(r.rule_id == "V005" for r in results)

    def test_v006_non_const_ref_argument(self):
        cu = _empty_cu(
            interfaces=(
                InterfaceType(
                    name="I",
                    qualified_name="I",
                    namespace=(),
                    methods=(
                        Method(
                            name="f",
                            return_type="void",
                            parameters=(
                                Parameter(
                                    name="x",
                                    type_name="Foo",
                                    is_const=False,
                                    is_ref=True,
                                ),
                            ),
                            is_pure_virtual=True,
                        ),
                    ),
                    annotations=(),
                ),
            )
        )
        results = validate_interfaces(cu)
        assert any(r.rule_id == "V006" for r in results)

    def test_const_ref_argument_passes(self):
        cu = _empty_cu(
            interfaces=(
                InterfaceType(
                    name="I",
                    qualified_name="I",
                    namespace=(),
                    methods=(
                        Method(
                            name="f",
                            return_type="void",
                            parameters=(
                                Parameter(
                                    name="x",
                                    type_name="std::string",
                                    is_const=True,
                                    is_ref=True,
                                ),
                            ),
                            is_pure_virtual=True,
                        ),
                    ),
                    annotations=(),
                ),
            )
        )
        results = validate_interfaces(cu)
        assert len(results) == 0


class TestValidateStructs:
    def test_v009_raw_pointer_field(self):
        cu = _empty_cu(
            structs=(
                StructType(
                    name="S",
                    qualified_name="S",
                    namespace=(),
                    fields=(Field(name="p", type_name="int *"),),
                    annotations=(),
                ),
            )
        )
        results = validate_structs(cu)
        assert any(r.rule_id == "V009" for r in results)

    def test_v008_unresolvable_field_type(self):
        cu = _empty_cu(
            structs=(
                StructType(
                    name="S",
                    qualified_name="S",
                    namespace=(),
                    fields=(Field(name="x", type_name="unknown::Bogus"),),
                    annotations=(),
                ),
            )
        )
        results = validate_structs(cu)
        assert any(r.rule_id == "V008" for r in results)

    def test_valid_struct_passes(self):
        cu = _empty_cu(
            structs=(
                StructType(
                    name="S",
                    qualified_name="S",
                    namespace=(),
                    fields=(Field(name="x", type_name="std::uint32_t"),),
                    annotations=(),
                ),
            )
        )
        results = validate_structs(cu)
        assert len(results) == 0


class TestValidateAttributes:
    def test_v011_ipc_type_on_struct(self):
        cu = _empty_cu(
            structs=(
                StructType(
                    name="S",
                    qualified_name="S",
                    namespace=(),
                    fields=(),
                    annotations=(Annotation(name="ipc_type", value="FileDescriptor"),),
                ),
            )
        )
        results = validate_attributes(cu)
        assert any(r.rule_id == "V011" for r in results)

    def test_v012_discriminated_variant_on_struct(self):
        cu = _empty_cu(
            structs=(
                StructType(
                    name="S",
                    qualified_name="S",
                    namespace=(),
                    fields=(),
                    annotations=(Annotation(name="use_discriminated_variant"),),
                ),
            )
        )
        results = validate_attributes(cu)
        assert any(r.rule_id == "V012" for r in results)

    def test_v012_discriminated_variant_on_enum(self):
        cu = _empty_cu(
            enums=(
                EnumType(
                    name="E",
                    qualified_name="E",
                    namespace=(),
                    underlying_type="std::uint8_t",
                    enumerators=(),
                    annotations=(Annotation(name="use_discriminated_variant"),),
                ),
            )
        )
        results = validate_attributes(cu)
        assert any(r.rule_id == "V012" for r in results)

    def test_v013_unnecessary_discriminant(self):
        cu = _empty_cu(
            variants=(
                VariantType(
                    name="V",
                    qualified_name="V",
                    namespace=(),
                    variant_kind="boost",
                    alternatives=("A", "B", "C"),
                    annotations=(Annotation(name="use_discriminated_variant"),),
                ),
            )
        )
        results = validate_attributes(cu)
        assert len(results) == 1
        assert results[0].rule_id == "V013"
        assert results[0].severity == "warning"


class TestValidateNoBareTypes:
    def test_v010_bare_int_in_struct(self):
        cu = _empty_cu(
            structs=(
                StructType(
                    name="S",
                    qualified_name="S",
                    namespace=(),
                    fields=(Field(name="x", type_name="int"),),
                    annotations=(),
                ),
            )
        )
        results = validate_no_bare_types(cu)
        assert any(r.rule_id == "V010" for r in results)

    def test_v010_bare_type_in_method_return(self):
        cu = _empty_cu(
            interfaces=(
                InterfaceType(
                    name="I",
                    qualified_name="I",
                    namespace=(),
                    methods=(
                        Method(
                            name="f",
                            return_type="long",
                            parameters=(),
                            is_pure_virtual=True,
                        ),
                    ),
                    annotations=(),
                ),
            )
        )
        results = validate_no_bare_types(cu)
        assert any(r.rule_id == "V010" for r in results)

    def test_v010_bare_type_in_param(self):
        cu = _empty_cu(
            interfaces=(
                InterfaceType(
                    name="I",
                    qualified_name="I",
                    namespace=(),
                    methods=(
                        Method(
                            name="f",
                            return_type="void",
                            parameters=(
                                Parameter(
                                    name="x",
                                    type_name="unsigned int",
                                    is_const=False,
                                    is_ref=False,
                                ),
                            ),
                            is_pure_virtual=True,
                        ),
                    ),
                    annotations=(),
                ),
            )
        )
        results = validate_no_bare_types(cu)
        assert any(r.rule_id == "V010" for r in results)


class TestValidateTypeModelPipeline:
    def test_valid_addressbook(self, addressbook_unit: CompilationUnit):
        result = validate_type_model(_ctx(addressbook_unit))
        assert result.is_just()
        assert result.value["validation_warnings"] == []

    def test_multiple_errors_collected(self):
        cu = _empty_cu(
            enums=(
                EnumType(
                    name="E1",
                    qualified_name="E1",
                    namespace=(),
                    underlying_type="",
                    enumerators=(),
                    annotations=(),
                ),
            ),
            structs=(
                StructType(
                    name="S1",
                    qualified_name="S1",
                    namespace=(),
                    fields=(Field(name="p", type_name="int *"),),
                    annotations=(),
                ),
            ),
        )
        result = validate_type_model(_ctx(cu))
        assert result.is_nothing()
        # Should mention both V001 and V009
        assert "V001" in result.value
        assert "V009" in result.value

    def test_warnings_dont_block(self):
        cu = _empty_cu(
            variants=(
                VariantType(
                    name="V",
                    qualified_name="V",
                    namespace=(),
                    variant_kind="boost",
                    alternatives=("A", "B"),
                    annotations=(Annotation(name="use_discriminated_variant"),),
                ),
            )
        )
        result = validate_type_model(_ctx(cu))
        assert result.is_just()
        assert len(result.value["validation_warnings"]) == 1
        assert "V013" in result.value["validation_warnings"][0]
