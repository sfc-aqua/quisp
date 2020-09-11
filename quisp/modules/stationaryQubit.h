/** \file StationaryQubit.h
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/14
 *
 *  \brief StationaryQubit
 */
#ifndef QUISP_MODULES_StationaryQubit_H_
#define QUISP_MODULES_StationaryQubit_H_

#include <PhotonicQubit_m.h>

using namespace Eigen;
using namespace omnetpp;
using namespace quisp::messages;

namespace quisp {
namespace modules {

#define STATIONARYQUBIT_PULSE_BEGIN 0x01
#define STATIONARYQUBIT_PULSE_END 0x02
#define STATIONARYQUBIT_PULSE_BOUND (STATIONARYQUBIT_PULSE_BEGIN | STATIONARYQUBIT_PULSE_END)

/** \class StationaryQubit StationaryQubit.h
 *
 *  \brief StationaryQubit
 */

typedef std::complex<double> Complex;

typedef struct {
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
} emission_error_model;

typedef struct {
  double pauli_error_rate;  // Overall error rate
  double Z_error_rate;
  double X_error_rate;
  double Y_error_rate;

  double No_error_ceil;
  double Z_error_ceil;
  double X_error_ceil;
  double Y_error_ceil;
} gate_error_model;

typedef struct {
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
} two_qubit_gate_error_model;

typedef struct {
  double error_rate;  // Overall error rate
  double Z_error_rate;
  double X_error_rate;
  double Y_error_rate;
  double excitation_error_rate;
  double relaxation_error_rate;
  double completely_mixed_rate;
} memory_error_model;

// Matrices of single qubit errors. Used when conducting tomography.
typedef struct {
  Matrix2cd X;  // double 2*2 matrix
  Matrix2cd Y;  // complex double 2*2 matrix
  Matrix2cd Z;
  Matrix2cd I;
} single_qubit_error;

typedef struct {
  Matrix4cd state_in_density_matrix;
  Vector4cd state_in_ket;
} quantum_state;

typedef struct {
  double probability_plus_plus;  // P(+,+)
  double probability_minus_plus;  // P(+,-)
  double probability_plus_minus;  // P(-,+)
  double probability_minus_minus;  // P(-,-)
} measurement_output_probabilities;

typedef struct {
  Matrix2cd plus;
  Matrix2cd minus;
  Vector2cd plus_ket;
  Vector2cd minus_ket;
  char basis;
} measurement_operator;

// Single qubit
typedef struct {
  measurement_operator X_basis;
  measurement_operator Y_basis;
  measurement_operator Z_basis;
  Matrix2cd identity;
} measurement_operators;

typedef struct {
  char basis;
  bool outcome_is_plus;
  char GOD_clean;
} measurement_outcome;

class StationaryQubit : public cSimpleModule {
 public:
  /** @name Errors
   *  @{
   */
  /*The Pauli errors get updated when this stationary qubit emits a photon,
   * when the emitted photon got an error in the channel and the BSA succeeded,
   * when a memory error occured due to idle time,
   * and local operation errors (gates).*/
  bool pauliXerr; /**< Bit flip error */
  bool pauliZerr; /**< Phase error. */
  /* For future use.
   * Completely mixed states, etc. */
  // bool nonPaulierr;
  // bool nonPaulierrTwo;
  //@}

  /** @name Entangled partner address
   *  @{                                  */
  /** Address node, or -1. */
  int NodeEntangledWith;
  /** Address and type of qNIC in node. */
  int QNICEntangledWith;
  int QNICtypeEntangledWith;
  /** Index of Qubit in qNIC. */
  int StationaryQubitEntangledWith;
  /** Pointer to the entangled qubit*/
  StationaryQubit *entangled_partner = nullptr;
  /** Photon emitted at*/
  simtime_t emitted_time = -1;
  /** Stationary qubit last updated at*/
  simtime_t updated_time = -1;
  //@}

  /** Stationary Qubit is free or reserved. */
  bool isBusy;
  /** Standard deviation */
  double std;

  double emission_success_probability;
  int numemitted;
  // emission_error_model emission_error;
  /** @name Pauli errors when emitting photons
   *  @{
   */
  /** Error rate when emitting photon*/

  gate_error_model Hgate_error;
  gate_error_model Xgate_error;
  gate_error_model Zgate_error;
  two_qubit_gate_error_model CNOTgate_error;
  gate_error_model Measurement_error;
  /* double emit_error_rate;
   double No_error_ceil;
   double X_error_ceil;
   double Y_error_ceil;
   double Z_error_ceil;*/
  //@}

  /** @name Pauli errors for Memories
   *  @{
   */
  /** Error rate for idle stationary qubits*/
  memory_error_model memory_err;
  double memory_error_rate;
  double memory_No_error_ceil;
  double memory_X_error_ceil;
  double memory_Y_error_ceil;
  double memory_Z_error_ceil;
  double memory_Excitation_error_ceil;
  double memory_Relaxation_error_ceil;
  //@}

