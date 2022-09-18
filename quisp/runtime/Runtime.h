#pragma once
#include <iostream>
#include <tuple>
#include <variant>
#include <vector>

namespace quisp::runtime {

enum class OpType {
  NONE = 0,
  DEBUG = 1,
};
class Identifier {};

using Var = std::variant<int, float, std::string, Identifier>;
using Operation0 = std::tuple<OpType>;
using Operation1 = std::tuple<OpType, Var>;

using OperationType = std::variant<Operation0, Operation1>;
class Program {
 public:
  Program(const std::string& name, const std::vector<OperationType>& opcodes) : name(name), opcodes(opcodes) {}

  std::string name;
  std::vector<OperationType> opcodes;
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

struct OperationVisitor {
  void operator()(Operation0 op);
  void operator()(Operation1 op);
};

class Runtime {
 public:
  Runtime();
  ~Runtime();
  void exec(RuleSet ruleset);

  RuntimeError* error;
  void eval(Program& program);

  void evalOperation(OperationType op);
  OperationVisitor visitor;
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
