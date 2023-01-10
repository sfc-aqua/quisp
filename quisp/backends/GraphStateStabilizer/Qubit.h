#pragma once
#include <unordered_set>
#include <unsupported/Eigen/MatrixFunctions>
#include "../interfaces/IQuantumBackend.h"
#include "../interfaces/IQubit.h"
#include "Configuration.h"
#include "backends/interfaces/IQubitId.h"
#include "omnetpp/simtime.h"
#include "types.h"

namespace quisp::backends::graph_state_stabilizer {

using abstract::EigenvalueResult;
using abstract::IQuantumBackend;
using abstract::IQubit;
using abstract::IQubitId;
using abstract::SimTime;
using Eigen::Matrix2cd;
using Eigen::Matrix4cd;
using Eigen::MatrixPower;
using Eigen::MatrixXd;
using Eigen::Vector2cd;
using Eigen::Vector4cd;
using types::CliffordOperator;
using types::MeasurementErrorModel;
using types::MemoryErrorModel;
using types::SingleGateErrorModel;
using types::TwoQubitGateErrorModel;

class GraphStateStabilizerBackend;
class GraphStateStabilizerQubit : public IQubit {
 public:
  GraphStateStabilizerQubit(const IQubitId *id, GraphStateStabilizerBackend *const backend);
  ~GraphStateStabilizerQubit();
  void configure(std::unique_ptr<GraphStateStabilizerConfiguration> configuration);
  void setFree() override;
  void gateH() override;
  void gateZ() override;
  void gateX() override;
  void gateS() override;
  void gateSdg() override;
  void gateCNOT(IQubit *const control_qubit) override;
  EigenvalueResult measureX();
  EigenvalueResult measureY();
  EigenvalueResult measureZ();

 protected:
  // error simulation
  void setMemoryErrorRates(double x_error_rate, double y_error_rate, double z_error_rate, double excitation_rate, double relaxation_rate);
  void applySingleQubitGateError(SingleGateErrorModel const &err);
  void applyTwoQubitGateError(TwoQubitGateErrorModel const &err, GraphStateStabilizerQubit *another_qubit);
  void applyMemoryError();
  void excite();
  void relax();
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
  bool isNeighbor(GraphStateStabilizerQubit *another_qubit);
  void addEdge(GraphStateStabilizerQubit *another_qubit);
  void deleteEdge(GraphStateStabilizerQubit *another_qubit);
  void toggleEdge(GraphStateStabilizerQubit *another_qubit);
  void removeAllEdges();
  void localComplement();
  void removeVertexOperation(GraphStateStabilizerQubit *qubit_to_avoid);
  void applyPureCZ(GraphStateStabilizerQubit *another_qubit);
  EigenvalueResult graphMeasureZ();

  SimTime updated_time = SimTime(0);

  // graph state
  std::unordered_set<GraphStateStabilizerQubit *> neighbors;
  CliffordOperator vertex_operator;

  // graph state tables
  static std::string decomposition_table[24];
  static CliffordOperator clifford_application_lookup[24][24];
  static bool controlled_Z_lookup_edge[2][24][24];
  static CliffordOperator controlled_Z_lookup_node_1[2][24][24];
  static CliffordOperator controlled_Z_lookup_node_2[2][24][24];

  const IQubitId *id;
  GraphStateStabilizerBackend *const backend;
};

}  // namespace quisp::backends::graph_state_stabilizer
