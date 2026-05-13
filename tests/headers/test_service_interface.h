#ifndef INCLUDE_OCP_IPC_TEST_SERVICE_TEST_SERVICE_INTERFACE_H_
#define INCLUDE_OCP_IPC_TEST_SERVICE_TEST_SERVICE_INTERFACE_H_

#include <string>
#include <vector>

namespace com::volvo::ocp::test_service::v1 {

enum struct PingStatus : std::uint8_t
{
  OK,
  ERROR,
  Timeout
};

using Payload = std::vector<std::uint8_t>;

/**
 * Server:      com.volvo.ocp.test_service
 * Object path: /com/volvo/ocp/test_service/TestServiceRequest
 * Interface:   com.volvo.ocp.test_service.v1.TestServiceRequest
 *
 * ping using TestServiceRequest will make message_handler to send ping
 * message to BOS. Once response is received from BOS, pong with
 * correct status will be send to dbus path, provided in ping
 * TestServiceRequest.
 *
 * Returns the id used in the message.
 *
 * TestServiceRequest ping parameters:
 * dbuspath: Address where ping response (pong) need to be sent.
 *
 * timeOut:  Maximum elapsed time in seconds, for an expected response
 *           from BOS.
 *
 *           If provided timeOut is less than 5 seconds, it will be
 *           disregarded and default timeout of 5 seconds will be used.
 */

struct TestServiceRequest
{
  virtual ~TestServiceRequest() {};
  virtual void ping(const std::string& dbuspath, std::uint64_t timeOut)                                                   = 0;
  virtual void beefyMessage(const std::string& dbuspath, std::uint64_t timeOut, const Payload& payload, bool copyPayload) = 0;
};

struct TestServiceResponse
{
  virtual ~TestServiceResponse() {};
  virtual void pong(PingStatus status)                                         = 0;
  virtual void beefyMessageResponse(PingStatus status, const Payload& payload) = 0;
};

}  // namespace com::volvo::ocp::test_service::v1

#endif /* INCLUDE_OCP_IPC_TEST_SERVICE_TEST_SERVICE_INTERFACE_H_ */
