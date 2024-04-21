#include <memory>

#include "RuleSetGenerator.h"
#include "rules/Action.h"
#include "rules/Clause.h"
#include "rules/Rule.h"

namespace quisp::modules::ruleset_gen {

using namespace quisp::rules;

void RuleSetGenerator::generateReverseSwapAtHalfRuleSets(int left_index, int right_index, std::map<int, std::vector<std::unique_ptr<Rule>>>& rules_map, std::vector<int>& path,
                                                         int& shared_rule_tag) {
  if (left_index == right_index || left_index + 1 == right_index) return;
  int swapper_index = (left_index + right_index) / 2;

  int swapper_addr = path[swapper_index];
  int left_addr = path[left_index];
  int right_addr = path[right_index];
  rules_map[swapper_addr].emplace_back(swapRule({left_addr, right_addr}, ++shared_rule_tag));
  rules_map[left_addr].emplace_back(swapCorrectionRule(swapper_addr, shared_rule_tag));
  rules_map[right_addr].emplace_back(swapCorrectionRule(swapper_addr, shared_rule_tag));

  // if you want to do purification between from and swapper or swapper and to before the swap; do it here.
  // e.g. generatePurificationRule(from, swapper, <protocol>);
  // e.g. generatePurificationRule(swapper, to, <protocol>);

  generateReverseSwapAtHalfRuleSets(left_index, swapper_index, rules_map, path, shared_rule_tag);
  generateReverseSwapAtHalfRuleSets(swapper_index, right_index, rules_map, path, shared_rule_tag);
};

std::map<int, json> RuleSetGenerator::generateRuleSets(messages::ConnectionSetupRequest* req, unsigned long ruleset_id) {
  // prepare information for RuleSets generation
  auto path = collectPath(req);
  std::map<int /* node addr */, std::vector<std::unique_ptr<Rule>>> rules_map;
  int num_measure = req->getNum_measure();
  int shared_rule_tag = 0;

  generateReverseSwapAtHalfRuleSets(0, path.size() - 1, rules_map, path, shared_rule_tag);
  // if you want to do link-level purification; do it here and add to the back.
  for (auto& [address, rs] : rules_map) {
    std::reverse(rs.begin(), rs.end());
  }

  // // if you want to do e2e purification before tomography do it here
  // int left_addr = path.front();
  // int right_addr = path.back();
  // rules_map[left_addr].emplace_back(purifyRule(right_addr, PurType::SINGLE_SELECTION_X_PURIFICATION, ++shared_rule_tag));
  // rules_map[right_addr].emplace_back(purifyRule(left_addr, PurType::SINGLE_SELECTION_X_PURIFICATION, shared_rule_tag));
  // rules_map[left_addr].emplace_back(purificationCorrelationRule(right_addr, PurType::SINGLE_SELECTION_X_PURIFICATION, shared_rule_tag));
  // rules_map[right_addr].emplace_back(purificationCorrelationRule(left_addr, PurType::SINGLE_SELECTION_X_PURIFICATION, shared_rule_tag));

  // rules_map[left_addr].emplace_back(purifyRule(right_addr, PurType::SINGLE_SELECTION_Z_PURIFICATION, ++shared_rule_tag));
  // rules_map[right_addr].emplace_back(purifyRule(left_addr, PurType::SINGLE_SELECTION_Z_PURIFICATION, shared_rule_tag));
  // rules_map[left_addr].emplace_back(purificationCorrelationRule(right_addr, PurType::SINGLE_SELECTION_Z_PURIFICATION, shared_rule_tag));
  // rules_map[right_addr].emplace_back(purificationCorrelationRule(left_addr, PurType::SINGLE_SELECTION_Z_PURIFICATION, shared_rule_tag));

  // add tomography rules
  auto initiator_addr = path.front();
  ++shared_rule_tag;
  rules_map[initiator_addr].emplace_back(tomographyRule(responder_addr, initiator_addr, num_measure, shared_rule_tag));
  rules_map[responder_addr].emplace_back(tomographyRule(initiator_addr, responder_addr, num_measure, shared_rule_tag));

  std::map<int, json> rulesets{};
  // pack rules into RuleSets and serialize it as json
  for (auto it = rules_map.begin(); it != rules_map.end(); ++it) {
    int owner_address = it->first;
    auto rules = std::move(it->second);
    RuleSet ruleset(ruleset_id, owner_address);
    for (int i = 0; i < rules.size(); i++) {
      auto rule = std::move(rules.at(i));
      ruleset.addRule(std::move(rule));
    }
    rulesets.emplace(owner_address, ruleset.serialize_json());
  }
  return rulesets;
}

std::vector<int> RuleSetGenerator::collectPath(messages::ConnectionSetupRequest* req) {
  // the number of nodes in between
  int hop_count = req->getStack_of_QNodeIndexesArraySize();
  std::vector<int> path;
  for (int i = 0; i < hop_count; i++) {
    path.push_back(req->getStack_of_QNodeIndexes(i));
  }
  path.push_back(responder_addr);  // path includes responder address
  return path;
}

std::unique_ptr<Rule> RuleSetGenerator::tomographyRule(int partner_address, int owner_address, int num_measure, int shared_rule_tag) {
  auto tomography_rule = std::make_unique<Rule>(partner_address, shared_rule_tag, shared_rule_tag);
  tomography_rule->setName("tomography with address " + std::to_string(partner_address));

  // prepare condition
  auto condition = std::make_unique<Condition>();
  auto enough_resource_clause = std::make_unique<EnoughResourceConditionClause>(1, partner_address);
  auto measure_count_clause = std::make_unique<MeasureCountConditionClause>(num_measure, partner_address);
  condition->addClause(std::move(enough_resource_clause));
  condition->addClause(std::move(measure_count_clause));
  tomography_rule->setCondition(std::move(condition));

  // prepare action
  auto tomography_action = std::make_unique<Tomography>(num_measure, owner_address, partner_address);
  tomography_rule->setAction(std::move(tomography_action));

  return tomography_rule;
}

std::unique_ptr<Rule> RuleSetGenerator::purifyRule(int partner_address, PurType purification_type, int shared_rule_tag) {
  auto purify_rule = std::make_unique<Rule>(partner_address, shared_rule_tag, -1);
  // TODO: add purification protocol to rule name
  purify_rule->setName("purification with " + std::to_string(partner_address));

  // decide how many Bell pairs are required
  int num_resource;
  if (purification_type == PurType::SINGLE_SELECTION_X_PURIFICATION || purification_type == PurType::SINGLE_SELECTION_Z_PURIFICATION ||
      purification_type == PurType::SINGLE_SELECTION_Y_PURIFICATION) {
    num_resource = 2;
  } else if (purification_type == PurType::SINGLE_SELECTION_XZ_PURIFICATION || purification_type == PurType::SINGLE_SELECTION_ZX_PURIFICATION ||
             purification_type == PurType::DOUBLE_SELECTION_X_PURIFICATION || purification_type == PurType::DOUBLE_SELECTION_Z_PURIFICATION) {
    num_resource = 3;
  } else if (purification_type == PurType::DOUBLE_SELECTION_X_PURIFICATION_SINGLE_SELECTION_Z_PURIFICATION ||
             purification_type == PurType::DOUBLE_SELECTION_Z_PURIFICATION_SINGLE_SELECTION_X_PURIFICATION) {
    num_resource = 4;
  } else if (purification_type == PurType::DOUBLE_SELECTION_XZ_PURIFICATION || purification_type == PurType::DOUBLE_SELECTION_ZX_PURIFICATION) {
    num_resource = 5;
  } else {
    throw std::runtime_error("unknown purification type");
  }

  // prepare condition
  auto condition = std::make_unique<Condition>();
  auto enough_resource_clause = std::make_unique<EnoughResourceConditionClause>(num_resource, partner_address);
  condition->addClause(std::move(enough_resource_clause));
  purify_rule->setCondition(std::move(condition));

  // prepare action
  auto purify_action = std::make_unique<Purification>(purification_type, partner_address, shared_rule_tag);
  purify_rule->setAction(std::move(purify_action));

  return purify_rule;
}

std::unique_ptr<Rule> RuleSetGenerator::purificationCorrelationRule(int partner_address, PurType protocol, int shared_rule_tag) {
  auto correlation_rule = std::make_unique<Rule>(partner_address, -1, shared_rule_tag);
  correlation_rule->setName("purification correlation with " + std::to_string(partner_address));

  auto condition = std::make_unique<Condition>();
  auto correlation_clause = std::make_unique<PurificationCorrelationClause>(partner_address, shared_rule_tag);
  condition->addClause(std::move(correlation_clause));

  auto action = std::make_unique<PurificationCorrelation>(partner_address, shared_rule_tag);

  correlation_rule->setCondition(std::move(condition));
  correlation_rule->setAction(std::move(action));
  return correlation_rule;
}

std::unique_ptr<Rule> RuleSetGenerator::swapRule(std::pair<int, int> partner_address, int shared_rule_tag) {
  auto swap_rule = std::make_unique<Rule>(std::vector<int>{partner_address.first, partner_address.second}, shared_rule_tag, -1);
  swap_rule->setName("swap between " + std::to_string(partner_address.first) + " and " + std::to_string(partner_address.second));
  auto condition = std::make_unique<Condition>();
  auto enough_resource_clause_first = std::make_unique<EnoughResourceConditionClause>(1, partner_address.first);
  auto enough_resource_clause_second = std::make_unique<EnoughResourceConditionClause>(1, partner_address.second);
  condition->addClause(std::move(enough_resource_clause_first));
  condition->addClause(std::move(enough_resource_clause_second));

  auto swap_action = std::make_unique<EntanglementSwapping>(std::vector<int>({partner_address.first, partner_address.second}), shared_rule_tag);

  swap_rule->setCondition(std::move(condition));
  swap_rule->setAction(std::move(swap_action));
  return swap_rule;
}

std::unique_ptr<Rule> RuleSetGenerator::swapCorrectionRule(int swapper_address, int shared_rule_tag) {
  auto correction_rule = std::make_unique<Rule>(swapper_address, -1, shared_rule_tag);
  correction_rule->setName("swapping correction from " + std::to_string(swapper_address));
  auto condition = std::make_unique<Condition>();
  auto swapping_correction_clause = std::make_unique<SwappingCorrectionClause>(swapper_address, shared_rule_tag);
  condition->addClause(std::move(swapping_correction_clause));

  auto action = std::make_unique<SwappingCorrection>(swapper_address, shared_rule_tag);

  correction_rule->setCondition(std::move(condition));
  correction_rule->setAction(std::move(action));
  return correction_rule;
}
}  // namespace quisp::modules::ruleset_gen
