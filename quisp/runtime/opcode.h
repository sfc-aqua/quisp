#pragma once
#include <tuple>
#include <variant>

#include "macro_utils.h"
#include "types.h"

namespace quisp::runtime {

// defines OpCode Enums
enum OpType : int {
#define OP(Opcode) Opcode,
#include "def_opcodes.h"
#undef OP
};

// Opcode Literal types for providing static type check for the instructions
// OP_ADD => Op<OpType::ADD>
// see also https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Int-To-Type
template <int I>
struct Op {
  enum { value = I };
};

// this defines OP(DEBUG) as OP_DEBUG
#define OP(Opcode) using OP_##Opcode = Op<OpType::Opcode>;
#define OP_LAST(Opcode) using OP_##Opcode = Op<OpType::Opcode>;
#include "def_opcodes.h"
#undef OP

/// @brief it describes each instruction. it corresponds each assmebly instruction line by line
template <class OpLit, class... Operands>
struct Instruction {
  Instruction(std::tuple<Operands...> args, std::string label = "") : opcode(OpLit::value), args(args), label(label) {}
  int opcode;
  std::tuple<Operands...> args;
  std::string label;
  std::string getLabel() { return label; }
};

// specialize template for each instruction
#define INSTR(Opcode, ...) using INSTRUCTION_TYPE_ALIAS(Opcode, __VA_ARGS__) = Instruction<OP_##Opcode, __VA_ARGS__>;
#include "def_instructions.h"
#undef INSTR

/// @brief a variant that is capable of storing all instructions
using InstructionTypes = std::variant<
#define INSTR(Opcode, ...) INSTRUCTION_TYPE_ALIAS(Opcode, __VA_ARGS__),
#define INSTR_LAST(Opcode, ...) INSTRUCTION_TYPE_ALIAS(Opcode, __VA_ARGS__)
#include "def_instructions.h"
#undef INSTR
    >;

}  // namespace quisp::runtime
