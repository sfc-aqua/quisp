#pragma once
#include "ErrorTracking/Backend.h"
#include "GraphState/Backend.h"
#include "backends/QubitConfiguration.h"
#include "interfaces/IConfiguration.h"
#include "interfaces/IQuantumBackend.h"
#include "interfaces/IQubit.h"
#include "interfaces/IQubitId.h"

// the namespace for exposing the backend
namespace quisp::backends {

using abstract::EigenvalueResult;
using abstract::IConfiguration;
using abstract::IQuantumBackend;
using abstract::IQubit;
using abstract::IQubitId;
using abstract::MeasurementOutcome;
using abstract::MeasureXResult;
using abstract::MeasureYResult;
using abstract::MeasureZResult;
// using backends::StationaryQubitConfiguration;
using error_tracking::ErrorTrackingBackend;
using error_tracking::ErrorTrackingQubit;
using graph_state::GraphStateBackend;
using graph_state::GraphStateQubit;

}  // namespace quisp::backends
