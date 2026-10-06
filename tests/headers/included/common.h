#ifndef COMMON_H
#define COMMON_H
#include <cstdint>
#include <string>
#include <memory>
namespace com { namespace example { namespace svc { namespace v1 {
  struct TriggerId { std::uint32_t value; };
  struct Unused { std::uint32_t u; };
  struct Logger {
    virtual ~Logger() {}
    virtual void log(const std::string& msg) = 0;
  };
}}}}
#endif
