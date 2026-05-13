#ifndef COUNTER_H_
#define COUNTER_H_

#include <cstdint>

namespace com::example::metrics::v1 {

enum class Counter : std::uint8_t {
    primary,
    secondary
};

struct CounterService {
    virtual ~CounterService() {}

    virtual void reset(Counter counter) = 0;
};

} // namespace com::example::metrics::v1

#endif
