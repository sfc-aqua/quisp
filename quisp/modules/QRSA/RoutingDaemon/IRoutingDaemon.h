#ifndef MODULES_IROUTING_DAEMON_H_
#define MODULES_IROUTING_DAEMON_H_

#include "omnetpp/csimplemodule.h"

using omnetpp::cSimpleModule;

namespace quisp {
namespace modules {

class IRoutingDaemon : public cSimpleModule {
 public:
  virtual int return_QNIC_address_to_destAddr(int destAddr) = 0;
};
}  // namespace modules
}  // namespace quisp

#endif
