#pragma once
#include <cstdint>
#include <string>
#include <vector>
namespace ns {
struct Item { std::uint32_t a; };
using Items = std::vector<Item>;
enum class Err : std::uint8_t { A, B };
}
namespace com::x::v1 {
struct Svc {
  virtual void f(std::uint32_t id, const ::ns::Items& items, const ::ns::Err& e) = 0;
  virtual ~Svc() = default;
};
}
