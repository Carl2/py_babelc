#ifndef ECHO_SERVICE_H_
#define ECHO_SERVICE_H_

#include <string>
#include <vector>
#include <cstdint>

namespace com::example::echo::v1 {

enum struct EchoStatus : std::uint8_t {
    OK,
    Error,
    Timeout
};

using Payload = std::vector<std::uint8_t>;

struct EchoRequest {
    virtual ~EchoRequest() {};

    virtual void ping(const std::string &destination, std::uint64_t timeoutMs)                                              = 0;
    virtual void sendPayload(const std::string &destination, std::uint64_t timeoutMs, const Payload &data, bool compressed) = 0;
};

struct EchoResponse {
    virtual ~EchoResponse() {};

    virtual void pong(EchoStatus status)                                      = 0;
    virtual void payloadReceived(EchoStatus status, const Payload &data) = 0;
};

} // namespace com::example::echo::v1

#endif
