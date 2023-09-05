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

  std::vector<InstructionTypes> opcodes;

  /**
   * @brief the map to find instruction index (pc) by label.
   *
   * The Runtime uses this to jump / branch its execution.
   */
  LabelMap label_map;

  /// @brief the Program name for debugging purpose.
  std::string name;

  /// @brief if it's true, show instruction and runtime state in each step.
  bool debugging = false;
};

/**
 * @brief The Runtime executable Rule in a RuleSet.
 */
class Rule {
 public:
  Rule(const Program& condition, const Program& action, bool debugging = false) : Rule("", -1, -1, condition, action, debugging) {}
  Rule(const std::string& name, int send_tag, int receive_tag, const Program& condition, const Program& action, bool debugging = false)
      : name(name), send_tag(send_tag), receive_tag(receive_tag), condition(condition), action(action), debugging(debugging) {}

  /// @brief the RuleSet name for debugging
  std::string name;

  /// @brief the Rule id. The RuleSet::finalize() determines the id.
  int id = -1;

  /// @brief the shared tag for identify a rule across QNodes in a connection.
  int send_tag = -1;
  int receive_tag = -1;

  /**
   * @brief The condition for the Rule. The Runtime executes the following.
   * action if this condition passed. If not, it goes the next Rule.
   *
   * This condition describes when the Runtime should execute the action in this
   * Rule.
   */
  Program condition;

  /// @brief The action for the Rule in the RuleSet.
  Program action;

  /// @brief if it's true, the Runtime shows debug info in each step.
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

  /// @brief analyzes its rules and instructions to collect informations for execution.
  void finalize();

  /// @brief the partner(connection participating nodes) QNodeAddrs used in this RuleSet.
  std::set<QNodeAddr> partners;

  /**
   * @brief This contains a list of pairs of the rule_id and partner's QNodeAddr.
   *
   * The Runtime assigns the entangled qubit to the rule by looking up this map.
   * This is initialized when the Runtime receives the RuleSet.
   */
  std::unordered_map<QNodeAddr, RuleId> partner_initial_rule_table;

  /**
   * @brief contains the next rule ids corresponding to the current partner and
   * rule id like: (partner_addr, current_rule_id): next_rule_id
   */
  std::unordered_map<std::pair<QNodeAddr, RuleId>, RuleId> next_rule_table = {};

  /// @brief the RuleSet id
  unsigned long id;

  /// @brief the owner's QNode address.
  int owner_addr;

  /// @brief the RuleSet name for debugging.
  std::string name;

  /// @brief the Rules in this RuleSet. Each Rule has Condition and Action.
  std::vector<Rule> rules;

  /// @brief the Program to check the RuleSet is terminated or not.
  Program termination_condition;
  bool debugging = false;

 protected:
  /**
   * @brief an internal method to traverse the given Rule's whole Program to
   * collect their partners.
   */
  static inline void collectPartners(const RuleId rule_id, const InstructionTypes& instr, std::set<QNodeAddr>& partners,
                                     std::unordered_map<QNodeAddr, std::vector<RuleId>>& partner_rules);
};
inline bool operator==(const RuleSet& a, const RuleSet& b) { return a.id == b.id; };
}  // namespace quisp::runtime
