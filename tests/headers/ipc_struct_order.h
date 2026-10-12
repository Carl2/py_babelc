#pragma once
#include <cstdint>
#include <string>
#include <vector>
namespace ns {
struct Item { std::uint32_t a; };
using Items = std::vector<Item>;
struct Mixed {
  std::uint32_t first;
  Items items;
  std::uint32_t last;
};
}
namespace com::x::v1 {
struct Svc {
  virtual void f(const ::ns::Mixed& m) = 0;
  virtual ~Svc() = default;
};
}
