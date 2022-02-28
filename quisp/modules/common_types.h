#pragma once
#include <backends/Backends.h>
#include <tuple>

namespace quisp::modules::common {

using QNodeAddr = int;
using QNicIndex = int;
using QNicType = int;
using QubitIndex = int;
using QubitId = std::tuple<QNodeAddr, QNicIndex, QNicType, QubitIndex>;
using IBackendQubit = quisp::backends::IQubit<QubitId>;
using IQuantumBackend = quisp::backends::IQuantumBackend<QubitId>;
using ErrorTrackingBackend = quisp::backends::ErrorTrackingBackend<QubitId>;
}  // namespace quisp::modules::common

// for backends' explicit instantiation
namespace quisp::backends::abstract {
template class quisp::backends::IQubit<quisp::modules::common::QubitId>;
template class quisp::backends::IQuantumBackend<quisp::modules::common::QubitId>;
}  // namespace quisp::backends::abstract
namespace quisp::backends::error_tracking {
template class quisp::backends::ErrorTrackingQubit<quisp::modules::common::QubitId>;
template class quisp::backends::ErrorTrackingBackend<quisp::modules::common::QubitId>;
}  // namespace quisp::backends::error_tracking
