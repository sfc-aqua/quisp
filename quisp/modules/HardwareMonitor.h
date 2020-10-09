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

typedef struct {
  bool isQNode;
  cModuleType *type;
  int address;  // May be QNode, SPDC, HOM
  int index;
  int neighborQNode_address;  // QNode (May be across SDPC or HOM node)
} neighborInfo;

typedef QNIC_id entangledWith;

typedef struct {
  int qnic_index;
  int qubit_index;
  bool isBusy;  // Reserved or free to use
  int assigned_job;  // Maybe useful for bufferspace multiplexing and so on. Indicates which job this qubit is assigned for if isBusy is true.
  entangledWith entangled_inf;
} stationaryQubitInfo;

typedef struct {
  // QubitAddr(int node_addr, int qnic_index, int qubit_index):node_address(node_addr),qnic_index(qnic_index),qubit_index(qubit_index){}
  QNIC qnic;
  double initial_fidelity = -1; /*Oka's protocol?*/
  int buffer_size;
  double link_cost;
  int neighborQNode_address;
  int neighborQNode_qnic_type;
  QNIC neighbor_qnic;
} Interface_inf;

typedef struct {
  QNIC_id qnic;
  int neighbor_address;
  int quantum_link_cost;
} connection_setup_inf;

typedef struct {
  char my_basis;
  bool my_output_is_plus;
  char my_GOD_clean;
  char partner_basis;
  bool partner_output_is_plus;
  char partner_GOD_clean;
} tomography_outcome;

typedef struct {
  int total_count;
  int plus_plus;
  int plus_minus;
  int minus_plus;
  int minus_minus;
} output_count;

typedef struct {
  simtime_t tomography_time;
  int tomography_measurements;
  double Bellpair_per_sec;
} link_cost;

/** \class HardwareMonitor HardwareMonitor.h
 *  \todo Documentation of the class header.
 *
 *  \brief HardwareMonitor
 */

class HardwareMonitor : public cSimpleModule {
 private:
  int myAddress;
  int numQnic, numQnic_r, numQnic_rp, numQnic_total;
  cModuleType *QNodeType = cModuleType::get("networks.QNode");
  cModuleType *SPDCType = cModuleType::get("networks.SPDC");
  cModuleType *HoMType = cModuleType::get("networks.HoM");
  bool do_link_level_tomography = false;
  int num_purification = 0;
  bool X_Purification = false;
  bool Z_Purification = false;
  int Purification_type = -1;
  int num_measure;

 public:
  // typedef std::map<int,Interface_inf> Interfaces;//qnic_index -> Interface{qnic_type, initial_fidelity...}
  typedef std::map<int, Interface_inf> NeighborTable;  // qnic_index -> Interface{qnic_type, initial_fidelity...}
  NeighborTable ntable;
  typedef std::map<int, stationaryQubitInfo> QnicInfo;  // stationary qubit index -> state
  typedef std::map<std::string, output_count>
      raw_data;  // basis combination -> raw output count e.g "XX" -> {plus_plus = 56, plus_minus = 55, minus_plus = 50, minus_minus = 50}, "XY" -> {....
  raw_data *tomography_data;
  QnicInfo *qtable;
  single_qubit_error Pauli;
  virtual NeighborTable passNeighborTable();
  virtual int checkNumBuff(int qnic_index, QNIC_type qnic_type);  // returns the total number of qubits
  virtual connection_setup_inf return_setupInf(int qnic_address);
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
  virtual NeighborTable prepareNeighborTable(NeighborTable ntable, int numQnic);
  virtual neighborInfo checkIfQNode(cModule *thisNode);
  virtual cModule *getQNode();
  virtual neighborInfo findNeighborAddress(cModule *qnic_pointer);
  virtual Interface_inf getInterface_inf_fromQnicAddress(int qnic_index, QNIC_type qnic_type);
  virtual void sendLinkTomographyRuleSet(int my_address, int partner_address, QNIC_type qnic_type, int qnic_index, unsigned long rule_id);
  virtual QNIC search_QNIC_from_Neighbor_QNode_address(int neighbor_address);
  virtual Matrix4cd reconstruct_Density_Matrix(int qnic_id);
  virtual unsigned long createUniqueId();
  virtual void writeToFile_Topology_with_LinkCost(int qnic_id, double link_cost, double fidelity, double bellpair_per_sec);
  // virtual QnicInfo* initializeQTable(int numQnic, QnicInfo *qtable);
  // simtime_t tomography_time;
};

}  // namespace modules
}  // namespace quisp

#endif /* QUISP_MODULES_HARDWAREMONITOR_H_ */
