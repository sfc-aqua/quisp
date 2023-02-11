#include "RuleSetGenerator.h"

namespace quisp::modules::ruleset_gen {

using namespace quisp::rules;

std::map<int, json> RuleSetGenerator::generateRuleSets(messages::ConnectionSetupRequest* req, unsigned long ruleset_id) {
  auto path = collectPath(req);
  size_t hop_count = req->getStack_of_QNodeIndexesArraySize();
  size_t divisions = hop_count * 2 - 1;
  auto swapping_partners_table = collectSwappingPartners(path, divisions, hop_count);

  std::map<int /* node addr */, std::vector<std::unique_ptr<Rule>>> rules_map;
  auto rev_path = path;
  std::reverse(rev_path.begin(), rev_path.end());
  int shared_tag = 0;  // used for identifying the partner rule.

  for (int distance = 1; distance < path.size() / 2 + 1; distance++) {
    // Entanglement Swapping
    for (int i = 1; i < (path.size() + 1) / 2; i++) {
      std::vector<int> swapper_nodes;
      if (rev_path.at(i) != path.at(i)) {
        swapper_nodes = {rev_path.at(i), path.at(i)};
      } else {
        swapper_nodes = {path.at(i)};
      }
      // iterate swapper nodes
      for (int swapper_node : swapper_nodes) {
        auto it = swapping_partners_table.find(swapper_node);
        int left_partner = it->second.first, right_partner = it->second.second;
        // check if the distance of swapping is the same as the target distance
        auto swapper_it = std::find(path.begin(), path.end(), swapper_node);
        auto left_it = std::find(path.begin(), path.end(), left_partner);
        auto right_it = std::find(path.begin(), path.end(), right_partner);
        int index = 0, lindex = 0, rindex = 0;
        if (swapper_it != path.end() && left_it != path.end() && right_it != path.end()) {
          index = swapper_it - path.begin();
          lindex = left_it - path.begin();
          rindex = right_it - path.begin();
        } else {
          throw std::runtime_error("swapper and partner indices are not found in the path. Should not happen.");
        }
        if (std::max(std::abs(index - lindex), std::abs(index - rindex)) == distance) {
          // Swapping Rules
          auto swapping_rule = swapRule(swapping_partners_table[swapper_node], shared_tag);
          shared_tag++;
          rules_map[swapper_node].push_back(std::move(swapping_rule));
        }
      }
    }
  }

  int initiator_addr = path.at(0);
  int num_measure = req->getNum_measure();
  auto tomo_rule_initiator = tomographyRule(responder_addr, initiator_addr, num_measure, shared_tag);
  auto tomo_rule_responder = tomographyRule(initiator_addr, responder_addr, num_measure, shared_tag);
  shared_tag++;
  rules_map[initiator_addr].push_back(std::move(tomo_rule_initiator));
  rules_map[responder_addr].push_back(std::move(tomo_rule_responder));

  std::map<int, json> rulesets{};
  for (auto it = rules_map.begin(); it != rules_map.end(); ++it) {
    int owner_address = it->first;
    auto rules = std::move(it->second);
    RuleSet ruleset(ruleset_id, owner_address);
    for (int i = 0; i < rules.size(); i++) {
      auto rule = std::move(rules.at(i));
      auto appended_rule = ruleset.addRule(std::move(rule));
      if (appended_rule->is_finalized) {
        // if the rule is entanglement swapping or tomography rule, no need to specify the next rule
        break;
      }
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

std::map<int, std::pair<int, int>> RuleSetGenerator::collectSwappingPartners(std::vector<int>& path, int divisions, int hop_count) {
  std::vector<int> link_left_nodes(divisions);
  std::vector<int> link_right_nodes(divisions);
  std::vector<int> swapper_nodes(divisions);
  if (fillPathDivision(path, 0, hop_count, link_left_nodes, link_right_nodes, swapper_nodes, 0) < divisions) {
    throw std::runtime_error("Something went wrong in path division computation.");
  }
  std::map<int, std::pair<int, int>> swapping_partner_table;
  for (int i = 0; i < divisions; i++) {
    std::vector<int> partners;
    if (swapper_nodes[i] > 0) {
      swapping_partner_table.insert({swapper_nodes[i], {link_left_nodes[i], link_right_nodes[i]}});
    }
  }
  return swapping_partner_table;
}

int RuleSetGenerator::fillPathDivision(std::vector<int>& path, int i, int l, std::vector<int>& link_left, std::vector<int>& link_right, std::vector<int>& swapper, int fill_start) {
  if (l > 1) {
    int hl = (l >> 1);
    fill_start = fillPathDivision(path, i, hl, link_left, link_right, swapper, fill_start);
    fill_start = fillPathDivision(path, i + hl, l - hl, link_left, link_right, swapper, fill_start);
    swapper[fill_start] = path.at(i + hl);
  }
  if (l > 0) {
    link_left[fill_start] = path.at(i);
    link_right[fill_start] = path.at(i + l);
    if (l == 1) swapper[fill_start] = -1;
    fill_start++;
  }
  return fill_start;
}

std::unique_ptr<Rule> RuleSetGenerator::waitRule(int partner_address, int shared_tag) {
  auto wait_rule = std::make_unique<Rule>(partner_address, shared_tag, false);

  auto condition = std::make_unique<Condition>();
  auto wait_clause = std::make_unique<WaitConditionClause>(partner_address);
  condition->addClause(std::move(wait_clause));
  wait_rule->setCondition(std::move(condition));

  auto wait_action = std::make_unique<Wait>(partner_address);
  wait_rule->setAction(std::move(wait_action));

  return wait_rule;
}

std::unique_ptr<Rule> RuleSetGenerator::tomographyRule(int partner_address, int owner_address, int num_measure, int shared_tag) {
  auto tomography_rule = std::make_unique<Rule>(partner_address, shared_tag, true);

  [[deprecated]] double threshold_fidelity = 0.9;  // placeholder

  // prepare condition
  auto condition = std::make_unique<Condition>();
  auto enough_resource_clause = std::make_unique<EnoughResourceConditionClause>(1, threshold_fidelity, partner_address);
  auto measure_count_clause = std::make_unique<MeasureCountConditionClause>(num_measure, partner_address);
  condition->addClause(std::move(enough_resource_clause));
  condition->addClause(std::move(measure_count_clause));
  tomography_rule->setCondition(std::move(condition));

  // prepare action
  auto tomography_action = std::make_unique<Tomography>(num_measure, owner_address, partner_address);
  tomography_rule->setAction(std::move(tomography_action));

  return tomography_rule;
}

std::unique_ptr<Rule> RuleSetGenerator::purifyRule(int partner_address, PurType purification_type, int shared_tag) {
  auto purify_rule = std::make_unique<Rule>(partner_address, shared_tag, false);

  [[deprecated]] double threshold_fidelity = 0.9;
  // decide how many Bell pairs are required
  int num_resource;
  if (purification_type == PurType::SINGLE_X || purification_type == PurType::SINGLE_Z) {
    num_resource = 2;
  } else if (purification_type == PurType::DOUBLE || purification_type == PurType::DOUBLE_INV || purification_type == PurType::DSSA || purification_type == PurType::DSSA_INV) {
    num_resource = 3;
  } else if (purification_type == PurType::DSDA_SECOND || purification_type == PurType::DSDA_SECOND_INV) {
    num_resource = 4;
  } else if (purification_type == PurType::DSDA || purification_type == PurType::DSDA_INV) {
    num_resource = 5;
  } else {
    throw std::runtime_error("unknown purification type");
  }

  // prepare condition
  auto condition = std::make_unique<Condition>();
  auto enough_resource_clause = std::make_unique<EnoughResourceConditionClause>(num_resource, threshold_fidelity, partner_address);
  condition->addClause(std::move(enough_resource_clause));
  purify_rule->setCondition(std::move(condition));

  // prepare action
  auto purify_action = std::make_unique<Purification>(purification_type, partner_address);
  purify_rule->setAction(std::move(purify_action));

  return purify_rule;
}

std::unique_ptr<Rule> RuleSetGenerator::swapRule(std::pair<int, int> partner_address, int shared_tag) {
  auto swap_rule = std::make_unique<Rule>(std::vector<int>{partner_address.first, partner_address.second}, shared_tag, true);

  // prepare condition and two enough resource clauses
  auto condition = std::make_unique<Condition>();
  double threshold_fidelity = 0.9;  // placeholder
  auto enough_resource_clause_first = std::make_unique<EnoughResourceConditionClause>(1, threshold_fidelity, partner_address.first);
  auto enough_resource_clause_second = std::make_unique<EnoughResourceConditionClause>(1, threshold_fidelity, partner_address.second);
  condition->addClause(std::move(enough_resource_clause_first));
  condition->addClause(std::move(enough_resource_clause_second));
  swap_rule->setCondition(std::move(condition));

  auto swap_action = std::make_unique<EntanglementSwapping>(std::vector<int>({partner_address.first, partner_address.second}));
  swap_rule->setAction(std::move(swap_action));

  return swap_rule;
}
}  // namespace quisp::modules::ruleset_gen
