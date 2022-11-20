#include <algorithm>
#include <unordered_map>
#include <variant>

#include "RuleSet.h"
#include "runtime/opcode.h"
#include "runtime/types.h"

namespace quisp::runtime {

Program::Program(const std::string& name, const std::vector<InstructionTypes>& opcodes, bool debugging) : opcodes(opcodes), name(name), debugging(debugging) {
  auto len = opcodes.size();
  for (int pc = 0; pc < len; pc++) {
    auto op = opcodes[pc];
    auto label = std::visit([](auto& o) { return o.label; }, op);
    if (label.size() > 0) {
      label_map.insert({label, pc});
    }
  }
}

void RuleSet::finalize() {
  // set index for each rule
  for (int i = 0; i < rules.size(); ++i) {
    rules[i].id = i;
  }

  // collect partner addresses and initial rules
  partners = {};
  partner_initial_rule_table.clear();
  std::unordered_map<QNodeAddr, std::vector<RuleId>> partner_rules{};
  for (auto rule_iter = rules.begin(); rule_iter != rules.end(); rule_iter++) {
    auto rule_id = rule_iter->id;
    for (auto& instr : rule_iter->condition.opcodes) {
      // if the instruction needs qubit, collect it
      collectPartners(rule_id, instr, partners, partner_rules);
    }
    for (auto& instr : rule_iter->action.opcodes) {
      collectPartners(rule_id, instr, partners, partner_rules);
    }
  }

  for (auto& [partner_addr, rule_ids] : partner_rules) {
    for (int i = 0; i < rule_ids.size() - 1; i++) {
      auto first_rule_id = rule_ids.at(i);
      auto second_rule_id = rule_ids.at(i + 1);

      next_rule_table.emplace(std::make_pair(partner_addr, first_rule_id), second_rule_id);
    }
    partner_initial_rule_table.emplace(partner_addr, rule_ids.at(0));
  }
}

void RuleSet::collectPartners(const RuleId rule_id, const InstructionTypes& instr, std::set<QNodeAddr>& partners,
                              std::unordered_map<QNodeAddr, std::vector<RuleId>>& partner_rules) {
  if (std::holds_alternative<INSTR_GET_QUBIT_QubitId_QNodeAddr_int_>(instr)) {
    auto [_qubit_id, partner_addr, _index] = std::get<INSTR_GET_QUBIT_QubitId_QNodeAddr_int_>(instr).args;
    partners.insert(partner_addr);

    if (partner_rules.find(partner_addr) == partner_rules.end()) {
      partner_rules.insert({partner_addr, {}});
    }
    auto& rule_ids = partner_rules.at(partner_addr);
    // if the rule_id doesn't exist, add it
    if (!std::binary_search(rule_ids.begin(), rule_ids.end(), rule_id)) {
      rule_ids.push_back(rule_id);
    }
  }
}

}  // namespace quisp::runtime
