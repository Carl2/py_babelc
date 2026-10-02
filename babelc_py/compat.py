"""Drop-in command line for the original C++ ``babelc``.

Usage: ``babelc <gcc options|-babelc options> header``

Understood: -babelcOutput=Ipc|Json, -babelcDirectory=DIR, -babelcCompiler=CXX,
-std=gnu++NN.  Accepted and ignored: -babelcForce, -babelcNoColor,
-babelcLog, -babelcUseTabs, -babelcKeepIntermediate, -babelcSummary.
Not supported: -babelcOutput=Stream|Dep, -babelcUnitTest.
Other options are gcc options; the preprocessor related ones are forwarded
to libclang, and the whole set is given to the compiler to discover its
system include directories (so --sysroot of a cross SDK works).
"""

import os
import re
import subprocess
import sys

from babelc_py.__main__ import generate
from babelc_py.clang_parser import discover_system_cpp_includes

_IGNORED = {
    "-babelcForce",
    "-babelcNoColor",
    "-babelcLog",
    "-babelcUseTabs",
    "-babelcKeepIntermediate",
    "-babelcSummary",
}
_SEPARATE_ARG = {"-I", "-isystem", "-iquote", "-include", "-D", "-U"}
_FORWARD = re.compile(r"^(-I|-isystem|-iquote|-include|-D|-U|--sysroot)")
_STD = re.compile(r"^-std=(?:gnu|c)\+\+(\d\d)$")


def parse_args(argv):
    """Split argv into (header, opts) where opts holds the parsed settings."""
    opts = {"output": "ipc", "directory": None, "compiler": "g++",
            "std": None, "gcc": [], "forward": []}
    if not argv:
        raise ValueError("no input header given")
    *rest, header = argv
    it = iter(rest)
    for a in it:
        if a.startswith("-babelc"):
            name, _, value = a.partition("=")
            if name == "-babelcOutput":
                kind = value.lower()
                if kind not in ("ipc", "json"):
                    raise ValueError(f"unsupported output generator: {value}")
                opts["output"] = kind
            elif name == "-babelcDirectory":
                opts["directory"] = value
            elif name == "-babelcCompiler":
                opts["compiler"] = value
            elif name == "-babelcUnitTest":
                raise ValueError("-babelcUnitTest is not supported")
            elif name not in _IGNORED:
                raise ValueError(f"unknown option: {a}")
            continue
        m = _STD.match(a)
        if m:
            opts["std"] = int(m.group(1))
            continue
        if a in _SEPARATE_ARG:
            a = a + next(it, "")
        opts["gcc"].append(a)
        if _FORWARD.match(a):
            opts["forward"].append(a)
    return header, opts


def output_path(header, kind, directory):
    stem, ext = os.path.splitext(os.path.basename(header))
    out_dir = directory if directory else os.path.dirname(header) or "."
    os.makedirs(out_dir, exist_ok=True)
    return os.path.join(out_dir, f"{stem}.{kind}{ext}")


def _user_include_dirs(opts):
    """Directories given with -I/-iquote; these must stay non-system."""
    out, it = set(), iter(opts)
    for o in it:
        for flag in ("-I", "-iquote"):
            if o == flag:
                o = flag + next(it, "")
            if o.startswith(flag) and len(o) > len(flag):
                out.add(os.path.realpath(o[len(flag):]))
                break
    return out


def compiler_includes(compiler, gcc_opts):
    """Ask the compiler for its C++ include search path (as -isystem args)."""
    try:
        proc = subprocess.run(
            [*compiler.split(), *gcc_opts, "-E", "-x", "c++", "-v", "-"],
            input="", capture_output=True, text=True, check=True,
        )
    except (OSError, subprocess.CalledProcessError):
        return None
    dirs, on = [], False
    for line in proc.stderr.splitlines():
        if line.startswith("#include <...>"):
            on = True
        elif line.startswith("End of search list"):
            break
        elif on and line.startswith(" "):
            dirs.append(line.strip())
    user = _user_include_dirs(gcc_opts)
    dirs = [d for d in dirs if os.path.realpath(d) not in user]
    if not dirs:
        return None
    return ["-nostdinc++"] + [x for d in dirs for x in ("-isystem", d)]


def compiler_target(compiler, gcc_opts):
    """Return ``--target=<triple>`` for a (cross) compiler, or None."""
    try:
        out = subprocess.run(
            [*compiler.split(), *gcc_opts, "-dumpmachine"],
            capture_output=True, text=True, check=True,
        ).stdout.strip()
    except (OSError, subprocess.CalledProcessError):
        return None
    return f"--target={out}" if out else None


def main(argv=None):
    argv = sys.argv[1:] if argv is None else argv
    try:
        header, opts = parse_args(argv)
    except ValueError as e:
        print(f"babelc: {e}", file=sys.stderr)
        return 2
    if not os.path.isfile(header):
        print(f"babelc: cannot read {header}", file=sys.stderr)
        return 2
    system = compiler_includes(opts["compiler"], opts["gcc"])
    if system is None:
        system = discover_system_cpp_includes()
    target = compiler_target(opts["compiler"], opts["gcc"])
    out = output_path(header, opts["output"], opts["directory"])
    return generate(header, out, opts["output"],
                    system + ([target] if target else []) + opts["forward"],
                    opts["std"] or 20)


if __name__ == "__main__":
    sys.exit(main())
