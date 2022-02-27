#pragma once
#include <Eigen/Eigen>
#include "../IQuantumBackend.h"
#include "types.h"

namespace quisp::backends::error_tracking {

using abstract::IQuantumBackend;
using abstract::IQubit;
using abstract::QubitId;
using abstract::SimTime;
using abstract::SimTimeUnit;

class ErrorTrackingQubit : public IQubit {
 public:
  ErrorTrackingQubit(const QubitId id);
  ~ErrorTrackingQubit();
  void setMemoryErrorRates(double x_error_rate, double y_error_rate, double z_error_rate, double excitation_rate, double relaxation_rate, double completely_mixed_rate);
  void reset();

  QubitId id;

 protected:
  void applySingleQubitGateError(SingleGateErrorModel const &err);
  void applyMemoryError();
  void addXerror();
  void addZerror();
  void addYerror();

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

  // state
  bool has_x_error;
  bool has_z_error;
  bool has_relaxation_error;
  bool has_excitation_error;
  SimTime updated_time;
};
}  // namespace quisp::backends::error_tracking
