#include "WaitAction.h"
#include <messages/classical_messages.h>
#include <modules/QRSA/RuleEngine/IRuleEngine.h>

namespace quisp::rules::active::actions {
  cPacket *WaitAction::run(cModule *re) {
    auto *pk = new WaitResult;
    pk->setKind(6);
    pk->setRuleSet_id(ruleset_id);
    pk->setRule_id(rule_id);
    return pk;
  }
}  // namespace quisp::rules::active::actions
