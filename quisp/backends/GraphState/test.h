#pragma once
#include <backends/Backends.h>
#include <omnetpp.h>
#include <memory>
#include <stdexcept>
#include "../interfaces/IQubitId.h"
#include "../interfaces/IRandomNumberGenerator.h"
#include "Backend.h"
#include "Configuration.h"
#include "Qubit.h"

using namespace quisp::backends::graph_state;
using namespace quisp::backends::graph_state::types;

namespace quisp_test::backends::graph_state {
using omnetpp::SimTime;
using ::quisp::backends::abstract::IQubit;
using ::quisp::backends::abstract::IQubitId;
using ::quisp::backends::graph_state::GraphStateBackend;
using ::quisp::backends::graph_state::GraphStateConfiguration;
using ::quisp::backends::graph_state::GraphStateQubit;
using namespace ::quisp::backends;
using namespace ::quisp::backends::abstract;

class QubitId : public IQubitId {
 public:
  QubitId(int id) : id(id) {}
  int id;

  inline std::size_t hash() const override { return std::hash<int>()(id); }
  bool compare(const IQubitId& qubit_id_ref) const override {
    auto qubit_id = dynamic_cast<const QubitId&>(qubit_id_ref);
    return id == qubit_id.id;
  }
};

class TestRNG : public quisp::backends::abstract::IRandomNumberGenerator {
 public:
  TestRNG() {}
  double doubleRandom() override { return double_value; }
  double double_value = 0.0;
};

class Qubit : public GraphStateQubit {
 public:
  using GraphStateQubit::addEdge;
  using GraphStateQubit::applyClifford;
  using GraphStateQubit::applyMemoryError;
  using GraphStateQubit::applyPureCZ;
  using GraphStateQubit::applyRightClifford;
  using GraphStateQubit::applySingleQubitGateError;
  using GraphStateQubit::applyTwoQubitGateError;
  using GraphStateQubit::deleteEdge;
  using GraphStateQubit::excite;
  using GraphStateQubit::gate_err_cnot;
  using GraphStateQubit::gate_err_h;
  using GraphStateQubit::gate_err_x;
  using GraphStateQubit::gate_err_z;
  using GraphStateQubit::gateCNOT;
  using GraphStateQubit::gateH;
  using GraphStateQubit::gateS;
  using GraphStateQubit::gateSdg;
  using GraphStateQubit::gateX;
  using GraphStateQubit::gateZ;
  using GraphStateQubit::graphMeasureZ;
  using GraphStateQubit::isNeighbor;
  using GraphStateQubit::localComplement;
  using GraphStateQubit::localMeasureX;
  using GraphStateQubit::localMeasureY;
  using GraphStateQubit::localMeasureZ;
  using GraphStateQubit::measureDensityIndependent;
  using GraphStateQubit::measurement_err;
  using GraphStateQubit::memory_transition_matrix;
  using GraphStateQubit::neighbors;
  using GraphStateQubit::pi_vector_completely_mixed;
  using GraphStateQubit::purifyX;
  using GraphStateQubit::purifyZ;
  using GraphStateQubit::relax;
  using GraphStateQubit::removeAllEdges;
  using GraphStateQubit::removeVertexOperation;
  using GraphStateQubit::setCompletelyMixedDensityMatrix;
  using GraphStateQubit::setEntangledPartner;
  using GraphStateQubit::setFree;
  using GraphStateQubit::setMemoryErrorRates;
  using GraphStateQubit::toggleEdge;
  using GraphStateQubit::updated_time;
  using GraphStateQubit::vertex_operator;

  std::unordered_set<GraphStateQubit*> getNeighborSet() { return neighbors; }
  void setVertexOperator(CliffordOperator op) { this->vertex_operator = op; }
  CliffordOperator getVertexOperator() { return this->vertex_operator; }
  Qubit(const IQubitId* id, GraphStateBackend* const backend) : GraphStateQubit(id, backend) {}
  void reset() {
    // we should not call setFree() here
    this->neighbors.clear();
    this->vertex_operator = CliffordOperator::H;
  }
};

class Backend : public GraphStateBackend {
 public:
  using GraphStateBackend::qubits;
  Backend(std::unique_ptr<IRandomNumberGenerator> rng, std::unique_ptr<GraphStateConfiguration> config) : GraphStateBackend(std::move(rng), std::move(config)) {}
  IQubit* getQubit(int id) { return this->getQubitInternal(new QubitId(id)); }
  IQubit* getQubitInternal(const IQubitId* id) {
    auto qubit = qubits.find(id);

    if (qubit != qubits.cend()) {
      return qubit->second.get();
    }
    auto original_qubit = std::make_unique<Qubit>(id, this);
    auto* qubit_ptr = original_qubit.get();
    qubits.insert({id, std::move(original_qubit)});
    return qubit_ptr;
  }
};

}  // namespace quisp_test::backends::graph_state
