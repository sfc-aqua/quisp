/*
 * ConnectionManager.h
 *
 *  Created on: Sep 14, 2020
 *      Author: zigen
 */

#ifndef MODULES_CONNECTIONMANAGER_H_
#define MODULES_CONNECTIONMANAGER_H_

#include <classical_messages_m.h>
#include <modules/QNIC.h>
#include <omnetpp.h>
#include <rules/RuleSet.h>
#include <vector>
#include "HardwareMonitor.h"
#include "RoutingDaemon.h"
#include "RuleEngine.h"

using namespace omnetpp;
using namespace quisp::messages;
using namespace quisp::rules;

namespace quisp {
namespace modules {

typedef struct {  // This is a little bit redundant
  int left_partner;
  QNIC_type lqnic_type;
  int lqnic_index;
  int lqnic_address;
  int lres;
  int right_partner;
  QNIC_type rqnic_type;
  int rqnic_index;
  int rqnic_address;
  int rres;
  int self_left_qnic_index;
  QNIC_type self_left_qnic_type;
  int self_right_qnic_index;
  QNIC_type self_right_qnic_type;
} SwappingConfig;

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
class ConnectionManager : public cSimpleModule {
 private:
  int my_address;
  int num_of_qnics;
  std::map<int, bool> qnic_res_table;
  RoutingDaemon *routing_daemon;
  HardwareMonitor *hardware_monitor;

  virtual void initialize() override;
  virtual void handleMessage(cMessage *msg) override;

  void respondToRequest(ConnectionSetupRequest *pk);
  void relayRequestToNextHop(ConnectionSetupRequest *pk);

  void storeRuleSetForApplication(ConnectionSetupResponse *pk);
  void storeRuleSet(ConnectionSetupResponse *pk);

  void responder_reject_req_handler(RejectConnectionSetupRequest *pk);
  void intermediate_reject_req_handler(RejectConnectionSetupRequest *pk);

  void rejectRequest(ConnectionSetupRequest *req);

  RuleSet *generateTomographyRuleSet(int owner, int partner, int num_measure, QNIC_type qnic_type, int qnic_index, int num_resources);
  RuleSet *generateEntanglementSwappingRuleSet(int owner, SwappingConfig conf);
  SwappingConfig generateSwappingConfig(int swapper_address, std::vector<int> path, std::map<int, std::vector<int>> swapping_partners, std::vector<QNIC_pair_info> qnics,
                                        int num_resources);

  void reserveQnic(int qnic_address);
  void releaseQnic(int qnic_address);
  bool isQnicBusy(int qnic_address);

  unsigned long createUniqueId();
  static int computePathDivisionSize(int l);
  static int fillPathDivision(std::vector<int> path, int i, int l, int *link_left, int *link_right, int *swapper, int fill_start);
};

Define_Module(ConnectionManager);
}  // namespace modules
}  // namespace quisp
#endif /* MODULES_CONNECTIONMANAGER_H_ */
