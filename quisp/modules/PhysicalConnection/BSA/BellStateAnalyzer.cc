/** \file BellStateAnalyzer.cc
 *
 *  \brief BellStateAnalyzer
 */
#include "BellStateAnalyzer.h"

#include <omnetpp/cexception.h>
#include <vector>

using namespace omnetpp;
using namespace quisp::messages;
using namespace quisp::physical::types;

namespace quisp::modules {

/** @class BellStateAnalyzer BellStateAnalyzer.cc
 *
 *  @brief BellStateAnalyzer
 */
Define_Module(BellStateAnalyzer);

BellStateAnalyzer::BellStateAnalyzer() : provider(utils::ComponentProvider{this}) {}

void BellStateAnalyzer::initialize() {
  state = BSAState::Idle;
  darkcount_probability = par("darkcount_probability").doubleValue();
  detection_efficiency = par("detection_efficiency").doubleValue();
  indistinguishability_window = SimTime(par("indistinguishable_time_window").doubleValue() * 1000, SIMTIME_PS);
  collection_efficiency = par("collection_efficiency").doubleValue();
  backend = provider.getQuantumBackend();
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
  if (photon.is_first) {
    if (state == BSAState::Idle && photon.from_port == PortNumber::First) {
      state = BSAState::FirstPortArrive;
    } else if (state == BSAState::Idle && photon.from_port == PortNumber::Second) {
      state = BSAState::SecondPortArrive;
    } else if (state == BSAState::FirstPortArrive && photon.from_port == PortNumber::Second) {
      state = BSAState::Accepting;
      send(new CancelBSMTimeOutMsg(), "to_bsa_controller");
    } else if (state == BSAState::SecondPortArrive && photon.from_port == PortNumber::First) {
      state = BSAState::Accepting;
      send(new CancelBSMTimeOutMsg(), "to_bsa_controller");
    } else if (state == BSAState::AcceptingFirstPort && photon.from_port == PortNumber::First) {
      send(new CancelBSMTimeOutMsg(), "to_bsa_controller");
    } else if (state == BSAState::AcceptingSecondPort && photon.from_port == PortNumber::Second) {
      send(new CancelBSMTimeOutMsg(), "to_bsa_controller");
    } else {
      throw cRuntimeError("This should not happen; BSA state isn't set correctly.");
    }
  }

  if (photon.from_port == PortNumber::First)
    first_port_records.emplace_back(photon);
  else
    second_port_records.emplace_back(photon);

  if (!photon.is_last) {
    return;
  }

  if (state == BSAState::AcceptingFirstPort || state == BSAState::AcceptingSecondPort) {  // must be last photon
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
  auto *batch_click_msg = new BatchClickEvent();
  int number_of_possible_pairs = std::min(first_port_records.size(), second_port_records.size());
  for (int i = 0; i < number_of_possible_pairs; i++) {
    auto p = first_port_records[i];
    auto q = second_port_records[i];

    if (fabs(p.arrival_time - q.arrival_time) < indistinguishability_window) {
      batch_click_msg->appendClickResults(processIndistinguishPhotons(p, q));
    } else {
      batch_click_msg->appendClickResults({.success = false, .correction_operation = PauliOperator::I});
      discardPhoton(p);
      discardPhoton(q);
    }
  }
  first_port_records.clear();
  second_port_records.clear();
  send(batch_click_msg, "to_bsa_controller");
}

PhotonRecord BellStateAnalyzer::getPhotonRecordFromMessage(PhotonicQubit *photon_msg) {
  PhotonRecord photon{.qubit_ref = photon_msg->getQubitRefForUpdate(),
                      .arrival_time = photon_msg->getArrivalTime(),
                      .from_port = (photon_msg->arrivedOn("quantum_port$i", 0)) ? PortNumber::First : PortNumber::Second,
                      .is_lost = photon_msg->isLost(),
                      .is_first = photon_msg->isFirst(),
                      .is_last = photon_msg->isLast(),
                      .has_x_error = photon_msg->hasXError(),
                      .has_z_error = photon_msg->hasZError()};

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
    discardPhoton(p);
    discardPhoton(q);
    return {.success = true, .correction_operation = isPsiPlus ? PauliOperator::X : PauliOperator::Y};
  }

  discardPhoton(p);
  discardPhoton(q);
  return {.success = false, .correction_operation = PauliOperator::I};
}

void BellStateAnalyzer::resetState() {
  state = BSAState::Idle;
  first_port_records.clear();
  second_port_records.clear();
}

void BellStateAnalyzer::validateProperties() {
  // currently we only allow 2 port BSA
  if (this->gateSize("quantum_port") != 2) {
    throw std::runtime_error("BellStateAnalyzer::parameter validation fail; BSA doesn't have 2 input quantum ports");
  }
  // validating parameters
  if (darkcount_probability < 0 || darkcount_probability > 1)
    throw std::runtime_error("BellStateAnalyzer::parameter validation fail; darkcount_probability does not in the [0, 1] range");
  if (detection_efficiency < 0 || detection_efficiency > 1)
    throw std::runtime_error("BellStateAnalyzer::parameter validation fail; detection_efficiency does not in the [0, 1] range");
  if (indistinguishability_window < 0) throw std::runtime_error("BellStateAnalyzer::parameter validation fail; indistinguishability_window cannot be lower than 0");
  if (collection_efficiency < 0 || collection_efficiency > 1)
    throw std::runtime_error("BellStateAnalyzer::parameter validation fail; collection_efficiency does not in the [0, 1] range");
}

void BellStateAnalyzer::measureSuccessfully(PhotonRecord &p, PhotonRecord &q, bool is_psi_plus) {
  auto p_ref = p.qubit_ref;
  auto q_ref = q.qubit_ref;

  if (p.has_x_error && p.has_z_error)
    y_error_count++;
  else if (p.has_x_error)
    x_error_count++;
  else if (p.has_z_error)
    z_error_count++;
  else
    no_error_count++;

  if (q.has_x_error && q.has_z_error)
    y_error_count++;
  else if (q.has_x_error)
    x_error_count++;
  else if (q.has_z_error)
    z_error_count++;
  else
    no_error_count++;

  p_ref->noiselessX();
  if (!is_psi_plus) {
    p_ref->noiselessZ();
  }
  p_ref->noiselessCNOT(q_ref);
  p_ref->noiselessMeasureX(backends::abstract::EigenvalueResult::PLUS_ONE);
  q_ref->noiselessMeasureZ(backends::abstract::EigenvalueResult::PLUS_ONE);
}

void BellStateAnalyzer::finish() {
  std::cout << "BSA Statistics (raw):\n";
  std::cout << "    " << no_error_count << ' ' << x_error_count << ' ' << y_error_count << ' ' << z_error_count << '\n';
}

void BellStateAnalyzer::discardPhoton(PhotonRecord &photon) { photon.qubit_ref->relaseBackToPool(); };

}  // namespace quisp::modules
