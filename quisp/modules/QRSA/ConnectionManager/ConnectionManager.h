/*
 * ConnectionManager.h
 *
 *  Created on: Sep 14, 2020
 *      Author: zigen
 */

#pragma once

#include <omnetpp.h>
#include <locale>
#include <map>
#include <queue>
#include <vector>

#include "IConnectionManager.h"
#include "messages/connection_teardown_messages_m.h"

#include <messages/classical_messages.h>
#include <modules/Logger/LoggerBase.h>
#include <modules/QNIC.h>
#include <modules/QRSA/HardwareMonitor/IHardwareMonitor.h>
#include <modules/QRSA/RoutingDaemon/IRoutingDaemon.h>
#include <rules/Action.h>
#include <utils/ComponentProvider.h>

struct SwappingConfig {
  int left_partner;
  int lres;
  int right_partner;
  int rres;
};

namespace quisp::modules {

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
class ConnectionManager : public IConnectionManager, public Logger::LoggerBase {
 public:
  ConnectionManager();
  ~ConnectionManager();
  utils::ComponentProvider provider;

 protected:
  int my_address;
  int num_of_qnics;

  std::vector<int> node_addresses_along_path;
  std::map<int, std::queue<messages::ConnectionSetupRequest *>> connection_setup_buffer;  // key is qnic address
  std::map<int, int> connection_retry_count;  // key is qnic address
  std::vector<int> reserved_qnics = {};  // reserved qnic address table
  std::vector<int> available_qnics = {};
  std::vector<cMessage *> request_send_timing;  // self message, notification for sending out request
  std::map<unsigned long, std::vector<int>> ruleset_id_node_addresses_along_path_map;
  bool simultaneous_es_enabled;
  bool es_with_purify = false;
  int num_remote_purification;
  double threshold_fidelity;
  rules::PurType purification_type;
  IRoutingDaemon *routing_daemon;
  IHardwareMonitor *hardware_monitor;

  void initialize() override;
  void handleMessage(cMessage *msg) override;

  void respondToRequest(messages::ConnectionSetupRequest *pk);
  void respondToRequest_deprecated(messages::ConnectionSetupRequest *pk);
  void tryRelayRequestToNextHop(messages::ConnectionSetupRequest *pk);

  void queueApplicationRequest(messages::ConnectionSetupRequest *pk);
  void initiateApplicationRequest(int qnic_address);
  void scheduleRequestRetry(int qnic_address);
  void popApplicationRequest(int qnic_address);

  void storeInternalConnectionTeardownMessage(messages::ConnectionTeardownMessage *pk);

  void storeRuleSetForApplication(messages::ConnectionSetupResponse *pk);
  void storeRuleSet(messages::ConnectionSetupResponse *pk);
  void storeInfoAboutNodeAddressesAlongPath(messages::ConnectionSetupResponse *pk);

  void initiator_reject_req_handler(messages::RejectConnectionSetupRequest *pk);
  void responder_reject_req_handler(messages::RejectConnectionSetupRequest *pk);
  void intermediate_reject_req_handler(messages::RejectConnectionSetupRequest *pk);

  void rejectRequest(messages::ConnectionSetupRequest *req);

  void reserveQnic(int qnic_address);
  void releaseQnic(int qnic_address);
  bool isQnicBusy(int qnic_address);

  static rules::PurType parsePurType(const std::string &pur_type);

  unsigned long createUniqueId() override;
  int getRuleSetIndexByOwnerAddress(std::map<int, nlohmann::json> rulesets, int owner_address);
};

}  // namespace quisp::modules
