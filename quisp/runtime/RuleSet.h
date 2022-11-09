#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "opcode.h"
#include "types.h"

namespace quisp::runtime {
class Program {
 public:
  Program(const std::string& name, const std::vector<InstructionTypes>& opcodes, bool debugging = false);

  std::string name;
  std::vector<InstructionTypes> opcodes;
  LabelMap label_map;
  bool debugging = false;
};

class Rule {
 public:
  Rule(const Program& condition, const Program& action, bool debugging = false) : Rule("", -1, condition, action, debugging) {}
  Rule(const std::string& name, int shared_tag, const Program& condition, const Program& action, bool debugging = false)
      : name(name), shared_tag(shared_tag), condition(condition), action(action), debugging(debugging) {}
  void finalize();
  std::string name;
  int id = -1;
  int shared_tag = -1;
  Program condition;
  Program action;
  bool debugging = false;
};

class RuleSet {
 public:
  RuleSet(const std::string& name = "", const std::vector<Rule>& rules = std::vector<Rule>(), const Program& termination_cond = Program{"never terminate", {}},
          bool debugging = false)
      : name(name), rules(rules), termination_condition(termination_cond), debugging(debugging) {}
  void finalize();

  // @brief partners contains partner QNodeAddrs
  std::set<QNodeAddr> partners;
  // @brief
  std::unordered_map<QNodeAddr, RuleId> partner_initial_rule_table;
  // [(partner_addr, current_rule_id): next_rule_id]
  std::unordered_map<std::pair<QNodeAddr, RuleId>, RuleId> next_rule_table = {};

  bool finalized = false;
  unsigned long id;
  int owner_addr;
  std::string name;
  std::vector<Rule> rules;
  Program termination_condition;
  bool debugging = false;

 protected:
  static inline void collectPartners(const RuleId rule_id, const InstructionTypes& instr, std::set<QNodeAddr>& partners,
                                     std::unordered_map<QNodeAddr, std::vector<RuleId>>& partner_rules);
};
}  // namespace quisp::runtime
