#include "RuleSetGenerator.h"

namespace quisp::modules::ruleset_gen {

using namespace quisp::rules;

void RuleSetGenerator::generateRuleSets(messages::ConnectionSetupRequest* req) {
  auto path = collectPath(req);
  size_t hop_count = req->getStack_of_QNodeIndexesArraySize();
  size_t divisions = hop_count * 2 - 1;
  auto swapping_partners_table = collectSwappingPartners(path, divisions, hop_count);

  // Initialize empty RuleSet
  // store rule as a map and vector
  /* {node1_addr, {rule1, rule2, ...}}
   * {node2_addr, {rule1, rule2, ...}}
   * ...
   */
  std::map<int, std::vector<std::unique_ptr<Rule>>> rules_map;
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
        auto config = generateSwappingConfig(swapper_node, path, swapping_partners_table, qnics, 0);
        int left_partner = config.left_partner, right_partner = config.right_partner;
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
          auto wait_rule_left = waitRule(swapper_node, shared_tag);
          auto wait_rule_right = waitRule(swapper_node, shared_tag);
          auto swapping_rule = swapRule(swapping_partners_table[swapper_node], threshold_fidelity, shared_tag);
          shared_tag++;
          rules_map[left_partner].push_back(std::move(wait_rule_left));
          rules_map[right_partner].push_back(std::move(wait_rule_right));
          rules_map[swapper_node].push_back(std::move(swapping_rule));

          // Purification Rules
          // for (int i = 0; i < num_remote_purification; i++) {
          //   auto pur_rule_left = purifyRule(right_partner, purification_type, threshold_fidelity, shared_tag);
          //   auto pur_rule_right = purifyRule(left_partner, purification_type, threshold_fidelity, shared_tag);
          //   shared_tag++;
          //   rules_map[left_partner].push_back(std::move(pur_rule_left));
          //   rules_map[right_partner].push_back(std::move(pur_rule_right));
          // }
        }
      }
    }
  }
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

std::unique_ptr<Rule> RuleSetGenerator::tomographyRule(int partner_address, int owner_address, int num_measure, double threshold_fidelity, int shared_tag, std::string name) {
  auto tomography_rule = std::make_unique<Rule>(partner_address, shared_tag, true);
  tomography_rule->setName(name);

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

std::unique_ptr<Rule> RuleSetGenerator::purifyRule(int partner_address, PurType purification_type, double threshold_fidelity, int shared_tag, std::string name) {
  auto purify_rule = std::make_unique<Rule>(partner_address, shared_tag, false);
  purify_rule->setName(name);

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

std::unique_ptr<Rule> RuleSetGenerator::swapRule(std::vector<int> partner_address, double threshold_fidelity, int shared_tag, std::string name) {
  auto swap_rule = std::make_unique<Rule>(partner_address, shared_tag, true);
  swap_rule->setName(name);

  // prepare condition and two enough resource clauses
  auto condition = std::make_unique<Condition>();
  auto enough_resource_clause_first = std::make_unique<EnoughResourceConditionClause>(1, threshold_fidelity, partner_address.at(0));
  auto enough_resource_clause_second = std::make_unique<EnoughResourceConditionClause>(1, threshold_fidelity, partner_address.at(1));
  condition->addClause(std::move(enough_resource_clause_first));
  condition->addClause(std::move(enough_resource_clause_second));
  swap_rule->setCondition(std::move(condition));

  auto swap_action = std::make_unique<EntanglementSwapping>(partner_address);
  swap_rule->setAction(std::move(swap_action));

  return swap_rule;
}
}  // namespace quisp::modules::ruleset_gen
