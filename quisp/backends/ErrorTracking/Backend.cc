#include "Backend.h"
#include <memory>
#include <stdexcept>
#include "Qubit.h"
#include "backends/ErrorTracking/Configuration.h"

namespace quisp::backends::error_tracking {
using error_tracking::ErrorTrackingQubit;

ErrorTrackingBackend::ErrorTrackingBackend(std::unique_ptr<IRandomNumberGenerator> rng, std::unique_ptr<ErrorTrackingConfiguration> configuration)
    : current_time(SimTime()), rng(std::move(rng)) {
  config = std::move(configuration);
}

ErrorTrackingBackend::~ErrorTrackingBackend() {
  for (auto& pair : qubits) {
    delete pair.first;
  }
}

IQubit* ErrorTrackingBackend::getQubit(const IQubitId* id, std::unique_ptr<IConfiguration> configuration) {
  auto qubit = qubits.find(id);

  if (qubit != qubits.cend()) {
    return qubit->second.get();
  }
  auto original_qubit = std::make_unique<ErrorTrackingQubit>(id, this);
  auto* qubit_ptr = original_qubit.get();
  qubits.insert({id, std::move(original_qubit)});
  return qubit_ptr;
}

IQubit* ErrorTrackingBackend::getQubit(const IQubitId* id) {
  auto qubit = qubits.find(id);

  if (qubit != qubits.cend()) {
    return qubit->second.get();
  }
  auto original_qubit = std::make_unique<ErrorTrackingQubit>(id, this);
  auto* qubit_ptr = original_qubit.get();
  qubits.insert({id, std::move(original_qubit)});
  return qubit_ptr;
}
std::unique_ptr<IConfiguration> ErrorTrackingBackend::getDefaultConfiguration() const {
  // copy the default backend configuration for each qubit
  return std::make_unique<ErrorTrackingConfiguration>(*config.get());
}
const SimTime& ErrorTrackingBackend::getSimTime() { return current_time; }
void ErrorTrackingBackend::setSimTime(SimTime time) { current_time = time; }
double ErrorTrackingBackend::dblrand() { return rng->doubleRandom(); }

}  // namespace quisp::backends::error_tracking
