#pragma once

#include <string>

namespace quisp::runtime {

using RuleId = int;

// these types are mainly used for describing type name in def_instruction.h
enum class RegId : int { REG0, REG1, REG2, REG3 };
using QNodeAddr = int;
using QubitId = int;
using String = std::string;

}  // namespace quisp::runtime
