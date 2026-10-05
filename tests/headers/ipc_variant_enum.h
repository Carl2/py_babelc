#pragma once
#include <cstdint>
#include <string>
#include <boost/variant.hpp>
namespace n {
enum struct E : std::uint8_t { A, B };
enum struct F : std::uint16_t { C, D };
typedef boost::variant<bool, E, F, std::string> V;
struct S { virtual ~S() {} virtual void f(const V& v) = 0; };
}
