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
  frequency = par("frequency");
  address = getParentModule()->par("address").intValue();
  timing_buffer = par("timing_buffer").doubleValue();
  speed_of_light_in_channel = par("speed_of_light_in_fiber").doubleValue();
  left_qnic_addr = getExternalAdressFromPort(0);
  right_qnic_addr = getExternalAdressFromPort(1);
  left_travel_time = getTravelTimeFromPort(0);
  right_travel_time = getTravelTimeFromPort(1);
  checkNeighborsBSACapacity();
}

void EPPSController::handleMessage(cMessage *msg) {
  if (msg == generatePacket) {
    EPPStimingNotifier *left_pk, *right_pk;
    left_pk = generateNotifier(left_travel_time, left_qnic_addr);
    right_pk = generateNotifier(right_travel_time, right_qnic_addr);
    send(left_pk, "to_router");  // send to port out. connected to local routing module (routing.localIn).
    send(right_pk, "to_router");
    startPump();
  } else if (dynamic_cast<EmitPhotonRequest *>(msg)) {
    epps->emitPhotons();
    SchedulePhotonTransmissionsOnebyOne *st = new SchedulePhotonTransmissionsOnebyOne("SchedulePhotonTransmissionsOneByOne");
    scheduleAt(simTime() + max_acceptance_rate, st);
  } else if (dynamic_cast<SchedulePhotonTransmissionsOnebyOne *>(msg)) {
    epps->emitPhotons();
    SchedulePhotonTransmissionsOnebyOne *st = new SchedulePhotonTransmissionsOnebyOne("SchedulePhotonTransmissionsOneByOne");
    scheduleAt(simTime() + max_acceptance_rate, st);
  }
  delete msg;
}

void EPPSController::startPump() {
  // for(int i=0; i<max_buffer; i++){
  //   emt = new  EmitPhotonRequest();
  //   scheduleAt(simTime()+timing_buffer+(max_accepted_rate*i), emt);
  // }
  emt = new EmitPhotonRequest("EmitPhotonRequest");
  scheduleAt(simTime() + timing_buffer + max_acceptance_rate, emt);
}

EPPStimingNotifier *EPPSController::generateNotifier(double time_to_travel, int dest_addr) {
  EPPStimingNotifier *pk = new EPPStimingNotifier("EppsTimingNotifier");
  pk->setTiming_at(timing_buffer + time_to_travel);
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

double EPPSController::getTravelTimeFromPort(int port) {
  cChannel *channel = getParentModule()->getSubmodule("bsa")->gate("quantum_port$i", port)->getIncomingTransmissionChannel();
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
