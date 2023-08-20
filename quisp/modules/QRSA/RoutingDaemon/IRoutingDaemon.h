#pragma once

#include <omnetpp.h>
#include <memory>
#include "modules/QNIC.h"

namespace quisp::modules {
using omnetpp::cSimpleModule;
using quisp::modules::QNIC;

struct QuantumInterfaceInfo {
  QNIC qnic;
  int buffer_size;
  double link_cost;
  int neighbor_address;
};

const QuantumInterfaceInfo NULL_QUANTUM_INTERFACE_IFNO{
    .qnic =
        {
            .type = QNIC_N,
            .index = -1,
        },
    .buffer_size = -1,
    .link_cost = -1,
    .neighbor_address = -1,
};

class IRoutingDaemon : public cSimpleModule {
 public:
  virtual int findQNicAddrByDestAddr(int destAddr) = 0;
  virtual std::vector<int> getNeighborAddresses() = 0;
  virtual std::unique_ptr<QuantumInterfaceInfo> getQuantumInterfaceInfo(int dest_addr) = 0;
};
}  // namespace quisp::modules
