/** \file HardwareMonitor.h
 *
 *  \brief HardwareMonitor
 */
#pragma once

#include "IHardwareMonitor.h"

#include <complex>

#include "rules/Rule.h"
#include "utils/ComponentProvider.h"
#include "utils/TomographyManager.h"

namespace quisp::modules {

/** \class HardwareMonitor HardwareMonitor.h
 *
 *  \brief HardwareMonitor
 */

class HardwareMonitor : public IHardwareMonitor {
 public:
  HardwareMonitor();
  ~HardwareMonitor();
  std::unique_ptr<InterfaceInfo> findInterfaceByNeighborAddr(int neighbor_address) override;
  std::unique_ptr<ConnectionSetupInfo> findConnectionInfoByQnicAddr(int qnic_address) override;

 protected:
  utils::ComponentProvider provider;
  utils::TomographyManager tomography_manager;

 private:
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
  int purification_type = -1;
  int num_measure;
  int num_end_nodes;

  // record all the partner information that perform tomography with this node.
  // Vector<Tuple<qnic_index, partner_address>>
  std::set<std::tuple<int, int>> tomography_partners;

  IRoutingDaemon *routing_daemon;

  cModule *getQnic(int qnic_index, QNIC_type qnic_type);
  NeighborTable neighbor_table;

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
  virtual void sendLinkTomographyRuleSet(int my_address, int partner_address, QNIC_type qnic_type, int qnic_index, unsigned long ruleset_id);
  virtual void writeToFile_Topology_with_LinkCost(int qnic_id, double link_cost, double fidelity, double bellpair_per_sec);
};

Define_Module(HardwareMonitor);

}  // namespace quisp::modules

namespace std {
std::stringstream &operator<<(std::stringstream &os, const quisp::modules::NeighborInfo &v);
std::basic_ostream<char> &operator<<(std::basic_ostream<char> &os, const quisp::modules::InterfaceInfo &v);
}  // namespace std
