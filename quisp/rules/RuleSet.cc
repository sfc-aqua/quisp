#include "RuleSet.h"
namespace quisp {
namespace rules {

RuleSet::RuleSet(unsigned long _ruleset_id, int _owner_addr) {
  ruleset_id = _ruleset_id;
  owner_addr = _owner_addr;
  started_at = simTime();
}

}  // namespace rules
}  // namespace quisp
