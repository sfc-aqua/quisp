#pragma once

#include <iostream>
#include "macro_utils.h"
#include "opcode.h"
#include "types.h"

namespace quisp::runtime {

class Runtime;
struct InstructionVisitor {
  explicit InstructionVisitor(Runtime* runtime_) : runtime(runtime_) {}
  InstructionVisitor(const InstructionVisitor& visitor);
  InstructionVisitor(InstructionVisitor&& visitor) = delete;
  InstructionVisitor& operator=(const InstructionVisitor& visitor);
  InstructionVisitor& operator=(InstructionVisitor&& visitor) = delete;

// the class declarations are done by macro expansion
#define INSTR(Opcode, ...) void operator()(const INSTRUCTION_TYPE_ALIAS(Opcode, __VA_ARGS__) & instruction);
#include "def_instructions.h"
#undef INSTR

  Runtime* runtime;
};

}  // namespace quisp::runtime
