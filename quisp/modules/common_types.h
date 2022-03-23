#pragma once
#include <backends/Backends.h>
#include <tuple>

namespace quisp::modules::common {

using QNodeAddr = int;
using QNicIndex = int;
using QNicType = int;
using QubitIndex = int;
using QubitId = std::tuple<QNodeAddr, QNicIndex, QNicType, QubitIndex>;
using IBackendQubit = quisp::backends::IQubit;
using quisp::backends::IQubitId;
using IQuantumBackend = quisp::backends::IQuantumBackend;
using ErrorTrackingBackend = quisp::backends::ErrorTrackingBackend;
}  // namespace quisp::modules::common
