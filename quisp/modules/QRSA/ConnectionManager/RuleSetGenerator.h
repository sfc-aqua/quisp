#pragma once
#include <map>
#include <utility>

#include <messages/classical_messages.h>
#include <rules/RuleSet.h>
#include <nlohmann/json.hpp>

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

  void generateSimpleSwappingRuleSets(std::map<int, std::vector<std::unique_ptr<rules::Rule>>>& rules_map, std::vector<int>& path, std::vector<int>& rev_path,
                                      std::map<int, std::pair<int, int>>& swapping_partners_table, int num_measure);

 protected:
  /**
   * @brief collect path infomation from initiator to responder
   *
   * @param req
   * @return std::vector<int> vector to store node addresses
   */
  std::vector<int> collectPath(messages::ConnectionSetupRequest* req);
  std::map<int, std::pair<int, int>> collectSwappingPartners(std::vector<int>& path, int divisions, int hop_count);

  /**
   * Treat subpath [i:...] of length l
   * @param path Nodes on the connection setup path
   * @param i Left of the subpath to consider
   * @param l Length of the subpath
   * @param link_left Left part of the list of "links"
   * @param link_right Right part
   * @param swapper Swappers to create those links (might be -1 for real links)
   * @param fill_start [0:fill_start[ is already filled
   **/
  int fillPathDivision(std::vector<int>& path, int i, int l, std::vector<int>& link_left, std::vector<int>& link_right, std::vector<int>& swapper, int fill_start);

  std::unique_ptr<rules::Rule> waitRule(int partner_address, int shared_tag);
  std::unique_ptr<rules::Rule> tomographyRule(int partner_address, int owner_address, int num_measure, int shared_tag);
  std::unique_ptr<rules::Rule> purifyRule(int partner_address, rules::PurType purification_type, int shared_tag);
  std::unique_ptr<rules::Rule> swapRule(std::pair<int, int> partner_address, int shared_tag);

  int responder_addr;
};
}  // namespace quisp::modules::ruleset_gen
