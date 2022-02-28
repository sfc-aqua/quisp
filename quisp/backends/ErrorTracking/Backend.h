#pragma once
#include <unordered_map>
#include "../IQuantumBackend.h"
#include "Qubit.h"

namespace quisp::backends::error_tracking {
using abstract::IQuantumBackend;
using abstract::IQubit;

template <typename QubitId>
class ErrorTrackingQubit;

template <typename QubitId>
class ErrorTrackingBackend : public IQuantumBackend<QubitId> {
 public:
  ErrorTrackingBackend() : current_time(SimTime()) {}
  ~ErrorTrackingBackend() {}
  IQubit<QubitId>* getQubit(QubitId id) override {
    auto qubit = qubits.find(id);

    if (qubit != qubits.cend()) {
      return qubit->second.get();
    }
    auto original_qubit = std::make_unique<ErrorTrackingQubit<QubitId>>(id);
    auto* qubit_ptr = original_qubit.get();
    qubits.insert({id, std::move(original_qubit)});
    return qubit_ptr;
  }
  const SimTime& getSimTime() override { return current_time; }
  void setSimTime(SimTime time) override { current_time = time; }

 protected:
  std::unordered_map<QubitId, std::unique_ptr<ErrorTrackingQubit<QubitId>>> qubits;
  SimTime current_time;
};

}  // namespace quisp::backends::error_tracking
