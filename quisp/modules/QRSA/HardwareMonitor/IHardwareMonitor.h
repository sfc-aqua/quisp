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

struct TomographyOutcome {
  char my_basis;
  bool my_output_is_plus;
  char my_GOD_clean;
  char partner_basis;
  bool partner_output_is_plus;
  char partner_GOD_clean;
};

struct OutputCount {
  int total_count;
  int plus_plus;
  int plus_minus;
  int minus_plus;
  int minus_minus;
};

struct LinkCost {
  simtime_t tomography_time;
  int tomography_measurements;
  double Bellpair_per_sec;
};

// qnic_index -> InterfaceInfo
using NeighborTable = std::map<int, InterfaceInfo>;

// basis combination -> raw output count
// e.g.
// "XX" -> {plus_plus = 56, plus_minus = 55, minus_plus = 50, minus_minus = 50},
// "XY" -> {....
using RawData = std::map<int, std::map<std::string, OutputCount>>;  // qnic -> partner . basis string . output
using LinkCostMap = std::map<int, LinkCost>;
using TomographyOutcomeTable = std::map<int, std::map<int, TomographyOutcome>>;  // partner -> <count_id, outcome>

class IHardwareMonitor : public cSimpleModule {
 public:
  virtual ~IHardwareMonitor(){};
  virtual std::unique_ptr<InterfaceInfo> findInterfaceByNeighborAddr(int neighbor_address) = 0;
  virtual std::unique_ptr<ConnectionSetupInfo> findConnectionInfoByQnicAddr(int qnic_address) = 0;
};
}  // namespace quisp::modules
