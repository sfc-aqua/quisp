/** \file StationaryQubit.cc
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/14
 *
 *  \brief StationaryQubit
 */
#include "StationaryQubit.h"

#include <PhotonicQubit_m.h>
#include <messages/classical_messages.h>
#include <omnetpp.h>
#include <bitset>
#include <unordered_set>
#include <unsupported/Eigen/KroneckerProduct>
#include <unsupported/Eigen/MatrixFunctions>
#include <vector>

using namespace Eigen;

using quisp::messages::PhotonicQubit;
using quisp::types::CliffordOperator;
using quisp::types::EigenvalueResult;
using quisp::types::MeasureXResult;
using quisp::types::MeasureYResult;
using quisp::types::MeasureZResult;

namespace quisp {
namespace modules {

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
  memory_err.X_error_rate = (double)par("memory_x_error_rate").doubleValue();
  memory_err.Y_error_rate = (double)par("memory_y_error_rate").doubleValue();
  memory_err.Z_error_rate = (double)par("memory_z_error_rate").doubleValue();
  memory_err.excitation_error_rate = (double)par("memory_energy_excitation_rate").doubleValue();
  memory_err.relaxation_error_rate = (double)par("memory_energy_relaxation_rate").doubleValue();
  memory_err.completely_mixed_rate = (double)par("memory_completely_mixed_rate").doubleValue();
  memory_err.error_rate = memory_err.X_error_rate + memory_err.Y_error_rate + memory_err.Z_error_rate + memory_err.excitation_error_rate + memory_err.relaxation_error_rate +
                          memory_err.completely_mixed_rate;  // This is per μs.
  Memory_Transition_matrix = MatrixXd::Zero(7, 7);
  // clang-format off
  Memory_Transition_matrix <<
    1 - memory_err.error_rate,  memory_err.X_error_rate,   memory_err.Z_error_rate,   memory_err.Y_error_rate,    memory_err.excitation_error_rate, memory_err.relaxation_error_rate, memory_err.completely_mixed_rate,
    memory_err.X_error_rate,    1 - memory_err.error_rate, memory_err.Y_error_rate,   memory_err.Z_error_rate,    memory_err.excitation_error_rate, memory_err.relaxation_error_rate, memory_err.completely_mixed_rate,
    memory_err.Z_error_rate,    memory_err.Y_error_rate,   1 - memory_err.error_rate, memory_err.X_error_rate,    memory_err.excitation_error_rate, memory_err.relaxation_error_rate, memory_err.completely_mixed_rate,
    memory_err.Y_error_rate,    memory_err.Z_error_rate,   memory_err.X_error_rate,   1 - memory_err.error_rate,  memory_err.excitation_error_rate, memory_err.relaxation_error_rate, memory_err.completely_mixed_rate,
    0,                          0,                         0,                         0,                          1 - memory_err.relaxation_error_rate - memory_err.completely_mixed_rate, memory_err.relaxation_error_rate, memory_err.completely_mixed_rate,
    0,                          0,                         0,                         0,                          memory_err.excitation_error_rate, 1 - memory_err.excitation_error_rate - memory_err.completely_mixed_rate, memory_err.completely_mixed_rate,
    0,                          0,                         0,                         0,                          memory_err.excitation_error_rate, memory_err.relaxation_error_rate, 1 - memory_err.excitation_error_rate - memory_err.relaxation_error_rate;
  // clang-format on
  GOD_err.has_X_error = par("god_x_error").boolValue();
  GOD_err.has_Z_error = par("god_z_error").boolValue();
  GOD_err.has_EX_error = par("god_excitation_error").boolValue();
  GOD_err.has_RE_error = par("god_relaxation_error").boolValue();
  GOD_err.has_CM_error = par("god_completely_mixed_error").boolValue();
  setSingleQubitGateErrorModel(Hgate_error, "h_gate");
  setSingleQubitGateErrorModel(Xgate_error, "x_gate");
  setSingleQubitGateErrorModel(Zgate_error, "z_gate");
  setTwoQubitGateErrorCeilings(CNOTgate_error, "cnot_gate");
  setMeasurementErrorModel(Measurement_error);

  // Set error matrices. This is used in the process of simulating tomography.
  Pauli.X << 0, 1, 1, 0;
  Pauli.Y << 0, Complex(0, -1), Complex(0, 1), 0;
  Pauli.Z << 1, 0, 0, -1;
  Pauli.I << 1, 0, 0, 1;

  // Set measurement operators. This is used in the process of simulating tomography.
  meas_op.X_basis.plus << 0.5, 0.5, 0.5, 0.5;
  meas_op.X_basis.minus << 0.5, -0.5, -0.5, 0.5;
  meas_op.X_basis.plus_ket << 1 / sqrt(2), 1 / sqrt(2);
  meas_op.X_basis.minus_ket << 1 / sqrt(2), -1 / sqrt(2);
  meas_op.X_basis.basis = 'X';
  meas_op.Z_basis.plus << 1, 0, 0, 0;
  meas_op.Z_basis.minus << 0, 0, 0, 1;
  meas_op.Z_basis.plus_ket << 1, 0;
  meas_op.Z_basis.minus_ket << 0, 1;
  meas_op.Z_basis.basis = 'Z';
  meas_op.Y_basis.plus << 0.5, Complex(0, -0.5), Complex(0, 0.5), 0.5;
  meas_op.Y_basis.minus << 0.5, Complex(0, 0.5), Complex(0, -0.5), 0.5;
  meas_op.Y_basis.plus_ket << 1 / sqrt(2), Complex(0, 1 / sqrt(2));
  meas_op.Y_basis.minus_ket << 1 / sqrt(2), -Complex(0, 1 / sqrt(2));
  meas_op.Y_basis.basis = 'Y';
  meas_op.identity << 1, 0, 0, 1;

  // Get parameters from omnet
  god_entangled_stationary_qubit_address = par("god_entangled_stationary_qubit_address");
  god_entangled_node_address = par("god_entangled_node_address");
  god_entangled_qnic_address = par("god_entangled_qnic_address");
  god_entangled_qnic_type = par("god_entangled_qnic_type");
  stationary_qubit_address = par("stationary_qubit_address");
  node_address = par("node_address");
  qnic_address = par("qnic_address");
  qnic_type = par("qnic_type");
  qnic_index = par("qnic_index");
  std = par("std");
  setFree(false);

  /* e^(t/T1) energy relaxation, e^(t/T2) phase relaxation. Want to use only 1/10 of T1 and T2 in general.*/

  // initialize variables for graph state representation tracking
  vertex_operator = CliffordOperator::H;

  auto *backend = provider.getQuantumBackend();
  // qubit_ref = backend->getQubit({node_address, qnic_index, qnic_type, stationary_qubit_address});
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
    pk->setPhotonLost(true);
    send(pk, "tolens_quantum_port$o");
  } else {
    send(msg, "tolens_quantum_port$o");
  }
}

