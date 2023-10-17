/** \file HardwareMonitor.h
 *
 *  \brief HardwareMonitor
 */
#pragma once

#include "IHardwareMonitor.h"

#include <complex>
#include <memory>

#include "rules/Rule.h"
#include "utils/ComponentProvider.h"
#include "utils/ITomographyManager.h"
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

 protected:
  utils::ComponentProvider provider;
  std::unique_ptr<utils::ITomographyManager> tomography_manager;

  // Store link cost information and routing daemon read this.
  // neighbor address -> link cost
  std::map<int, double> link_cost_table;

 private:
  int my_address;

  bool do_link_level_tomography = false;
  int num_purification = 0;
  bool x_purification = false;
  bool z_purification = false;
  int purification_type = -1;
  int num_measure;

  // record all the partner information that perform tomography with this node.
  // Vector<Tuple<qnic_index, partner_address>>
  std::set<std::tuple<int, int>> tomography_partners;

  IRoutingDaemon *routing_daemon;

  std::string tomography_output_filename;

 protected:
  void initialize(int stage) override;
  void finish() override;
  void handleMessage(cMessage *msg) override;
  int numInitStages() const override { return 2; };
  double getLinkCost(int neighbor_addr) override;
  [[deprecated("sendTomographyRuleSet should be moved to connection manager")]] virtual void sendLinkTomographyRuleSet(int my_address, int partner_address, QNIC_type qnic_type,
                                                                                                                       int qnic_index, unsigned long ruleset_id);
};

Define_Module(HardwareMonitor);

}  // namespace quisp::modules
