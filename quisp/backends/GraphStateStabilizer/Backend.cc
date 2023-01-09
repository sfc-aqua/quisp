#include "Backend.h"
#include <cstddef>
#include <memory>
#include <stdexcept>
#include "Configuration.h"
#include "Qubit.h"
#include "backends/GraphStateStabilizer/Configuration.h"
#include "backends/interfaces/IConfiguration.h"

namespace quisp::backends::graph_state_stabilizer {
GraphStateStabilizerBackend::GraphStateStabilizerBackend(std::unique_ptr<IRandomNumberGenerator> rng, std::unique_ptr<GraphStateStabilizerConfiguration> configuration)
    : current_time(SimTime()), rng(std::move(rng)) {
  config = std::move(configuration);
}
GraphStateStabilizerBackend::GraphStateStabilizerBackend(std::unique_ptr<IRandomNumberGenerator> rng, std::unique_ptr<GraphStateStabilizerConfiguration> configuration,
                                                         ICallback* cb)
    : GraphStateStabilizerBackend(std::move(rng), std::move(configuration)) {
  callback = cb;
}
GraphStateStabilizerBackend::~GraphStateStabilizerBackend() {
  for (auto& pair : qubits) {
    delete pair.first;
  }
}

IQubit* GraphStateStabilizerBackend::getQubit(const IQubitId* id, std::unique_ptr<IConfiguration> conf) {
  auto qubit = qubits.find(id);

  if (qubit != qubits.cend()) {
    return qubit->second.get();
  }
  auto original_qubit = std::make_unique<GraphStateStabilizerQubit>(id, this);

  IConfiguration* raw_conf = conf.release();
  GraphStateStabilizerConfiguration* gss_conf = dynamic_cast<GraphStateStabilizerConfiguration*>(raw_conf);

  if (gss_conf == nullptr) {
    delete raw_conf;
    throw std::runtime_error("GraphStateStabilizer::getQubit: failed to cast. got invalid configulation.");
  }

  original_qubit->configure(std::unique_ptr<GraphStateStabilizerConfiguration>(gss_conf));
  auto* qubit_ptr = original_qubit.get();
  qubits.insert({id, std::move(original_qubit)});
  return qubit_ptr;
}
IQubit* GraphStateStabilizerBackend::getQubit(const IQubitId* id) { return getQubit(id, getDefaultConfiguration()); }
std::unique_ptr<IConfiguration> GraphStateStabilizerBackend::getDefaultConfiguration() const {
  // copy the default backend configuration for each qubit
  return std::make_unique<GraphStateStabilizerConfiguration>(*config.get());
}
const SimTime& GraphStateStabilizerBackend::getSimTime() {
  if (callback != nullptr) callback->willUpdate(*this);
  return current_time;
}
void GraphStateStabilizerBackend::setSimTime(SimTime time) { current_time = time; }
double GraphStateStabilizerBackend::dblrand() { return rng->doubleRandom(); }

}  // namespace quisp::backends::graph_state_stabilizer
