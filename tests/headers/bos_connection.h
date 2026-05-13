#ifndef INCLUDE_OCP_IPC_MESSAGE_HANDLER_BOS_CONNECTION_H_
#define INCLUDE_OCP_IPC_MESSAGE_HANDLER_BOS_CONNECTION_H_

#include <cstdint>

namespace com::volvo::ocp::message_handler::v1 {

enum struct ConnectionClass : std::uint8_t
{
  NoConnection,
  Fallback,  // SMS, Satellite i.e. limited bandwidth and/or high cost
  Preferred  // Mqtt
};

/**
 * Server:      com.volvo.ocp.messagehandler
 * Object path: /com/volvo/ocp/messagehandler/BOSConnection
 * Interface:   com.volvo.ocp.messagehandler.v1.BOSConnection
 */
struct BOSConnection
{
  virtual ~BOSConnection() {}

  virtual ConnectionClass getActiveClass() = 0;
};

/**
 * Signal interface of BOSConnection
 *
 * It present itself as a part of the BOSConnection interface on dBus.
 *
 * To receive this signal, call generated function
 * registerBOSConnectionUpdateBroadcastListener with the parameter theObjectPath
 * set to "/com/volvo/ocp/messagehandler/BOSConnection".
 *
 */
struct BOSConnectionUpdate
{
  virtual ~BOSConnectionUpdate() {};

  /**
   *  Signal emitted when a the connection class has changed.
   *
   *  @param The connectionClass that is currently active
   */
  virtual void activeBOSConnectionClass(const ConnectionClass connectionClass) = 0;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
  /* clang-format off */
} [[babelc::interface_name("com.volvo.ocp.message_handler.v1.BOSConnection")]];  //lint !e4206 'interface_name' attribute cannot be applied to types
/* clang-format on */
#pragma GCC diagnostic pop

}  // namespace com::volvo::ocp::message_handler::v1

#endif