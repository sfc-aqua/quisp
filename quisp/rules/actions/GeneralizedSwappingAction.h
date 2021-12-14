#pragma once

#include "BaseAction.h"
#include <string.h>

namespace quisp {
namespace rules {
namespace actions {

class GeneralizedSwappingAction : public Action {
 protected:
  // First partner
  std::vector<int> partners;
  std::vector<int> associated_end_nodes;
  std::vector<QNIC_type> qnic_types;
  std::vector<int> qnic_ids;
  std::vector<int> qnic_addresses;
  std::vector<int> resources;
  std::map<int, int> correction_number_for_node;
  std::string label = "";
  int size_tree_leafless;
  int action_index = 0;

  std::vector<int> self_qnic_ids;
  std::vector<QNIC_type> self_qnic_types;

 public:
  // constructor of entanglement swapping
  GeneralizedSwappingAction(unsigned long RuleSet_id, int rule_index, std::vector<int> partners, std::vector<int> associated_end_nodes,
                            std::vector<QNIC_type> types, std::vector<int> ids, std::vector<int> addresses,
                            std::vector<int> resources, std::vector<int> self_ids, std::vector<QNIC_type> self_types,
                            std::string label, int size_tree, std::map<int,int> correction_number);
  // cPacket* run(qnicResources *resources) override;
  // cPacket* run(cModule *re, qnicResources *resources) override;
  cPacket* run(cModule* re) override;
};

}  // namespace actions
}  // namespace rules
}  // namespace quisp
