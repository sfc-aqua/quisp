#include "RuleSetGenerator.h"

namespace quisp::modules::ruleset_gen {

using namespace quisp::rules;

void RuleSetGenerator::generateSimpleSwappingRuleSets(std::map<int, std::vector<std::unique_ptr<Rule>>>& rules_map, std::vector<int>& path, std::vector<int>& rev_path,
                                                      std::map<int, std::pair<int, int>>& swapping_partners_table, int num_measure) {
  // used for identifying the partner rule.
  int shared_tag = 0;

  // distance between swapper and its partners
  for (int distance = 1; distance < path.size() / 2 + 1; distance++) {
    // swapper's index
    for (int i = 1; i < (path.size() + 1) / 2; i++) {
      std::vector<int> swapper_nodes;
      if (rev_path.at(i) != path.at(i)) {
        swapper_nodes = {rev_path.at(i), path.at(i)};
      } else {
        swapper_nodes = {path.at(i)};
      }
      // iterate swapper nodes
      for (int swapper_node : swapper_nodes) {
        auto [left_partner, right_partner] = swapping_partners_table.find(swapper_node)->second;

        auto swapper_it = std::find(path.begin(), path.end(), swapper_node);
        auto left_it = std::find(path.begin(), path.end(), left_partner);
        auto right_it = std::find(path.begin(), path.end(), right_partner);
        if (swapper_it == path.end() || left_it == path.end() || right_it == path.end()) {
          throw std::runtime_error("swapper and partner indices are not found in the path. Should not happen.");
        }

        // check if the distance of swapping is the same as the target distance
        auto left_swapper_dist = std::abs(std::distance(left_it, swapper_it));
        auto right_swapper_dist = std::abs(std::distance(swapper_it, right_it));
        if (std::max(left_swapper_dist, right_swapper_dist) == distance) {
          rules_map[swapper_node].push_back(swapRule(swapping_partners_table[swapper_node], shared_tag));
          shared_tag++;
        }
      }
    }
  }

  // add tomography rules
  int initiator_addr = path.at(0);
  rules_map[initiator_addr].emplace_back(tomographyRule(responder_addr, initiator_addr, num_measure, shared_tag));
  rules_map[responder_addr].emplace_back(tomographyRule(initiator_addr, responder_addr, num_measure, shared_tag));
  shared_tag++;
}

std::map<int, json> RuleSetGenerator::generateRuleSets(messages::ConnectionSetupRequest* req, unsigned long ruleset_id) {
  // prepare information for RuleSets generation
  auto path = collectPath(req);
  size_t hop_count = req->getStack_of_QNodeIndexesArraySize();
  size_t divisions = hop_count * 2 - 1;
  auto swapping_partners_table = collectSwappingPartners(path, divisions, hop_count);

  std::map<int /* node addr */, std::vector<std::unique_ptr<Rule>>> rules_map;
  auto rev_path = path;
  std::reverse(rev_path.begin(), rev_path.end());
  int num_measure = req->getNum_measure();
  std::map<int, json> rulesets{};

  // generate rules and put it into rules_map
  generateSimpleSwappingRuleSets(rules_map, path, rev_path, swapping_partners_table, num_measure);

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

std::map<int, std::pair<int, int>> RuleSetGenerator::collectSwappingPartners(std::vector<int>& path, int divisions, int hop_count) {
  /// recognize partner. (which node is left partner, right partner)
  /// Currently, we choose every other node in the path to do swapping in the first round.
  /// In the examples below, the number in parentheses is the round of swapping,
  /// and designates which nodes are swapping.
  /// If the number of hops is a power of two, we get something like
  /// \verbatim
  /// node1 --- node2(1) --- node3 --- node4(1) --- node5
  /// node1 ---------------- node3 ---------------- node5
  /// node1 ---------------- node3(2) ------------- node5
  /// node1 --------------------------------------- node5
  /// \endverbatim
  /// If the number of hops is not a power of two, at some stage
  /// the number of hops will become become odd as we proceed,
  /// forcing us to decide which to do first.  In this version
  /// of the code, we just give priority starting from the left
  /// (start of our list)
  /// \verbatim
  /// node1 --- node2(1) --- node3 --- node4(1) --- node5 --- node6
  /// node1 ---------------- node3 ---------------- node5 --- node6
  /// node1 ---------------- node3(2) ------------- node5 --- node6
  /// node1 --------------------------------------- node5 --- node6
  /// node1 ------------------------------------ node5(3) --- node6
  /// node1 ------------------------------------------------- node6
  /// \endverbatim
  /// todo hypothetically, with no purification, all of the intermediate
  /// nodes could swap asynchronously and essentially simultaneously.
  /// In fact, that's probably what we want, to minimize decoherence.
  /// But, the condition clause will have to be extended in order to support
  /// "when part of this connection" rather than "when entangled with this node"
  /// and you have to be careful of not creating the wrong result by accident.

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

std::unique_ptr<Rule> RuleSetGenerator::tomographyRule(int partner_address, int owner_address, int num_measure, int shared_tag) {
  auto tomography_rule = std::make_unique<Rule>(partner_address, shared_tag, true);

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

std::unique_ptr<Rule> RuleSetGenerator::purifyRule(int partner_address, PurType purification_type, int shared_tag) {
  auto purify_rule = std::make_unique<Rule>(partner_address, shared_tag, false);

  // decide how many Bell pairs are required
  int num_resource;
  if (purification_type == PurType::SINGLE_X || purification_type == PurType::SINGLE_Z || purification_type == PurType::SINGLE_Y) {
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
  auto enough_resource_clause = std::make_unique<EnoughResourceConditionClause>(num_resource, partner_address);
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
  auto enough_resource_clause_first = std::make_unique<EnoughResourceConditionClause>(1, partner_address.first);
  auto enough_resource_clause_second = std::make_unique<EnoughResourceConditionClause>(1, partner_address.second);
  condition->addClause(std::move(enough_resource_clause_first));
  condition->addClause(std::move(enough_resource_clause_second));
  swap_rule->setCondition(std::move(condition));

  auto swap_action = std::make_unique<EntanglementSwapping>(std::vector<int>({partner_address.first, partner_address.second}));
  swap_rule->setAction(std::move(swap_action));

  return swap_rule;
}
}  // namespace quisp::modules::ruleset_gen
