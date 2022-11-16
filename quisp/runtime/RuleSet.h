#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "opcode.h"
#include "types.h"

namespace quisp::runtime {

/**
 * @brief The Program is a list of Instructions with metadata.
 * The Runtime can execute the Program.
 *
 */
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

/**
 * @brief The RuleSet
 *
 * The responder QNode creates a set of RuleSets for each QNode in the path.
 * The RuleSet contains a list of Rules. The Runtime receives the given RuleSet
 * and executes it. The Runtime and the Ruleset will be deleted when the RuleSet
 * is terminated.
 */
class RuleSet {
 public:
  RuleSet(const std::string& name = "", const std::vector<Rule>& rules = std::vector<Rule>(), const Program& termination_cond = Program{"never terminate", {}},
          bool debugging = false)
      : name(name), rules(rules), termination_condition(termination_cond), debugging(debugging) {}
  void finalize();

  /// @brief the partner QNodeAddrs used in this RuleSet
  std::set<QNodeAddr> partners;

  /**
   * @brief This contains a list of pairs of the rule_id and partner's QNodeAddr.
   *
   * The Runtime assigns the entangled qubit to the rule by looking up this map.
   * This is initialized when the Runtime receives the RuleSet.
   */
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
