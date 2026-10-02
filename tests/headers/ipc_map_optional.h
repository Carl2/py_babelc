#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include <boost/optional.hpp>
namespace n {
struct V { std::uint32_t a; std::string b; };
using Vec = std::vector<V>;
using M = std::map<std::uint32_t, V>;
using O = boost::optional<V>;
struct S { M m; O o; Vec v; };
struct I { virtual ~I() {}; virtual bool f(const M& m, const O& o) = 0; };
}
