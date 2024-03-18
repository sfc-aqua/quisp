/** \file EPPSController.cc
 *
 *  \brief EPPSController
 */
#include "EPPSController.h"
#include <PhotonicQubit_m.h>
#include <messages/classical_messages.h>
#include <omnetpp.h>
#include <cfloat>
#include <cmath>
#include <vector>
#include "messages/QNode_ipc_messages_m.h"
#include "messages/link_generation_messages_m.h"
#include "modules/QNIC.h"
#include "omnetpp/cmessage.h"
#include "omnetpp/csimulation.h"
#include "omnetpp/simtime.h"
#include "omnetpp/simtime_t.h"
using namespace omnetpp;

namespace quisp::modules {

Define_Module(EPPSController);

EPPSController::EPPSController() : provider(utils::ComponentProvider{this}) {}

EPPSController::~EPPSController() {}

void EPPSController::finish() { std::cout << "last EPPS message that was sent " << last_result_send_time << "\n"; }

void EPPSController::initialize() {
  epps = check_and_cast<EntangledPhotonPairSource *>(getParentModule()->getSubmodule("epps"));
  address = getParentModule()->par("address").intValue();
  left_addr = getExternalAdressFromPort(0);
  right_addr = getExternalAdressFromPort(1);
  left_qnic_index = getExternalQNICIndexFromPort(0);
  right_qnic_index = getExternalQNICIndexFromPort(1);
  left_travel_time = getTravelTimeFromPort(0);
  right_travel_time = getTravelTimeFromPort(1);
  time_out_count = 0;
  emission_stopped = false;
  setEPPSFrequency();
  time_out_message = new EPPSNotificationTimeout();
  simtime_t first_notification_timer = par("initial_notification_timing_buffer").doubleValue();
  scheduleAt(first_notification_timer, time_out_message);
}

void EPPSController::handleMessage(cMessage *msg) {
  if (auto *pk = dynamic_cast<EmitPhotonRequest *>(msg)) {
    epps->emitPhotons();
    scheduleAt(simTime() + pk->getIntervalBetweenPhotons(), pk);
    return;
  } else if (msg == time_out_message) {
    last_result_send_time = simTime();
    emit_time = simTime() + 2 * std::max(left_travel_time, right_travel_time);
    EPPSTimingNotification *left_pk = generateNotifier(true);
    EPPSTimingNotification *right_pk = generateNotifier(false);
    send(left_pk, "to_router");
    send(right_pk, "to_router");
    emit_req = new EmitPhotonRequest();
    emit_req->setIntervalBetweenPhotons(time_interval_between_photons);
    scheduleAt(emit_time, emit_req);
  } else if (dynamic_cast<StopEPPSEmission *>(msg)) {
    if (!emission_stopped) {
      cancelAndDelete(emit_req);
      emission_stopped = true;
    }
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
  pk->setFirstPhotonEmitTime(emit_time + (is_left ? left_travel_time : right_travel_time));
  pk->setKind(4);
  pk->setInterval(time_interval_between_photons);
  pk->setSrcAddr(address);
  pk->setDestAddr(is_left ? left_addr : right_addr);
  pk->setTotalTravelTime(left_travel_time + right_travel_time);
  return pk;
}

void EPPSController::setEPPSFrequency() {
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
  int left_memory_size = getParentModule()
                             ->getSubmodule("epps")
                             ->gate("quantum_port$i", 0)
                             ->getPreviousGate()  // EPPSNode quantum_port
                             ->getPreviousGate()  // QNode quantum_port_receiver_passive
                             ->getPreviousGate()  // QNIC quantum_port
                             ->getOwnerModule()  // QNIC
                             ->par("num_buffer");
  int right_memory_size = getParentModule()
                              ->getSubmodule("epps")
                              ->gate("quantum_port$i", 1)
                              ->getPreviousGate()  // EPPSNode quantum_port
                              ->getPreviousGate()  // QNode quantum_port_receiver_passive
                              ->getPreviousGate()  // QNIC quantum_port
                              ->getOwnerModule()  // QNIC
                              ->par("num_buffer");
  double left_success_prob = getBSASuccessProbability(0);
  double right_success_prob = getBSASuccessProbability(1);
  double min_photon_detection_per_second_bsa = std::min(left_photon_detection_per_second, right_photon_detection_per_second);
  double max_photon_detection_per_second_epps = par("max_photon_emission_per_second").doubleValue();
  // if adaptive epps option is enabled, the frequency is determined by our previous results.
  bool adaptive_epps = par("adaptive_epps").boolValue();
  double frequency_epps = DBL_MAX;
  if (adaptive_epps) {
    frequency_epps = std::min(left_memory_size / (2 * left_travel_time.dbl() * left_success_prob), right_memory_size / (2 * right_travel_time.dbl() * right_success_prob));
  }
  // However if that value is larger than the minimum photon detection rate of BSA, or/and maximum photon emission rate of EPPS, we use the smallest value of those.
  if (min_photon_detection_per_second_bsa < frequency_epps) {
    frequency_epps = min_photon_detection_per_second_bsa;
  }
  if (max_photon_detection_per_second_epps < frequency_epps) {
    frequency_epps = max_photon_detection_per_second_epps;
  }
  time_interval_between_photons = (double)1 / frequency_epps;
  return;
}

double EPPSController::getTravelTimeFromPort(int port) {
  cChannel *channel = getParentModule()->getSubmodule("epps")->gate("quantum_port$i", port)->getIncomingTransmissionChannel();
  double distance = channel->par("distance").doubleValue();
  double speed_of_light_in_fiber = channel->par("speed_of_light_in_fiber");
  return distance / speed_of_light_in_fiber;
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

double EPPSController::getBSASuccessProbability(int port) {
  double collection_efficiency = getParentModule()
                                     ->getSubmodule("epps")
                                     ->gate("quantum_port$i", port)
                                     ->getPreviousGate()  // EPPSNode quantum_port
                                     ->getPreviousGate()  // QNode quantum_port_receiver_passive
                                     ->getPreviousGate()  // QNIC quantum_port
                                     ->getOwnerModule()  // QNIC
                                     ->getSubmodule("bsa")  // BellStateAnalyzer
                                     ->par("collection_efficiency");

  double detection_efficiency = getParentModule()
                                    ->getSubmodule("epps")
                                    ->gate("quantum_port$i", port)
                                    ->getPreviousGate()  // EPPSNode quantum_port
                                    ->getPreviousGate()  // QNode quantum_port_receiver_passive
                                    ->getPreviousGate()  // QNIC quantum_port
                                    ->getOwnerModule()  // QNIC
                                    ->getSubmodule("bsa")  // BellStateAnalyzer
                                    ->par("detection_efficiency");
  cChannel *channel = getParentModule()->getSubmodule("epps")->gate("quantum_port$i", port)->getIncomingTransmissionChannel();
  double distance = channel->par("distance").doubleValue();
  double fiber_attenuation = exp(-distance / 21);
  return collection_efficiency * detection_efficiency * fiber_attenuation * 0.5;
}

}  // namespace quisp::modules
