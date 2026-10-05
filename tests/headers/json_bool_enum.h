#pragma once
#include <cstdint>
namespace n {
enum class E : bool { off = false, on = true };
struct S { E e = E::off; std::uint8_t v; };
}
