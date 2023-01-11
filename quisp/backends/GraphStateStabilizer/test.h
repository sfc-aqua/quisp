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

using namespace quisp::backends::graph_state_stabilizer;
using namespace quisp::backends::graph_state_stabilizer::types;

namespace quisp_test::backends::graph_state_stabilizer {
using omnetpp::SimTime;
using ::quisp::backends::abstract::IQubit;
using ::quisp::backends::abstract::IQubitId;
using ::quisp::backends::graph_state_stabilizer::GraphStateStabilizerBackend;
using ::quisp::backends::graph_state_stabilizer::GraphStateStabilizerConfiguration;
using ::quisp::backends::graph_state_stabilizer::GraphStateStabilizerQubit;
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

class Qubit : public GraphStateStabilizerQubit {
 public:
  using GraphStateStabilizerQubit::addEdge;
  using GraphStateStabilizerQubit::applyClifford;
  using GraphStateStabilizerQubit::applyMemoryError;
  using GraphStateStabilizerQubit::applyPureCZ;
  using GraphStateStabilizerQubit::applyRightClifford;
  using GraphStateStabilizerQubit::applySingleQubitGateError;
  using GraphStateStabilizerQubit::applyTwoQubitGateError;
  using GraphStateStabilizerQubit::deleteEdge;
  using GraphStateStabilizerQubit::excite;
  using GraphStateStabilizerQubit::gate_err_cnot;
  using GraphStateStabilizerQubit::gate_err_h;
  using GraphStateStabilizerQubit::gate_err_x;
  using GraphStateStabilizerQubit::gate_err_z;
  using GraphStateStabilizerQubit::gateCNOT;
  using GraphStateStabilizerQubit::gateH;
  using GraphStateStabilizerQubit::gateS;
  using GraphStateStabilizerQubit::gateSdg;
  using GraphStateStabilizerQubit::gateX;
  using GraphStateStabilizerQubit::gateZ;
  using GraphStateStabilizerQubit::graphMeasureZ;
  using GraphStateStabilizerQubit::isNeighbor;
  using GraphStateStabilizerQubit::localComplement;
  using GraphStateStabilizerQubit::localMeasureX;
  using GraphStateStabilizerQubit::localMeasureY;
  using GraphStateStabilizerQubit::localMeasureZ;
  using GraphStateStabilizerQubit::correlationMeasureX;
  using GraphStateStabilizerQubit::correlationMeasureY;
  using GraphStateStabilizerQubit::correlationMeasureZ;
  using GraphStateStabilizerQubit::measureDensityIndependent;
  using GraphStateStabilizerQubit::purifyX;
  using GraphStateStabilizerQubit::purifyZ;
  using GraphStateStabilizerQubit::setCompletelyMixedDensityMatrix;
  using GraphStateStabilizerQubit::setEntangledPartner;
  using GraphStateStabilizerQubit::measurement_err;
  using GraphStateStabilizerQubit::memory_transition_matrix;
  using GraphStateStabilizerQubit::pi_vector;
  using GraphStateStabilizerQubit::neighbors;
  using GraphStateStabilizerQubit::relax;
  using GraphStateStabilizerQubit::removeAllEdges;
  using GraphStateStabilizerQubit::removeVertexOperation;
  using GraphStateStabilizerQubit::setFree;
  using GraphStateStabilizerQubit::setMemoryErrorRates;
  using GraphStateStabilizerQubit::toggleEdge;
  using GraphStateStabilizerQubit::updated_time;
  using GraphStateStabilizerQubit::vertex_operator;

  std::unordered_set<GraphStateStabilizerQubit*> getNeighborSet() { return neighbors; }
  void setVertexOperator(CliffordOperator op) { this->vertex_operator = op; }
  CliffordOperator getVertexOperator() { return this->vertex_operator; }
  Qubit(const IQubitId* id, GraphStateStabilizerBackend* const backend) : GraphStateStabilizerQubit(id, backend) {}
  void reset() {
    // we should not call setFree() here
    this->neighbors.clear();
    this->vertex_operator = CliffordOperator::H;
  }
};

class Backend : public GraphStateStabilizerBackend {
 public:
  using GraphStateStabilizerBackend::qubits;
  Backend(std::unique_ptr<IRandomNumberGenerator> rng, std::unique_ptr<GraphStateStabilizerConfiguration> config)
      : GraphStateStabilizerBackend(std::move(rng), std::move(config)) {}
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

}  // namespace quisp_test::backends::graph_state_stabilizer
