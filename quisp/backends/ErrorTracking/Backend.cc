#include "Backend.h"

namespace quisp::backends::error_tracking {
ErrorTrackingBackend::ErrorTrackingBackend() : current_time(SimTime()) {}
ErrorTrackingBackend::~ErrorTrackingBackend() {}
IQubit* ErrorTrackingBackend::getQubit(const QubitId id) {
  auto qubit = qubits.find(id);

  if (qubit != qubits.cend()) {
    return qubit->second.get();
  }
  auto original_qubit = std::make_unique<ErrorTrackingQubit>(id);
  auto* qubit_ptr = original_qubit.get();
  qubits.insert({id, std::move(original_qubit)});
  return qubit_ptr;
}

const SimTime& ErrorTrackingBackend::getTime() { return current_time; }
void ErrorTrackingBackend::setTime(SimTime time) { current_time = time; }
}  // namespace quisp::backends::error_tracking
