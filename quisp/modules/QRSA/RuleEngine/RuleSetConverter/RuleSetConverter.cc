#include "RuleSetConverter.h"
#include <rules/Action.h>
#include <rules/Clause.h>
#include <runtime/Runtime.h>
#include <stdexcept>

namespace quisp::modules::rs_converter {

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
    rs.rules.emplace_back(Rule{rule_data->name, action, action});
  }
  return rs;
}

Program RuleSetConverter::constructCondition(const ConditionData *data) {
  auto opcodes = std::vector<InstructionTypes>{};
  std::string name;
  for (auto &clause_data : data->clauses) {
    auto clause_ptr = clause_data.get();
    if (auto *c = dynamic_cast<const EnoughResourceConditionClause *>(clause_ptr)) {
      name += "EnoughResource ";
    } else if (auto *c = dynamic_cast<const FidelityConditionClause *>(clause_ptr)) {
      name += "FidelityCondition ";
    } else if (auto *c = dynamic_cast<const WaitConditionClause *>(clause_ptr)) {
      name += "Wait ";
    } else if (auto *c = dynamic_cast<const MeasureCountConditionClause *>(clause_ptr)) {
      name += "MeasureCountCondition ";
    }
  }
  return Program{name, opcodes};
}

Program RuleSetConverter::constructAction(const ActionData *data) {
  if (auto *act = dynamic_cast<const Purification *>(data)) {
    return constructPurificationAction(act);
  }
  if (auto *act = dynamic_cast<const EntanglementSwapping *>(data)) {
    return constructEntanglementSwappingAction(act);
  }
  if (auto *act = dynamic_cast<const Tomography *>(data)) {
    return constructTomographyAction(act);
  }
  if (auto *act = dynamic_cast<const Wait *>(data)) {
    return constructWaitAction(act);
  }

  throw std::runtime_error("got invalid actions");
  return Program{"empty", {}};
}

Program RuleSetConverter::constructEntanglementSwappingAction(const EntanglementSwapping *act) { return Program{"EntanglementSwapping", {}}; }
Program RuleSetConverter::constructPurificationAction(const Purification *act) { return Program{"Purification", {}}; }
Program RuleSetConverter::constructWaitAction(const Wait *act) {
  // todo: maybe promote qubit to the next rule
  return Program{"Wait", {}};
}

Program RuleSetConverter::constructTomographyAction(const Tomography *act) {
  auto q0 = 0;
  auto count = RegId::REG0;
  int max_count = act->num_measurement;
  auto &qnic = act->qnic_interfaces.at(0);
  QNodeAddr partner_addr = qnic.partner_addr;
  auto qubit_resource_index = 0;
  return Program{"Tomography",
                 {
                     // clang-format off
INSTR_LOAD_RegId_MemoryKey_{{count, "count"}},
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner_addr, qubit_resource_index}},
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
}  // namespace quisp::modules::rs_converter
