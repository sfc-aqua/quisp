/** \file EPPSController.cc
 *
 *  \brief EPPSController
 */
#include "EPPSController.h"
#include <PhotonicQubit_m.h>
#include <messages/classical_messages.h>
#include <omnetpp.h>
#include <vector>
#include "channels/FSChannel.h"
#include "messages/QNode_ipc_messages_m.h"
#include "messages/link_generation_messages_m.h"
#include "modules/QNIC.h"
#include "omnetpp/cmessage.h"
#include "omnetpp/csimulation.h"
#include "omnetpp/simtime.h"

using namespace omnetpp;
using quisp::channels::FSChannel;

namespace quisp::modules {

Define_Module(EPPSController);

EPPSController::EPPSController() : provider(utils::ComponentProvider{this}) {}

EPPSController::~EPPSController() {}

void EPPSController::finish() { std::cout << "last EPPS message that was sent " << last_result_send_time << "\n"; }

void EPPSController::initialize() {
  epps = check_and_cast<EntangledPhotonPairSource *>(getParentModule()->getSubmodule("epps"));
  photon_emission_per_second = par("photon_emission_per_second");
  address = getParentModule()->par("address").intValue();
  left_addr = getExternalAdressFromPort(0);
  right_addr = getExternalAdressFromPort(1);
  left_qnic_index = getExternalQNICIndexFromPort(0);
  right_qnic_index = getExternalQNICIndexFromPort(1);
  // left_travel_time = getCurrentTravelTimeFromPort(0);
  // right_travel_time = getCurrentTravelTimeFromPort(1);
  time_out_count = 0;
  emission_stopped = false;
  checkNeighborsBSACapacity();
  time_out_message = new EPPSNotificationTimeout();
  simtime_t first_notification_timer = par("initial_notification_timing_buffer").doubleValue();
  scheduleAt(first_notification_timer, time_out_message);
  resync_delay = SimTime(par("SAT_resync_delay"));
  if (resync_delay > 0) {
    cMessage *resync = new cMessage("Resync");
    scheduleAt(first_notification_timer + resync_delay, resync);
  }
}

void EPPSController::handleMessage(cMessage *msg) {
  if (auto *pk = dynamic_cast<EmitPhotonRequest *>(msg)) {
    epps->emitPhotons();
    scheduleAt(simTime() + pk->getIntervalBetweenPhotons(), pk);
    return;
  } else if (msg == time_out_message) {
    left_travel_time = getCurrentTravelTimeFromPort(0);
    right_travel_time = getCurrentTravelTimeFromPort(1);
    local_emit_time = simTime() + std::max(left_travel_time, right_travel_time);
    left_travel_time_predicted = getPredictedTravelTimeFromPort(0);
    right_travel_time_predicted = getPredictedTravelTimeFromPort(1);

    last_result_send_time = simTime();
    EPPSTimingNotification *left_pk = generateNotifier(true);
    EPPSTimingNotification *right_pk = generateNotifier(false);
    send(left_pk, "to_router");
    send(right_pk, "to_router");
    emit_req = new EmitPhotonRequest();
    emit_req->setIntervalBetweenPhotons(time_interval_between_photons);
    scheduleAt(local_emit_time, emit_req);
  } else if (dynamic_cast<StopEPPSEmission *>(msg)) {
    if (!emission_stopped) {
      cancelAndDelete(emit_req);
      emission_stopped = true;
    }
  } else if (!strcmp(msg->getName(), "Resync")) {
    cancelAndDelete(emit_req);
    time_out_message = new EPPSNotificationTimeout();
    scheduleAt(simTime(), time_out_message);
    scheduleAfter(resync_delay, msg);
    return;
  }
  delete msg;
  return;
}

EPPSTimingNotification *EPPSController::generateNotifier(bool is_left) {
  EPPSTimingNotification *pk = new EPPSTimingNotification("EPPSTimingNotification");
  pk->setEPPSAddr(address);
  pk->setQnicParentAddr(is_left ? left_addr : right_addr);
  pk->setQnicIndex(is_left ? left_qnic_index : right_qnic_index);
  pk->setQnicType(QNIC_RP);
  pk->setOtherQnicParentAddr(is_left ? right_addr : left_addr);
  pk->setOtherQnicIndex(is_left ? right_qnic_index : left_qnic_index);
  pk->setOtherQnicType(QNIC_RP);
  pk->setFirstPhotonEmitTime(local_emit_time + (is_left ? left_travel_time_predicted : right_travel_time_predicted));
  pk->setKind(4);
  pk->setInterval(time_interval_between_photons);
  pk->setSrcAddr(address);
  pk->setDestAddr(is_left ? left_addr : right_addr);
  pk->setTotalTravelTime(left_travel_time_predicted + right_travel_time_predicted);
  return pk;
}

void EPPSController::checkNeighborsBSACapacity() {
  int left_photon_detection_per_second = getParentModule()
                                             ->getSubmodule("epps")
                                             ->gate("quantum_port$i", 0)
                                             ->getPreviousGate()  // EPPSNode quantum_port
                                             ->getPreviousGate()  // QNode quantum_port_receiver_passive
                                             ->getPreviousGate()  // QNIC quantum_port
                                             ->getOwnerModule()  // QNIC
                                             ->getSubmodule("bsa")  // BellStateAnalyzer
                                             ->par("photon_detection_per_second");
  int right_photon_detection_per_second = getParentModule()
                                              ->getSubmodule("epps")
                                              ->gate("quantum_port$i", 1)
                                              ->getPreviousGate()  // EPPSNode quantum_port
                                              ->getPreviousGate()  // QNode quantum_port_receiver_passive
                                              ->getPreviousGate()  // QNIC quantum_port
                                              ->getOwnerModule()  // QNIC
                                              ->getSubmodule("bsa")  // BellStateAnalyzer
                                              ->par("photon_detection_per_second");
  int min_photon_detection_per_second = std::min(left_photon_detection_per_second, right_photon_detection_per_second);
  time_interval_between_photons = (double)1 / (double)min_photon_detection_per_second;
  // If the photon_emission_per_second is higher than the capacity of the neighbor's BSA, the time interval between photons is adjusted to the capacity of the neighbor's BSA.
  // If not, the time interval between photons is adjusted to the photon_emission_per_second.
  simtime_t pump_rate = (double)1 / (double)photon_emission_per_second;
  if (pump_rate > time_interval_between_photons) time_interval_between_photons = pump_rate;
}

double EPPSController::getCurrentTravelTimeFromPort(int port) {
  cChannel *channel = getParentModule()->getSubmodule("epps")->gate("quantum_port$i", port)->getIncomingTransmissionChannel();
  double distance = 1;
  double speed_of_light_in_channel = 1;
  if (FSChannel *FS_chl = dynamic_cast<FSChannel *>(channel)) {  // free-space channel
    distance = FS_chl->getDistanceAtTime(simTime());
    speed_of_light_in_channel = FS_chl->par("speed_of_light_in_FS").doubleValue();  // km/sec
  } else {  // fiber channel
    distance = channel->par("distance").doubleValue();
    speed_of_light_in_channel = channel->par("speed_of_light_in_fiber");
  }
  return distance / speed_of_light_in_channel;
}

double EPPSController::getPredictedTravelTimeFromPort(int port) {
  cChannel *channel = getParentModule()->getSubmodule("epps")->gate("quantum_port$i", port)->getIncomingTransmissionChannel();
  double distance = 1;
  double speed_of_light_in_channel = 1;
  if (FSChannel *FS_chl = dynamic_cast<FSChannel *>(channel)) {
    speed_of_light_in_channel = FS_chl->par("speed_of_light_in_FS").doubleValue();  // km/sec

    // I need to predict where the satellite is going to be when emission starts. If I send the notification now, that's distance(simTime() + travel_time).
    // double current_distance = FS_chl->getDistanceAtTime(simTime());
    // simtime_t current_travel_time = SimTime(current_distance / speed_of_light_in_channel);

    double predicted_distance = FS_chl->getDistanceAtTime(local_emit_time);
    // double offset = (predicted_distance-current_distance)/speed_of_light_in_channel;

    // distance = FS_chl->getDistanceAtTime(simTime());
    return predicted_distance / speed_of_light_in_channel;  // + offset;

  } else {
    distance = channel->par("distance").doubleValue();  // km
    speed_of_light_in_channel = channel->par("speed_of_light_in_fiber").doubleValue();
  }

  return distance / speed_of_light_in_channel;
}

int EPPSController::getExternalAdressFromPort(int port) {
  return getParentModule()
      ->getSubmodule("epps")
      ->gate("quantum_port$i", port)
      ->getPreviousGate()  // EPPSNode quantum_port
      ->getPreviousGate()  // QNode quantum_port_receiver_passive
      ->getOwnerModule()  // QNode
      ->par("address");
}

int EPPSController::getExternalQNICIndexFromPort(int port) {
  return getParentModule()
      ->getSubmodule("epps")
      ->gate("quantum_port$i", port)
      ->getPreviousGate()  // EPPSNode quantum_port
      ->getPreviousGate()  // QNode quantum_port_receiver_passive
      ->getPreviousGate()  // QNIC quantum_port
      ->getOwnerModule()  // QNIC
      ->par("self_qnic_index");
}

}  // namespace quisp::modules
