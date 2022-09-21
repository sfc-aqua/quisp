#pragma once
#include <string>
#include <vector>
#include "opcode.h"

namespace quisp::runtime {
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
}  // namespace quisp::runtime
