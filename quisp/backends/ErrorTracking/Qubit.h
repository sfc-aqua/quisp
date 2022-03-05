#pragma once
#include <Eigen/Eigen>
#include <iostream>
#include <stdexcept>
#include <unsupported/Eigen/KroneckerProduct>
#include <unsupported/Eigen/MatrixFunctions>
#include "../IQuantumBackend.h"
#include "omnetpp/simtime.h"
#include "types.h"
// #include "Backend.h"
namespace quisp::backends::error_tracking {

using abstract::EigenvalueResult;
using abstract::IQuantumBackend;
using abstract::IQubit;
using abstract::IQubitId;
using abstract::MeasureXResult;
using abstract::MeasureYResult;
using abstract::MeasureZResult;
using abstract::SimTime;
using abstract::SimTimeUnit;
using Eigen::Matrix2cd;
using Eigen::MatrixPower;
using Eigen::MatrixXd;
using Eigen::Vector2cd;

class ErrorTrackingBackend;
class ErrorTrackingQubit : public IQubit {
 public:
  const IQubitId* id;

  ErrorTrackingQubit(const IQubitId* id, ErrorTrackingBackend* const backend);
  ~ErrorTrackingQubit();
  void setMemoryErrorRates(double x_error_rate, double y_error_rate, double z_error_rate, double excitation_rate, double relaxation_rate, double completely_mixed_rate);
  void reset();

 protected:
  void applySingleQubitGateError(SingleGateErrorModel const& err);

  void applyTwoQubitGateError(TwoQubitGateErrorModel const& err, ErrorTrackingQubit* another_qubit);
  void applyMemoryError();
  void addXerror();
  void addZerror();
  void setFree();
  void setRelaxedDensityMatrix();
  void setExcitedDensityMatrix();
  void setCompletelyMixedDensityMatrix();

  void update();
  MeasureXResult correlationMeasureX();
  MeasureYResult correlationMeasureY();
  MeasureZResult correlationMeasureZ();
  EigenvalueResult localMeasureX();
  EigenvalueResult localMeasureZ();

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
  ErrorTrackingBackend* const backend;
  ErrorTrackingQubit* entangled_partner = nullptr;

  // state
  bool has_x_error = false;
  bool has_z_error = false;
  bool has_relaxation_error = false;
  bool has_excitation_error = false;
  bool has_completely_mixed_error = false;
  SimTime updated_time = SimTime(0);
  Matrix2cd Density_Matrix_Collapsed;  // Used when partner has been measured.
  bool no_density_matrix_nullptr_entangled_partner_ok = false;
};

}  // namespace quisp::backends::error_tracking
