/** \file StationaryQubit.cc
 *
 *  \brief StationaryQubit
 */
#include "StationaryQubit.h"

#include <PhotonicQubit_m.h>
#include <messages/classical_messages.h>
#include <omnetpp.h>
#include <stdexcept>
#include <unsupported/Eigen/KroneckerProduct>
#include <unsupported/Eigen/MatrixFunctions>
#include "backends/interfaces/IQubit.h"
#include "omnetpp/cexception.h"

using namespace Eigen;

using quisp::messages::PhotonicQubit;
using quisp::modules::qubit_id::QubitId;
using quisp::types::EigenvalueResult;
using quisp::types::MeasurementOutcome;
using quisp::types::MeasureXResult;
using quisp::types::MeasureYResult;
using quisp::types::MeasureZResult;

namespace quisp::modules {

Define_Module(StationaryQubit);

StationaryQubit::StationaryQubit() : provider(utils::ComponentProvider{this}) {}

/**
 * \brief Initialize StationaryQubit
 *
 * Omnet called method to initialize objects.
 *
 */
void StationaryQubit::initialize() {
  // read and set parameters
  emission_success_probability = par("emission_success_probability");

  // Get parameters from omnet
  stationary_qubit_address = par("stationary_qubit_address");
  node_address = par("node_address");
  qnic_address = par("qnic_address");
  qnic_type = par("qnic_type");
  qnic_index = par("qnic_index");
  emission_jittering_standard_deviation = par("emission_jittering_standard_deviation").doubleValue();

  /* e^(t/T1) energy relaxation, e^(t/T2) phase relaxation. Want to use only 1/10 of T1 and T2 in general.*/

  backend = provider.getQuantumBackend();
  auto config = prepareBackendQubitConfiguration(true);
  qubit_ref = backend->createQubit(new QubitId(node_address, qnic_index, qnic_type, stationary_qubit_address), std::move(config));
  if (qubit_ref == nullptr) throw std::runtime_error("qubit_ref nullptr error");
  setFree(false);

  // watch variables to show them in the GUI
  WATCH(emitted_time);
  WATCH(is_busy);
  WATCH(qubit_ref);
}

std::unique_ptr<IConfiguration> StationaryQubit::prepareBackendQubitConfiguration(bool overwrite) {
  auto conf = backend->getDefaultConfiguration();
  if (!overwrite) return conf;
  if (auto et_conf = dynamic_cast<backend::StationaryQubitConfiguration *>(conf.get())) {
    et_conf->measurement_x_err_rate = par("x_measurement_error_rate").doubleValue();
    et_conf->measurement_y_err_rate = par("y_measurement_error_rate").doubleValue();
    et_conf->measurement_z_err_rate = par("z_measurement_error_rate").doubleValue();

    et_conf->h_gate_err_rate = par("h_gate_error_rate").doubleValue();
    et_conf->h_gate_x_err_ratio = par("h_gate_x_error_ratio").doubleValue();
    et_conf->h_gate_y_err_ratio = par("h_gate_y_error_ratio").doubleValue();
    et_conf->h_gate_z_err_ratio = par("h_gate_z_error_ratio").doubleValue();

    et_conf->x_gate_err_rate = par("x_gate_error_rate").doubleValue();
    et_conf->x_gate_x_err_ratio = par("x_gate_x_error_ratio").doubleValue();
    et_conf->x_gate_y_err_ratio = par("x_gate_y_error_ratio").doubleValue();
    et_conf->x_gate_z_err_ratio = par("x_gate_z_error_ratio").doubleValue();

    et_conf->z_gate_err_rate = par("z_gate_error_rate").doubleValue();
    et_conf->z_gate_x_err_ratio = par("z_gate_x_error_ratio").doubleValue();
    et_conf->z_gate_y_err_ratio = par("z_gate_y_error_ratio").doubleValue();
    et_conf->z_gate_z_err_ratio = par("z_gate_z_error_ratio").doubleValue();

    et_conf->cnot_gate_err_rate = par("cnot_gate_error_rate").doubleValue();
    et_conf->cnot_gate_ix_err_ratio = par("cnot_gate_ix_error_ratio").doubleValue();
    et_conf->cnot_gate_iy_err_ratio = par("cnot_gate_iy_error_ratio").doubleValue();
    et_conf->cnot_gate_iz_err_ratio = par("cnot_gate_iz_error_ratio").doubleValue();
    et_conf->cnot_gate_xi_err_ratio = par("cnot_gate_xi_error_ratio").doubleValue();
    et_conf->cnot_gate_xx_err_ratio = par("cnot_gate_xx_error_ratio").doubleValue();
    et_conf->cnot_gate_xy_err_ratio = par("cnot_gate_xy_error_ratio").doubleValue();
    et_conf->cnot_gate_xz_err_ratio = par("cnot_gate_xz_error_ratio").doubleValue();
    et_conf->cnot_gate_yi_err_ratio = par("cnot_gate_yi_error_ratio").doubleValue();
    et_conf->cnot_gate_yx_err_ratio = par("cnot_gate_yx_error_ratio").doubleValue();
    et_conf->cnot_gate_yy_err_ratio = par("cnot_gate_yy_error_ratio").doubleValue();
    et_conf->cnot_gate_yz_err_ratio = par("cnot_gate_yz_error_ratio").doubleValue();
    et_conf->cnot_gate_zi_err_ratio = par("cnot_gate_zi_error_ratio").doubleValue();
    et_conf->cnot_gate_zx_err_ratio = par("cnot_gate_zx_error_ratio").doubleValue();
    et_conf->cnot_gate_zy_err_ratio = par("cnot_gate_zy_error_ratio").doubleValue();
    et_conf->cnot_gate_zz_err_ratio = par("cnot_gate_zz_error_ratio").doubleValue();

    et_conf->memory_x_err_rate = par("memory_x_error_rate").doubleValue();
    et_conf->memory_y_err_rate = par("memory_y_error_rate").doubleValue();
    et_conf->memory_z_err_rate = par("memory_z_error_rate").doubleValue();
    et_conf->memory_excitation_rate = par("memory_energy_excitation_rate").doubleValue();
    et_conf->memory_relaxation_rate = par("memory_energy_relaxation_rate").doubleValue();
    et_conf->memory_completely_mixed_rate = par("memory_completely_mixed_rate").doubleValue();
  }
  return conf;
}

void StationaryQubit::finish() {}

/**
 * \brief handle PhotonicQubit generated by StatinoryQubit itself
 *
 * \param msg is the PhotonicQubit message
 */
void StationaryQubit::handleMessage(cMessage *msg) {
  if (!msg->isSelfMessage()) {
    throw cRuntimeError("StationaryQubit::handleMessage: message from outside is not expected");
  }
  bubble("Got a photon!!");
  setBusy();
  double rand = dblrand();
  if (rand < (1 - emission_success_probability)) {
    PhotonicQubit *pk = check_and_cast<PhotonicQubit *>(msg);
    pk->setLost(true);
    send(pk, "tolens_quantum_port");
  } else {
    send(msg, "tolens_quantum_port");
  }
}

EigenvalueResult StationaryQubit::measureX() { return qubit_ref->measureX(); }

EigenvalueResult StationaryQubit::measureY() { return qubit_ref->measureY(); }

EigenvalueResult StationaryQubit::measureZ() { return qubit_ref->measureZ(); }

void StationaryQubit::gateHadamard() { qubit_ref->gateH(); }

void StationaryQubit::gateX() { qubit_ref->gateX(); }

void StationaryQubit::gateZ() { qubit_ref->gateZ(); }

void StationaryQubit::gateY() { qubit_ref->gateY(); }

void StationaryQubit::gateS() { qubit_ref->gateS(); }

void StationaryQubit::gateSdg() { qubit_ref->gateSdg(); }

void StationaryQubit::gateCNOT(IStationaryQubit *target_qubit) { qubit_ref->gateCNOT(check_and_cast<StationaryQubit *>(target_qubit)->qubit_ref); }

// This is invoked whenever a photon is emitted out from this particular qubit.
void StationaryQubit::setBusy() {
  is_busy = true;
  emitted_time = simTime();
  if (hasGUI()) {
    getDisplayString().setTagArg("i", 1, "red");
  }
}

// Re-initialization of this stationary qubit
// This is called at the beginning of the simulation (in initialization() above), and whenever it is reinitialized via the RealTimeController.
void StationaryQubit::setFree(bool consumed) {
  qubit_ref->setFree();
  is_busy = false;
  locked = false;
  locked_ruleset_id = -1;
  locked_rule_id = -1;
  action_index = -1;
  emitted_time = -1;

  EV_DEBUG << "Freeing this qubit! " << this << " at qnode: " << node_address << " qnic_type: " << qnic_type << " qnic_index: " << qnic_index << "\n";
  if (hasGUI()) {
    if (consumed) {
      bubble("Consumed!");
      getDisplayString().setTagArg("i", 1, "yellow");
    } else {
      bubble("Failed to entangle!");
      getDisplayString().setTagArg("i", 1, "blue");
    }
  }
}

/*To avoid disturbing this qubit.*/
void StationaryQubit::Lock(unsigned long rs_id, int rule_id, int action_id) {
  if (rs_id == -1 || rule_id == -1 || action_id == -1) {
    error("ruleset_id || rule_id || action_id == -1");
  }
  locked = true;
  locked_ruleset_id = rs_id;  // Used to identify what this qubit is locked for.
  locked_rule_id = rule_id;
  action_index = action_id;
  if (hasGUI()) {
    bubble("Locked!");
    getDisplayString().setTagArg("i", 1, "purple");
  }
}

void StationaryQubit::Unlock() {
  locked = false;
  locked_ruleset_id = -1;  // Used to identify what this qubit is locked for.
  locked_rule_id = -1;
  action_index = -1;
  if (hasGUI()) {
    bubble("Unlocked!");
    getDisplayString().setTagArg("i", 1, "pink");
  }
}

bool StationaryQubit::isLocked() { return locked; }

/**
 * \brief Generate photon entangled with the memory
 * \warning Shouldn't we destroy a possibly existing photon object before? <- No, I dont think so...
 */
PhotonicQubit *StationaryQubit::generateEntangledPhoton() {
  Enter_Method("generateEntangledPhoton()");
  auto *photon = new PhotonicQubit("Photon");
  auto *photon_ref = backend->getShortLiveQubit();
  qubit_ref->noiselessH();
  qubit_ref->noiselessCNOT(photon_ref);
  photon->setQubitRef(photon_ref);
  return photon;
}

/**
 * \brief Emit photon
 *
 * \param pulse: 0 for nothing, 1 for first, 2 for last, 3 for first and last
 *
 * The stationary qubit shouldn't be already busy.
 */
void StationaryQubit::emitPhoton(int pulse) {
  Enter_Method("emitPhoton()");
  if (is_busy) {
    error("Requested a photon emission to a busy qubit... this should not happen!");
    return;
  }
  PhotonicQubit *pk = generateEntangledPhoton();
  if (pulse & STATIONARYQUBIT_PULSE_BEGIN) pk->setFirst(true);
  if (pulse & STATIONARYQUBIT_PULSE_END) pk->setLast(true);
  if (pulse & STATIONARYQUBIT_PULSE_BOUND) pk->setKind(3);
  float jitter_timing = normal(0, emission_jittering_standard_deviation);
  float abso = fabs(jitter_timing);
  scheduleAt(simTime() + abso, pk);  // cannot send back in time, so only positive lag
}

backends::IQubit *StationaryQubit::getBackendQubitRef() const { return qubit_ref; }

MeasurementOutcome StationaryQubit::measureRandomPauliBasis() {
  auto rand = dblrand();
  auto outcome = MeasurementOutcome();
  if (rand < 1.0 / 3) {
    outcome.outcome_is_plus = qubit_ref->measureX() == EigenvalueResult::PLUS_ONE;
    outcome.basis = 'X';
  } else if (rand < 2.0 / 3) {
    outcome.outcome_is_plus = qubit_ref->measureY() == EigenvalueResult::PLUS_ONE;
    outcome.basis = 'Y';
  } else {
    outcome.outcome_is_plus = qubit_ref->measureZ() == EigenvalueResult::PLUS_ONE;
    outcome.basis = 'Z';
  }
  outcome.GOD_clean = 'F';  // need to fix this to properly track the error
  return outcome;
}

}  // namespace quisp::modules
