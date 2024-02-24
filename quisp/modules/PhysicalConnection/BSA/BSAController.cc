/** \file BSA_Controller.cc
 *
 *  \brief BSAController
 */
#include "BSAController.h"

#include <channels/FSChannel.h>
#include <cstring>
#include <stdexcept>
#include "messages/BSA_ipc_messages_m.h"
#include "messages/base_messages_m.h"
#include "messages/link_generation_messages_m.h"
#include "omnetpp/cexception.h"
#include "omnetpp/cmessage.h"

using quisp::channels::FSChannel;

namespace quisp::modules {

Define_Module(BSAController);

BSAController::BSAController() : provider(utils::ComponentProvider{this}) {}

BSAController::~BSAController() { cancelAndDelete(time_out_message); }

void BSAController::finish() { std::cout << "last BSM message that was sent " << last_result_send_time << "\n"; }

void BSAController::initialize() {
  bsa = check_and_cast<BellStateAnalyzer *>(getParentModule()->getSubmodule("bsa"));
  // if this BSA is internal set left to be self node
  if (strcmp(getParentModule()->getName(), "qnic_r") == 0 || strcmp(getParentModule()->getName(), "qnic_rp") == 0) {
    address = provider.getNodeAddr();
    left_qnic.parent_node_addr = address;
    left_qnic.index = getParentModule()->par("self_qnic_index").intValue();
    left_qnic.type = strcmp(getParentModule()->getName(), "qnic_r") == 0 ? QNIC_R : QNIC_RP;
  } else {
    address = getParentModule()->par("address").intValue();
    left_qnic = getExternalQNICInfoFromPort(0);
  }
  is_active = strcmp(par("mode").stringValue(), "active") == 0;
  left_travel_time = getPredictedTravelTimeFromPort(0);
  right_travel_time = getPredictedTravelTimeFromPort(1);
  time_interval_between_photons = SimTime(1, SIMTIME_S) / getParentModule()->getSubmodule("bsa")->par("photon_detection_per_second").intValue();
  simtime_t first_notification_timer = SimTime(par("initial_notification_timing_buffer").doubleValue());
  // right_qnic = getExternalQNICInfoFromPort(1);
  time_out_count = 0;
  time_out_message = new BSMNotificationTimeout("bsm_notification_timeout");
  if (is_active) {
    time_interval_between_photons = SimTime(1, SIMTIME_S) / SimTime(getParentModule()->getSubmodule("bsa")->par("photon_detection_per_second").intValue(), SIMTIME_S);
    simtime_t first_notification_timer = SimTime(par("initial_notification_timing_buffer").doubleValue());
    right_qnic = getExternalQNICInfoFromPort(1);
    offset_time_for_first_photon = calculateOffsetTimeFromDistance();
    scheduleAt(first_notification_timer, time_out_message);
  }
}

void BSAController::handleMessage(cMessage *msg) {
  if (msg == time_out_message) {
    // P: For satellite links, we need to recalculate this for every pulse train due to variable channel length!
    send(generateFirstNotificationTiming(true), "to_router");
    send(generateFirstNotificationTiming(false), "to_router");
    bsa->resetState();
    // set timeout to be twice the travel time plus number of no response
    time_out_count++;

    scheduleAt(simTime() + (2 + time_out_count) * (offset_time_for_first_photon), msg);
    return;
  }
  if (dynamic_cast<CancelBSMTimeOutMsg *>(msg)) {
    cancelBSMTimeOut();
    delete msg;
    return;
  }
  if (auto *batch_click_msg = dynamic_cast<BatchClickEvent *>(msg)) {
    sendMeasurementResults(batch_click_msg);
    delete msg;
    return;
  }
  // a more realistic way of execution would be to send every click events through here.
  // but we opt for a better performance, since we are more interested in protocols
  // no emulating physical hardwares.
}

void BSAController::sendMeasurementResults(BatchClickEvent *batch_click_msg) {
  if (is_active) {
    CombinedBSAresults *leftpk = generateNextNotificationTiming(true);
    CombinedBSAresults *rightpk = generateNextNotificationTiming(false);
    for (int index = 0; index < batch_click_msg->numberOfClicks(); index++) {
      if (!batch_click_msg->getClickResults(index).success) continue;
      leftpk->appendSuccessIndex(index);
      leftpk->appendCorrectionOperation(PauliOperator::I);
      leftpk->setNeighborAddress(right_qnic.parent_node_addr);
      rightpk->appendSuccessIndex(index);
      rightpk->appendCorrectionOperation(batch_click_msg->getClickResults(index).correction_operation);
      rightpk->setNeighborAddress(left_qnic.parent_node_addr);
    }
    send(leftpk, "to_router");
    send(rightpk, "to_router");
    scheduleAt(simTime() + 1.1 * offset_time_for_first_photon, time_out_message);
  } else {
    SingleClickResult *click_result = new SingleClickResult();
    if (batch_click_msg->numberOfClicks() != 1) {
      throw cRuntimeError("Number of clicks of BSA should be one");
    }
    click_result->setClickResult(batch_click_msg->getClickResults(0));
    click_result->setQnicIndex(left_qnic.index);
    click_result->setDestAddr(left_qnic.parent_node_addr);
    click_result->setSrcAddr(left_qnic.parent_node_addr);
    send(click_result, "to_router");
  }
  //  send(leftpk, "to_router");
  //  send(rightpk, "to_router");
  offset_time_for_first_photon = calculateOffsetTimeFromDistance();
  last_result_send_time = simTime();
}

BSMTimingNotification *BSAController::generateFirstNotificationTiming(bool is_left) {
  int destination = (is_left) ? left_qnic.parent_node_addr : right_qnic.parent_node_addr;
  int qnic_index = (is_left) ? left_qnic.index : right_qnic.index;
  auto qnic_type = (is_left) ? left_qnic.type : right_qnic.type;
  auto *notification_packet = new BSMTimingNotification();

  offset_time_for_first_photon = calculateOffsetTimeFromDistance();
  left_travel_time = getPredictedTravelTimeFromPort(0);
  right_travel_time = getPredictedTravelTimeFromPort(1);

  auto travel_time = (is_left) ? left_travel_time : right_travel_time;

  // The node should emit at <arrival_time - travel_time>

  simtime_t arrival_time = simTime() + offset_time_for_first_photon;
  simtime_t emit_time = arrival_time - travel_time;

  notification_packet->setSrcAddr(address);
  notification_packet->setDestAddr(destination);
  notification_packet->setFirstPhotonEmitTime(emit_time);
  notification_packet->setInterval(time_interval_between_photons);
  notification_packet->setQnicIndex(qnic_index);
  notification_packet->setQnicType(qnic_type);
  return notification_packet;
}

CombinedBSAresults *BSAController::generateNextNotificationTiming(bool is_left) {
  int destination = (is_left) ? left_qnic.parent_node_addr : right_qnic.parent_node_addr;
  int qnic_index = (is_left) ? left_qnic.index : right_qnic.index;
  auto qnic_type = (is_left) ? left_qnic.type : right_qnic.type;
  auto *notification_packet = new CombinedBSAresults();

  offset_time_for_first_photon = calculateOffsetTimeFromDistance();
  left_travel_time = getPredictedTravelTimeFromPort(0);
  right_travel_time = getPredictedTravelTimeFromPort(1);

  auto travel_time = (is_left) ? left_travel_time : right_travel_time;

  // The node should emit at <arrival_time - travel_time>
  simtime_t arrival_time = simTime() + offset_time_for_first_photon;
  simtime_t emit_time = arrival_time - travel_time;

  notification_packet->setSrcAddr(address);
  notification_packet->setDestAddr(destination);
  notification_packet->setFirstPhotonEmitTime(emit_time);
  notification_packet->setInterval(time_interval_between_photons);
  notification_packet->setQnicIndex(qnic_index);
  notification_packet->setQnicType(qnic_type);
  return notification_packet;
}

simtime_t BSAController::calculateOffsetTimeFromDistance() {
  auto current_longer_travel_time = std::max(getCurrentTravelTimeFromPort(0), getCurrentTravelTimeFromPort(1));
  auto predicted_longer_travel_time = std::max(getPredictedTravelTimeFromPort(0), getPredictedTravelTimeFromPort(1));

  // we add 10 times the photon interval to offset the travel time for safety in case RuleEngine has internal delay;
  return current_longer_travel_time + predicted_longer_travel_time + time_interval_between_photons * 10;
}

int BSAController::getExternalAdressFromPort(int port) {
  if (port == 0 && strcmp(getParentModule()->getName(), "qnic_r") == 0) {
    throw cRuntimeError("Trying to get external QNIC information from a port connecting to internal QNIC_R. Address %d, BSAController port %d", address, port);
  }

  // this BSAController is inside QNIC_R but the port is connecting to outside
  if (port != 0 && strcmp(getParentModule()->getName(), "qnic_r") == 0) {
    return getParentModule()
        ->getSubmodule("bsa")
        ->gate("quantum_port$i", port)
        ->getPreviousGate()  // qnic_quantum_port
        ->getPreviousGate()  // QNode quantum_port_receiver
        ->getPreviousGate()  // another QNode quantum_port
        ->getOwnerModule()
        ->par("address");
  }

  // this BSAController is in a stand-alone BSANode
  return getParentModule()
      ->getSubmodule("bsa")
      ->gate("quantum_port$i", port)
      ->getPreviousGate()  // BSANode quantum_port
      ->getPreviousGate()  // QNode quantum_port
      ->getOwnerModule()  // QNode
      ->par("address");
}

int BSAController::getExternalQNICIndexFromPort(int port) {
  if (port == 0 && strcmp(getParentModule()->getName(), "qnic_r") == 0) {
    throw cRuntimeError("Trying to get external QNIC information from a port connecting to internal QNIC_R. Address %d, BSAController port %d", address, port);
  }

  // this BSAController is inside QNIC_R but the port is connecting to outside
  if (port != 0 && strcmp(getParentModule()->getName(), "qnic_r") == 0) {
    return getParentModule()
        ->getSubmodule("bsa")
        ->gate("quantum_port$i", port)
        ->getPreviousGate()  // qnic_quantum_port
        ->getPreviousGate()  // QNode quantum_port_receiver
        ->getPreviousGate()  // another QNode quantum_port
        ->getPreviousGate()  // QNIC quantum port
        ->getOwnerModule()
        ->par("self_qnic_index");
  }

  // this BSAController is in a stand-alone BSANode
  return getParentModule()
      ->getSubmodule("bsa")
      ->gate("quantum_port$i", port)
      ->getPreviousGate()  // BSANode quantum_port
      ->getPreviousGate()  // QNode quantum_port
      ->getPreviousGate()  // QNIC quantum port
      ->getOwnerModule()
      ->par("self_qnic_index");
}

simtime_t BSAController::getPredictedTravelTimeFromPort(int port) {
  cChannel *channel;
  double distance = 0;  // Initialization to avoid complaints
  double speed_of_light_in_channel = 1;
  // this port connects to internal QNIC
  // since only port 0 is supposed to be connected to internal QNIC
  if (port == 0 && (strcmp(getParentModule()->getName(), "qnic_r") == 0 || strcmp(getParentModule()->getName(), "qnic_rp") == 0)) {
    return 0;
  } else {
    // this port connects to outside QNode
    channel = getParentModule()->getSubmodule("bsa")->gate("quantum_port$i", port)->getIncomingTransmissionChannel();
  }

  if (FSChannel *FS_chl = dynamic_cast<FSChannel *>(channel)) {
    speed_of_light_in_channel = FS_chl->par("speed_of_light_in_FS").doubleValue();  // km/sec

    // I need to predict where the satellite is going to be when emission starts. If I send the notification now, that's distance(simTime() + travel_time).
    double current_distance = FS_chl->getDistanceAtTime(simTime());
    simtime_t current_travel_time = SimTime(current_distance / speed_of_light_in_channel);

    double predicted_distance = FS_chl->getDistanceAtTime(simTime() + current_travel_time);
    double offset = (predicted_distance - current_distance) / speed_of_light_in_channel;

    // distance = FS_chl->getDistanceAtTime(simTime());
    return SimTime(current_distance / speed_of_light_in_channel) + offset;

  } else {
    distance = channel->par("distance").doubleValue();  // km
    speed_of_light_in_channel = channel->par("speed_of_light_in_fiber").doubleValue();
    return SimTime(distance / speed_of_light_in_channel);
  }
}

simtime_t BSAController::getCurrentTravelTimeFromPort(int port) {
  cChannel *channel;
  double distance = 0;  // Initialization to avoid complaints
  double speed_of_light_in_channel = 1;
  // this port connects to internal QNIC
  // since only port 0 is supposed to be connected to internal QNIC
  if (port == 0 && (strcmp(getParentModule()->getName(), "qnic_r") == 0 || strcmp(getParentModule()->getName(), "qnic_rp") == 0)) {
    return 0;
  } else {
    // this port connects to outside QNode
    channel = getParentModule()->getSubmodule("bsa")->gate("quantum_port$i", port)->getIncomingTransmissionChannel();
  }

  if (FSChannel *FS_chl = dynamic_cast<FSChannel *>(channel)) {
    speed_of_light_in_channel = FS_chl->par("speed_of_light_in_FS").doubleValue();  // km/sec
    distance = FS_chl->getDistanceAtTime(simTime());

  } else {
    distance = channel->par("distance").doubleValue();  // km
    speed_of_light_in_channel = channel->par("speed_of_light_in_fiber").doubleValue();
  }
  return SimTime(distance / speed_of_light_in_channel);
}

BSAController::QNicInfo BSAController::getExternalQNICInfoFromPort(int port) {
  return QNicInfo{.type = QNIC_E, .index = getExternalQNICIndexFromPort(port), .parent_node_addr = getExternalAdressFromPort(port)};
}

void BSAController::cancelBSMTimeOut() {
  cancelEvent(time_out_message);
  time_out_count = 0;
}

}  // namespace quisp::modules
