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
