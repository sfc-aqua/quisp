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

namespace quisp {
namespace rules {

/** \class Rule Rule.h
 *
 *  \brief Rule
 */
class Rule {
    private:
        std::list<Condition> conditions;
        std::list<Action> actions;
};

} // namespace rules
} // namespace quisp

#endif//QUISP_RULES_RULE_H_
