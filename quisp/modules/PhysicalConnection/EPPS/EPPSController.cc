/** \file EPPSController.cc
 *
 *  \brief EPPSController
 */
#include "EPPSController.h"
#include <PhotonicQubit_m.h>
#include <messages/classical_messages.h>
#include <omnetpp.h>
#include <utility>
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
  } else if (auto combined_result = dynamic_cast<CombinedBatchClickEventResults *>(msg)) {
    handleCombinedBatchClickEventResults(combined_result);
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

void EPPSController::handleCombinedBatchClickEventResults(CombinedBatchClickEventResults *combined_result) {
  auto left_right_addr_pair = std::make_pair(left_qnic_index, right_qnic_index);
    if (combined_result->getSrcAddr() == left_addr) {
    for (int index = 0; index < combined_result->numberOfClicks(); index++) {
      msm_info_map[left_right_addr_pair].left_clicks.emplace_back(combined_result->getClickResults(index));
    }
  } else if (combined_result->getSrcAddr() == right_addr) {
    for (int index = 0; index < combined_result->numberOfClicks(); index++) {
      msm_info_map[left_right_addr_pair].right_clicks.emplace_back(combined_result->getClickResults(index));
    }
  }
  if (!msm_info_map[left_right_addr_pair].left_clicks.empty() && !msm_info_map[left_right_addr_pair].right_clicks.empty()) {
    sendCombinedBSAresults(left_right_addr_pair);
  }
  return;
}

void EPPSController::sendCombinedBSAresults(std::pair<int, int> left_right_addr_pair) {
  CombinedBSAresults *left_bsa_results = new CombinedBSAresults();
  left_bsa_results->setSrcAddr(address);
  left_bsa_results->setDestAddr(left_addr);
  left_bsa_results->setQnicIndex(left_qnic_index);
  left_bsa_results->setQnicType(QNIC_RP);
  left_bsa_results->setNeighborAddress(msm_info_map[left_right_addr_pair].address);
  left_bsa_results->setIsPureBSAResult(true);
  CombinedBSAresults *right_bsa_results = new CombinedBSAresults();
  right_bsa_results->setSrcAddr(address);
  right_bsa_results->setDestAddr(right_addr);
  right_bsa_results->setQnicIndex(right_qnic_index);
  right_bsa_results->setQnicType(QNIC_RP);
  right_bsa_results->setNeighborAddress(msm_info_map[left_right_addr_pair].address);
  left_bsa_results->setIsPureBSAResult(true);
  for (int index = 0; index < msm_info_map[left_right_addr_pair].left_clicks.size(); index++) {
    if (!msm_info_map[left_right_addr_pair].left_clicks.at(index).success || !msm_info_map[left_right_addr_pair].right_clicks.at(index).success) continue;
    bool is_phi_minus = msm_info_map[left_right_addr_pair].left_clicks.at(index).correction_operation != msm_info_map[left_right_addr_pair].right_clicks.at(index).correction_operation;
    left_bsa_results->appendSuccessIndex(index);
    left_bsa_results->appendCorrectionOperation(is_phi_minus ? PauliOperator::Z : PauliOperator::I);
    right_bsa_results->appendSuccessIndex(index);
    right_bsa_results->appendCorrectionOperation(PauliOperator::I);
  }
  msm_info_map[left_right_addr_pair].left_clicks.clear();
  msm_info_map[left_right_addr_pair].right_clicks.clear();
  send(left_bsa_results, "to_router");
  send(right_bsa_results, "to_router");
  return;
}

EPPSTimingNotification *EPPSController::generateNotifier(bool is_left) {
  EPPSTimingNotification *pk = new EPPSTimingNotification("EPPSTimingNotification");
  pk->setEppsAddr(address);
  pk->setQnicIndex(is_left ? left_qnic_index : right_qnic_index);
  pk->setQnicType(QNIC_RP);
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
