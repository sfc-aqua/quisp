#pragma once

#include <omnetpp.h>

using omnetpp::cSimpleModule;

namespace quisp::modules {

class IRoutingDaemon : public cSimpleModule {
 public:
  virtual int getNumEndNodes() = 0;
  virtual int findQNicAddrByDestAddr(int destAddr) = 0;
};
}  // namespace quisp::modules
