#pragma once

#include <PhotonicQubit_m.h>
#include <Eigen/Eigen>
#include <unordered_set>
namespace quisp {

namespace types {
enum class MeasureXResult : int {
  NO_Z_ERROR,
  HAS_Z_ERROR,
};
enum class MeasureYResult : int {
  NO_XZ_ERROR,
  HAS_XZ_ERROR,
};
enum class MeasureZResult : int {
  NO_X_ERROR,
  HAS_X_ERROR,
};

enum class EigenvalueResult : int {
  PLUS_ONE,
  MINUS_ONE,
};

enum class CliffordOperator : int {
  Id = 0,
  X,
  Y,
  Z,
  RX_INV,
  RX,
  Z_RX_INV,
  Z_RX,
  RY_INV,
  RY,
  H,
  Z_RY,
  S_INV,
  S,
  X_S_INV,
  X_S,
  S_INV_RX_INV,
  S_INV_RX,
  S_RX_INV,
  S_RX,
  S_INV_RY_INV,
  S_INV_RY,
  S_RY_INV,
  S_RY,
};

}  // namespace types

namespace modules {
struct emission_error_model {
  double pauli_error_rate;  // Overall error rate
  double Z_error_rate;
  double X_error_rate;
  double Y_error_rate;
  double Loss_error_rate;

  double No_error_ceil;
  double X_error_ceil;
  double Y_error_ceil;
  double Z_error_ceil;
  double Loss_error_ceil;
};

struct SingleGateErrorModel {
  double pauli_error_rate;  // Overall error rate
  double Z_error_rate;
  double X_error_rate;
  double Y_error_rate;

  double No_error_ceil;
  double Z_error_ceil;
  double X_error_ceil;
  double Y_error_ceil;
};

struct TwoQubitGateErrorModel {
  double pauli_error_rate;  // Overall error rate
  double IZ_error_rate;
  double ZI_error_rate;
  double ZZ_error_rate;
  double IY_error_rate;
  double YI_error_rate;
  double YY_error_rate;
  double IX_error_rate;
  double XI_error_rate;
  double XX_error_rate;

  double No_error_ceil;
  double IZ_error_ceil;
  double ZI_error_ceil;
  double ZZ_error_ceil;
  double IY_error_ceil;
  double YI_error_ceil;
  double YY_error_ceil;
  double IX_error_ceil;
  double XI_error_ceil;
  double XX_error_ceil;
};

struct memory_error_model {
  double error_rate;  // Overall error rate
  double Z_error_rate;
  double X_error_rate;
  double Y_error_rate;
  double excitation_error_rate;
  double relaxation_error_rate;
  double completely_mixed_rate;
};

struct MeasurementErrorModel {
  double x_error_rate;
  double y_error_rate;
  double z_error_rate;
};

struct GOD_error_model {
  bool has_X_error;
  bool has_Z_error;
  bool has_EX_error;
  bool has_RE_error;
  bool has_CM_error;
};

// Matrices of single qubit errors. Used when conducting tomography.
struct single_qubit_error {
  Eigen::Matrix2cd X;  // double 2*2 matrix
  Eigen::Matrix2cd Y;  // complex double 2*2 matrix
  Eigen::Matrix2cd Z;
  Eigen::Matrix2cd I;
};

struct quantum_state {
  Eigen::Matrix4cd state_in_density_matrix;
  Eigen::Vector4cd state_in_ket;
};

struct measurement_output_probabilities {
  double probability_plus_plus;  // P(+,+)
  double probability_minus_plus;  // P(+,-)
  double probability_plus_minus;  // P(-,+)
  double probability_minus_minus;  // P(-,-)
};

struct measurement_operator {
  Eigen::Matrix2cd plus;
  Eigen::Matrix2cd minus;
  Eigen::Vector2cd plus_ket;
  Eigen::Vector2cd minus_ket;
  char basis;
};

// Single qubit
struct measurement_operators {
  measurement_operator X_basis;
  measurement_operator Y_basis;
  measurement_operator Z_basis;
  Eigen::Matrix2cd identity;
};

struct measurement_outcome {
  char basis;
  bool outcome_is_plus;
  char GOD_clean;
};

class IStationaryQubit : public omnetpp::cSimpleModule {
 public:
  IStationaryQubit(){};
  virtual ~IStationaryQubit(){};

