#include "Backend.h"
#include <cstddef>
#include <memory>
#include <stdexcept>
#include "Qubit.h"
#include "backends/ErrorTracking/Configuration.h"
#include "backends/interfaces/IConfiguration.h"

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

IQubit* ErrorTrackingBackend::getQubit(const IQubitId* id, std::unique_ptr<IConfiguration> conf) {
  auto qubit = qubits.find(id);

  if (qubit != qubits.cend()) {
    return qubit->second.get();
  }
  auto original_qubit = std::make_unique<ErrorTrackingQubit>(id, this);

  IConfiguration* raw_conf = conf.release();
  ErrorTrackingConfiguration* et_conf = dynamic_cast<ErrorTrackingConfiguration*>(raw_conf);

  if (et_conf == nullptr) {
    delete raw_conf;
    throw std::runtime_error("ErrorTrackingBackend::getQubit: failed to cast. got invalid configulation.");
  }

  original_qubit->configure(std::unique_ptr<ErrorTrackingConfiguration>(et_conf));
  auto* qubit_ptr = original_qubit.get();
  qubits.insert({id, std::move(original_qubit)});
  return qubit_ptr;
}

IQubit* ErrorTrackingBackend::getQubit(const IQubitId* id) { return getQubit(id, getDefaultConfiguration()); }
std::unique_ptr<IConfiguration> ErrorTrackingBackend::getDefaultConfiguration() const {
  // copy the default backend configuration for each qubit
  return std::make_unique<ErrorTrackingConfiguration>(*config.get());
}
const SimTime& ErrorTrackingBackend::getSimTime() { return current_time; }
void ErrorTrackingBackend::setSimTime(SimTime time) { current_time = time; }
double ErrorTrackingBackend::dblrand() { return rng->doubleRandom(); }

}  // namespace quisp::backends::error_tracking
