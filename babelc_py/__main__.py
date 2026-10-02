"""CLI entry point for py_babelc."""

import argparse
import sys

from pymonad.maybe import Just

from babelc_py.clang_parser import (
    discover_system_cpp_includes,
    extract_type_model,
    parse_with_clang,
)
from babelc_py.ipc_generator import render_ipc_header, write_output
from babelc_py.json_generator import render_json_header
from babelc_py.pre_process import cleanup_temp_files, rewrite_babelc_attributes
from babelc_py.type_model import validate_type_model


def main():
    parser = argparse.ArgumentParser(
        prog="py-babelc",
        description="Generate sdbus D-Bus IPC stubs from annotated C++ headers.",
    )
    parser.add_argument("header", help="Input C++ header file")
    parser.add_argument("-o", "--output", required=True, help="Output file path")
    parser.add_argument(
        "--clang-arg",
        action="append",
        default=[],
        help="Extra argument passed to libclang (repeatable)",
    )
    parser.add_argument(
        "-t",
        "--type",
        choices=("ipc", "json"),
        default="ipc",
        help="Kind of output to generate (default: ipc)",
    )
    parser.add_argument(
        "--cpp-std",
        type=int,
        default=20,
        metavar="YEAR",
        help="C++ standard of the generated code and of the parse: 14, 17, 20, "
        "... (default: 20). 14 selects boost:: instead of std:: adapters.",
    )
    args = parser.parse_args()
    code = generate(
        args.header,
        args.output,
        args.type,
        discover_system_cpp_includes() + args.clang_arg,
        args.cpp_std,
    )
    if code:
        sys.exit(code)


def generate(header, output, kind, clang_args, cpp_std):
    """Run the pipeline and return a process exit code (0 = success)."""
    try:
        result = (
            Just(
                {
                    "header_path": header,
                    "clang_args": clang_args,
                    "cpp_std": cpp_std,
                }
            )
            .bind(rewrite_babelc_attributes)
            .bind(parse_with_clang)
            .bind(extract_type_model)
            .bind(validate_type_model)
            .bind(
                render_json_header(output)
                if kind == "json"
                else render_ipc_header(output)
            )
            .bind(write_output)
        )
    finally:
        cleanup_temp_files()

    if result.is_nothing():
        print(f"py-babelc: {result.value}", file=sys.stderr)
        return 1

    for w in result.value.get("validation_warnings", []):
        print(f"py-babelc: warning: {w}", file=sys.stderr)
    return 0


if __name__ == "__main__":
    main()
