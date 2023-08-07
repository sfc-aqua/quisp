#pragma once

#include <omnetpp.h>

using omnetpp::cSimpleModule;

namespace quisp::modules {

class IRoutingDaemon : public cSimpleModule {
 public:
  virtual int findQNicAddrByDestAddr(int destAddr) = 0;
};
}  // namespace quisp::modules
