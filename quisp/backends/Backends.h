#pragma once
#include "ErrorTracking/Backend.h"
#include "interfaces/IQuantumBackend.h"
#include "interfaces/IQubitId.h"

// the namespace for exposing the backend
namespace quisp::backends {

using abstract::IQuantumBackend;
using abstract::IQubit;
using abstract::IQubitId;
using error_tracking::ErrorTrackingBackend;
using error_tracking::ErrorTrackingQubit;

}  // namespace quisp::backends
