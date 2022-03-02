#pragma once
#include <Eigen/Eigen>
#include <stdexcept>
#include <unsupported/Eigen/KroneckerProduct>
#include <unsupported/Eigen/MatrixFunctions>
#include "../IQuantumBackend.h"
#include "types.h"

namespace quisp::backends::error_tracking {

using abstract::IQuantumBackend;
using abstract::IQubit;
using abstract::SimTime;
using abstract::SimTimeUnit;
using Eigen::Matrix2cd;
using Eigen::MatrixPower;
using Eigen::MatrixXd;
using Eigen::Vector2cd;

template <typename QubitId>
class ErrorTrackingBackend;

template <typename QubitId>
class ErrorTrackingQubit : public IQubit<QubitId> {
 public:
  ErrorTrackingQubit(const QubitId id, ErrorTrackingBackend<QubitId>* const backend)
      : id(id), Memory_Transition_matrix(MatrixXd::Zero(7, 7)), backend(backend), updated_time(SimTime()) {
    // emission_success_probability = par("emission_success_probability");

    // setSingleQubitGateErrorModel(Hgate_error, "Hgate");
    // setSingleQubitGateErrorModel(Xgate_error, "Xgate");
    // setSingleQubitGateErrorModel(Zgate_error, "Zgate");
    // setTwoQubitGateErrorCeilings(CNOTgate_error, "CNOTgate");
    // setMeasurementErrorModel(Measurement_error);
  }
  ~ErrorTrackingQubit() {}
  void setMemoryErrorRates(double x_error_rate, double y_error_rate, double z_error_rate, double excitation_rate, double relaxation_rate, double completely_mixed_rate) {
    memory_err.X_error_rate = x_error_rate;
    memory_err.Y_error_rate = y_error_rate;
    memory_err.Z_error_rate = z_error_rate;
    memory_err.excitation_error_rate = excitation_rate;
    memory_err.relaxation_error_rate = relaxation_rate;
    memory_err.completely_mixed_rate = completely_mixed_rate;
    double error_rate = x_error_rate + y_error_rate + z_error_rate + excitation_rate + relaxation_rate + completely_mixed_rate;  // This is per μs.
    memory_err.error_rate = error_rate;
    // clang-format off
  Memory_Transition_matrix <<
    1 - error_rate,  x_error_rate,   z_error_rate,   y_error_rate,   excitation_rate,                             relaxation_rate,                             completely_mixed_rate,
    x_error_rate,    1 - error_rate, y_error_rate,   z_error_rate,   excitation_rate,                             relaxation_rate,                             completely_mixed_rate,
    z_error_rate,    y_error_rate,   1 - error_rate, x_error_rate,   excitation_rate,                             relaxation_rate,                             completely_mixed_rate,
    y_error_rate,    z_error_rate,   x_error_rate,   1 - error_rate, excitation_rate,                             relaxation_rate,                             completely_mixed_rate,
    0,               0,              0,              0,              1 - relaxation_rate - completely_mixed_rate, relaxation_rate,                             completely_mixed_rate,
    0,               0,              0,              0,              excitation_rate,                             1 - excitation_rate - completely_mixed_rate, completely_mixed_rate,
    0,               0,              0,              0,              excitation_rate,                             relaxation_rate,                             1 - excitation_rate - relaxation_rate;
    // clang-format on
  }
  void reset();

  QubitId id;

