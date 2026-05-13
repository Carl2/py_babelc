#ifndef DIAGNOSTICS_H_
#define DIAGNOSTICS_H_

#include <string>

namespace com::example::diagnostics::v1 {

struct Diagnostics {
    virtual ~Diagnostics() {}

    virtual std::string getStatus()  = 0;
    virtual std::string getVersion() = 0;
};

} // namespace com::example::diagnostics::v1

#endif
