"""Tests for per-type JSON templates and variant sanity checks (Task 15)."""

import shutil
import subprocess

import pytest

from babelc_py.json_generator import (
    check_variant,
    prepare_struct,
    render_declaration,
    render_implementation,
)
from babelc_py.type_model import (
    AliasType,
    CompilationUnit,
    EnumType,
    Enumerator,
    Field,
    StructType,
    VariantType,
    Annotation,
)
from tests.test_json_static import HEADER_PREFIX, _assemble

NS = ("shop",)
LEVEL = EnumType("Level", "::shop::Level", NS, "std::int32_t", (Enumerator("Low"), Enumerator("High")), ())
FLAGS = EnumType("Flags", "::shop::Flags", NS, "std::uint16_t", (), ())
POINT = StructType(
    "Point", "::shop::Point", NS,
    (Field("x", "std::int32_t"), Field("y", "std::int32_t", "0"), Field("level", "Level", "Level::Low")),
    (),
)
EMPTY = StructType("Empty", "::shop::Empty", NS, (), ())
GLOBAL = StructType("G", "G", (), (Field("a", "std::int32_t"),), ())


def _cu(**kw):
    base = dict(
        header_path="x.h", namespaces=(), enums=(), structs=(), interfaces=(),
        aliases=(), containers=(), pointers=(), variants=(),
    )
    base.update(kw)
    return CompilationUnit(**base)


def test_prepare_struct_required_and_padding():
    s = prepare_struct(POINT)
    assert [f.required for f in s.fields] == [True, False, False]
    assert [f.req_index for f in s.fields] == [0, -1, -1]
    assert s.fields[0].pad == "    "


def test_guards_have_no_double_underscore():
    for t in (LEVEL, POINT, EMPTY, FLAGS):
        for text in (render_declaration(t), render_implementation(t)):
            assert "__" not in text.replace("__clang_analyzer__", "").replace("__attribute__", "")
            assert "#ifndef HAVE_BABEL_JSON_SHOP_" in text


def test_named_enum_uses_lookup_and_failbit():
    out = render_implementation(LEVEL)
    assert "theLookupTable" in out and "failbit" in out


def test_empty_enum_is_numeric():
    out = render_implementation(FLAGS)
    assert "getNumericValue" in out and "theLookupTable" not in out


def test_global_namespace_has_no_namespace_block():
    assert "namespace" not in render_declaration(GLOBAL)


def test_cpp14_nested_namespaces():
    t = StructType("P", "::a::b::P", ("a", "b"), (), ())
    assert "namespace a { namespace b {" in render_declaration(t, 14)
    assert "namespace a::b {" in render_declaration(t, 20)


def test_empty_struct_has_no_dangling_else():
    out = render_implementation(EMPTY)
    assert "else if" not in out and "theRequiredFields" not in out


# --- variant sanity ---------------------------------------------------------


def _variant(alts, annotations=()):
    return VariantType("V", "::V", (), "std", tuple(alts), tuple(annotations))


def test_variant_collision_is_error():
    cu = _cu(structs=(POINT, StructType("Q", "::shop::Q", NS, (Field("z", "std::int32_t"),), ())))
    w, e = check_variant(_variant(["::shop::Point", "::shop::Q"]), cu)
    assert e and any("collides" in x for x in w)


def test_variant_incomplete_warns_unless_intentional():
    cu = _cu()
    w, e = check_variant(_variant(["std::int32_t", "std::string"]), cu)
    assert not e and w
    ann = (Annotation("intentionally_incomplete_variant"),)
    w, e = check_variant(_variant(["std::int32_t", "std::string"], ann), cu)
    assert not e and not w


def test_variant_complete_with_redundant_attribute_warns():
    from babelc_py.type_model import ContainerType
    arr = ContainerType("arr", "::arr", (), "vector", "std::int32_t")
    opt = ContainerType("opt", "::opt", (), "optional", "bool")
    cu = _cu(structs=(POINT,), containers=(arr, opt))
    ann = (Annotation("intentionally_incomplete_variant"),)
    alts = ["bool", "std::int32_t", "std::string", "::shop::Point", "arr", "opt"]
    w, e = check_variant(_variant(alts, ann), cu)
    assert any("redundant" in x for x in w)


# --- compile & run ----------------------------------------------------------