void StationaryQubit::setSingleQubitGateErrorModel(SingleGateErrorModel &model, std::string gate_name) {
  auto err_rate_name = gate_name + std::string("_error_rate");
  auto x_ratio_name = gate_name + std::string("_x_error_ratio");
  auto z_ratio_name = gate_name + std::string("_z_error_ratio");
  auto y_ratio_name = gate_name + std::string("_y_error_ratio");
  model.pauli_error_rate = par(err_rate_name.c_str()).doubleValue();
  auto x_ratio = par(x_ratio_name.c_str()).doubleValue();
  auto z_ratio = par(z_ratio_name.c_str()).doubleValue();
  auto y_ratio = par(y_ratio_name.c_str()).doubleValue();

  double sum = x_ratio + z_ratio + y_ratio;
  if (sum == 0) {
    x_ratio = 1.;
    z_ratio = 1.;
    y_ratio = 1.;
    sum = 3.;
  }

  model.X_error_rate = model.pauli_error_rate * (x_ratio / sum);
  model.Y_error_rate = model.pauli_error_rate * (y_ratio / sum);
  model.Z_error_rate = model.pauli_error_rate * (z_ratio / sum);
  model.No_error_ceil = 1 - model.pauli_error_rate;
  model.X_error_ceil = model.No_error_ceil + model.X_error_rate;
  model.Z_error_ceil = model.X_error_ceil + model.Z_error_rate;
  model.Y_error_ceil = model.Z_error_ceil + model.Y_error_rate;
}

void StationaryQubit::setTwoQubitGateErrorCeilings(TwoQubitGateErrorModel &model, std::string gate_name) {
  // prepare parameter names
  std::string err_rate_name = std::string(gate_name) + std::string("_error_rate");
  auto ix_ratio_name = gate_name + std::string("_ix_error_ratio");
  auto xi_ratio_name = gate_name + std::string("_xi_error_ratio");
  auto xx_rationame = gate_name + std::string("_xx_error_ratio");

  auto iz_ratio_name = gate_name + std::string("_iz_error_ratio");
  auto zi_ratio_name = gate_name + std::string("_zi_error_ratio");
  auto zz_ratio_name = gate_name + std::string("_zz_error_ratio");

  auto iy_ratio_name = gate_name + std::string("_iy_error_ratio");
  auto yi_ratio_name = gate_name + std::string("_yi_error_ratio");
  auto yy_ratio_name = gate_name + std::string("_yy_error_ratio");

  // get error ratios from parameter
  model.pauli_error_rate = par(err_rate_name.c_str()).doubleValue();
  double ix_ratio = par(ix_ratio_name.c_str()).doubleValue();
  double xi_ratio = par(xi_ratio_name.c_str()).doubleValue();
  double xx_ratio = par(xx_rationame.c_str()).doubleValue();

  double iz_ratio = par(iz_ratio_name.c_str()).doubleValue();
  double zi_ratio = par(zi_ratio_name.c_str()).doubleValue();
  double zz_ratio = par(zz_ratio_name.c_str()).doubleValue();

  double iy_ratio = par(iy_ratio_name.c_str()).doubleValue();
  double yi_ratio = par(yi_ratio_name.c_str()).doubleValue();
  double yy_ratio = par(yy_ratio_name.c_str()).doubleValue();

  double ratio_sum = ix_ratio + xi_ratio + xx_ratio + iz_ratio + zi_ratio + zz_ratio + iy_ratio + yi_ratio + yy_ratio;

  if (ratio_sum == 0) {
    ix_ratio = 1.;
    xi_ratio = 1.;
    xx_ratio = 1.;
    iz_ratio = 1.;
    zi_ratio = 1.;
    zz_ratio = 1.;
    iy_ratio = 1.;
    yi_ratio = 1.;
    yy_ratio = 1.;
    ratio_sum = 9.;
  }

  model.IX_error_rate = model.pauli_error_rate * (ix_ratio / ratio_sum);
  model.XI_error_rate = model.pauli_error_rate * (xi_ratio / ratio_sum);
  model.XX_error_rate = model.pauli_error_rate * (xx_ratio / ratio_sum);

  model.IZ_error_rate = model.pauli_error_rate * (iz_ratio / ratio_sum);
  model.ZI_error_rate = model.pauli_error_rate * (zi_ratio / ratio_sum);
  model.ZZ_error_rate = model.pauli_error_rate * (zz_ratio / ratio_sum);

  model.IY_error_rate = model.pauli_error_rate * (iy_ratio / ratio_sum);
  model.YI_error_rate = model.pauli_error_rate * (yi_ratio / ratio_sum);
  model.YY_error_rate = model.pauli_error_rate * (yy_ratio / ratio_sum);

  model.No_error_ceil = 1 - model.pauli_error_rate;
  model.IX_error_ceil = model.No_error_ceil + model.IX_error_rate;
  model.XI_error_ceil = model.IX_error_ceil + model.XI_error_rate;
  model.XX_error_ceil = model.XI_error_ceil + model.XX_error_rate;

  model.IZ_error_ceil = model.XX_error_ceil + model.IZ_error_rate;
  model.ZI_error_ceil = model.IZ_error_ceil + model.ZI_error_rate;
  model.ZZ_error_ceil = model.ZI_error_ceil + model.ZZ_error_rate;

  model.IY_error_ceil = model.ZZ_error_ceil + model.IY_error_rate;
  model.YI_error_ceil = model.IY_error_ceil + model.YI_error_rate;
  model.YY_error_ceil = model.YI_error_ceil + model.YY_error_rate;
}

void StationaryQubit::setMeasurementErrorModel(MeasurementErrorModel &model) {
  model.x_error_rate = par("x_measurement_error_rate").doubleValue();
  model.y_error_rate = par("y_measurement_error_rate").doubleValue();
  model.z_error_rate = par("z_measurement_error_rate").doubleValue();
}

MeasureXResult StationaryQubit::correlationMeasureX() {
  bool error = GOD_err.has_Z_error;
  if (dblrand() < Measurement_error.x_error_rate) {
    error = !error;
  }
  return error ? MeasureXResult::HAS_Z_ERROR : MeasureXResult::NO_Z_ERROR;
}

MeasureYResult StationaryQubit::correlationMeasureY() {
  bool error = GOD_err.has_Z_error != GOD_err.has_X_error;
  if (dblrand() < Measurement_error.y_error_rate) {
    error = !error;
  }
  return error ? MeasureYResult::HAS_XZ_ERROR : MeasureYResult::NO_XZ_ERROR;
}

MeasureZResult StationaryQubit::correlationMeasureZ() {
  bool error = GOD_err.has_X_error;
  if (dblrand() < Measurement_error.x_error_rate) {
    error = !error;
  }
  return error ? MeasureZResult::HAS_X_ERROR : MeasureZResult::NO_X_ERROR;
}

EigenvalueResult StationaryQubit::localMeasureX() {
  // the Z error will propagate to its partner; This only works for Bell pair and entanglement swapping for now
  if (this->entangled_partner != nullptr && GOD_err.has_Z_error) {
    this->entangled_partner->addZerror();
  }

  auto result = EigenvalueResult::PLUS_ONE;
  if (dblrand() < 0.5) {
    result = EigenvalueResult::MINUS_ONE;
    if (this->entangled_partner != nullptr) {
      this->entangled_partner->addZerror();
    }
  }
  if (dblrand() < this->Measurement_error.x_error_rate) {
    result = result == EigenvalueResult::PLUS_ONE ? EigenvalueResult::MINUS_ONE : EigenvalueResult::PLUS_ONE;
  }
  return result;
}

