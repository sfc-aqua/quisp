/** \file RuleSet.h
 *  \authors cldurand
 *  \date 2018/06/25
 *
 *  \brief RuleSet
 */
#ifndef QUISP_RULES_RULESET_H_
#define QUISP_RULES_RULESET_H_

#include "Rule.h"
#include <omnetpp.h>

namespace quisp {
namespace rules {

/** \class RuleSet RuleSet.h
 *
 * \brief Set of rules for the RuleEngine.
 */
class RuleSet {
    private:
        Rule rules[];
};

} // namespace rules
} // namespace quisp

#endif//QUISP_RULES_RULESET_H_
