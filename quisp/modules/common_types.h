#pragma once
#include <backends/Backends.h>
#include <backends/QubitConfiguration.h>
#include <tuple>

namespace quisp::modules::common {

using QNodeAddr = int;
using QNicIndex = int;
using QNicType = int;
using QubitIndex = int;
using QubitId = std::tuple<QNodeAddr, QNicIndex, QNicType, QubitIndex>;
using IBackendQubit = quisp::backends::IQubit;
using quisp::backends::GraphStateBackend;
using quisp::backends::IConfiguration;
using quisp::backends::IQuantumBackend;
using quisp::backends::IQubitId;
using quisp::backends::StationaryQubitConfiguration;
}  // namespace quisp::modules::common
