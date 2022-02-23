#pragma once
#include "ErrorTrackingBackend/ErrorTrackingBackend.h"
#include "IQuantumBackend.h"

// the namespace for exposing the backend
namespace quisp::backends {
using abstract::IQuantumBackend;
using abstract::IQubit;
using abstract::QubitId;
using error_tracking::ErrorTrackingBackend;
}  // namespace quisp::backends
