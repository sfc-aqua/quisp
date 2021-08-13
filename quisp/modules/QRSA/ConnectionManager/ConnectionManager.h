/*
 * ConnectionManager.h
 *
 *  Created on: Sep 14, 2020
 *      Author: zigen
 */

#ifndef MODULES_CONNECTIONMANAGER_H_
#define MODULES_CONNECTIONMANAGER_H_

#include "IConnectionManager.h"

using namespace omnetpp;
using namespace quisp::messages;
using namespace quisp::rules;

namespace quisp {
namespace modules {

/** \class ConnectionManager ConnectionManager.cc
 *  \todo Documentation of the class header.
 *
 *  \brief ConnectionManager
 *
 * The ConnectionManager is one of the five key modules in the
 * software for a quantum repeater/router (qrsa).  It is responsible for
 * managing the connections: initiating ConnectionSetupRequests,
 * behaving as responder for a ConnectionSetupRequest (which involves
 * actually creating the RuleSets), and handling the requests and
 * responses as the move along the path at setup time.
 *
 * It communicates with the RuleEngine, which is responsible for
 * actually executing the Rules as it is notified of events, but
 * the ConnectionManager has _nothing_ to do with the actual
 * processing of the quantum states as they evolve.
 *
 * You will see member functions for the roles as initiator, responder,
 * and intermediate node.  The main tasks are to respond to ConnectionSetupRequest,
 * ConnectionSetupResponse, RejectConnectionSetupRequest, and ConnectionTeardown messages.
 *
 * It is also responsible for the end-to-end reservation of resources,
 * as dictated by the multiplexing (muxing) discipline in use.
 */
class ConnectionManager : public IConnectionManager {
 public:
  ConnectionManager();
  utils::ComponentProvider provider;

 private:
  int my_address;
  int num_of_qnics;
  std::map<int, bool> qnic_res_table;
  bool simultaneous_es_enabled;
  bool es_with_purify;
  int num_remote_purification;
  IRoutingDaemon *routing_daemon;
  IHardwareMonitor *hardware_monitor;

  void initialize() override;
  void handleMessage(cMessage *msg) override;

  void respondToRequest(ConnectionSetupRequest *pk);
  void relayRequestToNextHop(ConnectionSetupRequest *pk);

  void storeRuleSetForApplication(ConnectionSetupResponse *pk);
  void storeRuleSet(ConnectionSetupResponse *pk);

  void responder_reject_req_handler(RejectConnectionSetupRequest *pk);
  void intermediate_reject_req_handler(RejectConnectionSetupRequest *pk);

  void rejectRequest(ConnectionSetupRequest *req);

  SwappingConfig generateSwappingConfig(int swapper_address, std::vector<int> path, std::map<int, std::vector<int>> swapping_partners, std::vector<QNIC_pair_info> qnics,
                                        int num_resources);
  SwappingConfig generateSimultaneousSwappingConfig(int swapper_address, std::vector<int> path, std::vector<QNIC_pair_info> qnics, int num_resources);
  // RuleSet generators
  RuleSet *generateTomographyRuleSet(int owner_address, int partner_address, int num_of_measure, QNIC_type qnic_type, int qnic_index, int num_resources, unsigned long ruleset_id);
  RuleSet *generateEntanglementSwappingRuleSet(int owner, SwappingConfig conf, unsigned long ruleset_id);
  RuleSet *generateSimultaneousEntanglementSwappingRuleSet(int owner, SwappingConfig conf, std::vector<int> path, unsigned long ruleset_id);
  RuleSet *generatePurificationRuleSet(int owner_address, int partner_address, int num_purification, QNIC_type qnic_type, int qnic_index, unsigned long ruleset_id);
  RuleSet *generateRGSsourceRuleSet(int owner, int partner, int num_of_measure);
  RuleSet *generateEsAndPurificationRuleSet(int owner_address, SwappingConfig conf, int num_purification, unsigned long ruleset_id);
  RuleSet *generatePurAndTomographyRuleSet(int owner_address, int tomography_partner_address, std::vector<int> purification_partner_addresses, int num_purification,
                                           QNIC_type qnic_type, int qnic_index, int num_of_measure, int num_resources, unsigned long ruleset_id);

  // Rule generator
  std::unique_ptr<Rule> purificationRule(int partner_address, int purification_type, int num_purification, QNIC_type qnic_type, int qnic_index, unsigned long ruleset_id,
                                         unsigned long rule_id);
  std::unique_ptr<Rule> swappingRule(SwappingConfig conf, unsigned long ruleset_id, unsigned long rule_id);
  std::unique_ptr<Rule> tomographyRule(int owner_address, int partner_address, int num_measure, QNIC_type qnic_type, int qnic_index, unsigned long ruleset_id, unsigned long rule_id);

  void reserveQnic(int qnic_address);
  void releaseQnic(int qnic_address);
  bool isQnicBusy(int qnic_address);
  QNIC_id getQnicInterface(int owner_address, int partner_address, std::vector<int> path, std::vector<QNIC_pair_info> qnics);

  unsigned long createUniqueId();
  static int computePathDivisionSize(int l);
  static int fillPathDivision(std::vector<int> path, int i, int l, int *link_left, int *link_right, int *swapper, int fill_start);
};

}  // namespace modules
}  // namespace quisp
#endif /* MODULES_CONNECTIONMANAGER_H_ */
