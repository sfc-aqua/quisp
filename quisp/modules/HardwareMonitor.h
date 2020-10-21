/** \file HardwareMonitor.h
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/19
 *
 *  \brief HardwareMonitor
 */
#ifndef QUISP_MODULES_HARDWAREMONITOR_H_
#define QUISP_MODULES_HARDWAREMONITOR_H_

#include <modules/QNIC.h>
#include <modules/stationaryQubit.h>
#include <omnetpp.h>
#include <vector>
#include "classical_messages_m.h"

using namespace omnetpp;

namespace quisp {
namespace modules {

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

/** \class HardwareMonitor HardwareMonitor.h
 *  \todo Documentation of the class header.
 *
 *  \brief HardwareMonitor
 */

class HardwareMonitor : public cSimpleModule {
 private:
  int my_address;

  // number of qnics connected to stand alone HoM or internal hom in the neighbor.
  int num_qnic;
  // number of qnics connected to internal hom.
  int num_qnic_r;
  // number of qnics connected to epps.
  int num_qnic_rp;
  int num_qnic_total;

  cModuleType *QNodeType = cModuleType::get("networks.QNode");
  cModuleType *SPDCType = cModuleType::get("networks.SPDC");
  cModuleType *HoMType = cModuleType::get("networks.HoM");
  bool do_link_level_tomography = false;
  int num_purification = 0;
  bool X_Purification = false;
  bool Z_Purification = false;
  int Purification_type = -1;
  int num_measure;

  std::unique_ptr<InterfaceInfo> findInterfaceByNeighborAddr(int neighbor_address);
  cModule *getQnic(int qnic_index, QNIC_type qnic_type);

 public:
  NeighborTable neighbor_table;
  raw_data *tomography_data;

  single_qubit_error Pauli;
  NeighborTable passNeighborTable();

  int getQnicNumQubits(int qnic_index, QNIC_type qnic_type);
  std::unique_ptr<ConnectionSetupInfo> findConnectionInfoByQnicAddr(int qnic_address);

  // virtual int* checkFreeBuffSet(int qnic_index, int *list_of_free_resources, QNIC_type qnic_type);//returns the set of free resources
  // virtual int checkNumFreeBuff(int qnic_index, QNIC_type qnic_type);//returns the number of free qubits
  typedef std::map<int, tomography_outcome> Temporal_Tomography_Output_Holder;  // measurement_count_id -> outcome. For single qnic
  // typedef std::map<int,Temporal_Tomography_Output_Holder> All_Temporal_Tomography_Output_Holder;//qnic_index -> tomography data. For all qnics.
  Temporal_Tomography_Output_Holder *all_temporal_tomography_output_holder;
  link_cost *all_temporal_tomography_runningtime_holder;
  std::string tomography_output_filename;
  std::string file_dir_name;

 protected:
  virtual void initialize(int stage) override;
  virtual void finish() override;
  virtual void handleMessage(cMessage *msg) override;
  virtual int numInitStages() const override { return 2; };
  virtual void prepareNeighborTable();

  virtual std::unique_ptr<NeighborInfo> createNeighborInfo(const cModule &thisNode);
  virtual cModule *getQNode();
  virtual std::unique_ptr<NeighborInfo> getNeighbor(cModule *qnic_pointer);
  virtual InterfaceInfo getQnicInterfaceByQnicAddr(int qnic_index, QNIC_type qnic_type);
  virtual void sendLinkTomographyRuleSet(int my_address, int partner_address, QNIC_type qnic_type, int qnic_index, unsigned long rule_id);
  virtual QNIC search_QNIC_from_Neighbor_QNode_address(int neighbor_address);
  virtual Matrix4cd reconstruct_Density_Matrix(int qnic_id);
  virtual unsigned long createUniqueId();
  virtual void writeToFile_Topology_with_LinkCost(int qnic_id, double link_cost, double fidelity, double bellpair_per_sec);
  // virtual QnicInfo* initializeQTable(int numQnic, QnicInfo *qtable);
  // simtime_t tomography_time;
};

Define_Module(HardwareMonitor);

}  // namespace modules
}  // namespace quisp

namespace std {
std::stringstream &operator<<(std::stringstream &os, const quisp::modules::NeighborInfo &v);
std::basic_ostream<char> &operator<<(std::basic_ostream<char> &os, const quisp::modules::InterfaceInfo &v);
}  // namespace std

#endif /* QUISP_MODULES_HARDWAREMONITOR_H_ */
