#pragma once

#include <rules/Action.h>
#include <rules/Clause.h>
#include <rules/Rule.h>
#include <rules/RuleSet.h>
#include <runtime/RuleSet.h>
#include <runtime/types.h>
#include <cstddef>

namespace quisp::modules::rs_converter {

// serialized RuleSet data
using RSData = quisp::rules::RuleSet;
using RuleData = quisp::rules::Rule;
using ActionData = quisp::rules::Action;
using ClauseData = quisp::rules::Clause;
using ConditionData = quisp::rules::Condition;

using rules::EnoughResourceConditionClause;
using rules::EntanglementSwapping;
using rules::FidelityConditionClause;
using rules::MeasureCountConditionClause;
using rules::Purification;
using rules::Tomography;
using rules::Wait;
using rules::WaitConditionClause;

// Runtime's RuleSet representation
using quisp::runtime::Label;
using quisp::runtime::MemoryKey;
using quisp::runtime::Program;
using quisp::runtime::Rule;
using quisp::runtime::RuleSet;
const std::nullptr_t None = nullptr;

/* \brief RuleSetConverter converts rules::RuleSet into runtime::RuleSet in RuleEngine.
 * RuleEngine receives rules::RuleSet that is json serializable format of RuleSet.
 */
class RuleSetConverter {
 public:
  static RuleSet construct(const RSData&);

  static Program constructAction(const ActionData* data);
  static Program constructCondition(const ConditionData* data);

  // actions
  static Program constructEntanglementSwappingAction(const EntanglementSwapping* data);
  static Program constructPurificationAction(const Purification* data);
  static Program constructWaitAction(const Wait* data);
  static Program constructTomographyAction(const Tomography* data);
};
}  // namespace quisp::modules::rs_converter
