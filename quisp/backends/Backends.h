#pragma once
#include "ErrorTracking/Backend.h"
#include "ErrorTracking/Configuration.h"
#include "GraphStateStabilizer/Backend.h"
#include "GraphStateStabilizer/Configuration.h"
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
using error_tracking::ErrorTrackingBackend;
using error_tracking::ErrorTrackingConfiguration;
using error_tracking::ErrorTrackingQubit;
using graph_state_stabilizer::GraphStateStabilizerBackend;
using graph_state_stabilizer::GraphStateStabilizerConfiguration;
using graph_state_stabilizer::GraphStateStabilizerQubit;

}  // namespace quisp::backends
