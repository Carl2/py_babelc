"""Tests for the static JSON templates (Task 14)."""

import re
import shutil
import subprocess

import pytest

from babelc_py.jinja_env import create_env, ns_begin, ns_end

HEADER_PREFIX = """
#include <memory>
#include <type_traits>
#include <algorithm>
#include <ostream>
#include <sstream>
#include <cctype>
#include <string>
"""


def _render(name, cpp_std=20, **kw):
    return create_env().get_template(name).render(cpp_std=cpp_std, **kw)


def _assemble(cpp_std, adapters=("std",), kinds=("std::vector", "std::map", "std::array")):
    parts = [HEADER_PREFIX]
    parts.append(_render("json_parser.j2", cpp_std))
    parts.append(_render("json_indent.j2", cpp_std))
    parts.append(_render("babel_helpers.j2"))
    for kind in kinds:
        parts.append(create_env().get_template("container_helpers.j2").render(kind=kind))
    parts.append(_render("babel_helpers_last.j2"))
    parts.append(_render("json_predefined_decl.j2", cpp_std))
    for ns in adapters:
        parts.append(_render("json_optional_decl.j2", cpp_std, ns=ns))
        parts.append(_render("json_variant_decl.j2", cpp_std, ns=ns))
    parts.append(_render("json_predefined_impl.j2", cpp_std))
    for ns in adapters:
        parts.append(_render("json_optional_impl.j2", cpp_std, ns=ns))
        parts.append(_render("json_variant_impl.j2", cpp_std, ns=ns))
    return "\n".join(parts)


class TestNamespaceHelpers:
    def test_cpp17_nested(self):
        assert ns_begin(["a", "b"], 17) == "namespace a::b {"
        assert ns_end(["a", "b"], 17) == "}"

    def test_cpp14_blocks(self):
        assert ns_begin(["a", "b"], 14) == "namespace a { namespace b {"
        assert ns_end(["a", "b"], 14) == "}}"


@pytest.mark.parametrize("cpp_std", [14, 20])
@pytest.mark.parametrize(
    "name",
    ["json_parser.j2", "json_indent.j2", "json_predefined_decl.j2", "json_predefined_impl.j2"],
)
def test_static_template_clean(name, cpp_std):
    out = _render(name, cpp_std)
    assert "__cplusplus" not in out
    for macro in re.findall(r"#(?:ifndef|define)\s+(\w+)", out):
        assert "__" not in macro and not macro.startswith("_"), macro
    if cpp_std == 14:
        assert not re.search(r"^namespace \w+::", out, re.M)


def test_parser_matches_reference():
    ref = open("tests/reference_output/addressbook.json.h").read()
    start = ref.index("#ifndef BABEL_JSON_PARSER_H_")
    end = ref.index("#ifndef __HAVE_BABEL__JSON_INDENT__")
    ref_parser = ref[start:end]
    ours = _render("json_parser.j2", 17)
    body = ours[ours.index("#ifndef BABEL_JSON_PARSER_H_") :]
    # reference has the C++14/17 namespace branches; compare the part in between
    inner_ref = ref_parser[ref_parser.index("#endif\n", ref_parser.index("namespace babel::JSON::parser")) + 7 :]
    inner_ref = inner_ref[: inner_ref.rindex("#if __cplusplus < 201700")]
    assert inner_ref.strip() in body


@pytest.mark.skipif(shutil.which("g++") is None, reason="g++ not available")
class TestCompiles:
    DRIVER = """
int main() {
    std::istringstream in("[1, null, 3]");
    std::vector<std::optional<int>> v;
    babel::JSON::readJSON<char>(in, v);
    std::ostringstream out;
    babel::JSON::writeJSON(out, v, babel::JSON::Indent(0));
    return out.str() == "[1,null,3]" ? 0 : 1;
}
"""
    VARIANT_DRIVER = """
int main() {
    std::istringstream in("\\"hi\\"");
    std::variant<std::int32_t, std::string> v;
    babel::JSON::readJSON<char>(in, v);
    std::ostringstream out;
    babel::JSON::writeJSON(out, v, babel::JSON::Indent(0));
    return out.str() == "\\"hi\\"" ? 0 : 1;
}
"""

    @pytest.mark.parametrize("std", [17, 20])
    @pytest.mark.parametrize("driver", ["DRIVER", "VARIANT_DRIVER"])
    def test_std_adapters_compile_and_run(self, tmp_path, std, driver):
        src = tmp_path / "t.cpp"
        src.write_text(
            "#include <optional>\n#include <variant>\n#include <cstdint>\n"
            + _assemble(std)
            + getattr(self, driver)
        )
        exe = tmp_path / "t"
        r = subprocess.run(
            ["g++", f"-std=c++{std}", "-Wall", "-Werror", str(src), "-o", str(exe)],
            capture_output=True,
            text=True,
        )
        assert r.returncode == 0, r.stderr[:3000]
        assert subprocess.run([str(exe)]).returncode == 0

    def test_cpp14_without_adapters_compiles(self, tmp_path):
        src = tmp_path / "t.cpp"
        src.write_text(
            "#include <cstdint>\n#include <vector>\n"
            + _assemble(14, adapters=())
            + "int main(){ std::istringstream in(\"[1,2]\"); std::vector<std::int32_t> v;"
            " babel::JSON::readJSON<char>(in, v); return v.size()==2?0:1; }\n"
        )
        exe = tmp_path / "t"
        r = subprocess.run(
            ["g++", "-std=c++14", "-Wall", "-Werror", str(src), "-o", str(exe)],
            capture_output=True,
            text=True,
        )
        assert r.returncode == 0, r.stderr[:3000]
        assert subprocess.run([str(exe)]).returncode == 0
