#ifndef DEVICE_STATUS_H_
#define DEVICE_STATUS_H_

#include <cstdint>

namespace com::example::device::v1 {

enum struct ConnectionState : std::uint8_t {
    Disconnected,
    Connecting,
    Connected
};

struct DeviceStatus {
    virtual ~DeviceStatus() {}

    virtual ConnectionState getState() = 0;
};

struct DeviceStatusUpdate {
    virtual ~DeviceStatusUpdate() {};

    virtual void stateChanged(const ConnectionState state) = 0;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
/* clang-format off */
} [[babelc::interface_name("com.example.device.v1.DeviceStatus")]];
/* clang-format on */
#pragma GCC diagnostic pop

} // namespace com::example::device::v1

#endif
