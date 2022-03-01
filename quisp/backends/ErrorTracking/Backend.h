#pragma once
#include <unordered_map>
#include "../IQuantumBackend.h"
#include "../IRandomNumberGenerator.h"
#include "Qubit.h"
namespace quisp::backends::error_tracking {
using abstract::IQuantumBackend;
using abstract::IQubit;
using abstract::IRandomNumberGenerator;

template <typename QubitId>
class ErrorTrackingQubit;

template <typename QubitId>
class ErrorTrackingBackend : public IQuantumBackend<QubitId> {
 public:
  ErrorTrackingBackend(IRandomNumberGenerator* const rng) : current_time(SimTime()), rng(rng) {}
  ~ErrorTrackingBackend() {}
  IQubit<QubitId>* getQubit(QubitId id) override {
    auto qubit = qubits.find(id);

    if (qubit != qubits.cend()) {
      return qubit->second.get();
    }
    auto original_qubit = std::make_unique<ErrorTrackingQubit<QubitId>>(id, this);
    auto* qubit_ptr = original_qubit.get();
    qubits.insert({id, std::move(original_qubit)});
    return qubit_ptr;
  }
  const SimTime& getSimTime() override { return current_time; }
  void setSimTime(SimTime time) override { current_time = time; }
  double dblrand() { return rng->doubleRandom(); }

 protected:
  std::unordered_map<QubitId, std::unique_ptr<ErrorTrackingQubit<QubitId>>> qubits;
  SimTime current_time;
  IRandomNumberGenerator* rng;
};

}  // namespace quisp::backends::error_tracking
