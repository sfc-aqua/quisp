#pragma once
#include <sstream>
#include <string>
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

static const std::string OpTypeStr[]{
#define OP(Opcode) #Opcode,
#include "def_opcodes.h"
#undef OP
};

// Opcode Literal types for providing static type check for the instructions
// OP_ADD => Op<OpType::ADD>
// see also https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Int-To-Type
template <int I>
struct Op {
  enum { Value = I };
};

// this defines OP(DEBUG) as OP_DEBUG
#define OP(Opcode) using OP_##Opcode = Op<OpType::Opcode>;
#define OP_LAST(Opcode) using OP_##Opcode = Op<OpType::Opcode>;
#include "def_opcodes.h"
#undef OP

/**
 * @brief This class represents IR (intermediate representation) instruction.
 * Program consists of Instructions.
 *
 * @tparam OpLit
 * @tparam Operands
 */
template <class OpLit, class... Operands>
struct Instruction {
  Instruction(std::tuple<Operands...> args, std::string label = "") : opcode(OpLit::Value), args(args), label(label) {}
  Instruction(std::tuple<Operands...> args, Label label) : opcode(OpLit::Value), args(args), label(label.val) {}
  int opcode;
  std::tuple<Operands...> args;
  std::string label;

  /// @brief returns string representation for debugging
  std::string toString() const {
    std::stringstream ss;
    ss << OpTypeStr[opcode];
    ss << " ";
    toStringArgs(args, ss);
    if (label.size() > 0) {
      ss << "     :" << label;
    }
    return ss.str();
  }

  template <size_t N = 0, typename T>
  void toStringArgs(const T& t, std::stringstream& s) const {
    if constexpr (N < std::tuple_size<T>::value) {
      const auto& x = std::get<N>(t);
      s << x << ", ";
      toStringArgs<N + 1>(t, s);
    }
  }
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
