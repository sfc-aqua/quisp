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
  std::unique_ptr<ConnectionSetupInfo> findConnectionInfoByQnicAddr(int qnic_address) override;

 protected:
  utils::ComponentProvider provider;
  utils::TomographyManager tomography_manager;

 private:
  int my_address;

  bool do_link_level_tomography = false;
  int num_purification = 0;
  bool x_purification = false;
  bool z_purification = false;
  int purification_type = -1;
  int num_measure;
  int num_end_nodes;

  // record all the partner information that perform tomography with this node.
  // Vector<Tuple<qnic_index, partner_address>>
  std::set<std::tuple<int, int>> tomography_partners;

  // Store link cost information and routing daemon read this.
  // neighbor address -> link cost
  std::map<int, double> link_cost_table;

  IRoutingDaemon *routing_daemon;

  std::string tomography_output_filename;
  std::string file_dir_name;

 protected:
  void initialize(int stage) override;
  void finish() override;
  void handleMessage(cMessage *msg) override;
  int numInitStages() const override { return 2; };
  double getLinkCost(int neighbor_addr);
  virtual void sendLinkTomographyRuleSet(int my_address, int partner_address, QNIC_type qnic_type, int qnic_index, unsigned long ruleset_id);
};

Define_Module(HardwareMonitor);

}  // namespace quisp::modules

namespace std {
std::stringstream &operator<<(std::stringstream &os, const quisp::modules::NeighborInfo &v);
std::basic_ostream<char> &operator<<(std::basic_ostream<char> &os, const quisp::modules::InterfaceInfo &v);
}  // namespace std
