#ifndef QUISP_MODULES_I_HARDWAREMONITOR_H_
#define QUISP_MODULES_I_HARDWAREMONITOR_H_
#include <memory>
#include "modules/QNIC.h"
#include "omnetpp/csimplemodule.h"
using namespace omnetpp;
namespace quisp {
namespace modules {
using quisp::modules::QNIC;
using quisp::modules::QNIC_N;

struct NeighborInfo {
  // QNode, SPDC, HOM
  cModuleType *type;
  int address;
  int neighborQNode_address;  // QNode (May be across SDPC or HOM node)
};

struct InterfaceInfo {
  // QubitAddr(int node_addr, int qnic_index, int qubit_index):node_address(node_addr),qnic_index(qnic_index),qubit_index(qubit_index){}
  QNIC qnic;
  double initial_fidelity = -1; /*Oka's protocol?*/
  int buffer_size;
  double link_cost;
  int neighborQNode_address;
  int neighborQNode_qnic_type;
  QNIC neighbor_qnic;
};

struct ConnectionSetupInfo {
  QNIC_id qnic;
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

struct tomography_outcome {
  char my_basis;
  bool my_output_is_plus;
  char my_GOD_clean;
  char partner_basis;
  bool partner_output_is_plus;
  char partner_GOD_clean;
};

struct output_count {
  int total_count;
  int plus_plus;
  int plus_minus;
  int minus_plus;
  int minus_minus;
};

struct link_cost {
  simtime_t tomography_time;
  int tomography_measurements;
  double Bellpair_per_sec;
};

// qnic_index -> InterfaceInfo
typedef std::map<int, InterfaceInfo> NeighborTable;

// basis combination -> raw output count
// e.g.
// "XX" -> {plus_plus = 56, plus_minus = 55, minus_plus = 50, minus_minus = 50},
// "XY" -> {....
typedef std::map<std::string, output_count> raw_data;
typedef std::map<int, tomography_outcome> Temporal_Tomography_Output_Holder;  // measurement_count_id -> outcome. For single qnic

class IHardwareMonitor : public cSimpleModule {
 public:
  virtual ~IHardwareMonitor(){};
  virtual NeighborTable passNeighborTable() = 0;
  virtual int getQnicNumQubits(int qnic_index, QNIC_type qnic_type) = 0;
  virtual std::unique_ptr<InterfaceInfo> findInterfaceByNeighborAddr(int neighbor_address) = 0;
  virtual std::unique_ptr<ConnectionSetupInfo> findConnectionInfoByQnicAddr(int qnic_address) = 0;
};
}  // namespace modules
}  // namespace quisp
#endif
