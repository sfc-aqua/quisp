#include "Backend.h"

namespace quisp::backends::error_tracking {
ErrorTrackingBackend::ErrorTrackingBackend() {}
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
}  // namespace quisp::backends::error_tracking
