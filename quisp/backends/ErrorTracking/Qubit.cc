#include "Qubit.h"
#include <Eigen/Dense>

namespace quisp::backends::error_tracking {
using Eigen::Matrix2cd;
using Eigen::MatrixXd;
using Eigen::Vector2cd;

// Set error matrices. This is used in the process of simulating tomography.
const single_qubit_error ErrorTrackingQubit::Pauli = {.X = (Matrix2cd() << 0, 1, 1, 0).finished(),
                                                      .Y = (Matrix2cd() << 0, Complex(0, -1), Complex(0, 1), 0).finished(),
                                                      .Z = (Matrix2cd() << 1, 0, 0, -1).finished(),
                                                      .I = (Matrix2cd() << 1, 0, 0, 1).finished()};

// Set measurement operators. This is used in the process of simulating tomography.
const measurement_operators ErrorTrackingQubit::meas_op = {.X_basis = {.plus = (Matrix2cd() << 0.5, 0.5, 0.5, 0.5).finished(),
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

ErrorTrackingQubit::ErrorTrackingQubit(const QubitId id)
    : id(id),
      Memory_Transition_matrix(MatrixXd::Zero(7, 7)),
      updated_time(SimTime()){
          // emission_success_probability = par("emission_success_probability");

          // setSingleQubitGateErrorModel(Hgate_error, "Hgate");
          // setSingleQubitGateErrorModel(Xgate_error, "Xgate");
          // setSingleQubitGateErrorModel(Zgate_error, "Zgate");
          // setTwoQubitGateErrorCeilings(CNOTgate_error, "CNOTgate");
          // setMeasurementErrorModel(Measurement_error);
      };
ErrorTrackingQubit::~ErrorTrackingQubit() {}

void ErrorTrackingQubit::setMemoryErrorRates(double x_error_rate, double y_error_rate, double z_error_rate, double excitation_rate, double relaxation_rate,
                                             double completely_mixed_rate) {
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

void ErrorTrackingQubit::applySingleQubitGateError(SingleGateErrorModel const &err) {
  if (err.pauli_error_rate == 0) {
    return;
  }
  // Gives a random double between 0.0 ~ 1.0
  double rand = 0;  // dblrand();

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
void ErrorTrackingQubit::applyMemoryError() {}

void ErrorTrackingQubit::addXerror() {}
void ErrorTrackingQubit::addZerror() {}
void ErrorTrackingQubit::addYerror() {}

}  // namespace quisp::backends::error_tracking
