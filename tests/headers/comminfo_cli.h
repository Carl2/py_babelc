#ifndef INCLUDE_OCP_IPC_MESSAGE_HANDLER_COM_INFO_H_
#define INCLUDE_OCP_IPC_MESSAGE_HANDLER_COM_INFO_H_

#include <string>

namespace com::volvo::ocp::message_handler::v1 {

struct CommInfoCli
{
  virtual ~CommInfoCli() {}
  virtual std::string getCommInfo()     = 0;
  virtual std::string getServicesInfo() = 0;
};

}  // namespace com::volvo::ocp::message_handler::v1

#endif /* INCLUDE_OCP_IPC_MESSAGE_HANDLER_COM_INFO_H_ */