#pragma once
#include <string>
#include <unordered_set>
#include <unsupported/Eigen/MatrixFunctions>
#include "../interfaces/IQuantumBackend.h"
#include "../interfaces/IQubit.h"
#include "Eigen/src/Core/Matrix.h"
#include "backends/QubitConfiguration.h"
#include "backends/interfaces/IQubitId.h"
#include "omnetpp/simtime.h"
#include "types.h"
#include "utils/UtilFunctions.h"
#include "vector"

namespace quisp {
using util_functions::samplingWithWeights;
namespace backends::graph_state {

using abstract::EigenvalueResult;
using abstract::IQuantumBackend;
using abstract::IQubit;
using abstract::IQubitId;
using abstract::MeasurementOutcome;
using abstract::MeasureXResult;
using abstract::MeasureYResult;
using abstract::MeasureZResult;
using abstract::SimTime;
using Eigen::Matrix;
using Eigen::MatrixPower;
using Eigen::MatrixXd;
using types::CliffordOperator;
using types::MeasurementErrorModel;
using types::MemoryErrorModel;
using types::SingleGateErrorModel;
using types::TwoQubitGateErrorModel;

class GraphStateBackend;
class GraphStateQubit : public IQubit {
 public:
  GraphStateQubit(const IQubitId *id, GraphStateBackend *const backend, bool is_short_live);
  ~GraphStateQubit();
  void configure(std::unique_ptr<StationaryQubitConfiguration> configuration);
  void setFree() override;
  const IQubitId *const getId() const override;
  void relaseBackToPool() override;

  void gateX() override;
  void gateZ() override;
  void gateY() override;
  void gateH() override;
  void gateS() override;
  void gateSdg() override;
  void gateCNOT(IQubit *const target_qubit) override;
  EigenvalueResult measureX() override;
  EigenvalueResult measureY() override;
  EigenvalueResult measureZ() override;

  void noiselessH() override;
  void noiselessX() override;
  void noiselessZ() override;
  void noiselessCNOT(IQubit *const target_qubit) override;
  EigenvalueResult noiselessMeasureZ() override;
  EigenvalueResult noiselessMeasureX() override;
  EigenvalueResult noiselessMeasureZ(EigenvalueResult forced_result) override;
  EigenvalueResult noiselessMeasureX(EigenvalueResult forced_result) override;

 protected:
  // error simulation
  void setMemoryErrorRates(double x_error_rate, double y_error_rate, double z_error_rate, double excitation_rate, double relaxation_rate);
  void applySingleQubitGateError(SingleGateErrorModel const &err);
  void applyTwoQubitGateError(TwoQubitGateErrorModel const &err, GraphStateQubit *another_qubit);
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
  bool isNeighbor(GraphStateQubit *another_qubit);
  void addEdge(GraphStateQubit *another_qubit);
  void deleteEdge(GraphStateQubit *another_qubit);
  void toggleEdge(GraphStateQubit *another_qubit);
  void removeAllEdges();
  void localComplement();
  void removeVertexOperation(GraphStateQubit *qubit_to_avoid);
  void applyPureCZ(GraphStateQubit *another_qubit);
  EigenvalueResult graphMeasureZ();
  EigenvalueResult graphMeasureZ(EigenvalueResult eigenvalue);

  SimTime updated_time = SimTime(0);

  // graph state
  std::unordered_set<GraphStateQubit *> neighbors;
  CliffordOperator vertex_operator;

  // graph state tables
  static std::string decomposition_table[24];
  static CliffordOperator clifford_application_lookup[24][24];
  static bool controlled_z_lookup_edge[2][24][24];
  static CliffordOperator controlled_z_lookup_node_1[2][24][24];
  static CliffordOperator controlled_z_lookup_node_2[2][24][24];

  const IQubitId *id;
  GraphStateBackend *const backend;
  const bool is_short_live;

  // for debugging
  std::string cliffordToString(CliffordOperator op);
};

}  // namespace backends::graph_state
}  // namespace quisp
