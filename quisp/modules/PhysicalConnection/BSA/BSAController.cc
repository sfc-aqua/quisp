/** \file BSA_Controller.cc
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/04/01
 *
 *  \brief BSAController
 */
#include "./BSAController.h"
#include <cstring>
#include <stdexcept>
#include "messages/link_generation_messages_m.h"
#include "modules/PhysicalConnection/BSA/types.h"
#include "omnetpp/csimulation.h"

namespace quisp::modules {

Define_Module(BSAController);

BSAController::BSAController() : provider(utils::ComponentProvider{this}) {}

void BSAController::initialize() {
  // BSA port 0 should always be to QNIC if it is internal
  if (strcmp(getParentModule()->getName(), "QNIC") == 0) {
    address = provider.getQNode()->par("address").intValue();
    left_address = provider.getQNode()->par("address").intValue();
    left_qnic_index = getParentModule()->par("self_qnic_index").intValue();
  } else {
    address = getParentModule()->par("address").intValue();
    left_address = getExternalAdressFromPort(0);
    left_qnic_index = getExternalQNICIndexFromPort(0);
  }
  right_address = getExternalAdressFromPort(1);
  right_qnic_index = getExternalQNICIndexFromPort(1);
}

void BSAController::handleMessage(cMessage *msg) {
  delete msg;
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
    rightpk->appendSuccessIndex(index);

    leftpk->appendCorrectionOperation(PauliOperator::I);
    rightpk->appendCorrectionOperation(results[index].correction_operation);
  }
  send(leftpk, "to_router");
  send(rightpk, "to_router");
}

BSMTimingNotification *BSAController::generateFirstNotificationTiming(bool is_left) {
  int destination = (is_left) ? left_address : right_address;
  int qnic_index = (is_left) ? left_qnic_index : right_qnic_index;
  auto *notification_packet = new BSMTimingNotification();

  notification_packet->setSrcAddr(address);
  notification_packet->setDestAddr(destination);
  notification_packet->setFirstPhotonArrivalTime(simTime().dbl() + offset_time_for_first_photon);
  notification_packet->setInterval(time_interval_between_photons);
  notification_packet->setQnicIndex(qnic_index);
  return notification_packet;
}

CombinedBSAresults *BSAController::generateNextNotificationTiming(bool is_left) {
  int destination = (is_left) ? left_address : right_address;
  int qnic_index = (is_left) ? left_qnic_index : right_qnic_index;
  auto *notification_packet = new CombinedBSAresults();

  notification_packet->setSrcAddr(address);
  notification_packet->setDestAddr(destination);
  notification_packet->setFirstPhotonArrivalTime(simTime().dbl() + offset_time_for_first_photon);
  notification_packet->setInterval(time_interval_between_photons);
  notification_packet->setQnicIndex(qnic_index);
  return notification_packet;
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

}  // namespace quisp::modules
