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

typedef struct swapping_rule_table {  // This is a little bit redundant
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
} swap_table;

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
 * as dictated by the multiplexing (muxing) discpline in use.
 */
class ConnectionManager : public cSimpleModule {
 private:
  int myAddress;
  int num_of_qnics;
  std::map<int, bool> qnic_res_table;
  RoutingDaemon *routingdaemon;
  HardwareMonitor *hardwaremonitor;

  virtual void initialize() override;

  virtual void handleMessage(cMessage *msg) override;
  void responder_alloc_req_handler(ConnectionSetupRequest *pk);
  void intermediate_alloc_req_handler(ConnectionSetupRequest *pk);

  void initiator_alloc_res_handler(ConnectionSetupResponse *pk);
  void intermediate_alloc_res_handler(ConnectionSetupResponse *pk);

  void responder_reject_req_handler(RejectConnectionSetupRequest *pk);
  void intermediate_reject_req_handler(RejectConnectionSetupRequest *pk);

  // virtual RuleSet* generateRuleSet_EntanglementSwapping(unsigned int RuleSet_id,int owner, int left_node, QNIC_type lqnic_type, int lqnic_index, int lres, int right_node,
  // QNIC_type rqnic_type, int rqnic_index, int rres);
  RuleSet *generateRuleSet_Tomography(unsigned long RuleSet_id, int owner, int partner, int num_measure, QNIC_type qnic_type, int qnic_index, int num_resources);
  RuleSet *generateRuleSet_EntanglementSwapping(unsigned long RuleSet_id, int owner, swap_table conf);
  swap_table EntanglementSwappingConfig(int swapper_address, std::vector<int> path, std::map<int, std::vector<int>> swapping_partners, std::vector<QNIC_pair_info> qnics,
                                        int num_resources);

  void reserve_qnic(int qnic_address);
  void release_qnic(int qnic_address);
  bool isQnic_busy(int qnic_address);

  unsigned long createUniqueId();
};

Define_Module(ConnectionManager);
}  // namespace modules
}  // namespace quisp
#endif /* MODULES_CONNECTIONMANAGER_H_ */
