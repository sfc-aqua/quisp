#include "Backend.h"
#include "Qubit.h"

namespace quisp::backends::error_tracking {
using error_tracking::ErrorTrackingQubit;

ErrorTrackingBackend::ErrorTrackingBackend(std::unique_ptr<IRandomNumberGenerator> rng) : current_time(SimTime()), rng(std::move(rng)) {}

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
const SimTime& ErrorTrackingBackend::getSimTime() { return current_time; }
void ErrorTrackingBackend::setSimTime(SimTime time) { current_time = time; }
double ErrorTrackingBackend::dblrand() { return rng->doubleRandom(); }

}  // namespace quisp::backends::error_tracking
