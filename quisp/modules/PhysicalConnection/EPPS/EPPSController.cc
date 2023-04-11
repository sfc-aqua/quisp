/** \file EPPSController.cc
 *
 *  \brief EPPSController
 */
#include "EPPSController.h"
#include <PhotonicQubit_m.h>
#include <messages/classical_messages.h>
#include <omnetpp.h>
#include <vector>
#include "messages/QNode_ipc_messages_m.h"
#include "modules/QNIC.h"
#include "omnetpp/cmessage.h"
#include "omnetpp/csimulation.h"
#include "omnetpp/simtime.h"
using namespace omnetpp;

namespace quisp::modules {

Define_Module(EPPSController);

EPPSController::EPPSController() : provider(utils::ComponentProvider{this}) {}

EPPSController::~EPPSController() {}

void EPPSController::finish() { std::cout << "last EPPS message that was sent " << last_result_send_time << "\n"; }

void EPPSController::initialize() {
  epps = check_and_cast<EntangledPhotonPairSource *>(getParentModule()->getSubmodule("epps"));
  frequency = par("frequency");
  address = getParentModule()->par("address").intValue();
  left_addr = getExternalAdressFromPort(0);
  right_addr = getExternalAdressFromPort(1);
  left_qnic_index = getExternalQNICIndexFromPort(0);
  right_qnic_index = getExternalQNICIndexFromPort(1);
  left_travel_time = getTravelTimeFromPort(0);
  right_travel_time = getTravelTimeFromPort(1);
  number_of_sent_photons = 0;
  time_out_count = 0;
  checkNeighborsBSACapacity();
  checkNeighborsBuffer();
  time_out_message = new EPPSNotificationTimeout();
  first_notification_timer = par("initial_notification_timing_buffer").doubleValue();
  scheduleAt(first_notification_timer, time_out_message);
}

void EPPSController::handleMessage(cMessage *msg) {
  if (dynamic_cast<EmitPhotonRequest *>(msg)) {
    if (number_of_sent_photons == 0) {
      epps->emitPhotons(1);
      number_of_sent_photons++;
      scheduleAt(simTime() + max_acceptance_rate, msg);
    } else if (number_of_sent_photons == number_of_photons - 1) {  // sending out last photon
      epps->emitPhotons(2);
      delete (msg);

      // Is this intended behavior?
      // set timeout to be twice the travel time plus number of no response
      time_out_count++;
      scheduleAt(simTime() + (2 + time_out_count) * (std::max(left_travel_time, right_travel_time)), time_out_message);

      number_of_sent_photons = 0;
    } else {
      epps->emitPhotons(0);
      number_of_sent_photons++;
      scheduleAt(simTime() + max_acceptance_rate, msg);
    }
  } else if (msg == time_out_message) {
    last_result_send_time = simTime();
    EPPSTimingNotification *left_pk = generateNotifier(true);
    EPPSTimingNotification *right_pk = generateNotifier(false);
    send(left_pk, "to_router");
    send(right_pk, "to_router");
    EmitPhotonRequest *emt = new EmitPhotonRequest();
    scheduleAt(simTime() + 2 * std::max(left_travel_time, right_travel_time), emt);
  }
  return;
}

EPPSTimingNotification *EPPSController::generateNotifier(bool is_left) {
  EPPSTimingNotification *pk = new EPPSTimingNotification("EPPSTimingNotification");
  pk->setQnicParentAddr(is_left ? left_addr : right_addr);
  pk->setQnicIndex(is_left ? left_qnic_index : right_qnic_index);
  pk->setQnicType(QNIC_RP);
  pk->setOtherQnicParentAddr(is_left ? right_addr : left_addr);
  pk->setOtherQnicIndex(is_left ? right_qnic_index : left_qnic_index);
  pk->setOtherQnicType(QNIC_RP);
  pk->setFirstPhotonEmitTime(simTime().dbl() + 2 * (is_left ? left_travel_time : right_travel_time));
  pk->setKind(4);
  pk->setInterval(max_acceptance_rate);
  pk->setSrcAddr(address);
  pk->setDestAddr(is_left ? left_addr : right_addr);
  pk->setTravelTime(is_left ? left_travel_time : right_travel_time);
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
  max_acceptance_rate = (double)1 / (double)min_photon_detection_per_second;
  // Adjust pump frequency to the lower BSA detection rate by neighbors.
  // if detection rate is better than emission rate.
  double pump_rate = (double)1 / (double)frequency;
  if (pump_rate < max_acceptance_rate) max_acceptance_rate = pump_rate;
}

void EPPSController::checkNeighborsBuffer() {
  int left_buffer = getParentModule()
                        ->getSubmodule("epps")
                        ->gate("quantum_port$i", 0)
                        ->getPreviousGate()  // EPPSNode quantum_port
                        ->getPreviousGate()  // QNode quantum_port
                        ->getOwnerModule()  // QNode
                        ->par("buffers");
  int right_buffer = getParentModule()
                         ->getSubmodule("epps")
                         ->gate("quantum_port$i", 1)
                         ->getPreviousGate()  // EPPSNode quantum_port
                         ->getPreviousGate()  // QNode quantum_port
                         ->getOwnerModule()  // QNode
                         ->par("buffers");
  number_of_photons = std::min(left_buffer, right_buffer);
}

double EPPSController::getTravelTimeFromPort(int port) {
  cChannel *channel = getParentModule()->getSubmodule("epps")->gate("quantum_port$i", port)->getIncomingTransmissionChannel();
  double distance = channel->par("distance").doubleValue();
  double speed_of_light_in_channel = channel->par("speed_of_light_in_fiber");
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