EigenvalueResult StationaryQubit::localMeasureY() {
  error("Not Yet Implemented");
  return EigenvalueResult::PLUS_ONE;
}

EigenvalueResult StationaryQubit::localMeasureZ() {
  // the X error will propagate to its partner; This only works for Bell pair and entanglement swapping for now
  if (this->entangled_partner != nullptr && GOD_err.has_X_error) {
    this->entangled_partner->addXerror();
  }

  auto result = EigenvalueResult::PLUS_ONE;
  if (dblrand() < 0.5) {
    result = EigenvalueResult::MINUS_ONE;
    if (this->entangled_partner != nullptr) {
      this->entangled_partner->addXerror();
    }
  }
  if (dblrand() < this->Measurement_error.z_error_rate) {
    result = result == EigenvalueResult::PLUS_ONE ? EigenvalueResult::MINUS_ONE : EigenvalueResult::PLUS_ONE;
  }
  return result;
}

// Convert X to Z, and Z to X error. Therefore, Y error stays as Y.
void StationaryQubit::Hadamard_gate() {
  // Need to add noise here later
  applySingleQubitGateError(Hgate_error);
  bool z = GOD_err.has_Z_error;
  GOD_err.has_Z_error = GOD_err.has_X_error;
  GOD_err.has_X_error = z;
}

void StationaryQubit::Z_gate() {
  // Need to add noise here later
  applySingleQubitGateError(Zgate_error);
  GOD_err.has_Z_error = !GOD_err.has_Z_error;
}

void StationaryQubit::X_gate() {
  // Need to add noise here later
  applySingleQubitGateError(Xgate_error);
  GOD_err.has_X_error = !GOD_err.has_X_error;
}

void StationaryQubit::CNOT_gate(IStationaryQubit *control_qubit) {
  // Need to add noise here later
  applyTwoQubitGateError(CNOTgate_error, check_and_cast<StationaryQubit *>(control_qubit));

  if (control_qubit->GOD_err.has_X_error) {
    // X error propagates from control to target. If an X error is already present, then it cancels out.
    GOD_err.has_X_error = !GOD_err.has_X_error;
  }

  if (GOD_err.has_Z_error) {
    // Z error propagates from target to control. If an Z error is already present, then it cancels out.
    control_qubit->GOD_err.has_Z_error = !control_qubit->GOD_err.has_Z_error;
  }
}

// This is invoked whenever a photon is emitted out from this particular qubit.
void StationaryQubit::setBusy() {
  is_busy = true;
  emitted_time = simTime();
  updated_time = simTime();  // Should be no error at this time.
  // GUI part
  if (hasGUI()) {
    getDisplayString().setTagArg("i", 1, "red");
    par("photon_emitted_at") = emitted_time.dbl();
    par("last_updated_at") = updated_time.dbl();
    par("is_busy") = true;
  }
}

