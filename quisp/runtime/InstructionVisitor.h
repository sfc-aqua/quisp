#pragma once

#include "macro_utils.h"
#include "opcode.h"
#include "types.h"

namespace quisp::runtime {

class Runtime;
struct InstructionVisitor {
  InstructionVisitor(Runtime* runtime_) : runtime(runtime_) {}

#define INSTR(Opcode, ...) void operator()(INSTRUCTION_TYPE_ALIAS(Opcode, __VA_ARGS__) instruction);
#include "def_instructions.h"
#undef INSTR

  Runtime* runtime;
};

}  // namespace quisp::runtime
