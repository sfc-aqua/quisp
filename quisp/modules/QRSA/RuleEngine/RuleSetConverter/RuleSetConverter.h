#pragma once

#include <rules/Action.h>
#include <rules/Clause.h>
#include <rules/Rule.h>
#include <rules/RuleSet.h>
#include <runtime/RuleSet.h>

namespace quisp::modules::rs_converter {

// serialized RuleSet data
using RSData = quisp::rules::RuleSet;
using RuleData = quisp::rules::Rule;
using ActionData = quisp::rules::Action;
using ClauseData = quisp::rules::Clause;
using ConditionData = quisp::rules::Condition;

// Runtime's RuleSet representation
using quisp::runtime::Program;
using quisp::runtime::Rule;
using quisp::runtime::RuleSet;

class RuleSetConverter {
 public:
  static RuleSet construct(const RSData&);

  static Program constructAction(const ActionData* data);
  static Program constructCondition(const ConditionData* data);
  static Program constructEntanglementSwappingAction(const ActionData* data);
  static Program constructPurificationAction(const ActionData* data);
  static Program constructWaitAction(const ActionData* data);
  static Program constructTomographyAction(const ActionData* data);
};
}  // namespace quisp::modules::rs_converter
