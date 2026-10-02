#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <boost/variant.hpp>
#include <boost/optional.hpp>
namespace n {
typedef std::string Str;
struct D { Str name; double value; };
typedef std::vector<D> DV;
typedef std::vector<Str> SV;
typedef boost::variant<D, Str> Var;
typedef std::vector<Var> VV;
typedef boost::optional<DV> ODV;
struct S {
  virtual ~S() {}
  virtual DV f(std::uint32_t x) = 0;
  virtual void g(const ODV& a, const SV& b, const VV& c) = 0;
};
}
