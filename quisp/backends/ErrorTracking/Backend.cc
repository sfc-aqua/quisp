#include "Backend.h"
#include "Qubit.h"

namespace quisp::backends::error_tracking {
  using error_tracking::ErrorTrackingQubit;
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
}