 protected:
  void applySingleQubitGateError(SingleGateErrorModel const& err) {
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

  void applyTwoQubitGateError(TwoQubitGateErrorModel const& err, ErrorTrackingQubit<QubitId>* another_qubit) {
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
  void applyMemoryError() {
    // update();
    if (entangled_partner == nullptr && Density_Matrix_Collapsed(0, 0).real() == -111 && !no_density_matrix_nullptr_entangled_partner_ok) {
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
  void addXerror() { has_x_error = !has_x_error; }
  void addZerror() { has_z_error = !has_z_error; }
  void setFree() {
    has_x_error = false;
    has_z_error = false;
    has_relaxation_error = false;
    has_excitation_error = false;
    has_completely_mixed_error = false;
  }
  void setRelaxedDensityMatrix() {
    Density_Matrix_Collapsed << 0, 0, 0, 1;
    has_completely_mixed_error = false;
    has_excitation_error = false;
    has_relaxation_error = true;
    has_x_error = false;
    has_z_error = false;
    // GOD_dm_Xerror = false;
    // GOD_dm_Zerror = false;

    // Still entangled
    if (entangled_partner != nullptr) {
      entangled_partner->updated_time = backend->getSimTime();
      entangled_partner->setCompletelyMixedDensityMatrix();
    }
  }
  void setExcitedDensityMatrix() {
    Density_Matrix_Collapsed << 1, 0, 0, 0;  // Overwrite density matrix
    has_completely_mixed_error = false;
    has_excitation_error = true;
    has_relaxation_error = false;
    has_x_error = false;
    has_z_error = false;
    // GOD_dm_Xerror = false;
    // GOD_dm_Zerror = false;

    if (entangled_partner != nullptr) {  // If it used to be entangled...
      entangled_partner->updated_time = backend->getSimTime();
      entangled_partner->setCompletelyMixedDensityMatrix();
    }
  }
  void setCompletelyMixedDensityMatrix() {
    Density_Matrix_Collapsed << (double)1. / (double)2., 0, 0, (double)1. / (double)2.;
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

  void update() { updated_time = backend->getSimTime(); }

  // constants
  SingleGateErrorModel Hgate_error;
  SingleGateErrorModel Xgate_error;
  SingleGateErrorModel Zgate_error;
  TwoQubitGateErrorModel CNOTgate_error;
  MeasurementErrorModel Measurement_error;
  double emission_success_probability;
  Eigen::MatrixXd Memory_Transition_matrix; /*I,X,Y,Z,Ex,Rl for single qubit. Unit in μs.*/
  memory_error_model memory_err;
  static const single_qubit_error Pauli;
  static const measurement_operators meas_op;
  // other components
  ErrorTrackingBackend<QubitId>* const backend;
  ErrorTrackingQubit<QubitId>* entangled_partner = nullptr;

  // state
  bool has_x_error;
  bool has_z_error;
  bool has_relaxation_error;
  bool has_excitation_error;
  bool has_completely_mixed_error;
  SimTime updated_time;
  Matrix2cd Density_Matrix_Collapsed;  // Used when partner has been measured.
  bool no_density_matrix_nullptr_entangled_partner_ok;
};

// Set error matrices. This is used in the process of simulating tomography.
template <typename QubitId>
const single_qubit_error ErrorTrackingQubit<QubitId>::Pauli = {.X = (Matrix2cd() << 0, 1, 1, 0).finished(),
                                                               .Y = (Matrix2cd() << 0, Complex(0, -1), Complex(0, 1), 0).finished(),
                                                               .Z = (Matrix2cd() << 1, 0, 0, -1).finished(),
                                                               .I = (Matrix2cd() << 1, 0, 0, 1).finished()};

// Set measurement operators. This is used in the process of simulating tomography.
template <typename QubitId>
const measurement_operators ErrorTrackingQubit<QubitId>::meas_op = {.X_basis = {.plus = (Matrix2cd() << 0.5, 0.5, 0.5, 0.5).finished(),
                                                                                .minus = (Matrix2cd() << 0.5, -0.5, -0.5, 0.5).finished(),
                                                                                .plus_ket = (Vector2cd() << 1 / sqrt(2), 1 / sqrt(2)).finished(),
                                                                                .minus_ket = (Vector2cd() << 1 / sqrt(2), -1 / sqrt(2)).finished(),
                                                                                .basis = 'X'},
                                                                    .Z_basis = {.plus = (Matrix2cd() << 1, 0, 0, 0).finished(),
                                                                                .minus = (Matrix2cd() << 0, 0, 0, 1).finished(),
                                                                                .plus_ket = (Vector2cd() << 1, 0).finished(),
                                                                                .minus_ket = (Vector2cd() << 0, 1).finished(),
                                                                                .basis = 'Z'},
                                                                    .Y_basis = {.plus = (Matrix2cd() << 0.5, Complex(0, -0.5), Complex(0, 0.5), 0.5).finished(),
                                                                                .minus = (Matrix2cd() << 0.5, Complex(0, 0.5), Complex(0, -0.5), 0.5).finished(),
                                                                                .plus_ket = (Vector2cd() << 1 / sqrt(2), Complex(0, 1 / sqrt(2))).finished(),
                                                                                .minus_ket = (Vector2cd() << 1 / sqrt(2), -Complex(0, 1 / sqrt(2))).finished(),
                                                                                .basis = 'Y'},
                                                                    .identity = (Matrix2cd() << 1, 0, 0, 1).finished()};

}  // namespace quisp::backends::error_tracking
