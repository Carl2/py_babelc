#pragma once
#include <array>
#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <boost/optional.hpp>

namespace shop {

enum class Color : std::uint8_t { Red, Green, Blue };
enum class Flags : std::uint16_t {};
enum class Level : std::int32_t { Low = 1, High = 2 };

struct Point {
  std::int32_t x;
  std::int32_t y = 0;
};

using PointList = std::vector<Point>;
using Dims = std::array<std::int32_t, 3>;
using ByName = std::map<std::string, Point>;
using ById = std::map<std::int32_t, std::string>;
using OptInt = boost::optional<std::int32_t>;
using PointPtr = std::shared_ptr<Point>;

struct Item {
  std::string name;
  double price;
  OptInt qty = boost::none;
  Dims dims;
  PointList points;
  ByName byName;
  ById byId;
  Color color = Color::Red;
  Flags flags;
  Level level;
  PointPtr ptr;
};

struct Empty {};

}  // namespace shop
