#pragma once
#include <array>
#include <cstdint>
namespace n {
enum class DbusBool : std::uint8_t { No = 0, Yes = 1 };
using BoolArray = std::array<DbusBool, 10>;
struct [[babelc::interface_name("n.X")]] X {
  virtual ~X() = default;
  virtual void set(const BoolArray& a) = 0;
};
}
