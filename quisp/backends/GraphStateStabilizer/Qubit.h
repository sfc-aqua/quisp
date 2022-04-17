#pragma once
#include <unordered_set>
#include "../interfaces/IQuantumBackend.h"
#include "../interfaces/IQubit.h"
#include "Backend.h"
#include "backends/interfaces/IQubitId.h"
#include "types.h"

namespace quisp::backends::graph_state_stabilizer {

using abstract::EigenvalueResult;
using abstract::IQuantumBackend;
using abstract::IQubit;
using abstract::IQubitId;

class GraphStateStabilizerBackend;
class GraphStateStabilizerQubit : public IQubit {
 public:
  GraphStateStabilizerQubit(const IQubitId *id, GraphStateStabilizerBackend *const backend);
  ~GraphStateStabilizerQubit();
  void setFree() override;
  void applyClifford(types::CliffordOperator op);
  void applyRightClifford(types::CliffordOperator op);
  bool isNeighbor(GraphStateStabilizerQubit *another_qubit);
  void addEdge(GraphStateStabilizerQubit *another_qubit);
  void deleteEdge(GraphStateStabilizerQubit *another_qubit);
  void toggleEdge(GraphStateStabilizerQubit *another_qubit);
  void removeAllEdges();
  void localComplement();
  void removeVertexOperation(GraphStateStabilizerQubit *qubit_to_avoid);
  void applyPureCZ(GraphStateStabilizerQubit *another_qubit);
  void gateH() override;
  void gateZ() override;
  void gateX() override;
  void gateS() override;
  void gateCNOT(IQubit *const control_qubit) override;
  EigenvalueResult measureX();
  EigenvalueResult measureY();
  EigenvalueResult measureZ();
  EigenvalueResult graphMeasureZ();
  void gateSdg();
  void excite();
  void relax();

  std::unordered_set<GraphStateStabilizerQubit *> neighbors;
  types::CliffordOperator vertex_operator;
  const IQubitId *id;
  GraphStateStabilizerBackend *const backend;

  static std::string decomposition_table[24];
  static types::CliffordOperator clifford_application_lookup[24][24];
  static bool controlled_Z_lookup_edge[2][24][24];
  static types::CliffordOperator controlled_Z_lookup_node_1[2][24][24];
  static types::CliffordOperator controlled_Z_lookup_node_2[2][24][24];
};

}  // namespace quisp::backends::graph_state_stabilizer
