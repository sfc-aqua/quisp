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

#include "IHardwareMonitor.h"
#include "modules/QNIC/StationaryQubit/StationaryQubit.h"
#include "utils/ComponentProvider.h"

namespace quisp {
namespace modules {

/** \class HardwareMonitor HardwareMonitor.h
 *  \todo Documentation of the class header.
 *
 *  \brief HardwareMonitor
 */

class HardwareMonitor : public IHardwareMonitor {
 public:
  HardwareMonitor();
  ~HardwareMonitor();
  NeighborTable passNeighborTable() override;
  int getQnicNumQubits(int qnic_index, QNIC_type qnic_type) override;
  std::unique_ptr<InterfaceInfo> findInterfaceByNeighborAddr(int neighbor_address) override;
  std::unique_ptr<ConnectionSetupInfo> findConnectionInfoByQnicAddr(int qnic_address) override;

 protected:
  utils::ComponentProvider provider;

 private:
  int my_address;

  // number of qnics connected to stand alone HoM or internal hom in the neighbor.
  int num_qnic;
  // number of qnics connected to internal hom.
  int num_qnic_r;
  // number of qnics connected to epps.
  int num_qnic_rp;
  int num_qnic_total;

  bool do_link_level_tomography = false;
  int num_purification = 0;
  bool X_Purification = false;
  bool Z_Purification = false;
  int Purification_type = -1;
  int num_measure;

  cModule *getQnic(int qnic_index, QNIC_type qnic_type);
  NeighborTable neighbor_table;
  raw_data *tomography_data;

  single_qubit_error Pauli;

  // virtual int* checkFreeBuffSet(int qnic_index, int *list_of_free_resources, QNIC_type qnic_type);//returns the set of free resources
  // virtual int checkNumFreeBuff(int qnic_index, QNIC_type qnic_type);//returns the number of free qubits
  // typedef std::map<int,Temporal_Tomography_Output_Holder> All_Temporal_Tomography_Output_Holder;//qnic_index -> tomography data. For all qnics.
  Temporal_Tomography_Output_Holder *all_temporal_tomography_output_holder;
  link_cost *all_temporal_tomography_runningtime_holder;
  std::string tomography_output_filename;
  std::string file_dir_name;

 protected:
  void initialize(int stage) override;
  void finish() override;
  void handleMessage(cMessage *msg) override;
  int numInitStages() const override { return 2; };
  void prepareNeighborTable();

  virtual std::unique_ptr<NeighborInfo> createNeighborInfo(const cModule &thisNode);
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
