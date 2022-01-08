/** \file RuleSet.h
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief RuleSet
 */
#ifndef QUISP_RULES_RULESET_H_
#define QUISP_RULES_RULESET_H_

#include <omnetpp.h>
#include "Rule.h"

namespace quisp {
namespace rules {

using namespace omnetpp;
/** \class RuleSet RuleSet.h
 *
 * \brief Set of rules for the RuleEngine.
 */
class RuleSet {
 public:
  RuleSet(unsigned long _ruleset_id, int _owner_addr);

  unsigned long ruleset_id;
  int owner_addr;
  simtime_t started_at;
};

}  // namespace rules
}  // namespace quisp

#endif  // QUISP_RULES_RULESET_H_
