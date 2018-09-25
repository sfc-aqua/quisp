/** \file Rule.h
 *  \authors cldurand
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
        pCondition condition;
        pAction action;
        Rule() {};
        void setCondition (Condition * c) { condition.reset(c); };
        //const pCondition& getCondition() { return condition; };
        void setAction (Action * a) { action.reset(a); };
        //const pAction& getAction() { return action; };
        int checkrun(qnicResources * resources,int qnic_type, int qnic_index,  int resource_entangled_with_address);
        int checkrun(qnicResources * resources);
        int checkTerminate(qnicResources * resources,int qnic_type, int qnic_index,  int resource_entangled_with_address);
        int checkTerminate(qnicResources * resources);
        int test(qnicResources * resources);
};
typedef std::unique_ptr<Rule> pRule;

} // namespace rules
} // namespace quisp

#endif//QUISP_RULES_RULE_H_
