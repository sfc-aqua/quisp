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
  int ruleset_id;
  int rule_index;
  pCondition condition;
  pAction action;
  std::multimap<int, StationaryQubit *> resources;
  int mutable number_of_resources_allocated_in_total = 0;
  // std::unique_ptr<Rule> next_rule;
  Rule(){};
  Rule(int rs_index, int r_index) {
    ruleset_id = rs_index;
    rule_index = r_index;
  };

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
  // bool checkTerminate(qnicResources * resources,int qnic_type, int qnic_index,  int resource_entangled_with_address);
};

typedef std::unique_ptr<Rule> pRule;

}  // namespace rules
}  // namespace quisp

#endif  // QUISP_RULES_RULE_H_
