#pragma once

#include <cstddef>
#include <string>

#include "modules/QNIC/StationaryQubit/IStationaryQubit.h"
#include "modules/QRSA/QRSA.h"

namespace quisp::runtime {

using RuleId = int;

using IQubitRecord = quisp::modules::qrsa::IQubitRecord;
using MeasurementOutcome = quisp::modules::measurement_outcome;

// these types are mainly used for describing type name in def_instruction.h
enum class RegId : int { REG0, REG1, REG2, REG3 };
std::ostream& operator<<(std::ostream& stream, const RegId& value);
using QNodeAddr = int;
using QubitId = int;
using String = std::string;
using Label = std::string;
using MemoryKey = std::string;
using None = std::nullptr_t;
enum class Basis : int { Z, X, RANDOM };
std::ostream& operator<<(std::ostream& stream, const Basis& value);

}  // namespace quisp::runtime
