#include "RuleSetConverter.h"
#include <rules/Action.h>
#include <rules/Clause.h>
#include <runtime/Runtime.h>

namespace quisp::modules::rs_converter {

using rules::EnoughResourceConditionClause;
using rules::EntanglementSwapping;
using rules::FidelityConditionClause;
using rules::MeasureCountConditionClause;
using rules::Purification;
using rules::Tomography;
using rules::Wait;
using rules::WaitConditionClause;
using runtime::InstructionTypes;

using namespace runtime;

RuleSet RuleSetConverter::construct(const RSData &data) {
  RuleSet rs;
  rs.id = data.ruleset_id;
  rs.owner_addr = data.owner_addr;
  auto &rules_data = data.rules;
  for (auto &rule_data : rules_data) {
    auto condition = constructCondition(rule_data->condition.get());
    auto action = constructAction(rule_data->action.get());
    rs.rules.emplace_back(Rule{action, action});
  }
  return rs;
}

Program RuleSetConverter::constructCondition(const ConditionData *data) {
  auto opcodes = std::vector<InstructionTypes>{};
  for (auto &clause_data : data->clauses) {
    auto clause_ptr = clause_data.get();
    if (auto *c = dynamic_cast<const EnoughResourceConditionClause *>(clause_ptr)) {
    } else if (auto *c = dynamic_cast<const FidelityConditionClause *>(clause_ptr)) {
    } else if (auto *c = dynamic_cast<const WaitConditionClause *>(clause_ptr)) {
    } else if (auto *c = dynamic_cast<const MeasureCountConditionClause *>(clause_ptr)) {
    }
  }
  return Program{"condition", opcodes};
}

Program RuleSetConverter::constructAction(const ActionData *data) {
  auto interface = data->qnic_interfaces.at(0);
  auto partner_addr = interface.partner_addr;
  auto qnic_type = interface.qnic_type;
  auto qnic_id = interface.qnic_id;

  if (auto *act = dynamic_cast<const Purification *>(data)) {
    return Program{"Purification", {}};
  }
  if (auto *act = dynamic_cast<const EntanglementSwapping *>(data)) {
    return Program{"EntanglementSwapping", {}};
  }
  if (auto *act = dynamic_cast<const Tomography *>(data)) {
    auto q0 = 0;
    auto count = RegId::REG0;
    int max_count = 100;
    QNodeAddr partner_addr = 1;
    auto qubit_index = 0;  // former 'resource'
    return Program{"Tomography",
                   {
                       // clang-format off
INSTR_LOAD_RegId_MemoryKey_{{count, "count"}},
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner_addr, qubit_index}},
INSTR_BNERR_Label_{"L1"},
INSTR_ERROR_String_{"Qubit not found for mesaurement"},
INSTR_MEASURE_RANDOM_MemoryKey_QubitId_{{"outcome", q0}, "L1"},
INSTR_INC_RegId_{count},
INSTR_STORE_MemoryKey_RegId_{{"count", count}},
INSTR_FREE_QUBIT_QubitId_{q0},
INSTR_SEND_LINK_TOMOGRAPHY_RESULT_QNodeAddr_RegId_MemoryKey_int_{{partner_addr, count, "outcome", max_count}}
                       // clang-format on
                   }};
  }
  if (auto *act = dynamic_cast<const Wait *>(data)) {
    return Program{"Wait", {}};
  }
  return Program{"empty", {}};
}
}  // namespace quisp::modules::rs_converter
