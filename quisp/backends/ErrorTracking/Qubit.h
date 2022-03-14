#pragma once
#include <Eigen/Eigen>
#include <iostream>
#include <stdexcept>
#include <unsupported/Eigen/KroneckerProduct>
#include <unsupported/Eigen/MatrixFunctions>
#include "../interfaces/IQuantumBackend.h"
#include "../interfaces/IQubit.h"
#include "omnetpp/simtime.h"
#include "types.h"

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

  void setFree() override;
  MeasureXResult correlationMeasureX();
  MeasureYResult correlationMeasureY();
  MeasureZResult correlationMeasureZ();
  EigenvalueResult localMeasureX();
  EigenvalueResult localMeasureZ();
  void gateX() override;
  void gateZ() override;
  void gateH() override;
  void gateCNOT(IQubit* const control_qubit) override;
  bool purifyX(IQubit* const control_qubit) override;
  bool purifyZ(IQubit* const target_qubit) override;

 protected:
  void applySingleQubitGateError(SingleGateErrorModel const& err);
  void applyTwoQubitGateError(TwoQubitGateErrorModel const& err, ErrorTrackingQubit* another_qubit);
  void applyMemoryError();
  void addErrorX();
  void addErrorZ();
  void setRelaxedDensityMatrix();
  void setExcitedDensityMatrix();
  void setCompletelyMixedDensityMatrix();

  void update();

  // constants
  SingleGateErrorModel gate_err_h;
  SingleGateErrorModel gate_err_x;
  SingleGateErrorModel gate_err_z;
  TwoQubitGateErrorModel gate_err_cnot;
  MeasurementErrorModel measurement_err;
  MemoryErrorModel memory_err;
  Eigen::MatrixXd memory_transition_matrix; /*I,X,Y,Z,Ex,Rl for single qubit. Unit in μs.*/
  double emission_success_probability;
  static const SingleQubitErrorModel pauli;
  static const MeasurementOperators measurement_op;

  // state
  bool has_x_error = false;
  bool has_z_error = false;
  bool has_relaxation_error = false;
  bool has_excitation_error = false;
  bool has_completely_mixed_error = false;
  SimTime updated_time = SimTime(0);
  Matrix2cd density_matrix_collapsed;  // Used when partner has been measured.
  bool no_density_matrix_nullptr_entangled_partner_ok = false;
  ErrorTrackingQubit* entangled_partner = nullptr;

  // other components
  ErrorTrackingBackend* const backend;
};

}  // namespace quisp::backends::error_tracking
