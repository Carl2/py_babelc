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
from babelc_py.pre_process import rewrite_babelc_attributes
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
    args = parser.parse_args()

    system_includes = discover_system_cpp_includes()

    result = (
        Just(
            {
                "header_path": args.header,
                "clang_args": system_includes + args.clang_arg,
            }
        )
        .bind(rewrite_babelc_attributes)
        .bind(parse_with_clang)
        .bind(extract_type_model)
        .bind(validate_type_model)
        .bind(render_ipc_header(args.output))
        .bind(write_output)
    )

    if result.is_nothing():
        print(f"py-babelc: {result.value}", file=sys.stderr)
        sys.exit(1)

    warnings = result.value.get("validation_warnings", [])
    for w in warnings:
        print(f"py-babelc: warning: {w}", file=sys.stderr)


if __name__ == "__main__":
    main()
