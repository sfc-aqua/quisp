/** \file BSA_Controller.cc
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/04/01
 *
 *  \brief BSAController
 */
#include "./BSAController.h"
#include <cstring>
#include <stdexcept>
#include "messages/BSA_ipc_messages_m.h"
#include "messages/link_generation_messages_m.h"
#include "modules/PhysicalConnection/BSA/types.h"
#include "modules/QNIC.h"
#include "omnetpp/cchannel.h"

namespace quisp::modules {

Define_Module(BSAController);

BSAController::BSAController() : provider(utils::ComponentProvider{this}) {}

BSAController::~BSAController() { delete timeout_message; }

void BSAController::initialize() {
  // if this BSA is internal set left to be self node
  if (strcmp(getParentModule()->getName(), "QNIC") == 0) {
    address = provider.getQNode()->par("address").intValue();
    left_qnic.address = provider.getQNode()->par("address").intValue();
    left_qnic.index = getParentModule()->par("self_qnic_index").intValue();
    left_qnic.type = QNIC_R;
  } else {
    address = getParentModule()->par("address").intValue();
    left_qnic = getExternalQNICInfoFromPort(0);
  }
  right_qnic = getExternalQNICInfoFromPort(1);
  offset_time_for_first_photon = calculateOffsetTimeFromDistance();
  auto first_notification_timer = par("initial_notification_timing_buffer").doubleValue();
  timeout_message = new BSMNotificationTimeout("bsm_notification_timeout");
  // TODO: set timeout in case no photons coming in at all. So we send out BSMTimingNotification again.
  scheduleAt(first_notification_timer, timeout_message);
}

void BSAController::handleMessage(cMessage *msg) {
  if (msg->isSelfMessage()) {
    send(generateFirstNotificationTiming(true), "to_router");
    send(generateFirstNotificationTiming(false), "to_router");
    // set timeout to be twice the travel time
    scheduleAt(simTime() + 2 * offset_time_for_first_photon, msg);
    return;
  }
  // a more realistic way of execution would be to send click events through here.
  // but we opt for a better performance, since we are more interested in protocols
  // no emulating physical hardwares.
  throw std::runtime_error("BSAController::handleMessage - message should not be sent here");
}

void BSAController::registerClickBatches(std::vector<BSAClickResult> &results) {
  // we will apply corrections at right nodes
  auto *leftpk = generateNextNotificationTiming(true);
  auto *rightpk = generateNextNotificationTiming(false);
  for (int index = 0; index < results.size(); index++) {
    if (!results[index].success) continue;

    leftpk->appendSuccessIndex(index);
    leftpk->appendCorrectionOperation(PauliOperator::I);
    leftpk->setNeighborAddress(right_qnic.address);
    rightpk->appendSuccessIndex(index);
    rightpk->appendCorrectionOperation(results[index].correction_operation);
    rightpk->setNeighborAddress(left_qnic.address);
  }
  send(leftpk, "to_router");
  send(rightpk, "to_router");

  // need to cancel the timeout and restart the timeout timer
  cancelEvent(timeout_message);
  scheduleAt(simTime() + 2 * offset_time_for_first_photon, timeout_message);
}

BSMTimingNotification *BSAController::generateFirstNotificationTiming(bool is_left) {
  int destination = (is_left) ? left_qnic.address : right_qnic.address;
  int qnic_index = (is_left) ? left_qnic.index : right_qnic.index;
  auto qnic_type = (is_left) ? left_qnic.type : right_qnic.type;
  auto *notification_packet = new BSMTimingNotification();

  notification_packet->setSrcAddr(address);
  notification_packet->setDestAddr(destination);
  notification_packet->setFirstPhotonArrivalTime(simTime().dbl() + offset_time_for_first_photon);
  notification_packet->setInterval(time_interval_between_photons);
  notification_packet->setQnicIndex(qnic_index);
  notification_packet->setQnicType(qnic_type);
  return notification_packet;
}

CombinedBSAresults *BSAController::generateNextNotificationTiming(bool is_left) {
  int destination = (is_left) ? left_qnic.address : right_qnic.address;
  int qnic_index = (is_left) ? left_qnic.index : right_qnic.index;
  auto qnic_type = (is_left) ? left_qnic.type : right_qnic.type;
  auto *notification_packet = new CombinedBSAresults();

  notification_packet->setSrcAddr(address);
  notification_packet->setDestAddr(destination);
  notification_packet->setFirstPhotonArrivalTime(simTime().dbl() + offset_time_for_first_photon);
  notification_packet->setInterval(time_interval_between_photons);
  notification_packet->setQnicIndex(qnic_index);
  notification_packet->setQnicType(qnic_type);
  return notification_packet;
}

double BSAController::calculateOffsetTimeFromDistance() {
  // this bsa is internal and left is connected to this node's qnic
  double one_way_travel_time = std::max(getTravelTimeFromPort(0), getTravelTimeFromPort(1));
  // we add 10 times the photon interval to offset the travel time for safety in case RuleEngine has internal delay;
  return one_way_travel_time * 2 + time_interval_between_photons * 10;
}

int BSAController::getExternalAdressFromPort(int port) {
  return getParentModule()
      ->getSubmodule("BellStateAnalyzer")
      ->gate("quantum_port", port)
      ->getPreviousGate()  // BSANode quantum_port
      ->getPreviousGate()  // QNode quantum_port
      ->getOwnerModule()  // QNode
      ->par("address");
}

int BSAController::getExternalQNICIndexFromPort(int port) {
  return getParentModule()
      ->getSubmodule("BellStateAnalyzer")
      ->gate("quantum_port", port)
      ->getPreviousGate()  // BSANode quantum_port
      ->getPreviousGate()  // QNode quantum_port
      ->getPreviousGate()  // QNIC quantum port
      ->getOwnerModule()
      ->par("self_qnic_index");
}

double BSAController::getTravelTimeFromPort(int port) {
  // this port connects to internal QNIC
  // since only port 0 is supposed to be connected to internal QNIC
  cChannel *channel;
  if (port == 0 && strcmp(getParentModule()->getName(), "QNIC") == 0) {
    auto this_qnic_index = getParentModule()->par("self_qnic_index").intValue();
    channel = provider.getQNode()->gate("quantum_port_receiver$o", this_qnic_index)->getChannel();
  } else {
    // this port connects to outside QNode
    channel = getParentModule()
                  ->getSubmodule("BellStateAnalyzer")
                  ->gate("quantum_port", port)
                  ->getPreviousGate()  // BSANode quantum_port
                  ->getChannel();
  }
  double distance = channel->par("distance").doubleValue();
  double speed_of_light_in_channel = channel->par("speed_of_light_in_fiber");
  return distance / speed_of_light_in_channel;
}

QNIC_id BSAController::getExternalQNICInfoFromPort(int port) {
  QNIC_id qid;
  qid.address = getExternalAdressFromPort(port);
  qid.index = getExternalQNICIndexFromPort(port);
  qid.type = QNIC_E;
  return qid;
}

}  // namespace quisp::modules
