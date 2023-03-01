#pragma once
#include <map>
#include <utility>

#include <nlohmann/json.hpp>

#include "messages/classical_messages.h"
#include "rules/RuleSet.h"

namespace quisp::modules::ruleset_gen {

class RuleSetGenerator {
 public:
  RuleSetGenerator(int responder_addr) : responder_addr(responder_addr) {}

  /**
   * @brief generate RuleSets for the given connection setup request.
   *
   * @param req
   * @param ruleset_id
   * @return std::map<int, nlohmann::json> a map of json serialized RuleSets and its node addresses as key
   */
  std::map<int, nlohmann::json> generateRuleSets(messages::ConnectionSetupRequest* req, unsigned long ruleset_id);

  /**
   * @brief generate rules for each node in the path.
   *
   * @param left_node_index  index in the path from initiator to responder
   * @param right_node_index index in the path from initiator to responder
   * @param rules_map        store rules for each node <node_address, vector<Rules>>
   * @param path             store address from initiator to responder
   * @param shared_rule_tag
   */
  void generateReverseSwapAtHalfRuleSets(int left_node_index, int right_node_index, std::map<int, std::vector<std::unique_ptr<rules::Rule>>>& rules_map, std::vector<int>& path,
                                         int& shared_rule_tag);

 protected:
  /**
   * @brief collect path infomation from initiator to responder
   *
   * @param req
   * @return std::vector<int> vector to store node addresses
   */
  std::vector<int> collectPath(messages::ConnectionSetupRequest* req);

  /**
   * @brief create tomography rule
   *
   * @param partner_address
   * @param owner_address
   * @param num_measure
   * @param shared_rule_tag
   * @return std::unique_ptr<rules::Rule>
   */
  std::unique_ptr<rules::Rule> tomographyRule(int partner_address, int owner_address, int num_measure, int shared_rule_tag);

  /**
   * @brief create purification rule
   *
   * @param partner_address
   * @param purification_type
   * @param shared_tag
   * @return std::unique_ptr<rules::Rule>
   */
  std::unique_ptr<rules::Rule> purifyRule(int partner_address, rules::PurType purification_type, int shared_tag);

  /**
   * @brief create entanglement swapping rule
   *
   * @param partner_address
   * @param shared_rule_tag
   * @return std::unique_ptr<rules::Rule>
   */
  std::unique_ptr<rules::Rule> swapRule(std::pair<int, int> partner_address, int shared_rule_tag);

  /**
   * @brief create rule that waits for the swapping correction/notification from swapper node
   *
   * @param swapper_address
   * @param shared_rule_tag
   * @return std::unique_ptr<rules::Rule>
   */
  std::unique_ptr<rules::Rule> swapCorrectionRule(int swapper_address, int shared_rule_tag);

  int responder_addr;
};
}  // namespace quisp::modules::ruleset_gen
