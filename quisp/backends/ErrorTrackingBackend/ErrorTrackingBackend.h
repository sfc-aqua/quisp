#pragma once
#include "../IQuantumBackend.h"

namespace quisp::backends::error_tracking {
using abstract::IQuantumBackend;
using abstract::IQubit;
using abstract::QubitId;

class ErrorTrackingBackend : public IQuantumBackend {
 public:
  ErrorTrackingBackend(){};
  ~ErrorTrackingBackend(){};
  IQubit* getQubit(QubitId id) override { return nullptr; };
};
}  // namespace quisp::backends::error_tracking
