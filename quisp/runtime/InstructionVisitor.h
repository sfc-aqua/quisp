#pragma once

#include <iostream>
#include "macro_utils.h"
#include "opcode.h"
#include "types.h"

namespace quisp::runtime {

class Runtime;

/**
 * @brief Visitor class for instructions in a Program.
 *
 * All Instruction signatures are defined in "def_instructions.h". This class
 * contains how to handle instructions. We must keep this class stateless.
 */
struct InstructionVisitor {
  explicit InstructionVisitor(Runtime* runtime) : runtime(runtime) {}
  InstructionVisitor(const InstructionVisitor& visitor);
  InstructionVisitor(InstructionVisitor&& visitor) = delete;
  InstructionVisitor& operator=(const InstructionVisitor& visitor);
  InstructionVisitor& operator=(InstructionVisitor&& visitor) = delete;

// the methods declarations are done by macro expansion
#define INSTR(Opcode, ...) void operator()(const INSTRUCTION_TYPE_ALIAS(Opcode, __VA_ARGS__) & instruction);
#include "def_instructions.h"
#undef INSTR

  /// @brief the pointer to the runtime holds this visitor instance.
  Runtime* runtime;
};

}  // namespace quisp::runtime
