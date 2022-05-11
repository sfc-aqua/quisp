#pragma once
#include <omnetpp.h>
#include <stdio.h>
#include <memory>
#include "ActiveAction.h"
#include "ActiveCondition.h"

namespace quisp::rules::active {
class ActiveRule {
 public:
  unsigned long ruleset_id;
  int rule_id;
  int next_rule_id = 0;
  int shared_tag;
  std::string name;
  std::unique_ptr<ActiveCondition> condition;
  std::unique_ptr<ActiveAction> action;
  std::multimap<int, IStationaryQubit *> resources;
  std::vector<int> action_partners;

  ActiveRule(unsigned long ruleset_id, int rule_id, int shared_tag, std::string rule_name = "", std::vector<int> action_partners = {});

  void addResource(int address_entangled_with, IStationaryQubit *qubit);
  void setCondition(ActiveCondition *c);
  void setAction(ActiveAction *a);

  cPacket *checkrun(cModule *re);
  bool checkTerminate();
};

}  // namespace quisp::rules::active
