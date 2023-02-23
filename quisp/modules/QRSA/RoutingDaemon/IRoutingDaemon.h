#pragma once

#include <omnetpp.h>
#include <types/QNodeAddr.h>

namespace quisp::modules {

class IRoutingDaemon : public omnetpp::cSimpleModule {
 public:
  virtual int getNumEndNodes() = 0;
  virtual int findQNicAddrByDestAddr(types::QNodeAddr destAddr) = 0;
};
}  // namespace quisp::modules
