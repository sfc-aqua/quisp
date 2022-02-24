#pragma once
#include <unordered_map>
#include "../IQuantumBackend.h"
#include "Qubit.h"

namespace quisp::backends::error_tracking {
using abstract::IQuantumBackend;
using abstract::IQubit;
using abstract::QubitId;
class ErrorTrackingQubit;
class ErrorTrackingBackend : public IQuantumBackend {
 public:
  ErrorTrackingBackend();
  ~ErrorTrackingBackend();
  IQubit* getQubit(QubitId id) override;

  protected:
  std::unordered_map<QubitId,std::unique_ptr<ErrorTrackingQubit>> qubits;
};

}  // namespace quisp::backends::error_tracking