// Re-initialization of this stationary qubit
// This is called at the beginning of the simulation (in initialization() above), and whenever it is reinitialized via the RealTimeController.
void StationaryQubit::setFree(bool consumed) {
  num_purified = 0;
  locked = false;
  locked_ruleset_id = -1;
  locked_rule_id = -1;
  action_index = -1;

  is_busy = false;
  emitted_time = -1;
  updated_time = simTime();

  partner_measured = false;
  completely_mixed = false;
  excited_or_relaxed = false;
  GOD_dm_Zerror = false;
  GOD_dm_Xerror = false;
  Density_Matrix_Collapsed << -111, -111, -111, -111;
  no_density_matrix_nullptr_entangled_partner_ok = false;
  god_entangled_stationary_qubit_address = -1;
  god_entangled_node_address = -1;
  god_entangled_qnic_address = -1;
  god_entangled_qnic_type = -1;
  GOD_err.has_X_error = false;
  GOD_err.has_Z_error = false;
  GOD_err.has_EX_error = false;
  GOD_err.has_RE_error = false;
  GOD_err.has_CM_error = false;
  entangled_partner = nullptr;
  EV_DEBUG << "Freeing this qubit!!!" << this << " at qnode: " << node_address << " qnic_type: " << qnic_type << " qnic_index: " << qnic_index << "\n";
  // GUI part
  if (hasGUI()) {
    par("photon_emitted_at") = emitted_time.dbl();
    par("last_updated_at") = updated_time.dbl();
    par("is_busy") = false;
    par("god_entangled_stationary_qubit_address") = -1;
    par("god_entangled_node_address") = -1;
    par("god_entangled_qnic_address") = -1;
    par("god_entangled_qnic_type") = -1;
    par("god_x_error") = false;
    par("god_z_error") = false;
    par("god_excitation_error") = false;
    par("god_relaxation_error") = false;
    par("god_completely_mixed_error") = false;
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
  // GUI part
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
  // GUI part
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
  // To simulate the actual physical entangled partner, not what the system thinks!!! we need this.

  // This photon is entangled with.... node_address = node's index
  photon->setNodeEntangledWith(node_address);

  // qnic_address != qnic_index. qnic_index is not unique because there are 3 types.
  photon->setQNICEntangledWith(qnic_address);

  // stationary_qubit_address = StationaryQubit's index
  photon->setStationaryQubitEntangledWith(stationary_qubit_address);
  photon->setQNICtypeEntangledWith(qnic_type);
  photon->setEntangled_with(this);
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
  float jitter_timing = normal(0, std);
  float abso = fabs(jitter_timing);
  scheduleAt(simTime() + abso, pk);  // cannot send back in time, so only positive lag
}

// This gets direcltly invoked when darkcount happened in BellStateAnalyzer.cc.
void StationaryQubit::setCompletelyMixedDensityMatrix() {
  this->Density_Matrix_Collapsed << (double)1 / (double)2, 0, 0, (double)1 / (double)2;
  // std::cout<<"Dm completely mixed "<<this->Density_Matrix_Collapsed<<"\n";
  this->completely_mixed = true;
  this->excited_or_relaxed = false;

  if (this->entangled_partner != nullptr) {  // Eliminate entangled information
    this->entangled_partner->entangled_partner = nullptr;
    this->entangled_partner = nullptr;
  }
  this->GOD_err.has_CM_error = true;
  this->GOD_err.has_EX_error = false;
  this->GOD_err.has_RE_error = false;
  this->GOD_err.has_X_error = false;
  this->GOD_err.has_Z_error = false;
  this->GOD_dm_Xerror = false;
  this->GOD_dm_Zerror = false;
  if (hasGUI()) {
    par("god_x_error") = false;
    par("god_z_error") = false;
    par("god_excitation_error") = false;
    par("god_relaxation_error") = false;
    par("god_completely_mixed_error") = true;
    bubble("Completely mixed. darkcount");
    getDisplayString().setTagArg("i", 1, "black");
  }
}

// This gets invoked in memory error simulation or by BellStateAnalyzer if photonLoss + darkcount.
void StationaryQubit::setExcitedDensityMatrix() {
  Density_Matrix_Collapsed << 1, 0, 0, 0;  // Overwrite density matrix
  completely_mixed = false;
  excited_or_relaxed = true;  // It is excited

  GOD_err.has_EX_error = true;
  GOD_err.has_RE_error = false;
  GOD_err.has_CM_error = false;
  GOD_err.has_X_error = false;
  GOD_err.has_Z_error = false;
  GOD_dm_Xerror = false;
  GOD_dm_Zerror = false;

  if (hasGUI()) {
    par("god_x_error") = false;
    par("god_z_error") = false;
    par("god_excitation_error") = true;
    par("god_relaxation_error") = false;
    par("god_completely_mixed_error") = false;
    bubble("Completely mixed. darkcount");
    getDisplayString().setTagArg("i", 1, "white");
  }

  if (this->entangled_partner != nullptr) {  // If it used to be entangled...
    // error("What?");
    this->entangled_partner->updated_time = simTime();
    // For GUI
    if (hasGUI()) this->entangled_partner->par("last_updated_at") = simTime().dbl();
    // This also eliminates the entanglement information.
    this->entangled_partner->setCompletelyMixedDensityMatrix();
  }  // else it is already not entangled. e.g. excited -> relaxed.
}

void StationaryQubit::setRelaxedDensityMatrix() {
  Density_Matrix_Collapsed << 0, 0, 0, 1;
  completely_mixed = false;
  excited_or_relaxed = true;
  GOD_err.has_EX_error = false;
  GOD_err.has_RE_error = true;
  GOD_err.has_CM_error = false;
  GOD_err.has_X_error = false;
  GOD_err.has_Z_error = false;
  GOD_dm_Xerror = false;
  GOD_dm_Zerror = false;
  if (hasGUI()) {
    par("god_x_error") = false;
    par("god_z_error") = false;
    par("god_excitation_error") = false;
    par("god_relaxation_error") = true;
    par("god_completely_mixed_error") = false;
    bubble("Completely mixed. darkcount");
    getDisplayString().setTagArg("i", 1, "white");
  }

  // Still entangled
  if (this->entangled_partner != nullptr) {
    this->entangled_partner->updated_time = simTime();
    // For GUI
    this->entangled_partner->par("last_updated_at") = simTime().dbl();
    this->entangled_partner->setCompletelyMixedDensityMatrix();
  }  // else it is already not entangled. e.g. excited -> relaxed.
}

void StationaryQubit::setEntangledPartnerInfo(IStationaryQubit *partner) {
  // When BSA succeeds, this method gets invoked to store entangled partner information.
  // This will also be sent classically to the partner node afterwards.
  entangled_partner = partner;
  god_entangled_stationary_qubit_address = partner->stationary_qubit_address;
  god_entangled_node_address = partner->node_address;
  god_entangled_qnic_address = partner->qnic_address;
  god_entangled_qnic_type = partner->qnic_type;
  // For GUI
  if (hasGUI()) {
    par("god_entangled_stationary_qubit_address") = partner->stationary_qubit_address;
    par("god_entangled_node_address") = partner->node_address;
    par("god_entangled_qnic_address") = partner->qnic_address;
    par("god_entangled_qnic_type") = partner->qnic_type;
  }
}

/* Add another X error. If an X error already exists, then they cancel out */
void StationaryQubit::addXerror() { this->GOD_err.has_X_error = !this->GOD_err.has_X_error; }

/* Add another Z error. If an Z error already exists, then they cancel out */
void StationaryQubit::addZerror() { this->GOD_err.has_Z_error = !this->GOD_err.has_Z_error; }

// Only tracks error propagation. If two booleans (Alice and Bob) agree (truetrue or falsefalse), keep the purified ebit.
bool StationaryQubit::Xpurify(IStationaryQubit *resource_qubit /*Controlled*/) {
  // std::cout<<"X puri\n";
  // This could result in completelty mixed, excited, relaxed, which also affects the entangled partner.
  applyMemoryError();
  check_and_cast<StationaryQubit *>(resource_qubit)->applyMemoryError();
  /*Target qubit*/ this->CNOT_gate(resource_qubit /*controlled qubit*/);
  bool meas = this->correlationMeasureZ() == MeasureZResult::NO_X_ERROR;
  return meas;
}

bool StationaryQubit::Zpurify(IStationaryQubit *resource_qubit /*Target*/) {
  applyMemoryError();  // This could result in completelty mixed, excited, relaxed, which also affects the entangled partner.
  check_and_cast<StationaryQubit *>(resource_qubit)->applyMemoryError();
  /*Target qubit*/ resource_qubit->CNOT_gate(this /*controlled qubit*/);
  this->Hadamard_gate();
  bool meas = this->correlationMeasureZ() == MeasureZResult::NO_X_ERROR;
  return meas;
}

// Single qubit memory error based on Markov-Chain
void StationaryQubit::applyMemoryError() {
  if (entangled_partner == nullptr && Density_Matrix_Collapsed(0, 0).real() == -111 && !no_density_matrix_nullptr_entangled_partner_ok)
    error("This must not happen in apply memory error");

  // If no memory error occurs, or if the state is completely mixed, skip this memory error simulation.
  if (memory_err.error_rate == 0) {
    // error("memory error is set to 0. If on purpose, that is fine. Comment this out.");
    return;
  }

  // Check when the error got updated last time.
  // Errors will be performed depending on the difference between that time and the current time.
  double time_evolution = simTime().dbl() - updated_time.dbl();
  double time_evolution_microsec = time_evolution * 1000000 /** 100*/;
  if (time_evolution_microsec > 0) {
    // Perform Monte-Carlo error simulation on this qubit.
    bool has_x_err = GOD_err.has_X_error;
    bool has_z_err = GOD_err.has_Z_error;
    bool is_excited = GOD_err.has_EX_error;
    bool is_relaxed = GOD_err.has_RE_error;
    bool is_completely_mixed = GOD_err.has_CM_error;
    if (completely_mixed != is_completely_mixed) {
      error("[apply_memory_error] Completely mixed flag not matching");
    }
    if (excited_or_relaxed != is_excited && excited_or_relaxed != is_relaxed) {
      error("[apply_memory_error] Relaxed/Excited flag not matching");
    }

    bool skip_exponentiation = false;
    for (int i = 0; i < Memory_Transition_matrix.cols(); i++) {
      if (Memory_Transition_matrix(0, i) == 1) {
        // Do not to the exponentiation! Eigen will mess up the exponentiation anyway...
        skip_exponentiation = true;
        break;
      }
    }

    MatrixXd transition_mat(7, 7);
    if (!skip_exponentiation) {
      // calculate time evoluted error matrix: Q^(time_evolution_microsec) in Eq 5.3
      MatrixPower<MatrixXd> q_pow(Memory_Transition_matrix);
      transition_mat = q_pow(time_evolution_microsec);
    } else {
      transition_mat = Memory_Transition_matrix;
    }

    // validate transition_mat
    for (int r = 0; r < transition_mat.rows(); r++) {
      double col_sum = 0;
      for (int i = 0; i < transition_mat.cols(); i++) {
        col_sum += transition_mat(r, i);
      }
      if (col_sum > 1.01 || col_sum < 0.99) {
        std::cout << "col_sum = " << col_sum << std::endl;
        error("Row of the transition matrix does not sum up to 1.");
      }
    }

    if (std::isnan(transition_mat(0, 0))) {
      std::cout << "transition_mat: " << transition_mat << std::endl;
      error("Transition maatrix is NaN. This is Eigen's fault.");
    }

    // pi(0 ~ 6) vector in Eq 5.3
    MatrixXd pi_vector(1, 7);  // I, X, Z, Y, Ex, Re, Cm
    if (is_excited) {
      pi_vector << 0, 0, 0, 0, 1, 0, 0;  // excitation error
    } else if (is_relaxed) {
      pi_vector << 0, 0, 0, 0, 0, 1, 0;  // relaxation error
    } else if (is_completely_mixed) {
      pi_vector << 0, 0, 0, 0, 0, 0, 1;  // completely mixed error
    } else if (has_z_err && has_x_err) {
      pi_vector << 0, 0, 0, 1, 0, 0, 0;  // Y error
    } else if (has_z_err && !has_x_err) {
      pi_vector << 0, 0, 1, 0, 0, 0, 0;  // Z error
    } else if (!has_z_err && has_x_err) {
      pi_vector << 0, 1, 0, 0, 0, 0, 0;  // X error
    } else {
      pi_vector << 1, 0, 0, 0, 0, 0, 0;  // No error
    }
    // pi(t) in Eq 5.3
    // Clean, X, Z, Y, Excited, Relaxed
    MatrixXd output_vector(1, 6);
    // take error rate vector from DynamicTransitionMatrix Eq 5.3
    output_vector = pi_vector * transition_mat;

    /* this prepares the sectors for Monte-Carlo. later, we'll pick a random value and check with this sectors.
     *
     * 0.0    clean_ceil             z_ceil              excited_ceil                       1.0
     *  |          |                   |                      |                              |
     *  | No Error | X Error | Z Error | Y Error | Excitation | Relaxation | Cmpletely Mixed |
     *                       |                   |                         |
     *                    x_ceil               y_ceil                relaxed_ceil
     */
    double clean_ceil = output_vector(0, 0);
    double x_ceil = clean_ceil + output_vector(0, 1);
    double z_ceil = x_ceil + output_vector(0, 2);
    double y_ceil = z_ceil + output_vector(0, 3);
    double excited_ceil = y_ceil + output_vector(0, 4);
    double relaxed_ceil = excited_ceil + output_vector(0, 5);

    // Gives a random double between 0.0 ~ 1.0
    double rand = dblrand();

    if (rand < clean_ceil) {
      // Qubit will end up with no error
      GOD_err.has_X_error = false;
      GOD_err.has_Z_error = false;
    } else if (clean_ceil <= rand && rand < x_ceil && (clean_ceil != x_ceil)) {
      // X error
      GOD_err.has_X_error = true;
      GOD_err.has_Z_error = false;
    } else if (x_ceil <= rand && rand < z_ceil && (x_ceil != z_ceil)) {
      // Z error
      GOD_err.has_X_error = false;
      GOD_err.has_Z_error = true;
    } else if (z_ceil <= rand && rand < y_ceil && (z_ceil != y_ceil)) {
      // Y error
      GOD_err.has_X_error = true;
      GOD_err.has_Z_error = true;
    } else if (y_ceil <= rand && rand < excited_ceil && (y_ceil != excited_ceil)) {
      // Excitation error
      // Also sets the partner completely mixed if it used to be entangled.
      setExcitedDensityMatrix();
    } else if (excited_ceil <= rand && rand < relaxed_ceil && (excited_ceil != relaxed_ceil)) {
      // Excitation error
      // Also sets the partner completely mixed if it used to be entangled.
      setRelaxedDensityMatrix();
    } else {
      // Memory completely mixed error

      // If this qubit still used to be entangled with another qubit.
      if (entangled_partner != nullptr) {
        entangled_partner->updated_time = simTime();
        entangled_partner->par("last_updated_at") = simTime().dbl();
        // Break entanglement with partner. Overwrite its density matrix.
        entangled_partner->setCompletelyMixedDensityMatrix();
      }
      setCompletelyMixedDensityMatrix();
    }
  }
  updated_time = simTime();
  // For GUI
  if (hasGUI()) {
    par("last_updated_at") = simTime().dbl();
    par("GOD_X_Error") = GOD_err.has_X_error;
    par("GOD_Z_Error") = GOD_err.has_Z_error;
  }
}

Matrix2cd StationaryQubit::getErrorMatrix(StationaryQubit *qubit) {
  if (qubit->GOD_err.has_CM_error || qubit->GOD_err.has_RE_error) {
    error("CMerror in getErrorMatrix. Not supposed to happen.");
  }

  auto has_z_err = qubit->GOD_err.has_Z_error;
  auto has_x_err = qubit->GOD_err.has_X_error;

  if (has_z_err && has_x_err) return Pauli.Y;
  if (has_z_err) return Pauli.Z;
  if (has_x_err) return Pauli.X;
  return Pauli.I;
}

// returns the density matrix of the Bell pair with error. This assumes that this is entangled with another stationary qubit.
// Measurement output will be based on this matrix, as long as it is still entangled.
quantum_state StationaryQubit::getQuantumState() {
  if (this->excited_or_relaxed) error("this qubit is excited or relaxed");
  if (this->entangled_partner == nullptr) error("no entangled partner");
  if (this->entangled_partner->excited_or_relaxed) error("partner qubit is excited or relaxed");

  Matrix4cd error_mat = kroneckerProduct(getErrorMatrix(this), getErrorMatrix(check_and_cast<StationaryQubit *>(entangled_partner))).eval();
  // Assumes that the state is a 2 qubit state |00> + |11>
  Vector4cd ideal_bell_state(1 / sqrt(2), 0, 0, 1 / sqrt(2));
  Vector4cd actual_bell_state = error_mat * ideal_bell_state;

  quantum_state q;
  q.state_in_density_matrix = actual_bell_state * actual_bell_state.adjoint();
  q.state_in_ket = actual_bell_state;
  return q;
}

void StationaryQubit::applySingleQubitGateError(SingleGateErrorModel const &err) {
  if (err.pauli_error_rate == 0) {
    return;
  }
  // Gives a random double between 0.0 ~ 1.0
  double rand = dblrand();

  /*
   * 0.0    No_error_ceil       Z_error_ceil  1.0
   *  |          |                   |         |
   *  | No Error | X Error | Z Error | Y Error |
   *                       |
   *                  X_error_ceil
   */
  if (rand <= err.No_error_ceil) {
    // No error
  } else if (err.No_error_ceil < rand && rand <= err.X_error_ceil && (err.No_error_ceil != err.X_error_ceil)) {
    // X error
    addXerror();
  } else if (err.X_error_ceil < rand && rand <= err.Z_error_ceil && (err.X_error_ceil != err.Z_error_ceil)) {
    // Z error
    addZerror();
  } else {
    // Y error
    addZerror();
    addXerror();
  }
}

void StationaryQubit::applyTwoQubitGateError(TwoQubitGateErrorModel const &err, StationaryQubit *another_qubit) {
  if (err.pauli_error_rate == 0) {
    return;
  }

  // Gives a random double between 0.0 ~ 1.0
  double rand = dblrand();

  /*
   * 0.0  No_error_ceil    XI_error_ceil     IY_error_ceil     YY_error_ceil    ZI_error_ceil  1.0
   *  |        |                 |                 |                 |                 |        |
   *  | No err | IX err | XI err | XX err | IY err | YI err | YY err | IZ err | ZI err | ZZ err |
   *                    |                 |                 |                 |
   *              IX_error_ceil      XX_error_ceil     YI_error_ceil    IZ_error_ceil
   */
  if (rand <= err.No_error_ceil) {
    // No error
  } else if (err.No_error_ceil < rand && rand <= err.IX_error_ceil && (err.No_error_ceil != err.IX_error_ceil)) {
    // IX error
    addXerror();
  } else if (err.IX_error_ceil < rand && rand <= err.XI_error_ceil && (err.IX_error_ceil != err.XI_error_ceil)) {
    // XI error
    another_qubit->addXerror();
  } else if (err.XI_error_ceil < rand && rand <= err.XX_error_ceil && (err.XI_error_ceil != err.XX_error_ceil)) {
    // XX error
    addXerror();
    another_qubit->addXerror();
  } else if (err.XX_error_ceil < rand && rand <= err.IZ_error_ceil && (err.XX_error_ceil != err.IZ_error_ceil)) {
    // IZ error
    addZerror();
  } else if (err.IZ_error_ceil < rand && rand <= err.ZI_error_ceil && (err.IZ_error_ceil != err.ZI_error_ceil)) {
    // ZI error
    another_qubit->addZerror();
  } else if (err.ZI_error_ceil < rand && rand <= err.ZZ_error_ceil && (err.ZI_error_ceil != err.ZZ_error_ceil)) {
    // ZZ error
    addZerror();
    another_qubit->addZerror();
  } else if (err.ZZ_error_ceil < rand && rand <= err.IY_error_ceil && (err.ZZ_error_ceil != err.IY_error_ceil)) {
    // IY error
    addXerror();
    addZerror();
  } else if (err.IY_error_ceil < rand && rand <= err.YI_error_ceil && (err.IY_error_ceil != err.YI_error_ceil)) {
    // YI error
    another_qubit->addXerror();
    another_qubit->addZerror();
  } else {
    // YY error
    addXerror();
    addZerror();
    another_qubit->addXerror();
    another_qubit->addZerror();
  }
}

measurement_outcome StationaryQubit::measure_density_independent() {
  if (this->entangled_partner == nullptr && this->Density_Matrix_Collapsed(0, 0).real() == -111) {
    std::cout << Density_Matrix_Collapsed << "\n";
    std::cout << "Measuring" << this << "in node[" << node_address << "]\n";
    std::cout << this->getIndex() << "\n";
    error("Measuring a qubit that is not entangled with another qubit. Probably not what you want! Check whether address for each node is unique!!!");
  }
  measurement_operator this_measurement = Random_Measurement_Basis_Selection();  // Select basis randomly
  char Output;
  bool Output_is_plus;

  // Add memory error depending on the idle time. If excited/relaxed, this will immediately break entanglement, leaving the other qubit as completely mixed.
  applyMemoryError();

  // This becomes nullptr if this qubit got excited/relaxed or measured.
  if (this->entangled_partner != nullptr) {
    if (this->entangled_partner->entangled_partner == nullptr) {
      std::cout << "Entanglement not tracked well between partners." << this << " in node[" << node_address << "]\n";
      std::cout << "Partner must be " << this->entangled_partner << " in node[" << this->entangled_partner->node_address << "]\n";
      error("NO!");
    }
    if (this->partner_measured) error("Entangled partner not nullptr but partner already measured....? Probably wrong.");
    if (this->completely_mixed || this->excited_or_relaxed) {
      std::cout << "[Error]" << this << "\n";
      error("Entangled but completely mixed / Excited / Relaxed ? Probably wrong.");
    }
    // Also do the same on the partner if it is still entangled! This could break the entanglement due to relaxation/excitation error!
    check_and_cast<StationaryQubit *>(this->entangled_partner)->applyMemoryError();
  }

  /*-For debugging-*/
  char GOD_state = 'F';  // Completely mixed

  if (this->GOD_err.has_EX_error)
    GOD_state = 'E';
  else if (this->GOD_err.has_EX_error)
    GOD_state = 'R';
  else if (this->GOD_err.has_CM_error)
    GOD_state = 'C';
  else if (!this->GOD_err.has_X_error && this->GOD_err.has_Z_error)  // To check stabilizers....
    GOD_state = 'Z';
  else if (this->GOD_err.has_X_error && !this->GOD_err.has_Z_error)
    GOD_state = 'X';
  else if (this->GOD_err.has_X_error && this->GOD_err.has_Z_error)
    GOD_state = 'Y';

  /*---------------*/

  if (this->completely_mixed != this->GOD_err.has_CM_error) {
    error("Cm track wrong\n");
  }
  if (this->excited_or_relaxed && !this->GOD_err.has_EX_error && !this->GOD_err.has_RE_error) {
    std::cout << "this->excited_or_relaxed = " << this->excited_or_relaxed << ", !this->GOD_err.has_RE_error=" << !this->GOD_err.has_RE_error
              << "!this->GOD_err.has_EX_error=" << !this->GOD_err.has_EX_error;
    error("Ex/Re track wrong\n");
  }
  // if there is an entanglement
  if (this->entangled_partner != nullptr) {
    // This qubit is nullptr
    if (this->entangled_partner->entangled_partner == nullptr) {
      error("Entangled_partner track wrong\n");
    }
    // check completely mixed tracking
    if (this->entangled_partner->completely_mixed != this->entangled_partner->GOD_err.has_CM_error) {
      error("Partner Cm track wrong\n");
    }
    // check excited and relaxation tracking
    if (this->entangled_partner->excited_or_relaxed && !this->entangled_partner->GOD_err.has_EX_error && !this->entangled_partner->GOD_err.has_RE_error) {
      error("Partner Re/Ex track wrong\n");
    }
    if (this->entangled_partner->GOD_err.has_CM_error || this->entangled_partner->GOD_err.has_RE_error || this->entangled_partner->GOD_err.has_EX_error) {
      // error("Partner CM/Re/Ex track wrong\n");
    }
  }

  // if the partner qubit is measured,
  if (this->partner_measured || this->completely_mixed || this->excited_or_relaxed) {  // The case when the density matrix is completely local to this qubit.
    // if this qubit is said to be completely mixed and no set value
    if (this->completely_mixed && !this->GOD_err.has_CM_error) {
      error("Mismatch between flags.");
    }
    if (this->Density_Matrix_Collapsed(0, 0).real() == -111) {  // We always need some kind of density matrix inside this if statement.
      error("Single qubit density matrix not stored properly after partner's measurement, excitation/relaxation error.");
    }
    bool Xerr = this->GOD_err.has_X_error;
    bool Zerr = this->GOD_err.has_Z_error;
    // This qubit's density matrix was created when the partner measured his own.
    // Because this qubit can be measured after that, we need to update the stored density matrix according to new errors occurred due to memory error.

    if (Xerr != GOD_dm_Xerror) {  // Another X error to the dm.
      // error("NO");
      Density_Matrix_Collapsed = Pauli.X * Density_Matrix_Collapsed * Pauli.X.adjoint();
    }
    if (Zerr != GOD_dm_Zerror) {  // Another Z error to the dm.
      // error("NO!");
      Density_Matrix_Collapsed = Pauli.Z * Density_Matrix_Collapsed * Pauli.Z.adjoint();
    }

    // std::cout<<"Not entangled anymore. Density matrix is "<<Density_Matrix_Collapsed<<"\n";

    Complex Prob_plus = (Density_Matrix_Collapsed * this_measurement.plus.adjoint() * this_measurement.plus).trace();
    Complex Prob_minus = (Density_Matrix_Collapsed * this_measurement.minus.adjoint() * this_measurement.minus).trace();
    double dbl = dblrand();
    if (dbl < Prob_plus.real()) {
      Output = '+';
      Output_is_plus = true;
    } else {
      Output = '-';
      Output_is_plus = false;
    }
    // std::cout<<"\n This qubit was "<<this_measurement.basis<<"("<<Output<<"). \n";
  } else if (!this->partner_measured && !this->completely_mixed && !this->excited_or_relaxed && this->entangled_partner != nullptr) {
    // This is assuming that this is some other qubit is entangled. Only Pauli errors are assumed.
    quantum_state current_state = getQuantumState();
    EV << "Current entangled state is " << current_state.state_in_ket << "\n";

    bool Xerr = this->GOD_err.has_X_error;
    bool Zerr = this->GOD_err.has_Z_error;
    // std::cout<<"Entangled state is "<<current_state.state_in_ket<<"\n";

    Complex Prob_plus = current_state.state_in_ket.adjoint() * kroneckerProduct(this_measurement.plus, meas_op.identity).eval().adjoint() *
                        kroneckerProduct(this_measurement.plus, meas_op.identity).eval() * current_state.state_in_ket;
    Complex Prob_minus = current_state.state_in_ket.adjoint() * kroneckerProduct(this_measurement.minus, meas_op.identity).eval().adjoint() *
                         kroneckerProduct(this_measurement.minus, meas_op.identity).eval() * current_state.state_in_ket;

    // std::cout<<"Measurement basis = "<<this_measurement.basis<<"P(+) = "<<Prob_plus.real()<<", P(-) = "<<Prob_minus.real()<<"\n";
    double dbl = dblrand();

    Vector2cd ms;
    if (dbl < Prob_plus.real()) {  // Measurement output was plus
      Output = '+';
      ms = this_measurement.plus_ket;
      Output_is_plus = true;
    } else {  // Otherwise, it was negative.
      Output = '-';
      ms = this_measurement.minus_ket;
      Output_is_plus = false;
    }
    // Now we have to calculate the density matrix of a single qubit that used to be entangled with this.
    Matrix2cd partners_dm, normalized_partners_dm;
    partners_dm =
        kroneckerProduct(ms.adjoint(), meas_op.identity).eval() * current_state.state_in_density_matrix * kroneckerProduct(ms.adjoint(), meas_op.identity).eval().adjoint();
    normalized_partners_dm = partners_dm / partners_dm.trace();
    EV << "kroneckerProduct(ms.adjoint(),meas_op.identity).eval() = " << kroneckerProduct(ms.adjoint(), meas_op.identity).eval() << "\n";
    EV << "dm = " << current_state.state_in_density_matrix << "\n";
    EV << "State was " << kroneckerProduct(ms.adjoint(), meas_op.identity).eval() * current_state.state_in_density_matrix << "\n";
    EV << "\n This qubit was " << this_measurement.basis << "(" << Output << "). Partner's dm is now = " << normalized_partners_dm << "\n";
    entangled_partner->Density_Matrix_Collapsed = normalized_partners_dm;

    // We actually do not need this as long as deleting entangled_partner completely is totally fine.
    entangled_partner->partner_measured = true;
    // if(entangled_partner->getIndex() == 71 && entangled_partner->node_address == 3)
    //	std::cout<<"-------------------"<<entangled_partner<<" in node["<<entangled_partner->node_address<<"] overwritten dm.\n";

    // Break entanglement.
    entangled_partner->entangled_partner = nullptr;
    // Save what error it had, when this density matrix was calculated.
    // Error may get updated in the future, so we need to track what error has been considered already in the dm.
    entangled_partner->GOD_dm_Xerror = entangled_partner->GOD_err.has_X_error;
    entangled_partner->GOD_dm_Zerror = entangled_partner->GOD_err.has_Z_error;
  } else {
    error("Check condition in measure func.");
  }

  // add measurement error
  auto rand_num = dblrand();
  if (this_measurement.basis == meas_op.X_basis.basis && rand_num < Measurement_error.x_error_rate ||
      this_measurement.basis == meas_op.Y_basis.basis && rand_num < Measurement_error.y_error_rate ||
      this_measurement.basis == meas_op.Z_basis.basis && rand_num < Measurement_error.z_error_rate) {
    Output_is_plus = !Output_is_plus;
  }

  measurement_outcome o;
  o.basis = this_measurement.basis;
  o.outcome_is_plus = Output_is_plus;
  o.GOD_clean = GOD_state;
  return o;
}

measurement_operator StationaryQubit::Random_Measurement_Basis_Selection() {
  measurement_operator this_measurement;
  double dbl = dblrand();  // Random double value for random basis selection.
  EV << "Random dbl = " << dbl << "! \n ";

  if (dbl < ((double)1 / (double)3)) {  // X measurement!
    EV << "X measurement\n";
    this_measurement.plus = meas_op.X_basis.plus;
    this_measurement.minus = meas_op.X_basis.minus;
    this_measurement.basis = meas_op.X_basis.basis;
    this_measurement.plus_ket = meas_op.X_basis.plus_ket;
    this_measurement.minus_ket = meas_op.X_basis.minus_ket;
  } else if (dbl >= ((double)1 / (double)3) && dbl < ((double)2 / (double)3)) {
    EV << "Z measurement\n";
    this_measurement.plus = meas_op.Z_basis.plus;
    this_measurement.minus = meas_op.Z_basis.minus;
    this_measurement.basis = meas_op.Z_basis.basis;
    this_measurement.plus_ket = meas_op.Z_basis.plus_ket;
    this_measurement.minus_ket = meas_op.Z_basis.minus_ket;
  } else {
    EV << "Y measurement\n";
    this_measurement.plus = meas_op.Y_basis.plus;
    this_measurement.minus = meas_op.Y_basis.minus;
    this_measurement.basis = meas_op.Y_basis.basis;
    this_measurement.plus_ket = meas_op.Y_basis.plus_ket;
    this_measurement.minus_ket = meas_op.Y_basis.minus_ket;
  }
  return this_measurement;
}

// protected internal graph backend functions

void StationaryQubit::applyClifford(types::CliffordOperator op) { this->vertex_operator = clifford_application_lookup[(int)op][(int)(this->vertex_operator)]; }

void StationaryQubit::applyRightClifford(types::CliffordOperator op) { this->vertex_operator = clifford_application_lookup[(int)(this->vertex_operator)][(int)op]; }

bool StationaryQubit::isNeighbor(StationaryQubit *another_qubit) { return this->neighbors.find(another_qubit) != this->neighbors.end(); }

void StationaryQubit::addEdge(StationaryQubit *another_qubit) {
  if (another_qubit == this) error("adding edge to self is not allowed");
  this->neighbors.insert(another_qubit);
  another_qubit->neighbors.insert(this);
}

void StationaryQubit::deleteEdge(StationaryQubit *another_qubit) {
  this->neighbors.erase(another_qubit);
  another_qubit->neighbors.erase(this);
}

void StationaryQubit::toggleEdge(StationaryQubit *another_qubit) {
  if (this->isNeighbor(another_qubit)) {
    this->deleteEdge(another_qubit);
  } else {
    this->addEdge(another_qubit);
  }
}

void StationaryQubit::removeAllEdges() {
  for (auto *v : this->neighbors) {
    v->neighbors.erase(this);
  }
  this->neighbors.clear();
}

void StationaryQubit::localComplement() {
  auto it_end = this->neighbors.end();
  for (auto it_u = this->neighbors.begin(); it_u != it_end; it_u++) {
    auto it_v = std::next(it_u);
    for (; it_v != it_end; it_v++) {
      (*it_u)->toggleEdge(*it_v);
    }
  }
  for (auto *v : this->neighbors) {
    v->applyRightClifford(CliffordOperator::S);
  }
  this->applyRightClifford(CliffordOperator::RX_INV);
}

void StationaryQubit::removeVertexOperation(StationaryQubit *qubit_to_avoid) {
  if (this->neighbors.empty() || this->vertex_operator == types::CliffordOperator::Id) {
    return;
  }
  auto *swapping_partner_temp = qubit_to_avoid;
  for (auto *v : this->neighbors) {
    if (v != qubit_to_avoid) {
      swapping_partner_temp = v;
      break;
    }
  }
  auto swapping_partner = swapping_partner_temp;
  std::string decomposition_string = decomposition_table[(int)this->vertex_operator];
  for (int i = decomposition_string.size() - 1; i >= 0; i--) {
    if (decomposition_string[i] == 'V') {
      this->localComplement();
    } else {
      // 'U'
      swapping_partner->localComplement();
    }
  }
}

void StationaryQubit::applyPureCZ(StationaryQubit *another_qubit) {
  auto *aq = another_qubit;
  this->removeVertexOperation(aq);
  aq->removeVertexOperation(this);
  this->removeVertexOperation(aq);

  bool has_edge = this->isNeighbor(aq);
  int current_vop = (int)(this->vertex_operator);
  int aq_vop = (int)(aq->vertex_operator);
  this->vertex_operator = controlled_Z_lookup_node_1[has_edge][current_vop][aq_vop];
  aq->vertex_operator = controlled_Z_lookup_node_2[has_edge][current_vop][aq_vop];
  if (has_edge != controlled_Z_lookup_edge[has_edge][current_vop][aq_vop]) {
    this->toggleEdge(aq);
  }
}

EigenvalueResult StationaryQubit::graphMeasureZ() {
  auto vop = this->vertex_operator;
  auto result = EigenvalueResult::PLUS_ONE;
  if (this->neighbors.empty()) {
    switch (vop) {
      case CliffordOperator::H:
      case CliffordOperator::RY_INV:
      case CliffordOperator::S_INV_RY_INV:
      case CliffordOperator::S_RY_INV:
        break;
      case CliffordOperator::RY:
      case CliffordOperator::S_INV_RY:
      case CliffordOperator::S_RY:
      case CliffordOperator::Z_RY:
        result = EigenvalueResult::MINUS_ONE;
        break;
      default:
        result = (dblrand() < 0.5) ? EigenvalueResult::PLUS_ONE : EigenvalueResult::MINUS_ONE;
    }
  } else {
    this->removeVertexOperation(this);  // nothing to be avoided
    result = (dblrand() < 0.5) ? EigenvalueResult::PLUS_ONE : EigenvalueResult::MINUS_ONE;
    this->removeAllEdges();
  }
  this->vertex_operator = (result == EigenvalueResult::PLUS_ONE) ? CliffordOperator::H : CliffordOperator::RY;
  return result;
}

// public member functions

void StationaryQubit::cnotGate(IStationaryQubit *control_qubit) {
  // apply memory error
  this->applyClifford(CliffordOperator::H);  // use apply Clifford for pure operation
  this->applyPureCZ((StationaryQubit *)control_qubit);
  this->applyClifford(CliffordOperator::H);
  // apply CNOT error
}

void StationaryQubit::hadamardGate() {
  // apply memory error
  this->applyClifford(CliffordOperator::H);
  // apply single qubit gate error
}
void StationaryQubit::zGate() {
  // apply memory error
  this->applyClifford(CliffordOperator::Z);
  // apply single qubit gate error
}
void StationaryQubit::xGate() {
  // apply memory error
  this->applyClifford(CliffordOperator::X);
  // apply single qubit gate error
}
void StationaryQubit::sGate() {
  // apply memory error
  this->applyClifford(CliffordOperator::S);
  // apply single qubit gate error
}
void StationaryQubit::sdgGate() {
  // apply memory error
  this->applyClifford(CliffordOperator::S_INV);
  // apply single qubit gate error
}
void StationaryQubit::excite() {
  auto result = this->measureZ();
  if (result == EigenvalueResult::PLUS_ONE) {
    this->applyClifford(CliffordOperator::X);
  }
}
void StationaryQubit::relax() {
  auto result = this->measureZ();
  if (result == EigenvalueResult::MINUS_ONE) {
    this->applyClifford(CliffordOperator::X);
  }
}

EigenvalueResult StationaryQubit::measureX() {
  this->hadamardGate();
  return this->measureZ();
}

EigenvalueResult StationaryQubit::measureY() {
  this->sdgGate();
  this->hadamardGate();
  return this->measureZ();
}

EigenvalueResult StationaryQubit::measureZ() {
  // apply memory error
  auto result = this->graphMeasureZ();
  // apply measurement error
  return result;
}

// initialize static variables
CliffordOperator StationaryQubit::clifford_application_lookup[24][24] =
#include "clifford_application_lookup.tbl"
    ;

bool StationaryQubit::controlled_Z_lookup_edge[2][24][24] =
#include "cz_lookup_edge.tbl"
    ;

CliffordOperator StationaryQubit::controlled_Z_lookup_node_1[2][24][24] =
#include "cz_lookup_node_1.tbl"
    ;

CliffordOperator StationaryQubit::controlled_Z_lookup_node_2[2][24][24] =
#include "cz_lookup_node_2.tbl"
    ;

std::string StationaryQubit::decomposition_table[24] = {
    "", "VV", "UUVV", "UU", "VVV", "V", "VUU", "UUV", "UVUUU", "UUUVU", "UVVVU", "UVU", "U", "UUU", "VVU", "UVV", "UVVV", "UV", "UVUU", "UUUV", "VVVU", "VU", "VUUU", "UUVU",
};

}  // namespace modules
}  // namespace quisp
