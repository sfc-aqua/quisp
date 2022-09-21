#pragma once
#include <cstddef>
#include <iostream>
#include <tuple>
#include <variant>
#include <vector>
#include "macro_utils.h"

namespace quisp::runtime {

using String = std::string;

// defines OpCode Enums
enum OpType : int {
#define OP(Opcode) Opcode,
#include "opcodes.h"
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
#include "opcodes.h"
#undef OP

class Identifier {};

template <class OpLit, class... Operands>
struct Instruction {
  Instruction(std::tuple<Operands...> args) : opcode(OpLit::value), args(args) {}
  int opcode;
  std::tuple<Operands...> args;
};

enum RegisterId { REG0, REG1, REG2, REG3 };

#define INST(Opcode, ...) using INSTRUCTION_TYPE_ALIAS(Opcode, __VA_ARGS__) = Instruction<OP_##Opcode, __VA_ARGS__>;
#define INST_LAST(Opcode, ...) using INSTRUCTION_TYPE_ALIAS(Opcode, __VA_ARGS__) = Instruction<OP_##Opcode, __VA_ARGS__>;
#include "instructions.h"
#undef INST

using InstructionTypes = std::variant<
#define INST(Opcode, ...) INSTRUCTION_TYPE_ALIAS(Opcode, __VA_ARGS__),
#define INST_LAST(Opcode, ...) INSTRUCTION_TYPE_ALIAS(Opcode, __VA_ARGS__)
#include "instructions.h"
#undef INST
    >;
class Program {
 public:
  Program(const std::string& name, const std::vector<InstructionTypes>& opcodes) : name(name), opcodes(opcodes) {}

  std::string name;
  std::vector<InstructionTypes> opcodes;
};

class Rule {
 public:
  Rule(const Program& condition, const Program& action) : condition(condition), action(action) {}

  Program condition;
  Program action;
};

class RuleSet {
 public:
  RuleSet(const std::string& name) : name(name), rules(std::vector<Rule>()) {}
  RuleSet(const std::string& name, const std::vector<Rule>& rules) : name(name), rules(rules) {}
  int id;
  std::string name;
  std::vector<Rule> rules;
};

class RuntimeError {
 public:
  std::string message;
};

class Runtime;

struct InstructionVisitor {
  InstructionVisitor(Runtime* runtime_) : runtime(runtime_) {}

#define INST(Opcode, ...) void operator()(INSTRUCTION_TYPE_ALIAS(Opcode, __VA_ARGS__) instruction);
#include "instructions.h"
#undef INST

  Runtime* runtime;
};

struct Register {
  const String name;
  unsigned long long value;
};

struct Flags {
  bool test_result;
};

class Runtime {
 public:
  Runtime();
  ~Runtime();
  void exec(RuleSet ruleset);
  void eval(Program& program);
  void evalOperation(InstructionTypes op);
  unsigned int pc = 0;
  Register registers[4];
  RuntimeError* error;
  InstructionVisitor visitor;
};

// namespace op {
// // Resource Preparations
// void assign() {}
// void validate() {}
// // Quantum Operations
// void gate() {}
// void measure() {}

// // Messaging
// void send() {}

// // Post processing
// void freeQubit() {}
// void setNameToResource() {}
// void update() {}

// };  // namespace op
}  // namespace quisp::runtime
