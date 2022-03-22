/** \file StationaryQubit.h
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/14
 *
 *  \brief StationaryQubit
 */
#pragma once

#include <PhotonicQubit_m.h>
#include <modules/common_types.h>
#include <utils/ComponentProvider.h>
#include <string>
#include "IStationaryQubit.h"
#include "QubitId.h"

namespace quisp {
namespace modules {

#define STATIONARYQUBIT_PULSE_BEGIN 0x01
#define STATIONARYQUBIT_PULSE_END 0x02
#define STATIONARYQUBIT_PULSE_BOUND (STATIONARYQUBIT_PULSE_BEGIN | STATIONARYQUBIT_PULSE_END)

/** \class StationaryQubit StationaryQubit.h
 *
 *  \brief StationaryQubit.
 *  \ref https://arxiv.org/abs/1908.10758
 */

typedef std::complex<double> Complex;
using quisp::modules::common::IBackendQubit;
using quisp::modules::common::IQuantumBackend;

class StationaryQubit : public IStationaryQubit {
 protected:
  std::unordered_set<StationaryQubit *> neighbors;
  types::CliffordOperator vertex_operator;
  void applyClifford(types::CliffordOperator op);
  void applyRightClifford(types::CliffordOperator op);
  bool isNeighbor(StationaryQubit *another_qubit);
  void addEdge(StationaryQubit *another_qubit);
  void deleteEdge(StationaryQubit *another_qubit);
  void toggleEdge(StationaryQubit *another_qubit);
  void removeAllEdges();
  void localComplement();
  void removeVertexOperation(StationaryQubit *qubit_to_avoid);
  void applyPureCZ(StationaryQubit *another_qubit);

  types::EigenvalueResult graphMeasureZ();

  static std::string decomposition_table[24];
  static types::CliffordOperator clifford_application_lookup[24][24];
  static bool controlled_Z_lookup_edge[2][24][24];
  static types::CliffordOperator controlled_Z_lookup_node_1[2][24][24];
  static types::CliffordOperator controlled_Z_lookup_node_2[2][24][24];

  IBackendQubit *qubit_ref;

 public:
  StationaryQubit();
  void setFree(bool consumed) override;
  /*In use. E.g. waiting for purification result.*/
  void Lock(unsigned long rs_id, int rule_id, int action_id) override;
  void Unlock() override;
  bool isLocked() override;

  /**
   * \brief Emit photon.
   * \param pulse is 1 for the beginning of the burst, 2 for the end.
   */
  void emitPhoton(int pulse) override;

  /**
   * \brief Single Qubit X measurement.
   * \param This is only for simulating error propagations.
   * New errors only occur when wrong measurement result is delivered for feed-forward
   * (The error on the measured qubit propagates to the byproduct gate target qubit).
   */
  virtual quisp::types::MeasureXResult correlationMeasureX() override;

  /**
   * \brief Single Qubit Y measurement.
   * This is only for simulating error propagations.
   * New errors only occur when wrong measurement result is delivered for feed-forward
   * (The error on the measured qubit propagates to the byproduct gate target qubit).
   */
  virtual types::MeasureYResult correlationMeasureY() override;

  /**
   * \brief Single Qubit Z measurement.
   * This is only for simulating error propagations.
   * New errors only occur when wrong measurement result is delivered for feed-forward
   * (The error on the measured qubit propagates to the byproduct gate target qubit).
   */
  virtual types::MeasureZResult correlationMeasureZ() override;

  virtual types::EigenvalueResult localMeasureX() override;
  virtual types::EigenvalueResult localMeasureY() override;
  virtual types::EigenvalueResult localMeasureZ() override;

  virtual types::EigenvalueResult measureX();
  virtual types::EigenvalueResult measureY();
  virtual types::EigenvalueResult measureZ();
  /**
   * Performs measurement and returns +(true) or -(false) based on the density matrix of the state. Used for tomography.
   * */
  // virtual std::bitset<1> measure_density(char basis_this_qubit);/*Simultaneous dm calculation*/
  virtual types::MeasurementOutcome measure_density_independent() override; /*Separate dm calculation*/

  /**
   * \brief Two qubit CNOT gate.
   * \param Need to specify the control qubit as an argument.
   */
  void cnotGate(IStationaryQubit *control_qubit) override;
  void CNOT_gate(IStationaryQubit *control_qubit) override;

  /**
   * \brief Single qubit Hadamard gate
   * \param X error transforms to Z, and vise-versa.
   */
  void Hadamard_gate() override;
  void Z_gate() override;
  void X_gate() override;
  bool Xpurify(IStationaryQubit *resource_qubit) override;
  bool Zpurify(IStationaryQubit *resource_qubit) override;

  // for graph state backend
  void hadamardGate() override;
  void zGate() override;
  void xGate() override;
  void sGate() override;
  void sdgGate() override;
  void excite() override;
  void relax() override;

  /*GOD parameters*/
  void setEntangledPartnerInfo(IStationaryQubit *partner) override;
  void setCompletelyMixedDensityMatrix();
  void setRelaxedDensityMatrix();
  void setExcitedDensityMatrix();
  void addXerror();
  void addZerror();

  double emission_success_probability;

  memory_error_model memory_err;

  single_qubit_error Pauli;
  measurement_operators meas_op;
  // https://arxiv.org/abs/1908.10758 Eq 5.2
  Eigen::MatrixXd Memory_Transition_matrix; /*I,X,Y,Z,Ex,Rl for single qubit. Unit in μs.*/
  int num_purified;

  bool locked;
  unsigned long locked_ruleset_id;
  unsigned long locked_rule_id;

 protected:
  void initialize() override;
  void finish() override;
  void handleMessage(omnetpp::cMessage *msg) override;
  messages::PhotonicQubit *generateEntangledPhoton();
  void setBusy();
  // returns the matrix that represents the errors on the Bell pair. (e.g. XY, XZ and ZI...)
  Eigen::Matrix2cd getErrorMatrix(StationaryQubit *qubit);
  // returns the dm of the physical Bell pair. Used for tomography.
  quantum_state getQuantumState();
  measurement_operator Random_Measurement_Basis_Selection();
  void setMeasurementErrorModel(MeasurementErrorModel &model);

  // this is for debugging. class internal use only.
  // and it's different from QubitRecord's one.
  bool is_busy;
  utils::ComponentProvider provider;
};

}  // namespace modules
}  // namespace quisp