@pytest.mark.skipif(shutil.which("g++") is None, reason="g++ not available")
@pytest.mark.parametrize("std", [14, 17, 20])
def test_generated_types_roundtrip(tmp_path, std):
    types_h = """
#include <cstdint>
#include <string>
namespace shop {
enum class Level : std::int32_t { Low = 1, High = 2 };
enum class Flags : std::uint16_t {};
struct Point { std::int32_t x; std::int32_t y = 0; Level level = Level::Low; };
struct Empty {};
}
"""
    order = [LEVEL, FLAGS, POINT, EMPTY]
    body = (
        HEADER_PREFIX + "#include <cstdint>\n#include <vector>\n" + types_h
        + _assemble(std, adapters=(), kinds=("std::vector",))
        + "".join(render_declaration(t, std) for t in order)
        + "".join(render_implementation(t, std) for t in order)
        + """
int main() {
    using babel::JSON::writeJSON;
    shop::Point p; std::istringstream in("{\\"x\\": 3, \\"level\\": \\"High\\"}");
    babel::JSON::readJSON<char>(in, p);
    if (p.x != 3 || p.y != 0 || p.level != shop::Level::High) return 1;
    std::ostringstream out; writeJSON(out, p, babel::JSON::Indent(0));
    if (out.str() != "{\\"x\\":3,\\"y\\":0,\\"level\\":\\"High\\"}") return 2;
    try { std::istringstream bad("{\\"y\\": 1, \\"z\\": 2}"); babel::JSON::readJSON<char>(bad, p); return 3; }
    catch (const std::invalid_argument &e) {
        std::string m = e.what();
        if (m.find("missing field(s): x") == std::string::npos || m.find("unknown field(s): z") == std::string::npos) return 4;
    }
    shop::Empty e; std::istringstream ein("{}"); babel::JSON::readJSON<char>(ein, e);
    std::ostringstream eo; writeJSON(eo, e, babel::JSON::Indent(0));
    if (eo.str() != "{}") return 5;
    shop::Flags f; std::istringstream fin("7"); babel::JSON::readJSON<char>(fin, f);
    if (static_cast<int>(f) != 7) return 6;
    return 0;
}
"""
    )
    src = tmp_path / "t.cpp"
    src.write_text(body)
    exe = tmp_path / "t"
    r = subprocess.run(
        ["g++", f"-std=c++{std}", "-Wall", "-Wextra", "-Werror", str(src), "-o", str(exe)],
        capture_output=True, text=True,
    )
    assert r.returncode == 0, r.stderr[:3000]
    assert subprocess.run([str(exe)]).returncode == 0


# --- orchestration ----------------------------------------------------------


def _render_cu(cu, std=20):
    from babelc_py.json_generator import render_json_header

    return render_json_header("out.json.h")({"compilation_unit": cu, "cpp_std": std})


def test_used_features_detects_flavours():
    from babelc_py.json_generator import used_features
    from babelc_py.type_model import ContainerType

    opt = ContainerType("O", "::O", (), "optional", "std::int32_t", optional_kind="boost")
    s = StructType("S", "::S", (), (Field("a", "std::vector<std::int32_t>"),
                                      Field("b", "std::optional<std::int32_t>")), ())
    kinds, opts, variants = used_features(_cu(structs=(s,), containers=(opt,)))
    assert kinds == ["std::vector"] and opts == ["boost", "std"] and variants == []


def test_std_optional_rejected_below_cpp17():
    s = StructType("S", "::S", (), (Field("b", "std::optional<std::int32_t>"),), ())
    r = _render_cu(_cu(structs=(s,)), 14)
    assert r.is_nothing() and "17" in r.value
    assert not _render_cu(_cu(structs=(s,)), 17).is_nothing()


def test_variant_error_fails_render():
    q = StructType("Q", "::shop::Q", NS, (Field("z", "std::int32_t"),), ())
    r = _render_cu(_cu(structs=(POINT, q), variants=(_variant(["::shop::Point", "::shop::Q"]),)))
    assert r.is_nothing() and "ambiguous" in r.value


def test_render_has_no_reserved_guards():
    out = _render_cu(_cu(enums=(LEVEL,), structs=(POINT,))).value["rendered_output"]
    assert out.startswith("#ifndef OUT_JSON_H")
