#pragma once
#include <map>
#include <utility>

#include <nlohmann/json.hpp>

#include "messages/classical_messages.h"
#include "rules/RuleSet.h"
#include "types/QNodeAddr.h"

namespace quisp::modules::ruleset_gen {

using types::QNodeAddr;

class RuleSetGenerator {
 public:
  RuleSetGenerator(QNodeAddr responder_addr) : responder_addr(responder_addr) {}

  /**
   * @brief generate RuleSets for the given connection setup request.
   *
   * @param req
   * @param ruleset_id
   * @return std::map<QNodeAddr, nlohmann::json> a map of json serialized RuleSets and its node addresses as key
   */
  std::map<QNodeAddr, nlohmann::json> generateRuleSets(messages::ConnectionSetupRequest* req, unsigned long ruleset_id);

  /**
   * @brief generate rules for each node in the path.
   *
   * @param left_node_index  index in the path from initiator to responder
   * @param right_node_index index in the path from initiator to responder
   * @param rules_map        store rules for each node <node_address, vector<Rules>>
   * @param path             store address from initiator to responder
   * @param shared_rule_tag
   */
  void generateReverseSwapAtHalfRuleSets(int left_node_index, int right_node_index, std::map<QNodeAddr, std::vector<std::unique_ptr<rules::Rule>>>& rules_map,
                                         std::vector<QNodeAddr>& path, int& shared_rule_tag);

 protected:
  /**
   * @brief collect path infomation from initiator to responder
   *
   * @param req
   * @return std::vector<int> vector to store node addresses
   */
  std::vector<QNodeAddr> collectPath(messages::ConnectionSetupRequest* req);

  /**
   * @brief create tomography rule
   *
   * @param partner_address
   * @param owner_address
   * @param num_measure
   * @param shared_rule_tag
   * @return std::unique_ptr<rules::Rule>
   */
  std::unique_ptr<rules::Rule> tomographyRule(QNodeAddr partner_address, QNodeAddr owner_address, int num_measure, int shared_rule_tag);

  /**
   * @brief create purification rule
   *
   * @param partner_address
   * @param purification_type
   * @param shared_rule_tag
   * @return std::unique_ptr<rules::Rule>
   */
  std::unique_ptr<rules::Rule> purifyRule(QNodeAddr partner_address, rules::PurType purification_type, int shared_rule_tag);

  /**
   * @brief create rule that waits for purification measurement result and check for its correlation
   *
   * @param partner_address
   * @param purification_protocol
   * @param shared_rule_tag
   * @return std::unique_ptr<rules::Rule>
   */
  std::unique_ptr<rules::Rule> purificationCorrelationRule(QNodeAddr partner_address, rules::PurType purification_protocol, int shared_rule_tag);

  /**
   * @brief create entanglement swapping rule
   *
   * @param partner_address
   * @param shared_rule_tag
   * @return std::unique_ptr<rules::Rule>
   */
  std::unique_ptr<rules::Rule> swapRule(std::pair<QNodeAddr, QNodeAddr> partner_address, int shared_rule_tag);

  /**
   * @brief create rule that waits for the swapping correction/notification from swapper node
   *
   * @param swapper_address
   * @param shared_rule_tag
   * @return std::unique_ptr<rules::Rule>
   */
  std::unique_ptr<rules::Rule> swapCorrectionRule(QNodeAddr swapper_address, int shared_rule_tag);

  QNodeAddr responder_addr;
};
}  // namespace quisp::modules::ruleset_gen
