#pragma once

#include <omnetpp.h>
#include <optional>

#include "types/QNodeAddr.h"

namespace quisp::modules {

using DestInfoTuple = std::tuple<int, types::QNodeAddr, types::QNodeAddr, types::QNodeAddr>;

class IRoutingDaemon : public omnetpp::cSimpleModule {
 public:
  virtual int getNumEndNodes() = 0;
  virtual int findQNicAddrByDestAddr(types::QNodeAddr destAddr) = 0;

  // for RNA
  virtual std::optional<DestInfoTuple> findLowerLayerDestInfoByDestAddr(types::QNodeAddr actual_dest_addr) = 0;
};
}  // namespace quisp::modules
