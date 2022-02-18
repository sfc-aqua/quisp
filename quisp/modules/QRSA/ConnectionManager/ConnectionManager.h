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
using namespace quisp::rules::active;
using quisp::rules::PurType;

namespace quisp {
namespace modules {

/** \class ConnectionManager ConnectionManager.cc
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

 protected:
  int my_address;
  int num_of_qnics;
  std::map<int, std::queue<ConnectionSetupRequest *>> connection_setup_buffer;  // key is qnic address
  std::map<int, int> connection_retry_count;  // key is qnic address
  std::map<int, bool> qnic_res_table;
  std::vector<cMessage *> request_send_timing;  // self message, notification for sending out request
  bool simultaneous_es_enabled;
  bool es_with_purify;
  int num_remote_purification;
  IRoutingDaemon *routing_daemon;
  IHardwareMonitor *hardware_monitor;

  void initialize() override;
  void handleMessage(cMessage *msg) override;
  void finish() override;

  void respondToRequest_deprecated(ConnectionSetupRequest *pk);
  void tryRelayRequestToNextHop(ConnectionSetupRequest *pk);

  void queueApplicationRequest(ConnectionSetupRequest *pk);
  void initiateApplicationRequest(int qnic_address);
  void scheduleRequestRetry(int qnic_address);
  void popApplicationRequest(int qnic_address);

  void storeRuleSetForApplication(ConnectionSetupResponse *pk);
  void storeRuleSet(ConnectionSetupResponse *pk);

  void initiator_reject_req_handler(RejectConnectionSetupRequest *pk);
  void responder_reject_req_handler(RejectConnectionSetupRequest *pk);
  void intermediate_reject_req_handler(RejectConnectionSetupRequest *pk);

  void rejectRequest(ConnectionSetupRequest *req);

  SwappingConfig generateSwappingConfig(int swapper_address, std::vector<int> path, std::map<int, std::vector<int>> swapping_partners, std::vector<QNIC_pair_info> qnics,
                                        int num_resources);
  SwappingConfig generateSimultaneousSwappingConfig(int swapper_address, std::vector<int> path, std::vector<QNIC_pair_info> qnics, int num_resources);

  std::unique_ptr<Rule> purifyRule(int partner_address, PurType purification_type, double threshold_fidelity, QNIC_type qnic_type, int qnic_id, std::string name = "purification");
  std::unique_ptr<Rule> swapRule(std::vector<int> partner_address, double threshold_fidelity, std::vector<QNIC_type> qnic_type, std::vector<int> qnic_id,
                                 std::string name = "swapping");
  std::unique_ptr<Rule> waitRule(int partner_address, QNIC_type qnic_type, int qnic_id, std::string name = "wait");
  std::unique_ptr<Rule> tomographyRule(int partner_address, int num_measure, double threshold_fidelity, QNIC_type qnic_type, int qnic_id, std::string name = "tomography");
  // Rule generators
  std::unique_ptr<ActiveRule> purificationRule(int partner_address, int purification_type, int num_purification, QNIC_type qnic_type, int qnic_index, unsigned long ruleset_id,
                                               unsigned long rule_id);
  std::unique_ptr<ActiveRule> swappingRule(SwappingConfig conf, unsigned long ruleset_id, unsigned long rule_id);
  std::unique_ptr<ActiveRule> simultaneousSwappingRule(SwappingConfig conf, std::vector<int> path, unsigned long ruleset_id, unsigned long rule_id);
  std::unique_ptr<ActiveRule> waitRule_deprecated(int partner_address, int next_partner_address, unsigned long ruleset_id, unsigned long rule_id);
  std::unique_ptr<ActiveRule> tomographyRule_deprecated(int owner_address, int partner_address, int num_measure, QNIC_type qnic_type, int qnic_index, unsigned long ruleset_id,
                                                        unsigned long rule_id);

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
