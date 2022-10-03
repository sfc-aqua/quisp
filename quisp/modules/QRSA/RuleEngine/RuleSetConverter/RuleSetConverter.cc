#include "RuleSetConverter.h"
#include <rules/Action.h>
#include "rules/Clause.h"
#include "runtime/opcode.h"

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
    return Program{"Tomography", {}};
  }
  if (auto *act = dynamic_cast<const Wait *>(data)) {
    return Program{"Wait", {}};
  }
  return Program{"empty", {}};
}
}  // namespace quisp::modules::rs_converter