  virtual void setFree(bool consumed) = 0;
  /*In use. E.g. waiting for purification result.*/
  virtual void Lock(unsigned long rs_id, int rule_id, int action_id) = 0;
  virtual void Unlock() = 0;
  virtual bool isLocked() = 0;

  /**
   * \brief Emit photon.
   * \param pulse is 1 for the beginning of the burst, 2 for the end.
   */
  virtual void emitPhoton(int pulse) = 0;
  virtual types::MeasureXResult correlationMeasureX() = 0;
  virtual types::MeasureYResult correlationMeasureY() = 0;
  virtual types::MeasureZResult correlationMeasureZ() = 0;

  virtual types::EigenvalueResult localMeasureX() = 0;
  virtual types::EigenvalueResult localMeasureY() = 0;
  virtual types::EigenvalueResult localMeasureZ() = 0;

  /**
   * Performs measurement and returns +(true) or -(false) based on the density matrix of the state. Used for tomography.
   * */
  virtual measurement_outcome measure_density_independent() = 0; /*Separate dm calculation*/
  virtual types::EigenvalueResult measureX() = 0;
  virtual types::EigenvalueResult measureY() = 0;
  virtual types::EigenvalueResult measureZ() = 0;

  virtual void CNOT_gate(IStationaryQubit *control_qubit) = 0;
  virtual void Hadamard_gate() = 0;
  virtual void Z_gate() = 0;
  virtual void X_gate() = 0;
  virtual bool Xpurify(IStationaryQubit *resource_qubit) = 0;
  virtual bool Zpurify(IStationaryQubit *resource_qubit) = 0;

  virtual void cnotGate(IStationaryQubit *control_qubit) = 0;
  virtual void hadamardGate() = 0;
  virtual void zGate() = 0;
  virtual void xGate() = 0;
  virtual void sGate() = 0;
  virtual void sdgGate() = 0;
  virtual void excite() = 0;
  virtual void relax() = 0;

  /*GOD parameters*/
  GOD_error_model GOD_err{.has_X_error = false, .has_Z_error = false, .has_EX_error = false, .has_RE_error = false, .has_CM_error = false};
  virtual void setEntangledPartnerInfo(IStationaryQubit *partner) = 0;
  virtual void setCompletelyMixedDensityMatrix() = 0;
  virtual void addXerror() = 0;
  virtual void addZerror() = 0;

  int stationaryQubit_address;
  int node_address;
  int qnic_address;
  int qnic_type;
  int qnic_index;
  int GOD_entangled_stationaryQubit_address;
  int GOD_entangled_node_address;
  int GOD_entangled_qnic_address;
  int GOD_entangled_qnic_type;

  int action_index;
  bool no_density_matrix_nullptr_entangled_partner_ok;

  /** Pointer to the entangled qubit*/
  IStationaryQubit *entangled_partner = nullptr;
  /** Photon emitted at*/
  omnetpp::simtime_t emitted_time = -1;
  /** Stationary qubit last updated at*/
  omnetpp::simtime_t updated_time = -1;

  /** Standard deviation */
  double std;

  SingleGateErrorModel Hgate_error;
  SingleGateErrorModel Xgate_error;
  SingleGateErrorModel Zgate_error;
  TwoQubitGateErrorModel CNOTgate_error;
  MeasurementErrorModel Measurement_error;

  Eigen::Matrix2cd Density_Matrix_Collapsed;  // Used when partner has been measured.
  bool partner_measured;
  bool completely_mixed;
  bool excited_or_relaxed;
  bool GOD_dm_Xerror;
  bool GOD_dm_Zerror;
};

}  // namespace modules
}  // namespace quisp
