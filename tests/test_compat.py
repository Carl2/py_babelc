"""Tests for the original-babelc compatible command line."""

import pytest

from babelc_py import compat

HDR = "tests/headers/addressbook.h"


def test_parse_args_original_style():
    header, o = compat.parse_args(
        ["-I", "inc", "-isystem/x", "-std=gnu++17", "-O2", "-babelcCompiler=c++",
         "-babelcForce", "-babelcNoColor", "-babelcOutput=Json",
         "-babelcDirectory=out", "a/b.h"])
    assert header == "a/b.h"
    assert o["output"] == "json" and o["directory"] == "out"
    assert o["compiler"] == "c++" and o["std"] == 17
    assert o["forward"] == ["-Iinc", "-isystem/x"]
    assert "-O2" in o["gcc"]


@pytest.mark.parametrize("bad", ["-babelcOutput=Stream", "-babelcUnitTest",
                                 "-babelcBogus"])
def test_parse_args_rejects(bad):
    with pytest.raises(ValueError):
        compat.parse_args([bad, "x.h"])


def test_output_path(tmp_path):
    p = compat.output_path("d/foo.hpp", "ipc", str(tmp_path / "o"))
    assert p == str(tmp_path / "o" / "foo.ipc.hpp")


def test_end_to_end(tmp_path):
    rc = compat.main(["-std=gnu++20", "-babelcForce", "-babelcOutput=Json",
                      f"-babelcDirectory={tmp_path}", HDR])
    assert rc == 0
    assert (tmp_path / "addressbook.json.h").is_file()


def test_missing_header(tmp_path):
    assert compat.main(["nope.h"]) == 2
