"""CLI-level tests for option plumbing."""

import subprocess
import sys

from conftest import HEADERS_DIR


def _run(*args):
    return subprocess.run(
        [sys.executable, "-m", "babelc_py", *args],
        capture_output=True,
        text=True,
    )


def test_cpp_std_is_passed_to_clang(tmp_path):
    out = tmp_path / "addressbook.ipc.h"
    r = _run(str(HEADERS_DIR / "addressbook.h"), "-o", str(out), "--cpp-std", "17")
    assert r.returncode == 0, r.stderr
    assert out.exists()


def test_invalid_cpp_std_rejected(tmp_path):
    r = _run(str(HEADERS_DIR / "addressbook.h"), "-o", str(tmp_path / "x.h"), "--cpp-std", "abc")
    assert r.returncode != 0


def test_type_json_generates_header(tmp_path):
    out = tmp_path / "addressbook.json.h"
    r = _run(str(HEADERS_DIR / "addressbook.h"), "-o", str(out), "--type", "json")
    assert r.returncode == 0, r.stderr
    assert "interpretJSON" in out.read_text()


def test_unknown_type_rejected(tmp_path):
    r = _run(str(HEADERS_DIR / "addressbook.h"), "-o", str(tmp_path / "x.h"), "--type", "xml")
    assert r.returncode != 0


def test_referenced_types_from_included_header_are_generated(tmp_path):
    hdr = HEADERS_DIR / "included" / "service.h"
    for kind in ("json", "ipc"):
        out = tmp_path / f"service.{kind}.h"
        r = _run(str(hdr), "-o", str(out), "--type", kind)
        assert r.returncode == 0, r.stderr
        text = out.read_text()
        assert "TriggerId" in text
        assert "Unused" not in text.replace("theFirstUnused", "")
        assert "Logger_TupleView" not in text


def test_json_skips_included_types_only_used_by_interfaces(tmp_path):
    (tmp_path / "inc.h").write_text(
        "#include <cstdint>\nnamespace n {\n"
        "struct OnlyIface { std::uint32_t b = 0; };\n"
        "struct Shared { std::uint32_t c = 0; }; }\n"
    )
    hdr = tmp_path / "main.h"
    hdr.write_text(
        '#include "inc.h"\n'
        "namespace n { struct Used { Shared s; };\n"
        "struct I { virtual ~I() {}\n"
        "  virtual void f(const OnlyIface& x) = 0; }; }\n"
    )
    out = tmp_path / "o.json.h"
    r = _run(str(hdr), "-o", str(out), "--type", "json")
    assert r.returncode == 0, r.stderr
    text = out.read_text()
    assert "Shared" in text
    assert "OnlyIface" not in text
    out2 = tmp_path / "o.ipc.h"
    r = _run(str(hdr), "-o", str(out2))
    assert r.returncode == 0, r.stderr
    assert "OnlyIface" in out2.read_text()


def test_brace_initialised_field_is_required_in_json(tmp_path):
    hdr = tmp_path / "b.h"
    hdr.write_text(
        "#include <cstdint>\nnamespace n { struct S {\n"
        "  double a{};\n  double b = 1.0;\n  std::uint32_t c; }; }\n"
    )
    out = tmp_path / "b.json.h"
    r = _run(str(hdr), "-o", str(out), "--type", "json")
    assert r.returncode == 0, r.stderr
    text = out.read_text()
    assert "theRequiredFields" in text
    import re
    m = re.search(r"theRequiredFields\[\]\s*=\s*\{([^}]*)\}", text)
    assert m and '"a"' in m.group(1) and '"c"' in m.group(1) and '"b"' not in m.group(1)


def test_included_container_alias_is_declared(tmp_path):
    inc = tmp_path / "common.h"
    inc.write_text(
        "#pragma once\n#include <vector>\n#include <cstdint>\nnamespace n {\n"
        "using Dv = std::vector<double>;\nstruct C { std::int64_t t{}; Dv d; };\n"
        "using Cs = std::vector<C>;\n}\n"
    )
    hdr = tmp_path / "svc.h"
    hdr.write_text(
        '#pragma once\n#include "common.h"\nnamespace n {\n'
        'struct [[babelc::interface_name("a.b")]] S {\n'
        "  virtual ~S() = default;\n  virtual void f(const Cs& c) = 0;\n};\n}\n"
    )
    out = tmp_path / "o.h"
    r = _run(str(hdr), "-o", str(out), f"--clang-arg=-I{tmp_path}")
    assert r.returncode == 0, r.stderr
    assert "IpcWriteContainer(  MessageT &&theMessage, const ::n::Cs" in out.read_text()
