#include <string>
#include <cstdint>
namespace n {
typedef std::string Str;
using Obj = std::string [[babelc::ipc_type("Object")]];
enum struct FD : std::int32_t [[babelc::ipc_type("FileDescriptor")]] {};
struct S { Obj o; FD f; };
struct I {
  virtual ~I(){};
  virtual void m(FD f, Obj o, S s) = 0;
  virtual FD r(Obj o) = 0;
};
}
