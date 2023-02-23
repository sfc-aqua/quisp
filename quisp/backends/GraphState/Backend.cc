#include "Backend.h"
#include "Qubit.h"
#include "backends/interfaces/IConfiguration.h"
#include "backends/interfaces/IQubit.h"
#include "modules/QNIC/StationaryQubit/QubitId.h"
#include "types/QNodeAddr.h"

using quisp::modules::qubit_id::QubitId;
using quisp::types::QNodeAddr;

namespace quisp::backends::graph_state {
GraphStateBackend::GraphStateBackend(std::unique_ptr<IRandomNumberGenerator> rng, std::unique_ptr<StationaryQubitConfiguration> configuration)
    : current_time(SimTime()), rng(std::move(rng)), short_live_qubit_pool_size(0) {
  config = std::move(configuration);
}
GraphStateBackend::GraphStateBackend(std::unique_ptr<IRandomNumberGenerator> rng, std::unique_ptr<StationaryQubitConfiguration> configuration, ICallback* cb)
    : GraphStateBackend(std::move(rng), std::move(configuration)) {
  callback = cb;
}
GraphStateBackend::~GraphStateBackend() {
  for (auto& pair : qubits) {
    delete pair.first;
  }
}

IQubit* GraphStateBackend::createShortLiveQubit() {
  auto* qubit_id = new QubitId(QNodeAddr{-1}, -1, -1, ++short_live_qubit_pool_size);
  auto original_qubit = std::make_unique<GraphStateQubit>(qubit_id, this, true);
  auto conf = getDefaultConfiguration();
  IConfiguration* raw_conf = conf.release();
  StationaryQubitConfiguration* gss_conf = dynamic_cast<StationaryQubitConfiguration*>(raw_conf);
  original_qubit->configure(std::unique_ptr<StationaryQubitConfiguration>(gss_conf));
  auto* qubit_ptr = original_qubit.get();
  qubits.insert({qubit_id, std::move(original_qubit)});
  return qubit_ptr;
}

IQubit* GraphStateBackend::createQubit(const IQubitId* id, std::unique_ptr<IConfiguration> conf) {
  if (qubits.find(id) != qubits.cend()) {
    throw std::runtime_error("GraphState::createQubit: trying to create qubit with already existed Id.");
  }
  auto original_qubit = std::make_unique<GraphStateQubit>(id, this, false);

  IConfiguration* raw_conf = conf.release();
  StationaryQubitConfiguration* gss_conf = dynamic_cast<StationaryQubitConfiguration*>(raw_conf);

  if (gss_conf == nullptr) {
    delete raw_conf;
    throw std::runtime_error("GraphState::getQubit: failed to cast. got invalid configuration.");
  }

  original_qubit->configure(std::unique_ptr<StationaryQubitConfiguration>(gss_conf));
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

IQubit* GraphStateBackend::getShortLiveQubit() {
  if (short_live_qubit_pool.empty()) {
    return createShortLiveQubit();
  }
  auto* qubit = short_live_qubit_pool.front();
  short_live_qubit_pool.pop_front();
  return qubit;
}

void GraphStateBackend::returnToPool(IQubit* pool_qubit) {
  pool_qubit->setFree();
  short_live_qubit_pool.emplace_back(pool_qubit);
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
  return std::make_unique<StationaryQubitConfiguration>(*config.get());
}
const SimTime& GraphStateBackend::getSimTime() {
  if (callback != nullptr) callback->willUpdate(*this);
  return current_time;
}
void GraphStateBackend::setSimTime(SimTime time) { current_time = time; }
double GraphStateBackend::dblrand() { return rng->doubleRandom(); }

}  // namespace quisp::backends::graph_state
