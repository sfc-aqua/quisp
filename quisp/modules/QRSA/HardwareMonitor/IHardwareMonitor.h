#pragma once

#include <omnetpp.h>
#include <memory>

#include "modules/QNIC.h"

using namespace omnetpp;

namespace quisp::modules {
using quisp::modules::QNIC;
using quisp::modules::QNIC_N;

struct NeighborInfo {
  int address;
  int neighborQNode_address;  // QNode (May be across SDPC or BSA node)
};

struct InterfaceInfo {
  QNIC qnic;
  int buffer_size;
  double link_cost;
  int neighborQNode_address;
};

struct ConnectionSetupInfo {
  QNIC qnic;
  int neighbor_address;
  int quantum_link_cost;
};

const ConnectionSetupInfo NULL_CONNECTION_SETUP_INFO{.qnic =
                                                         {
                                                             .type = QNIC_N,
                                                             .index = -1,
                                                         },
                                                     .neighbor_address = -1,
                                                     .quantum_link_cost = -1};

// qnic_index -> InterfaceInfo
using NeighborTable = std::map<int, InterfaceInfo>;

class IHardwareMonitor : public cSimpleModule {
 public:
  virtual ~IHardwareMonitor(){};
  virtual double getLinkCost(int neighbor_address) = 0;
  virtual std::unique_ptr<ConnectionSetupInfo> findConnectionInfoByQnicAddr(int qnic_address) = 0;
};
}  // namespace quisp::modules
