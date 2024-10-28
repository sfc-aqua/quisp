/** \file HardwareMonitor.h
 *
 *  \brief HardwareMonitor
 */
#pragma once

#include "IHardwareMonitor.h"

#include <complex>

#include "rules/Rule.h"
#include "utils/ComponentProvider.h"

namespace quisp::modules {

/** \class HardwareMonitor HardwareMonitor.h
 *
 *  \brief HardwareMonitor
 */

class HardwareMonitor : public IHardwareMonitor {
 public:
  HardwareMonitor();
  ~HardwareMonitor();
  int getQnicNumQubits(int qnic_index, QNIC_type qnic_type) override;
  std::unique_ptr<InterfaceInfo> findInterfaceByNeighborAddr(int neighbor_address) override;
  std::unique_ptr<ConnectionSetupInfo> findConnectionInfoByQnicAddr(int qnic_address) override;

 protected:
  utils::ComponentProvider provider;

 private:
  // Matrices of single qubit errors. Used when conducting tomography.
  struct SingleQubitError {
    Eigen::Matrix2cd X;  // double 2*2 matrix
    Eigen::Matrix2cd Y;  // complex double 2*2 matrix
    Eigen::Matrix2cd Z;
    Eigen::Matrix2cd I;
  };

  int my_address;

  // number of qnics connected to stand alone BSA or internal hom in the neighbor.
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
  int num_measure;
  int num_end_nodes;

  // in the case of retry connection setup, the partner could be changed.
  std::map<int, int> qnic_partner_map;

  IRoutingDaemon *routing_daemon;

  cModule *getQnic(int qnic_index, QNIC_type qnic_type);
  NeighborTable neighbor_table;
  RawData *tomography_data;
  SingleQubitError Pauli;

  TomographyOutcomeTable *temporal_tomography_output;  // qnic address -> partner . count_id . outcome
  LinkCostMap *tomography_runningtime_holder;
  std::string tomography_output_filename;
  std::string file_dir_name;
  std::string purification_type;

 protected:
  void initialize(int stage) override;
  void finish() override;
  void handleMessage(cMessage *msg) override;
  int numInitStages() const override { return 2; };
  void prepareNeighborTable();
  virtual std::unique_ptr<NeighborInfo> createNeighborInfo(const cModule &thisNode);
  virtual std::unique_ptr<NeighborInfo> getNeighbor(cModule *qnic_pointer);
  virtual cModule *getQNodeWithAddress(int address);
  virtual InterfaceInfo getQnicInterfaceByQnicAddr(int qnic_index, QNIC_type qnic_type);
  virtual void sendLinkTomographyRuleSet(int my_address, int partner_address, QNIC_type qnic_type, int qnic_index, unsigned long rule_id);
  virtual Eigen::Matrix4cd reconstruct_density_matrix(int qnic_id, int partner);
  virtual unsigned long createUniqueId();
  virtual void writeToFile_Topology_with_LinkCost(int qnic_id, double link_cost, double fidelity, double bellpair_per_sec);
  virtual void makeQnicReservationForTomography(int node_address, int qnic_addr, unsigned long ruleset_id);

  std::unique_ptr<quisp::rules::Rule> constructPurifyRule(const std::string &rule_name, const rules::PurType pur_type, const int partner_address, const QNIC_type qnic_type,
                                                          const int qnic_index, const int send_tag) const;

  std::unique_ptr<quisp::rules::Rule> constructCorrelationCheckRule(const std::string &rule_name, const rules::PurType pur_type, const int partner_address,
                                                                    const QNIC_type qnic_type, const int qnic_index, const int receive_tag) const;
};

Define_Module(HardwareMonitor);

}  // namespace quisp::modules

namespace std {
std::stringstream &operator<<(std::stringstream &os, const quisp::modules::NeighborInfo &v);
std::basic_ostream<char> &operator<<(std::basic_ostream<char> &os, const quisp::modules::InterfaceInfo &v);
}  // namespace std
