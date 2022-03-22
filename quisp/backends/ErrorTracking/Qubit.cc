#include "Qubit.h"
#include <stdexcept>
#include "Backend.h"
namespace quisp::backends::error_tracking {

ErrorTrackingQubit::ErrorTrackingQubit(const IQubitId* id, ErrorTrackingBackend* const backend) : id(id), memory_transition_matrix(MatrixXd::Zero(7, 7)), backend(backend) {
  // emission_success_probability = par("emission_success_probability");
}
ErrorTrackingQubit::~ErrorTrackingQubit() {}
void ErrorTrackingQubit::setMemoryErrorRates(double x_error_rate, double y_error_rate, double z_error_rate, double excitation_rate, double relaxation_rate,
                                             double completely_mixed_rate) {
  memory_err.x_error_rate = x_error_rate;
  memory_err.y_error_rate = y_error_rate;
  memory_err.z_error_rate = z_error_rate;
  memory_err.excitation_error_rate = excitation_rate;
  memory_err.relaxation_error_rate = relaxation_rate;
  memory_err.completely_mixed_rate = completely_mixed_rate;
  double error_rate = x_error_rate + y_error_rate + z_error_rate + excitation_rate + relaxation_rate + completely_mixed_rate;  // This is per μs.
  memory_err.error_rate = error_rate;
  // clang-format off
  memory_transition_matrix <<
    1 - error_rate,  x_error_rate,   z_error_rate,   y_error_rate,   excitation_rate,                             relaxation_rate,                             completely_mixed_rate,
    x_error_rate,    1 - error_rate, y_error_rate,   z_error_rate,   excitation_rate,                             relaxation_rate,                             completely_mixed_rate,
    z_error_rate,    y_error_rate,   1 - error_rate, x_error_rate,   excitation_rate,                             relaxation_rate,                             completely_mixed_rate,
    y_error_rate,    z_error_rate,   x_error_rate,   1 - error_rate, excitation_rate,                             relaxation_rate,                             completely_mixed_rate,
    0,               0,              0,              0,              1 - relaxation_rate - completely_mixed_rate, relaxation_rate,                             completely_mixed_rate,
    0,               0,              0,              0,              excitation_rate,                             1 - excitation_rate - completely_mixed_rate, completely_mixed_rate,
    0,               0,              0,              0,              excitation_rate,                             relaxation_rate,                             1 - excitation_rate - relaxation_rate;
  // clang-format on
}

void ErrorTrackingQubit::applySingleQubitGateError(SingleGateErrorModel const& err) {
  if (err.pauli_error_rate == 0) {
    return;
  }
  // Gives a random double between 0.0 ~ 1.0
  double rand = backend->dblrand();

  /*
   * 0.0    No_error_ceil       Z_error_ceil  1.0
   *  |          |                   |         |
   *  | No Error | X Error | Z Error | Y Error |
   *                       |
   *                  X_error_ceil
   */
  if (rand <= err.no_error_ceil) {
    // No error
  } else if (err.no_error_ceil < rand && rand <= err.x_error_ceil && (err.no_error_ceil != err.x_error_ceil)) {
    // X error
    addErrorX();
  } else if (err.x_error_ceil < rand && rand <= err.z_error_ceil && (err.x_error_ceil != err.z_error_ceil)) {
    // Z error
    addErrorZ();
  } else {
    // Y error
    addErrorZ();
    addErrorX();
  }
}

void ErrorTrackingQubit::applyTwoQubitGateError(TwoQubitGateErrorModel const& err, ErrorTrackingQubit* another_qubit) {
  if (err.pauli_error_rate == 0) {
    return;
  }

  // Gives a random double between 0.0 ~ 1.0
  double rand = backend->dblrand();

  /*
   * 0.0  No_error_ceil    XI_error_ceil     IY_error_ceil     YY_error_ceil    ZI_error_ceil  1.0
   *  |        |                 |                 |                 |                 |        |
   *  | No err | IX err | XI err | XX err | IY err | YI err | YY err | IZ err | ZI err | ZZ err |
   *                    |                 |                 |                 |
   *              IX_error_ceil      XX_error_ceil     YI_error_ceil    IZ_error_ceil
   */
  if (rand <= err.no_error_ceil) {
    // No error
  } else if (err.no_error_ceil < rand && rand <= err.ix_error_ceil && (err.no_error_ceil != err.ix_error_ceil)) {
    // IX error
    addErrorX();
  } else if (err.ix_error_ceil < rand && rand <= err.xi_error_ceil && (err.ix_error_ceil != err.xi_error_ceil)) {
    // XI error
    another_qubit->addErrorX();
  } else if (err.xi_error_ceil < rand && rand <= err.xx_error_ceil && (err.xi_error_ceil != err.xx_error_ceil)) {
    // XX error
    addErrorX();
    another_qubit->addErrorX();
  } else if (err.xx_error_ceil < rand && rand <= err.iz_error_ceil && (err.xx_error_ceil != err.iz_error_ceil)) {
    // IZ error
    addErrorZ();
  } else if (err.iz_error_ceil < rand && rand <= err.zi_error_ceil && (err.iz_error_ceil != err.zi_error_ceil)) {
    // ZI error
    another_qubit->addErrorZ();
  } else if (err.zi_error_ceil < rand && rand <= err.zz_error_ceil && (err.zi_error_ceil != err.zz_error_ceil)) {
    // ZZ error
    addErrorZ();
    another_qubit->addErrorZ();
  } else if (err.zz_error_ceil < rand && rand <= err.iy_error_ceil && (err.zz_error_ceil != err.iy_error_ceil)) {
    // IY error
    addErrorX();
    addErrorZ();
  } else if (err.iy_error_ceil < rand && rand <= err.yi_error_ceil && (err.iy_error_ceil != err.yi_error_ceil)) {
    // YI error
    another_qubit->addErrorX();
    another_qubit->addErrorZ();
  } else {
    // YY error
    addErrorX();
    addErrorZ();
    another_qubit->addErrorX();
    another_qubit->addErrorZ();
  }
}
void ErrorTrackingQubit::applyMemoryError() {
  // update();
  if (entangled_partner == nullptr && density_matrix_collapsed(0, 0).real() == -111 && !no_density_matrix_nullptr_entangled_partner_ok) {
    throw std::runtime_error("This must not happen in apply memory error");
  }

  // If no memory error occurs, or if the state is completely mixed, skip this memory error simulation.
  if (memory_err.error_rate == 0) return;

  SimTime current_time = backend->getSimTime();

  // Check when the error got updated last time.
  // Errors will be performed depending on the difference between that time and the current time.
  double time_evolution = current_time.dbl() - updated_time.dbl();
  double time_evolution_microsec = time_evolution * 1000000 /** 100*/;
  if (time_evolution_microsec > 0) {
    bool skip_exponentiation = false;
    for (int i = 0; i < memory_transition_matrix.cols(); i++) {
      if (memory_transition_matrix(0, i) == 1) {
        // Do not to the exponentiation! Eigen will mess up the exponentiation anyway...
        skip_exponentiation = true;
        break;
      }
    }

    MatrixXd transition_mat(7, 7);
    if (!skip_exponentiation) {
      // calculate time evoluted error matrix: Q^(time_evolution_microsec) in Eq 5.3
      MatrixPower<MatrixXd> q_pow(memory_transition_matrix);
      transition_mat = q_pow(time_evolution_microsec);
    } else {
      transition_mat = memory_transition_matrix;
    }

    // validate transition_mat
    for (int r = 0; r < transition_mat.rows(); r++) {
      double col_sum = 0;
      for (int i = 0; i < transition_mat.cols(); i++) {
        col_sum += transition_mat(r, i);
      }
      if (col_sum > 1.01 || col_sum < 0.99) {
        throw std::runtime_error("Row of the transition matrix does not sum up to 1.");
      }
    }

    if (std::isnan(transition_mat(0, 0))) {
      throw std::runtime_error("Transition maatrix is NaN. This is Eigen's fault.");
    }

    // pi(0 ~ 6) vector in Eq 5.3
    MatrixXd pi_vector(1, 7);  // I, X, Z, Y, Ex, Re, Cm
    if (has_excitation_error) {
      pi_vector << 0, 0, 0, 0, 1, 0, 0;  // excitation error
    } else if (has_relaxation_error) {
      pi_vector << 0, 0, 0, 0, 0, 1, 0;  // relaxation error
    } else if (has_completely_mixed_error) {
      pi_vector << 0, 0, 0, 0, 0, 0, 1;  // completely mixed error
    } else if (has_z_error && has_x_error) {
      pi_vector << 0, 0, 0, 1, 0, 0, 0;  // Y error
    } else if (has_z_error && !has_x_error) {
      pi_vector << 0, 0, 1, 0, 0, 0, 0;  // Z error
    } else if (!has_z_error && has_x_error) {
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
    double rand = backend->dblrand();

    if (rand < clean_ceil) {
      // Qubit will end up with no error
      has_x_error = false;
      has_z_error = false;
    } else if (clean_ceil <= rand && rand < x_ceil && (clean_ceil != x_ceil)) {
      // X error
      has_x_error = true;
      has_z_error = false;
    } else if (x_ceil <= rand && rand < z_ceil && (x_ceil != z_ceil)) {
      // Z error
      has_x_error = false;
      has_z_error = true;
    } else if (z_ceil <= rand && rand < y_ceil && (z_ceil != y_ceil)) {
      // Y error
      has_x_error = true;
      has_z_error = true;
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
        entangled_partner->updated_time = current_time;
        // Break entanglement with partner. Overwrite its density matrix.
        entangled_partner->setCompletelyMixedDensityMatrix();
      }
      setCompletelyMixedDensityMatrix();
    }
  }
  updated_time = current_time;
}
void ErrorTrackingQubit::addErrorX() { has_x_error = !has_x_error; }
void ErrorTrackingQubit::addErrorZ() { has_z_error = !has_z_error; }
void ErrorTrackingQubit::setFree() {
  has_x_error = false;
  has_z_error = false;
  has_relaxation_error = false;
  has_excitation_error = false;
  has_completely_mixed_error = false;
}
void ErrorTrackingQubit::setRelaxedDensityMatrix() {
  density_matrix_collapsed << 0, 0, 0, 1;
  has_completely_mixed_error = false;
  has_excitation_error = false;
  has_relaxation_error = true;
  has_x_error = false;
  has_z_error = false;
  god_dm_has_x_error = false;
  god_dm_has_z_error = false;

  // Still entangled
  if (entangled_partner != nullptr) {
    entangled_partner->updated_time = backend->getSimTime();
    entangled_partner->setCompletelyMixedDensityMatrix();
  }
}
void ErrorTrackingQubit::setExcitedDensityMatrix() {
  density_matrix_collapsed << 1, 0, 0, 0;  // Overwrite density matrix
  has_completely_mixed_error = false;
  has_excitation_error = true;
  has_relaxation_error = false;
  has_x_error = false;
  has_z_error = false;
  god_dm_has_x_error = false;
  god_dm_has_z_error = false;

  if (entangled_partner != nullptr) {  // If it used to be entangled...
    entangled_partner->updated_time = backend->getSimTime();
    entangled_partner->setCompletelyMixedDensityMatrix();
  }
}
void ErrorTrackingQubit::setCompletelyMixedDensityMatrix() {
  density_matrix_collapsed << (double)1. / (double)2., 0, 0, (double)1. / (double)2.;
  has_completely_mixed_error = true;
  has_excitation_error = false;
  has_relaxation_error = false;
  has_x_error = false;
  has_z_error = false;
  if (entangled_partner != nullptr) {
    entangled_partner->entangled_partner = nullptr;
    entangled_partner = nullptr;
  }
}

void ErrorTrackingQubit::update() { updated_time = backend->getSimTime(); }

MeasureXResult ErrorTrackingQubit::correlationMeasureX() {
  bool error = has_z_error;
  if (backend->dblrand() < measurement_err.x_error_rate) {
    error = !error;
  }
  return error ? MeasureXResult::HAS_Z_ERROR : MeasureXResult::NO_Z_ERROR;
}

MeasureYResult ErrorTrackingQubit::correlationMeasureY() {
  bool error = has_z_error != has_x_error;
  if (backend->dblrand() < measurement_err.y_error_rate) {
    error = !error;
  }
  return error ? MeasureYResult::HAS_XZ_ERROR : MeasureYResult::NO_XZ_ERROR;
}

MeasureZResult ErrorTrackingQubit::correlationMeasureZ() {
  bool error = has_x_error;
  if (backend->dblrand() < measurement_err.x_error_rate) {
    error = !error;
  }
  return error ? MeasureZResult::HAS_X_ERROR : MeasureZResult::NO_X_ERROR;
}

EigenvalueResult ErrorTrackingQubit::localMeasureX() {
  // the Z error will propagate to its partner; This only works for Bell pair and entanglement swapping for now
  if (this->entangled_partner != nullptr && has_z_error) {
    this->entangled_partner->addErrorZ();
  }

  auto result = EigenvalueResult::PLUS_ONE;
  if (backend->dblrand() < 0.5) {
    result = EigenvalueResult::MINUS_ONE;
    if (this->entangled_partner != nullptr) {
      this->entangled_partner->addErrorZ();
    }
  }
  if (backend->dblrand() < this->measurement_err.x_error_rate) {
    result = result == EigenvalueResult::PLUS_ONE ? EigenvalueResult::MINUS_ONE : EigenvalueResult::PLUS_ONE;
  }
  return result;
}

EigenvalueResult ErrorTrackingQubit::localMeasureZ() {
  // the X error will propagate to its partner; This only works for Bell pair and entanglement swapping for now

  if (this->entangled_partner != nullptr && has_x_error) {
    this->entangled_partner->addErrorX();
  }

  auto result = EigenvalueResult::PLUS_ONE;
  if (backend->dblrand() < 0.5) {
    result = EigenvalueResult::MINUS_ONE;
    if (this->entangled_partner != nullptr) {
      this->entangled_partner->addErrorX();
    }
  }
  if (backend->dblrand() < this->measurement_err.z_error_rate) {
    result = result == EigenvalueResult::PLUS_ONE ? EigenvalueResult::MINUS_ONE : EigenvalueResult::PLUS_ONE;
  }
  return result;
}

void ErrorTrackingQubit::gateX() {
  applySingleQubitGateError(gate_err_x);
  has_x_error = !has_x_error;
}
void ErrorTrackingQubit::gateZ() {
  applySingleQubitGateError(gate_err_z);
  has_z_error = !has_z_error;
}
void ErrorTrackingQubit::gateH() {
  applySingleQubitGateError(gate_err_h);
  bool z = has_z_error;
  has_z_error = has_x_error;
  has_x_error = z;
}
void ErrorTrackingQubit::gateCNOT(IQubit* const control_qubit) {
  // Need to add noise here later
  auto* et_control_qubit = dynamic_cast<ErrorTrackingQubit*>(control_qubit);
  if (et_control_qubit == nullptr) {
    throw std::runtime_error("ErrorTrackingQubit::gateCNOT: control_qubit is not an ErrorTrackingQubit");
  }
  applyTwoQubitGateError(gate_err_cnot, et_control_qubit);

  if (et_control_qubit->has_x_error) {
    // X error propagates from control to target. If an X error is already present, then it cancels out.
    has_x_error = !has_x_error;
  }

  if (has_z_error) {
    // Z error propagates from target to control. If an Z error is already present, then it cancels out.
    et_control_qubit->has_z_error = !et_control_qubit->has_z_error;
  }
}

bool ErrorTrackingQubit::purifyX(IQubit* const control_qubit) {
  auto* et_control_qubit = dynamic_cast<ErrorTrackingQubit*>(control_qubit);
  if (et_control_qubit == nullptr) {
    throw std::runtime_error("ErrorTrackingQubit::purifyX: control_qubit is not an ErrorTrackingQubit");
  }
  // This could result in completelty mixed, excited, relaxed, which also affects the entangled partner.
  applyMemoryError();
  et_control_qubit->applyMemoryError();
  gateCNOT(control_qubit);
  return correlationMeasureZ() == MeasureZResult::NO_X_ERROR;
}

bool ErrorTrackingQubit::purifyZ(IQubit* const target_qubit) {
  auto* et_target_qubit = dynamic_cast<ErrorTrackingQubit*>(target_qubit);
  if (et_target_qubit == nullptr) {
    throw std::runtime_error("ErrorTrackingQubit::purifyZ: target_qubit is not an ErrorTrackingQubit");
  }
  applyMemoryError();  // This could result in completelty mixed, excited, relaxed, which also affects the entangled partner.
  et_target_qubit->applyMemoryError();
  et_target_qubit->gateCNOT(this);
  gateH();
  return this->correlationMeasureZ() == MeasureZResult::NO_X_ERROR;
}

Matrix2cd ErrorTrackingQubit::getErrorMatrix() {
  if (has_completely_mixed_error || has_relaxation_error) {
    throw std::runtime_error("CMerror in getErrorMatrix. Not supposed to happen.");
  }
  if (has_z_error && has_x_error) return pauli.Y;
  if (has_z_error) return pauli.Z;
  if (has_x_error) return pauli.X;
  return pauli.I;
}

// returns the density matrix of the Bell pair with error. This assumes that this is entangled with another stationary qubit.
// Measurement output will be based on this matrix, as long as it is still entangled.
QuantumState ErrorTrackingQubit::getQuantumState() {
  if (has_excitation_error || has_relaxation_error) throw std::runtime_error("this qubit is excited or relaxed");
  if (entangled_partner == nullptr) throw std::runtime_error("no entangled partner");
  if (entangled_partner->has_excitation_error || entangled_partner->has_relaxation_error) throw std::runtime_error("partner qubit is excited or relaxed");

  Matrix4cd error_mat = kroneckerProduct(getErrorMatrix(), entangled_partner->getErrorMatrix()).eval();
  // Assumes that the state is a 2 qubit state |00> + |11>
  Vector4cd ideal_bell_state(1 / sqrt(2), 0, 0, 1 / sqrt(2));
  Vector4cd actual_bell_state = error_mat * ideal_bell_state;

  QuantumState q;
  q.state_in_density_matrix = actual_bell_state * actual_bell_state.adjoint();
  q.state_in_ket = actual_bell_state;
  return q;
}

MeasurementOutcome ErrorTrackingQubit::measureDensityIndependent() {
  if (this->entangled_partner == nullptr && density_matrix_collapsed(0, 0).real() == -111) {
    std::cout << density_matrix_collapsed << "\n";
    throw std::runtime_error("Measuring a qubit that is not entangled with another qubit. Probably not what you want! Check whether address for each node is unique!!!");
  }
  MeasurementOperator this_measurement = randomMeasurementBasisSelection();  // Select basis randomly
  char Output;
  bool Output_is_plus;

  // Add memory error depending on the idle time. If excited/relaxed, this will immediately break entanglement, leaving the other qubit as completely mixed.
  applyMemoryError();

  // This becomes nullptr if this qubit got excited/relaxed or measured.
  if (this->entangled_partner != nullptr) {
    if (this->entangled_partner->entangled_partner == nullptr) {
      throw std::runtime_error("invalid entanglement partner");
    }
    // if (partner_measured) error("Entangled partner not nullptr but partner already measured....? Probably wrong.");
    if (has_completely_mixed_error || has_excitation_error || has_relaxation_error) {
      std::cout << "[Error]" << this << "\n";
      throw std::runtime_error("Entangled but completely mixed / Excited / Relaxed ? Probably wrong.");
    }
    // Also do the same on the partner if it is still entangled! This could break the entanglement due to relaxation/excitation error!
    entangled_partner->applyMemoryError();
  }

  /*-For debugging-*/
  char GOD_state = 'F';  // Completely mixed

  if (has_excitation_error)
    GOD_state = 'E';
  else if (has_excitation_error /* XXX: this might be relaxation error? */)
    GOD_state = 'R';
  else if (has_completely_mixed_error)
    GOD_state = 'C';
  else if (!has_x_error && has_z_error)  // To check stabilizers....
    GOD_state = 'Z';
  else if (has_x_error && !has_z_error)
    GOD_state = 'X';
  else if (has_x_error && has_z_error)
    GOD_state = 'Y';

  /*---------------*/

  // if there is an entanglement
  if (this->entangled_partner != nullptr) {
    // This qubit is nullptr
    if (this->entangled_partner->entangled_partner == nullptr) {
      throw std::runtime_error("Entangled_partner track wrong\n");
    }
  }

  // if the partner qubit is measured,
  if (this->partner_measured ||  has_completely_mixed_error || has_excitation_error ||
      has_relaxation_error) {  // The case when the density matrix is completely local to this qubit.

    if (density_matrix_collapsed(0, 0).real() == -111) {  // We always need some kind of density matrix inside this if statement.
      throw std::runtime_error("Single qubit density matrix not stored properly after partner's measurement, excitation/relaxation error.");
    }
    bool Xerr = has_x_error;
    bool Zerr = has_z_error;
    // This qubit's density matrix was created when the partner measured his own.
    // Because this qubit can be measured after that, we need to update the stored density matrix according to new errors occurred due to memory error.

    if (Xerr != god_dm_has_x_error) {  // Another X error to the dm.
      density_matrix_collapsed = pauli.X * density_matrix_collapsed * pauli.X.adjoint();
    }
    if (Zerr != god_dm_has_z_error) {  // Another Z error to the dm.
      density_matrix_collapsed = pauli.Z * density_matrix_collapsed * pauli.Z.adjoint();
    }

    // std::cout<<"Not entangled anymore. Density matrix is "<<density_matrix_collapsed<<"\n";

    Complex Prob_plus = (density_matrix_collapsed * this_measurement.plus.adjoint() * this_measurement.plus).trace();
    Complex Prob_minus = (density_matrix_collapsed * this_measurement.minus.adjoint() * this_measurement.minus).trace();
    double dbl = backend->dblrand();
    if (dbl < Prob_plus.real()) {
      Output = '+';
      Output_is_plus = true;
    } else {
      Output = '-';
      Output_is_plus = false;
    }
    // std::cout<<"\n This qubit was "<<this_measurement.basis<<"("<<Output<<"). \n";
  } else if (!this->partner_measured && !has_completely_mixed_error && !(has_relaxation_error || has_excitation_error) && this->entangled_partner != nullptr) {
    // This is assuming that this is some other qubit is entangled. Only Pauli errors are assumed.
    QuantumState current_state = getQuantumState();
    std::cout << "Current entangled state is " << current_state.state_in_ket << "\n";

    bool Xerr = god_dm_has_x_error;
    bool Zerr = god_dm_has_z_error;
    // std::cout<<"Entangled state is "<<current_state.state_in_ket<<"\n";

    Complex Prob_plus = current_state.state_in_ket.adjoint() * kroneckerProduct(this_measurement.plus, measurement_op.identity).eval().adjoint() *
                        kroneckerProduct(this_measurement.plus, measurement_op.identity).eval() * current_state.state_in_ket;
    Complex Prob_minus = current_state.state_in_ket.adjoint() * kroneckerProduct(this_measurement.minus, measurement_op.identity).eval().adjoint() *
                         kroneckerProduct(this_measurement.minus, measurement_op.identity).eval() * current_state.state_in_ket;

    // std::cout<<"Measurement basis = "<<this_measurement.basis<<"P(+) = "<<Prob_plus.real()<<", P(-) = "<<Prob_minus.real()<<"\n";
    double dbl = backend->dblrand();

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
    partners_dm = kroneckerProduct(ms.adjoint(), measurement_op.identity).eval() * current_state.state_in_density_matrix *
                  kroneckerProduct(ms.adjoint(), measurement_op.identity).eval().adjoint();
    normalized_partners_dm = partners_dm / partners_dm.trace();
    std::cout << "kroneckerProduct(ms.adjoint(),meas_op.identity).eval() = " << kroneckerProduct(ms.adjoint(), measurement_op.identity).eval() << "\n";
    std::cout << "dm = " << current_state.state_in_density_matrix << "\n";
    std::cout << "State was " << kroneckerProduct(ms.adjoint(), measurement_op.identity).eval() * current_state.state_in_density_matrix << "\n";
    std::cout << "\n This qubit was " << this_measurement.basis << "(" << Output << "). Partner's dm is now = " << normalized_partners_dm << "\n";
    entangled_partner->density_matrix_collapsed = normalized_partners_dm;

    // We actually do not need this as long as deleting entangled_partner completely is totally fine.
    entangled_partner->partner_measured = true;
    // if(entangled_partner->getIndex() == 71 && entangled_partner->node_address == 3)
    //	std::cout<<"-------------------"<<entangled_partner<<" in node["<<entangled_partner->node_address<<"] overwritten dm.\n";

    // Break entanglement.
    entangled_partner->entangled_partner = nullptr;
    // Save what error it had, when this density matrix was calculated.
    // Error may get updated in the future, so we need to track what error has been considered already in the dm.
    entangled_partner->god_dm_has_x_error = entangled_partner->has_x_error;
    entangled_partner->god_dm_has_z_error = entangled_partner->has_z_error;
  } else {
    throw std::runtime_error("Check condition in measure func.");
  }

  // add measurement error
  auto rand_num = backend->dblrand();
  if (this_measurement.basis == measurement_op.x_basis.basis && rand_num < measurement_err.x_error_rate ||
      this_measurement.basis == measurement_op.y_basis.basis && rand_num < measurement_err.y_error_rate ||
      this_measurement.basis == measurement_op.z_basis.basis && rand_num < measurement_err.z_error_rate) {
    Output_is_plus = !Output_is_plus;
  }

  MeasurementOutcome o;
  o.basis = this_measurement.basis;
  o.outcome_is_plus = Output_is_plus;
  o.GOD_clean = GOD_state;
  return o;
}

MeasurementOperator ErrorTrackingQubit::randomMeasurementBasisSelection() {
  MeasurementOperator this_measurement;
  double dbl = backend->dblrand();  // Random double value for random basis selection.
  std::cout << "Random dbl = " << dbl << "! \n ";

  if (dbl < ((double)1 / (double)3)) {  // X measurement!
    std::cout << "X measurement\n";
    this_measurement.plus = measurement_op.x_basis.plus;
    this_measurement.minus = measurement_op.x_basis.minus;
    this_measurement.basis = measurement_op.x_basis.basis;
    this_measurement.plus_ket = measurement_op.x_basis.plus_ket;
    this_measurement.minus_ket = measurement_op.x_basis.minus_ket;
  } else if (dbl >= ((double)1 / (double)3) && dbl < ((double)2 / (double)3)) {
    std::cout << "Z measurement\n";
    this_measurement.plus = measurement_op.z_basis.plus;
    this_measurement.minus = measurement_op.z_basis.minus;
    this_measurement.basis = measurement_op.z_basis.basis;
    this_measurement.plus_ket = measurement_op.z_basis.plus_ket;
    this_measurement.minus_ket = measurement_op.z_basis.minus_ket;
  } else {
    std::cout << "Y measurement\n";
    this_measurement.plus = measurement_op.y_basis.plus;
    this_measurement.minus = measurement_op.y_basis.minus;
    this_measurement.basis = measurement_op.y_basis.basis;
    this_measurement.plus_ket = measurement_op.y_basis.plus_ket;
    this_measurement.minus_ket = measurement_op.y_basis.minus_ket;
  }
  return this_measurement;
}

// Set error matrices. This is used in the process of simulating tomography.
const SingleQubitErrorModel ErrorTrackingQubit::pauli = {.X = (Matrix2cd() << 0, 1, 1, 0).finished(),
                                                         .Y = (Matrix2cd() << 0, Complex(0, -1), Complex(0, 1), 0).finished(),
                                                         .Z = (Matrix2cd() << 1, 0, 0, -1).finished(),
                                                         .I = (Matrix2cd() << 1, 0, 0, 1).finished()};

// Set measurement operators. This is used in the process of simulating tomography.
const MeasurementOperators ErrorTrackingQubit::measurement_op = {.x_basis = {.plus = (Matrix2cd() << 0.5, 0.5, 0.5, 0.5).finished(),
                                                                             .minus = (Matrix2cd() << 0.5, -0.5, -0.5, 0.5).finished(),
                                                                             .plus_ket = (Vector2cd() << 1 / sqrt(2), 1 / sqrt(2)).finished(),
                                                                             .minus_ket = (Vector2cd() << 1 / sqrt(2), -1 / sqrt(2)).finished(),
                                                                             .basis = 'X'},
                                                                 .z_basis = {.plus = (Matrix2cd() << 1, 0, 0, 0).finished(),
                                                                             .minus = (Matrix2cd() << 0, 0, 0, 1).finished(),
                                                                             .plus_ket = (Vector2cd() << 1, 0).finished(),
                                                                             .minus_ket = (Vector2cd() << 0, 1).finished(),
                                                                             .basis = 'Z'},
                                                                 .y_basis = {.plus = (Matrix2cd() << 0.5, Complex(0, -0.5), Complex(0, 0.5), 0.5).finished(),
                                                                             .minus = (Matrix2cd() << 0.5, Complex(0, 0.5), Complex(0, -0.5), 0.5).finished(),
                                                                             .plus_ket = (Vector2cd() << 1 / sqrt(2), Complex(0, 1 / sqrt(2))).finished(),
                                                                             .minus_ket = (Vector2cd() << 1 / sqrt(2), -Complex(0, 1 / sqrt(2))).finished(),
                                                                             .basis = 'Y'},
                                                                 .identity = (Matrix2cd() << 1, 0, 0, 1).finished()};

}  // namespace quisp::backends::error_tracking
