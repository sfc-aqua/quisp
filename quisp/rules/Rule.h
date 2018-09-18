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
        void setAction (Action * a) { action.reset(a); };
};
typedef std::unique_ptr<Rule> pRule;

} // namespace rules
} // namespace quisp

#endif//QUISP_RULES_RULE_H_
