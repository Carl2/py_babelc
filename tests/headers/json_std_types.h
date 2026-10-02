#pragma once
#include <cstdint>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace stdshop {

enum class Kind : std::uint8_t { A, B };

using Kinds = std::vector<Kind>;
using OptName = std::optional<std::string>;
using Value = std::variant<std::int32_t, std::string>;

struct Entry {
  std::string key;
  OptName label;
  Kinds kinds;
  Value value;
};

}  // namespace stdshop
