#pragma once

#include <messages/classical_messages.h>
#include <rules/RuleSet.h>

namespace quisp::modules::ruleset_gen {

class RuleSetGenerator {
 public:
  RuleSetGenerator(int responder_addr) : responder_addr(responder_addr) {}
  void generateRuleSets(messages::ConnectionSetupRequest* req);

 protected:
  /**
   * @brief collect path infomation from initiator to responder
   *
   * @param req
   * @return std::vector<int> vector to store node addresses
   */
  std::vector<int> collectPath(messages::ConnectionSetupRequest* req);
  std::map<int, std::pair<int, int>> collectSwappingPartners(std::vector<int>& path, int divisions, int hop_count);
  int fillPathDivision(std::vector<int>& path, int i, int l, std::vector<int>& link_left, std::vector<int>& link_right, std::vector<int>& swapper, int fill_start);
  std::unique_ptr<rules::Rule> waitRule(int partner_address, int shared_tag);
  std::unique_ptr<rules::Rule> tomographyRule(int partner_address, int owner_address, int num_measure, double threshold_fidelity, int shared_tag, std::string name);
  std::unique_ptr<rules::Rule> purifyRule(int partner_address, rules::PurType purification_type, double threshold_fidelity, int shared_tag, std::string name);
  std::unique_ptr<rules::Rule> swapRule(std::vector<int> partner_address, double threshold_fidelity, int shared_tag, std::string name);

  int responder_addr;
};
}  // namespace quisp::modules::ruleset_gen
