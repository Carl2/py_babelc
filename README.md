# py-babelc

py-babelc generates D-Bus IPC code (`*.ipc.h`) and JSON serialisation code
(`*.json.h`) from plain C++ headers. It is a Python re-implementation of
[babelc](http://www.babelc.com) by Mattias Sjösvärd. It accepts the same
headers and the same command line, and it generates the same kind of code.

The generated IPC code still uses the unchanged runtime policy header
`sdbus-policy.h` (`policies/sdbus-policy.h`), so existing applications keep
working.

## Why py-babelc instead of babelc

| | babelc (C++) | py-babelc |
|---|---|---|
| Parser | Own regular-expression parser on top of gcc preprocessor output | libclang, a real C++ AST |
| Generated code | Large C++ string literals inside the generator | Jinja2 templates, see below |
| Language level | Written in C++14, hard to change | Python, small modules, 200+ tests |
| Error messages | Rejects some valid C++ (`class`, `= default` destructors) | Reports problems per type with a code (`V001`...) |
| Output | Reserved identifiers in include guards (`__X__`) | Guards without `__` and without a leading `_` |
| Brace initialisers | Needs `T x = 0;` | Also understands `T x{};` (JSON treats it as required, same as babelc) |
| Cross compiling | Own gcc options | Takes `--sysroot` and `-babelcCompiler` and asks the compiler for its include paths |

Other reasons:

- The generator is easy to read and to extend. Adding a feature means editing a
  template and a few lines of Python, not a C++ code generator.
- Output is checked in tests against the output of the original babelc (block
  by block), and against `g++ -fsyntax-only` for C++14, 17 and 20.
- Newer C++ is supported: `std::optional` and `std::variant` as well as the
  boost versions, and `--cpp-std` selects the language level of the output.
- It was built and tested against the real production repositories: a sweep over the `babelc_generate` calls found no header where the original
  babelc works and py-babelc fails.

What is **not** supported: `-babelcOutput=Stream` and `Dep` (not used in the
repositories), `-babelcUnitTest`.

## Install

Requires Python 3.10 or newer, and libclang.

```sh
python3 -m venv .venv
.venv/bin/pip install .          # pulls in pymonad, Jinja2 and libclang (PyPI wheel)
```

Two commands are installed:

| Command | Purpose |
|---|---|
| `babelc-compat` | Same command line as the original babelc. Use this one in CMake |
| `py-babelc` | Own, shorter command line, see below |

In the Yocto SDK and in the Yocto image build py-babelc is installed as
`babelc`, so `find_program(BABELC_PATH babelc)` in `FindBabelc.cmake` finds it
without any change. The C++ version stays available as `babelc-cpp`.

## Usage, original babelc command line (`babelc-compat`)

```
babelc-compat [gcc options] [-babelc options] header.h
```

| Option | Meaning |
|---|---|
| `-babelcOutput=Ipc\|Json` | What to generate. Default `Ipc` |
| `-babelcDirectory=DIR` | Output directory. Default: next to the header |
| `-babelcCompiler=CXX` | Compiler used to find the system include paths. Default `g++` |
| `-std=gnu++NN` | C++ standard (e.g. `gnu++20`). `14`... selects the language level of the output |
| `-I`, `-isystem`, `-iquote`, `-include`, `-D`, `-U`, `--sysroot` | Forwarded to libclang and to the compiler |
| `-babelcForce`, `-babelcNoColor`, `-babelcLog`, `-babelcUseTabs`, `-babelcKeepIntermediate`, `-babelcSummary` | Accepted and ignored |
| `-babelcOutput=Stream\|Dep`, `-babelcUnitTest` | Rejected with an error |

The output is named `<header stem>.ipc.h` or `<header stem>.json.h`, in the
same way as the original.

Environment variable: `PY_BABELC_PYTHON` selects the Python interpreter in the
`py-babelc` wrapper script that the Yocto recipe installs (default `python3`).

## Usage, own command line (`py-babelc`)

```
py-babelc -o OUTPUT [-t ipc|json] [--cpp-std YEAR] [--clang-arg ARG ...] header.h
```

| Option | Meaning |
|---|---|
| `-o`, `--output` | Output file (required) |
| `-t`, `--type` | `ipc` (default) or `json` |
| `--cpp-std YEAR` | C++ standard of the parse and of the generated code: 14, 17, 20... Default 20. With 14 the boost adapters are used instead of the `std::` ones, and `std::optional` / `std::variant` are rejected |
| `--clang-arg ARG` | Extra libclang argument, repeatable. Use for `-I` paths, e.g. `--clang-arg=-Isrc/include` |

## Example

The example is taken from `app-service-discovery`.

`src/include/ipc/service_discovery_types.h`:

```cpp
namespace com::volvo::ocp::servicediscovery::v1 {

struct ServiceData {
  std::string ipAddress;
  std::uint16_t port = 0;           // has a default => optional in JSON
  std::string serviceInstance;
  std::string serviceType;
};

using ServiceDataVector = std::vector<ServiceData>;

}
```

`src/include/ipc/service_discovery.h`:

```cpp
#include "service_discovery_types.h"

namespace com::volvo::ocp::servicediscovery::v1 {

struct RegisterServiceRequest {
  virtual void request(std::uint32_t msgId, const ServiceDataVector& serviceData) = 0;

  // babelc requires a non-defaulted virtual destructor
  virtual ~RegisterServiceRequest() {}
};

}
```

Generate the IPC code and the JSON code:

```sh
INC=src/include/ipc

babelc-compat -I$INC -std=gnu++20 -babelcOutput=Ipc  -babelcDirectory=gen_files $INC/service_discovery.h
babelc-compat -I$INC -std=gnu++20 -babelcOutput=Json -babelcDirectory=gen_files $INC/service_discovery_types.h
```

Result:

```
gen_files/service_discovery.ipc.h        # IPC client and server code for RegisterServiceRequest
gen_files/service_discovery_types.json.h # readJSON/writeJSON/interpretJSON for ServiceData
```

The same with the own command line:

```sh
py-babelc -t ipc  -o gen_files/service_discovery.ipc.h        --clang-arg=-I$INC $INC/service_discovery.h
py-babelc -t json -o gen_files/service_discovery_types.json.h --clang-arg=-I$INC $INC/service_discovery_types.h
```

Include the generated headers in the application, next to the original ones:

```cpp
#include "service_discovery.ipc.h"
#include "service_discovery_types.json.h"
```

### From CMake

Nothing changes in the repositories. `babelc_generate()` from `ocp-cmake`
calls `${BABELC_PATH}` with the original options. To select py-babelc in an
SDK where it is not the default:

```sh
cmake -DBABELC_PATH=$OECORE_NATIVE_SYSROOT/usr/bin/py-babelc ...
```

## Annotations

The annotations of the original babelc are understood. They are written as
C++ attributes and are rewritten to `clang::annotate` before parsing:

| Annotation | Where | Effect |
|---|---|---|
| `[[babelc::interface_name("a.b.C")]]` | after an interface struct | D-Bus interface name |
| `[[babelc::ipc_type("Object")]]`, `("FileDescriptor")` | on an alias or on an opaque enum | Maps to an object path or a file descriptor in the IPC policy |
| `[[babelc::use_discriminated_variant]]` | on a variant | Discriminated variant on the wire |
| `[[babelc::intentionally_incomplete_variant]]` | on a variant | Silences the JSON completeness warning |

Example from `tests/headers/device_status.h`:

```cpp
struct DeviceStatusUpdate {
    virtual ~DeviceStatusUpdate() {};
    virtual void stateChanged(const ConnectionState state) = 0;
} [[babelc::interface_name("com.example.device.v1.DeviceStatus")]];
```

## The Jinja templates

All generated C++ comes from Jinja2 templates in `babelc_py/templates/`.
Python code decides *what* to generate (types, order, wire view types, which
helpers are needed). The templates decide *how it looks*.

| Template | Content |
|---|---|
| `ipc_header.h.j2` | IPC header: order of all parts |
| `helpers.j2`, `babel_helpers.j2`, `babel_helpers_last.j2`, `container_helpers.j2` | Shared support code, emitted only when used |
| `struct.j2`, `enum.j2`, `container.j2`, `variant.j2` | Read and write code per type (declaration and implementation macros) |
| `interface.j2` | Client proxy, server stub, broadcast listener |
| `json_header.h.j2` | JSON header: order of all parts |
| `json_parser.j2` | Embedded `babel::JSON::parser` (MIT, from the original) |
| `json_indent.j2`, `json_predefined_*.j2` | Static JSON helpers for built-in types and containers |
| `json_enum.j2`, `json_struct.j2`, `json_common.j2` | Per-type JSON code |
| `json_optional_*.j2`, `json_variant_*.j2` | `std::` or `boost::` optional/variant adapters (`ns` parameter) |

Things worth knowing when you edit a template:

- Each block has its own include guard such as
  `HAVE_BABEL_IPC_<QUALIFIED_NAME>_IPC_DECLARATIONS`, so blocks can appear in
  several generated headers in one translation unit. Names never contain `__`.
- Filters and globals are defined in `babelc_py/jinja_env.py`:
  `guard_macro`, `qualified`, `ns_open`, `ns_close`, `ns_begin`, `ns_end`.
  Namespaces are nested `a::b {` from C++17 and `namespace a { namespace b {`
  for C++14.
- Types are emitted in dependency order. Declarations come first, then all
  implementations.
- After a change, run the tests. `tests/test_ipc_correctness.py` and
  `tests/test_json_correctness.py` compare the output block by block with the
  output of the original babelc (`tests/reference_output/`) and compile the
  result with `g++`.

## Development

```sh
.venv/bin/pip install -e . pytest
.venv/bin/python -m pytest -q
```

Source layout:

| File | Purpose |
|---|---|
| `babelc_py/pre_process.py` | Rewrites `[[babelc::...]]` to `clang::annotate` |
| `babelc_py/clang_parser.py` | libclang front end, builds the type model |
| `babelc_py/type_model.py` | Type model and validation (`V001`...) |
| `babelc_py/ipc_generator.py`, `json_generator.py` | Prepare data and render the templates |
| `babelc_py/compat.py`, `__main__.py` | The two command lines |

The code uses a railway-oriented style: each step is a function that returns a
`pymonad` `Maybe`, and the steps are chained with `bind`.

## Licence

GPL version 2, see `LICENSE`. py-babelc is a re-implementation of the original
babelc, see `NOTICE.md` for what is reused. The embedded JSON parser is MIT
licensed. According to the original author, the code that is generated is not
covered by the GPL.
