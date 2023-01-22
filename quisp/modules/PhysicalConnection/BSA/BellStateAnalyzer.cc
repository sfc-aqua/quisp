/** \file BellStateAnalyzer.cc
 *  \authors cldurand,takaakimatsuo
 *
 *  \brief BellStateAnalyzer
 */
#include "BellStateAnalyzer.h"
#include <PhotonicQubit_m.h>
#include <omnetpp.h>
#include <stdexcept>
#include <vector>

using namespace omnetpp;
using namespace quisp::messages;

namespace quisp::modules {

/** @class BellStateAnalyzer BellStateAnalyzer.cc
 *
 *  @brief BellStateAnalyzer
 */
Define_Module(BellStateAnalyzer);

BellStateAnalyzer::BellStateAnalyzer() {}

void BellStateAnalyzer::initialize() {
  state = BSAState::Idle;
  darkcount_probability = par("darkcount_probability").doubleValue();
  detection_efficiency = par("detection_efficiency").doubleValue();
  indistinguishability_window = par("indistinguishable_time_window").doubleValue();
  collection_efficiency = par("collection_efficiency").doubleValue();
  controller = static_cast<BSAController *>(this->getParentModule()->getSubmodule("BSAController"));

  validateProperties();
}

/**
 * @brief Handle the flying photonic qubits coming in to the BSA.
 * If the two photons arrive at the same time (within indistinguishable time window),
 * it will be entangled. We assume that we can distinguish between Psi+/- while
 * we cannot Phi+/- cannot be distinguished. Gate operations will be applied on the photons.
 *
 * @param msg must be of type PhotonicQubit message
 */
void BellStateAnalyzer::handleMessage(cMessage *msg) {
  auto photon = getPhotonRecordFromMessage(static_cast<PhotonicQubit *>(msg));
  delete msg;

  // clang-format off
  if ((state == BSAState::Idle && !photon.is_first) ||
      (state == BSAState::AcceptingFirstPort && photon.from_port == PortNumber::Second) ||
      (state == BSAState::AcceptingSecondPort && photon.from_port == PortNumber::First)) {
    discardPhoton(photon);
    return;
  }
  // clang-format on

  if (state == BSAState::Idle) {  // must be first photon
    state = BSAState::Accepting;
  }

  if (photon.from_port == PortNumber::First)
    first_port_records.emplace_back(photon);
  else
    second_port_records.emplace_back(photon);

  if (!photon.is_last) {
    return;
  }

  if (state != BSAState::Accepting) {  // must be last photon
    state = BSAState::Idle;
    processPhotonRecords();
    return;
  }

  if (photon.from_port == PortNumber::First)
    state = BSAState::AcceptingSecondPort;
  else
    state = BSAState::AcceptingFirstPort;
}

void BellStateAnalyzer::processPhotonRecords() {
  int number_of_possible_pairs = std::min(first_port_records.size(), second_port_records.size());
  std::vector<BSAClickResult> results;
  for (int i = 0; i < number_of_possible_pairs; i++) {
    auto p = first_port_records[i];
    auto q = second_port_records[i];

    if (std::abs(p.arrival_time.dbl() - q.arrival_time.dbl()) < indistinguishability_window)
      results.emplace_back(processIndistinguishPhotons(p, q));
    else
      results.push_back({.success = false, .correction_operation = PauliOperator::I});
  }
  // TODO: process this at controller
  controller->registerClickBatches(results);
}

PhotonRecord BellStateAnalyzer::getPhotonRecordFromMessage(PhotonicQubit *photon_msg) {
  PhotonRecord photon{
      .qubit_ref = photon_msg->getQubitRefForUpdate(),
      .arrival_time = photon_msg->getArrivalTime(),
      .from_port = (photon_msg->arrivedOn("quantum_port", 0)) ? PortNumber::First : PortNumber::Second,
      .is_lost = photon_msg->isLost(),
      .is_first = photon_msg->isFirst(),
      .is_last = photon_msg->isLast(),
  };

  return photon;
}

BSAClickResult BellStateAnalyzer::processIndistinguishPhotons(PhotonRecord &p, PhotonRecord &q) {
  // although the photons get out of the fiber, we still need to roll the rng whether it will get collected by the detectors
  if (dblrand() > collection_efficiency) p.is_lost = true;
  if (dblrand() > collection_efficiency) q.is_lost = true;

  bool left_darkcount_click = dblrand() < darkcount_probability;
  bool right_darkcount_click = dblrand() < darkcount_probability;
  // false positive case
  if ((p.is_lost && left_darkcount_click && q.is_lost && right_darkcount_click) || (!p.is_lost && q.is_lost && right_darkcount_click) ||
      (p.is_lost && left_darkcount_click && !q.is_lost)) {
    discardPhoton(p);
    discardPhoton(q);
    // correction operation doesn't really matter but we still make it 50:50
    return {.success = true, .correction_operation = (dblrand() < 0.5) ? PauliOperator::X : PauliOperator::Y};
  }

  // we assume that only Psi+/- can de distinguished while we can't for Phi+/-
  bool isPsi = dblrand() < 0.5;
  bool left_click = dblrand() < detection_efficiency;
  bool right_click = dblrand() < detection_efficiency;
  if (!p.is_lost && !q.is_lost && isPsi && left_click && right_click) {
    bool isPsiPlus = dblrand() < 0.5;
    measureSuccessfully(p, q, isPsiPlus);
    return {.success = true, .correction_operation = isPsiPlus ? PauliOperator::X : PauliOperator::Y};
  }

  discardPhoton(p);
  discardPhoton(q);
  return {.success = false, .correction_operation = PauliOperator::I};
}

void BellStateAnalyzer::validateProperties() {
  // currently we only allow 2 port BSA
  if (this->gateSize("fromBSA_quantum_port$i") != 2) {
    throw std::runtime_error("BellStateAnalyzer::parameter validation fail; BSA doesn't have 2 input quantum ports");
  }
  // validating parameters
  if (darkcount_probability < 0 || darkcount_probability > 1)
    throw std::runtime_error("BellStateAnalyzer::parameter validation fail; darkcount_probability does not in the [0, 1] range");
  if (detection_efficiency < 0 || detection_efficiency > 1)
    throw std::runtime_error("BellStateAnalyzer::parameter validation fail; detection_efficiency does not in the [0, 1] range");
  if (indistinguishability_window < 0 || indistinguishability_window > 1)
    throw std::runtime_error("BellStateAnalyzer::parameter validation fail; indistinguishability_window does not in the [0, 1] range");
  if (collection_efficiency < 0 || collection_efficiency > 1)
    throw std::runtime_error("BellStateAnalyzer::parameter validation fail; collection_efficiency does not in the [0, 1] range");
  if (controller == nullptr) {
    throw std::runtime_error("BellStateAnalyzer::parameter validation fail; cannot find BSAController for this BSA");
  }
}

void BellStateAnalyzer::measureSuccessfully(PhotonRecord &p, PhotonRecord &q, bool is_psi_plus) {
  auto p_ref = p.qubit_ref;
  auto q_ref = q.qubit_ref;
  p_ref->noiselessX();
  if (is_psi_plus) p_ref->noiselessZ();
  q_ref->gateCNOT(p_ref);
  p_ref->noiselessMeasureX(backends::abstract::EigenvalueResult::PLUS_ONE);
  q_ref->noiselessMeasureZ(backends::abstract::EigenvalueResult::PLUS_ONE);
}

void BellStateAnalyzer::finish() {}

void BellStateAnalyzer::discardPhoton(PhotonRecord &photon) { photon.qubit_ref->noiselessMeasureZ(); };

}  // namespace quisp::modules
