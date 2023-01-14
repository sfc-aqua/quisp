#pragma once
#include <unordered_set>
#include <unsupported/Eigen/MatrixFunctions>
#include "../interfaces/IQuantumBackend.h"
#include "../interfaces/IQubit.h"
#include "Configuration.h"
#include "Eigen/src/Core/Matrix.h"
#include "backends/interfaces/IQubitId.h"
#include "omnetpp/simtime.h"
#include "types.h"

namespace quisp::backends::graph_state {

using abstract::EigenvalueResult;
using abstract::MeasureXResult;
using abstract::MeasureYResult;
using abstract::MeasureZResult;
using abstract::MeasurementOutcome;
using abstract::IQuantumBackend;
using abstract::IQubit;
using abstract::IQubitId;
using abstract::SimTime;
using Eigen::MatrixPower;
using Eigen::MatrixXd;
using Eigen::Matrix;
using types::CliffordOperator;
using types::MeasurementErrorModel;
using types::MemoryErrorModel;
using types::SingleGateErrorModel;
using types::TwoQubitGateErrorModel;

class GraphStateBackend;
class GraphStateQubit : public IQubit {
 public:
  GraphStateQubit(const IQubitId *id, GraphStateBackend *const backend);
  ~GraphStateQubit();
  void configure(std::unique_ptr<GraphStateConfiguration> configuration);
  void setFree() override;
  // The name of these functions might be misleading; these are used in bsa, will be renamed and modifed in the future
  void setCompletelyMixedDensityMatrix() override;
  void setEntangledPartner(IQubit *const partner) override;

  void gateH() override;
  void gateZ() override;
  void gateX() override;
  void gateS() override;
  void gateSdg() override;
  void gateCNOT(IQubit *const control_qubit) override;
  EigenvalueResult localMeasureX() override;
  EigenvalueResult localMeasureY() override;
  EigenvalueResult localMeasureZ() override;
  // functions below here are deprecated ones, just for the compatibility with stationary qubit. Will be deleted.
  bool purifyX(IQubit *const control_qubit) override;
  bool purifyZ(IQubit *const target_qubit) override;
  MeasurementOutcome measureDensityIndependent() override;

 protected:
  // error simulation
  void setMemoryErrorRates(double x_error_rate, double y_error_rate, double z_error_rate, double excitation_rate, double relaxation_rate);
  void applySingleQubitGateError(SingleGateErrorModel const &err);
  void applyTwoQubitGateError(TwoQubitGateErrorModel const &err, GraphStateQubit *another_qubit);
  void applyMemoryError();
  void excite();
  void relax();
  // pi(0 ~ 6) vector in Eq 5.3
  // I, X, Z, Y, Ex, Re
  Matrix<double, 6 ,1> pi_vector;
  // error simulation constants
  SingleGateErrorModel gate_err_h;
  SingleGateErrorModel gate_err_x;
  SingleGateErrorModel gate_err_z;
  TwoQubitGateErrorModel gate_err_cnot;
  MeasurementErrorModel measurement_err;
  MemoryErrorModel memory_err;
  Eigen::MatrixXd memory_transition_matrix; /*I,X,Y,Z,Ex,Rl for single qubit. Unit in μs.*/

  // graph state specific operations
  void applyClifford(CliffordOperator op);
  void applyRightClifford(CliffordOperator op);
  bool isNeighbor(GraphStateQubit *another_qubit);
  void addEdge(GraphStateQubit *another_qubit);
  void deleteEdge(GraphStateQubit *another_qubit);
  void toggleEdge(GraphStateQubit *another_qubit);
  void removeAllEdges();
  void localComplement();
  void removeVertexOperation(GraphStateQubit *qubit_to_avoid);
  void applyPureCZ(GraphStateQubit *another_qubit);
  EigenvalueResult graphMeasureZ();

  SimTime updated_time = SimTime(0);

  // graph state
  std::unordered_set<GraphStateQubit *> neighbors;
  CliffordOperator vertex_operator;

  // graph state tables
  static std::string decomposition_table[24];
  static CliffordOperator clifford_application_lookup[24][24];
  static bool controlled_Z_lookup_edge[2][24][24];
  static CliffordOperator controlled_Z_lookup_node_1[2][24][24];
  static CliffordOperator controlled_Z_lookup_node_2[2][24][24];

  const IQubitId *id;
  GraphStateBackend *const backend;
};

}  // namespace quisp::backends::graph_state
