#pragma once
#include "../IQuantumBackend.h"

namespace quisp::backends::error_tracking {
using abstract::IQuantumBackend;
using abstract::IQubit;
using abstract::QubitId;

class ErrorTrackingQubit : public IQubit {
  public:
   ErrorTrackingQubit(const QubitId id);
   ~ErrorTrackingQubit();

  QubitId id;
};
}  // namespace quisp::backends::error_tracking
