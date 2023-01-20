#include "Backend.h"
#include "Qubit.h"
#include "backends/QubitConfiguration.h"
#include "backends/interfaces/IConfiguration.h"

namespace quisp::backends::error_tracking {
using error_tracking::ErrorTrackingQubit;

ErrorTrackingBackend::ErrorTrackingBackend(std::unique_ptr<IRandomNumberGenerator> rng, std::unique_ptr<StationaryQubitConfiguration> configuration)
    : current_time(SimTime()), rng(std::move(rng)) {
  config = std::move(configuration);
}
ErrorTrackingBackend::ErrorTrackingBackend(std::unique_ptr<IRandomNumberGenerator> rng, std::unique_ptr<StationaryQubitConfiguration> configuration, ICallback* cb)
    : ErrorTrackingBackend(std::move(rng), std::move(configuration)) {
  callback = cb;
}

ErrorTrackingBackend::~ErrorTrackingBackend() {
  for (auto& pair : qubits) {
    delete pair.first;
  }
}

IQubit* ErrorTrackingBackend::getQubit(const IQubitId* id) {
  auto qubit = qubits.find(id);

  if (qubit != qubits.cend()) {
    return qubit->second.get();
  }
  throw std::runtime_error("ErrorTrackingBackend::getQubit: trying to get qubit with nonexisted Id.");
}

IQubit* ErrorTrackingBackend::createQubit(const IQubitId* id, std::unique_ptr<IConfiguration> conf) {
  if (qubits.find(id) != qubits.cend()) {
    throw std::runtime_error("ErrorTrackingBackend::createQubit: trying to create qubit with already existing Id.");
  }
  auto original_qubit = std::make_unique<ErrorTrackingQubit>(id, this);

  IConfiguration* raw_conf = conf.release();
  StationaryQubitConfiguration* et_conf = dynamic_cast<StationaryQubitConfiguration*>(raw_conf);

  if (et_conf == nullptr) {
    delete raw_conf;
    throw std::runtime_error("ErrorTrackingBackend::getQubit: failed to cast. got invalid configulation.");
  }

  original_qubit->configure(std::unique_ptr<StationaryQubitConfiguration>(et_conf));
  auto* qubit_ptr = original_qubit.get();
  qubits.insert({id, std::move(original_qubit)});
  return qubit_ptr;
}

IQubit* ErrorTrackingBackend::createQubit(const IQubitId* id) { return createQubit(id, std::move(getDefaultConfiguration())); }

void ErrorTrackingBackend::deleteQubit(const IQubitId* id) {
  auto qubit_iterator = qubits.find(id);
  if (qubit_iterator == qubits.cend()) {
    throw std::runtime_error("ErrorTrackingBackend::deleteQubit: trying to delete qubit with unknown Id.");
  }
  qubits.erase(qubit_iterator);
}

std::unique_ptr<IConfiguration> ErrorTrackingBackend::getDefaultConfiguration() const {
  // copy the default backend configuration for each qubit
  return std::make_unique<StationaryQubitConfiguration>(*config.get());
}
const SimTime& ErrorTrackingBackend::getSimTime() {
  if (callback != nullptr) callback->willUpdate(*this);
  return current_time;
}
void ErrorTrackingBackend::setSimTime(SimTime time) { current_time = time; }
double ErrorTrackingBackend::dblrand() { return rng->doubleRandom(); }

}  // namespace quisp::backends::error_tracking
