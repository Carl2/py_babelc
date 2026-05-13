#ifndef CDE_TRIPLOG_H_
#define CDE_TRIPLOG_H_

#include <cstdint>

namespace com::volvo::ocp::cde::v1 {

enum class Log : std::uint8_t
{
  log1,
  log2
};

/*!
 * Interface for resetting a trip log.
 * This interface is only available for VTT1!
 */
struct Triplog
{
  virtual ~Triplog() {}

  /*!
   * Reset the triplog
   *
   * \throws no exception.
   */
  virtual void reset(Log log) = 0;
};

}  // namespace com::volvo::ocp::cde::v1

#endif