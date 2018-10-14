/** \file Rule.h
 *  \authors cldurand, takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief Rule
 */
#ifndef QUISP_RULES_RULE_H_
#define QUISP_RULES_RULE_H_

#include "Condition.h"
#include "Action.h"
#include <omnetpp.h>
#include <memory>
#include <stdio.h>

namespace quisp {
namespace rules {

/** \class Rule Rule.h
 *
 *  \brief Rule
 */
class Rule {
    public:
        int rule_identifier;
        pCondition condition;
        pAction action;
        Rule() {};
        Rule(int id) {rule_identifier = id;};
        typedef std::map<int, stationaryQubit*> AvailableResourceForThisStage;
        AvailableResourceForThisStage rc;
        void setCondition (Condition * c) { condition.reset(c); };
        void setAction (Action * a) { action.reset(a); };
        void eraseResource(stationaryQubit * qubit){
            bool erased = false;
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
            }
        };
        void addResource(stationaryQubit * qubit){
            int index = rc.size();
            rc.insert(std::make_pair(index,qubit));
        }

        cPacket* checkrun(cModule *re, qnicResources * resources,int qnic_type, int qnic_index,  int resource_entangled_with_address);
        bool checkTerminate(qnicResources * resources,int qnic_type, int qnic_index,  int resource_entangled_with_address);

};
typedef std::unique_ptr<Rule> pRule;

} // namespace rules
} // namespace quisp

#endif//QUISP_RULES_RULE_H_
