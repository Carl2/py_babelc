#include "common.h"
namespace com { namespace example { namespace svc { namespace v1 {
  struct Trigger { TriggerId id; };
  typedef std::shared_ptr<Logger> LoggerPtr;
  struct Service {
    virtual ~Service() {}
    virtual void fire(const Trigger& t) = 0;
    virtual void setLogger(LoggerPtr l) = 0;
  };
}}}}
