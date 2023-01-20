#include "Backend.h"
#include <cstddef>
#include <memory>
#include <stdexcept>
#include "Configuration.h"
#include "Qubit.h"
#include "backends/GraphState/Configuration.h"
#include "backends/interfaces/IConfiguration.h"

namespace quisp::backends::graph_state {
GraphStateBackend::GraphStateBackend(std::unique_ptr<IRandomNumberGenerator> rng, std::unique_ptr<GraphStateConfiguration> configuration)
    : current_time(SimTime()), rng(std::move(rng)) {
  config = std::move(configuration);
}
GraphStateBackend::GraphStateBackend(std::unique_ptr<IRandomNumberGenerator> rng, std::unique_ptr<GraphStateConfiguration> configuration, ICallback* cb)
    : GraphStateBackend(std::move(rng), std::move(configuration)) {
  callback = cb;
}
GraphStateBackend::~GraphStateBackend() {
  for (auto& pair : qubits) {
    delete pair.first;
  }
}

IQubit* GraphStateBackend::createQubit(const IQubitId* id, std::unique_ptr<IConfiguration> conf) {
  if (qubits.find(id) != qubits.cend()) {
    throw std::runtime_error("GraphState::createQubit: trying to get qubit with already existed Id.");
  }
  auto original_qubit = std::make_unique<GraphStateQubit>(id, this);

  IConfiguration* raw_conf = conf.release();
  GraphStateConfiguration* gss_conf = dynamic_cast<GraphStateConfiguration*>(raw_conf);

  if (gss_conf == nullptr) {
    delete raw_conf;
    throw std::runtime_error("GraphState::getQubit: failed to cast. got invalid configulation.");
  }

  original_qubit->configure(std::unique_ptr<GraphStateConfiguration>(gss_conf));
  auto* qubit_ptr = original_qubit.get();
  qubits.insert({id, std::move(original_qubit)});
  return qubit_ptr;
}
IQubit* GraphStateBackend::createQubit(const IQubitId* id) { return createQubit(id, getDefaultConfiguration()); }

IQubit* GraphStateBackend::getQubit(const IQubitId* id) {
  auto qubit_iterator = qubits.find(id);
  if (qubit_iterator == qubits.cend()) {
    throw std::runtime_error("GraphState::getQubit: trying to get qubit with non existing Id.");
  }
  return qubit_iterator->second.get();
}

void GraphStateBackend::deleteQubit(const IQubitId* id) {
  auto qubit_iterator = qubits.find(id);
  if (qubit_iterator == qubits.cend()) {
    throw std::runtime_error("GraphState::getQubit: trying to delete qubit with non existing Id.");
  }
  qubits.erase(qubit_iterator);
}

std::unique_ptr<IConfiguration> GraphStateBackend::getDefaultConfiguration() const {
  // copy the default backend configuration for each qubit
  return std::make_unique<GraphStateConfiguration>(*config.get());
}
const SimTime& GraphStateBackend::getSimTime() {
  if (callback != nullptr) callback->willUpdate(*this);
  return current_time;
}
void GraphStateBackend::setSimTime(SimTime time) { current_time = time; }
double GraphStateBackend::dblrand() { return rng->doubleRandom(); }

}  // namespace quisp::backends::graph_state
