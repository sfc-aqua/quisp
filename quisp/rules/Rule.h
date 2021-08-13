/** \file Rule.h
 *  \authors cldurand, takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief Rule
 */
#ifndef QUISP_RULES_RULE_H_
#define QUISP_RULES_RULE_H_

#include <omnetpp.h>
#include <stdio.h>
#include <memory>
#include "Action.h"
#include "Condition.h"

namespace quisp {
namespace rules {

/** \class Rule Rule.h
 *
 *  \brief Rule
 */

class Rule {
 public:
  unsigned long ruleset_id;
  unsigned long rule_index;
  std::string name;
  std::unique_ptr<Condition> condition;
  std::unique_ptr<Action> action;
  std::multimap<int, StationaryQubit *> resources;
  std::vector<int> action_partners;
  int mutable number_of_resources_allocated_in_total = 0;
  // std::unique_ptr<Rule> next_rule;
  Rule(){};
  Rule(unsigned long rs_index, unsigned long r_index) {
    ruleset_id = rs_index;
    rule_index = r_index;
  };

  Rule(unsigned long rs_index, unsigned long r_index, std::string r_name) {
    ruleset_id = rs_index;
    rule_index = r_index;
    name = r_name;
  };

  // May need combine with above two constructors
  Rule(unsigned long rs_index, unsigned long r_index, std::string r_name, std::vector<int> _action_partners) {
    ruleset_id = rs_index;
    rule_index = r_index;
    name = r_name;
    action_partners = _action_partners;
  };

  int num_partners() { return action_partners.size(); };
  void addResource(int address_entangled_with, StationaryQubit *qubit);
  void setCondition(Condition *c);
  void setAction(Action *a);
  void eraseResource(StationaryQubit *qubit){
      /*bool erased = false;
      for (auto it =  rc.cbegin(), next_it =  rc.cbegin(); it !=  rc.cend(); it = next_it){
          next_it = it; ++next_it;
          if (it->second == qubit){
              rc.erase(it);
              erased = true;
              break;
          }
      }
      if(!erased){
          std::cout<<"Trying to erase an un-queued resource.....! \n";
      }*/
  };

  // cPacket* checkrun(cModule *re, qnicResources * resources,int qnic_type, int qnic_index,  int resource_entangled_with_address);
  cPacket *checkrun(cModule *re);
  bool checkTerminate();
  bool checkActionPartner(int action_partner);
  // bool checkTerminate(qnicResources * resources,int qnic_type, int qnic_index,  int resource_entangled_with_address);
};

}  // namespace rules
}  // namespace quisp

#endif  // QUISP_RULES_RULE_H_
