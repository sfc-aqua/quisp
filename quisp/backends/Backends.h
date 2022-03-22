#pragma once
#include "ErrorTracking/Backend.h"
#include "backends/interfaces/IQubit.h"
#include "interfaces/IQuantumBackend.h"
#include "interfaces/IQubitId.h"

// the namespace for exposing the backend
namespace quisp::backends {

using abstract::EigenvalueResult;
using abstract::IQuantumBackend;
using abstract::IQubit;
using abstract::IQubitId;
using abstract::MeasurementOutcome;
using abstract::MeasureXResult;
using abstract::MeasureYResult;
using abstract::MeasureZResult;
using error_tracking::ErrorTrackingBackend;
using error_tracking::ErrorTrackingQubit;

}  // namespace quisp::backends
