#include "RuleSet.h"
#include <variant>
#include "runtime/types.h"

namespace quisp::runtime {
void Rule::finalize() {}

void RuleSet::finalize() {
  // set index for each rule
  for (int i = 0; i < rules.size(); ++i) {
    rules[i].id = i;
  }

  // collect partner addresses
  partners = {};
  for (auto &rule : rules) {
    for (auto &instr : rule.condition.opcodes) {
      if (std::holds_alternative<INSTR_GET_QUBIT_QubitId_QNodeAddr_int_>(instr)) {
        auto [_qubit_id, partner_addr, _index] = std::get<INSTR_GET_QUBIT_QubitId_QNodeAddr_int_>(instr).args;
        partners.insert(partner_addr);
      }
    }
    for (auto &instr : rule.action.opcodes) {
      if (std::holds_alternative<INSTR_GET_QUBIT_QubitId_QNodeAddr_int_>(instr)) {
        auto [_qubit_id, partner_addr, _index] = std::get<INSTR_GET_QUBIT_QubitId_QNodeAddr_int_>(instr).args;
        partners.insert(partner_addr);
      }
    }
  }
  finalized = true;
}
}  // namespace quisp::runtime