  single_qubit_error Pauli;
  measurement_operators meas_op;
  MatrixXd Memory_Transition_matrix; /*I,X,Y,Z,Ex,Rl for single qubit. Unit in μs.*/
  MatrixXd Memory_Transition_matrix_ns; /*I,X,Y,Z,Ex,Rl for single qubit. Unit in ns.*/
  MatrixXd Memory_Transition_matrix_ms; /*I,X,Y,Z,Ex,Rl for single qubit. Unit in ns.*/
  // MatrixPower<MatrixXd> Apow(MatrixXd);
  // projected_states proj_states;
  Matrix2cd Density_Matrix_Collapsed;  // Used when partner has been measured.
  int num_purified;
  bool partner_measured;
  bool completely_mixed;
  bool excited_or_relaxed;
  bool GOD_dm_Xerror;
  bool GOD_dm_Zerror;

  virtual bool checkBusy();
  virtual void setFree(bool consumed);
  virtual void Lock(unsigned long rs_id, int rule_id, int action_id); /*In use. E.g. waiting for purification result.*/
  virtual void Unlock();
  virtual bool isLocked();
  virtual void Allocate();
  virtual void Deallocate();
  virtual bool isAllocated();

  double getFidelity() const { return fidelity; };
  void setFidelity(const double f) {
    fidelity = f;
    par("fidelity") = f;
  };

  /**
   * \brief Emit photon.
   * \param pulse is 1 for the beginning of the burst, 2 for the end.
   */
  virtual void emitPhoton(int pulse);

  /**
   * \brief Single Qubit X measurement.
   * \param If a Z error, which affects the X-measurement, is present, then returns false. Otherwise it returns true. This is only for simulating error propagations.
   * New errors only occur when wrong measurement result is delivered for feed-forward (The error on the measured qubit propagates to the byproduct gate target qubit).
   */
  virtual bool measure_X();

  /**
   * \brief Single Qubit Y measurement.
   * \param If a Z error OR an X error, which affects the Y-measurement, is present, then returns false. Otherwise it returns true. This is only for simulating error propagations.
   * New errors only occur when wrong measurement result is delivered for feed-forward (The error on the measured qubit propagates to the byproduct gate target qubit).
   */
  virtual bool measure_Y();

  /**
   * \brief Single Qubit Z measurement.
   * \param If an X error, which affects the Z-measurement, is present, then returns false. Otherwise it returns true. This is only for simulating error propagations.
   * New errors only occur when wrong measurement result is delivered for feed-forward (The error on the measured qubit propagates to the byproduct gate target qubit).
   */
  virtual bool measure_Z();

  /**
   * Performs measurement and returns +(true) or -(false) based on the density matrix of the state. Used for tomography.
   * */
  // virtual std::bitset<1> measure_density(char basis_this_qubit);/*Simultaneous dm calculation*/
  virtual measurement_outcome measure_density_independent(); /*Separate dm calculation*/

  /*Applies memory error to the given qubit*/
  virtual void apply_memory_error(StationaryQubit *qubit);

  virtual void apply_single_qubit_gate_error(gate_error_model gate, StationaryQubit *qubit);
  virtual void apply_two_qubit_gate_error(two_qubit_gate_error_model gate, StationaryQubit *first_qubit, StationaryQubit *second_qubit);
  /**
   * \brief Two qubit CNOT gate.
   * \param Need to specify the control qubit as an argument.
   */
  virtual void CNOT_gate(StationaryQubit *control_qubit);
  /**
   * \brief Single qubit Hadamard gate
   * \param X error transforms to Z, and vise-versa.
   */
  virtual void Hadamard_gate();

  virtual void Z_gate();

  virtual void X_gate();
  virtual bool Xpurify(StationaryQubit *resource_qubit);
  virtual bool Zpurify(StationaryQubit *resource_qubit);

  /*GOD parameters*/
  virtual void setEntangledPartnerInfo(StationaryQubit *partner);
  virtual void setCompletelyMixedDensityMatrix();
  virtual void setRelaxedDensityMatrix();
  virtual void setExcitedDensityMatrix();
  virtual void addXerror();
  virtual void addZerror();

  /** @name Self address
   *  @{                   */
  int stationaryQubit_address;
  int node_address;
  int qnic_address;
  int qnic_type;
  int qnic_index;

  //@}
  bool locked;
  unsigned long locked_ruleset_id;
  int locked_rule_id;
  int action_index;
  bool no_density_matrix_nullptr_entangled_partner_ok;

 private:
  PhotonicQubit *photon;
  double fidelity;
  bool allocated;
  int DEBUG_memory_X_count;
  int DEBUG_memory_Y_count;
  int DEBUG_memory_Z_count;

 protected:
  virtual void initialize();
  virtual void finish();
  virtual void handleMessage(cMessage *msg);
  virtual PhotonicQubit *generateEntangledPhoton();
  virtual void setBusy();
  // virtual void setErrorCeilings();
  // virtual void setEmissionPauliError();
  virtual Matrix2cd getErrorMatrix(StationaryQubit *qubit);  // returns the matrix that represents the errors on the Bell pair. (e.g. XY, XZ and ZI...)
  virtual quantum_state getQuantumState();  // returns the dm of the physical Bell pair. Used for tomography.
  virtual measurement_operator Random_Measurement_Basis_Selection();
  virtual gate_error_model SetSingleQubitGateErrorCeilings(std::string gate_name);
  virtual two_qubit_gate_error_model SetTwoQubitGateErrorCeilings(std::string gate_name);
  // virtual measurement_output_probabilities getOutputProbabilities(quantum_state state, char meas_basis);
};

}  // namespace modules
}  // namespace quisp

#endif /* QUISP_MODULES_StationaryQubit_H_ */
