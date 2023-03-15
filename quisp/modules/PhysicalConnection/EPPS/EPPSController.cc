/** \file EPPSController.cc
 *
 *  \brief EPPSController
 */
#include <PhotonicQubit_m.h>
#include <messages/classical_messages.h>
#include <omnetpp.h>
#include <vector>

#include "EntangledPhotonPairSource.h"
#include "EPPSController.h"
#include "modules/QNIC.h"
using namespace omnetpp;

namespace quisp::modules{

Define_Module(EPPSController);

EPPSController::EPPSController() : provider(utils::ComponentProvider{this}) {}

EPPSController::~EPPSController() {}

void EPPSController::initialize() {
  epps = check_and_cast<EntangledPhotonPairSource *>(getParentModule()->getSubmodule("epps"));
  frequency = par("frequency");
  address = getParentModule()->par("address").intValue();
  first_notification_timer = par("first_notification_timer").doubleValue();
  left_qnic_addr = getExternalAdressFromPort(0);
  right_qnic_addr = getExternalAdressFromPort(1);
  left_travel_time = getTravelTimeFromPort(0);
  right_travel_time = getTravelTimeFromPort(1);
  number_of_sent_photons = 0;
  checkNeighborsBSACapacity();
  checkNeighborsBuffer();
  startPump();
}

void EPPSController::handleMessage(cMessage *msg) {
  auto emt = dynamic_cast<EmitPhotonRequest *>(msg);
  if (number_of_sent_photons == 0) {
    EPPStimingNotifier *left_pk, *right_pk;
    left_pk = generateNotifier(left_travel_time, left_qnic_addr);
    right_pk = generateNotifier(right_travel_time, right_qnic_addr);
    send(left_pk, "to_router");  // send to port out. connected to local routing module (routing.localIn).
    send(right_pk, "to_router");
    epps->emitPhotons(1);
    number_of_sent_photons++;
    emt->setFirst(false);
    scheduleAt(simTime() + max_acceptance_rate, emt);
  } else if (number_of_sent_photons == number_of_photons - 1){ // sending out last photon
    epps->emitPhotons(2);
    number_of_sent_photons++;
    scheduleAt(simTime() + max_acceptance_rate, emt);
  } else {
    epps->emitPhotons(0);
    number_of_sent_photons++;
    scheduleAt(simTime() + max_acceptance_rate, emt);
  }
  delete msg;
}

void EPPSController::startPump() {
  EmitPhotonRequest *emt = new EmitPhotonRequest();
  scheduleAt(simTime() + first_notification_timer, emt);
}

EPPStimingNotifier *EPPSController::generateNotifier(double time_to_travel, int dest_addr) {
  EPPStimingNotifier *pk = new EPPStimingNotifier("EppsTimingNotifier");
  pk->setTiming_at(first_notification_timer + time_to_travel);
  pk->setKind(4);
  pk->setInterval(max_acceptance_rate);
  pk->setSrcAddr(address);
  pk->setDestAddr(dest_addr);
  return pk;
}

void EPPSController::checkNeighborsBSACapacity() {
  int left_photon_detection_per_second = getParentModule()
      ->getSubmodule("epps")
      ->gate("quantum_port$i", 1)
      ->getPreviousGate()  // EPPSNode quantum_port
      ->getPreviousGate()  // QNode quantum_port
      ->getPreviousGate() // qnic_rp quantum_port
      ->getOwnerModule() // qnic_rp
      ->getSubmodule("bsa") // BellStateAnalyzer
      ->par("photon_detection_per_second");
  int right_photon_detection_per_second = getParentModule()
      ->getSubmodule("epps")
      ->gate("quantum_port$i", 1)
      ->getPreviousGate()  // EPPSNode quantum_port
      ->getPreviousGate()  // QNode quantum_port
      ->getPreviousGate() // qnic_rp quantum_port
      ->getOwnerModule() // qnic_rp
      ->getSubmodule("bsa") // BellStateAnalyzer
      ->par("photon_detection_per_second");
  int min_photon_detection_per_second = std::min(left_photon_detection_per_second, right_photon_detection_per_second);
  max_acceptance_rate = (double)1 / (double)min_photon_detection_per_second;
  // Adjust pump frequency to the lower BSA detection rate by neighbors.
  // if detection rate is better than emission rate.
  double pump_rate = (double)1 / (double)frequency;
  if (pump_rate < max_acceptance_rate) max_acceptance_rate = pump_rate;
}

void EPPSController::checkNeighborsBuffer(){
  int left_buffer = getParentModule()
    ->getSubmodule("epps")
    ->gate("quantum_port$i", 0)
    ->getPreviousGate()  // EPPSNode quantum_port
    ->getPreviousGate()  // QNode quantum_port
    ->getOwnerModule() // QNode
    ->par("buffer");
  int right_buffer = getParentModule()
    ->getSubmodule("epps")
    ->gate("quantum_port$i", 1)
    ->getPreviousGate()  // EPPSNode quantum_port
    ->getPreviousGate()  // QNode quantum_port
    ->getOwnerModule() // QNode
    ->par("buffer");
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
      ->getPreviousGate()  // QNode quantum_port
      ->getOwnerModule()  // QNode
      ->par("address");
}

}  // namespace quisp::modules
