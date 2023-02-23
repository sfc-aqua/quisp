#pragma once
#include <map>
#include <utility>

#include <messages/classical_messages.h>
#include <rules/RuleSet.h>
#include <types/QNodeAddr.h>
#include <nlohmann/json.hpp>

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
   * @param rules_map
   * @param path
   * @param rev_path
   * @param swapping_partners_table
   * @param num_measure
   */
  void generateSimpleSwappingRuleSets(std::map<QNodeAddr, std::vector<std::unique_ptr<rules::Rule>>>& rules_map, std::vector<QNodeAddr>& path, std::vector<QNodeAddr>& rev_path,
                                      std::map<QNodeAddr, std::pair<QNodeAddr, QNodeAddr>>& swapping_partners_table, int num_measure);

 protected:
  /**
   * @brief collect path infomation from initiator to responder
   *
   * @param req
   * @return std::vector<int> vector to store node addresses
   */
  std::vector<QNodeAddr> collectPath(messages::ConnectionSetupRequest* req);

  /**
   * @brief collect swapper and partners from the given path information
   *
   * @param path
   * @param divisions
   * @param hop_count
   * @return std::map<QNodeAddr, std::pair<QNodeAddr, QNodeAddr>> swapper addr -> {left partner addr, right partner addr}
   */
  std::map<QNodeAddr, std::pair<QNodeAddr, QNodeAddr>> collectSwappingPartners(std::vector<QNodeAddr>& path, int divisions, int hop_count);

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
  int fillPathDivision(std::vector<QNodeAddr>& path, int i, int l, std::vector<QNodeAddr>& link_left, std::vector<QNodeAddr>& link_right, std::vector<QNodeAddr>& swapper,
                       int fill_start);

  /**
   * @brief create tomography rule
   *
   * @param partner_address
   * @param owner_address
   * @param num_measure
   * @param shared_tag
   * @return std::unique_ptr<rules::Rule>
   */
  std::unique_ptr<rules::Rule> tomographyRule(QNodeAddr partner_address, QNodeAddr owner_address, int num_measure, int shared_tag);

  /**
   * @brief create purification rule
   *
   * @param partner_address
   * @param purification_type
   * @param shared_tag
   * @return std::unique_ptr<rules::Rule>
   */
  std::unique_ptr<rules::Rule> purifyRule(QNodeAddr partner_address, rules::PurType purification_type, int shared_tag);

  /**
   * @brief create entanglement swapping rule
   *
   * @param partner_address
   * @param shared_tag
   * @return std::unique_ptr<rules::Rule>
   */
  std::unique_ptr<rules::Rule> swapRule(std::pair<QNodeAddr, QNodeAddr> partner_address, int shared_tag);

  QNodeAddr responder_addr;
};
}  // namespace quisp::modules::ruleset_gen
