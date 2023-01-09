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

namespace quisp_test::backends {
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
  Qubit(const IQubitId* id, GraphStateStabilizerBackend* const backend) : GraphStateStabilizerQubit(id, backend) {}
  void reset() {
    setFree();
  }
};

class Backend : public GraphStateStabilizerBackend {
 public:
  using GraphStateStabilizerBackend::qubits;
  Backend(std::unique_ptr<IRandomNumberGenerator> rng, std::unique_ptr<GraphStateStabilizerConfiguration> config) : GraphStateStabilizerBackend(std::move(rng), std::move(config)) {}
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

}  // namespace quisp_test::backends
