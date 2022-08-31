/** \file Action.cc
 *
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief Action
 */
#include <messages/base_messages_m.h>
#include <omnetpp.h>
#include "ActiveAction.h"

namespace quisp::rules::active::actions {

ActiveAction::ActiveAction(unsigned long ruleset_id, int rule_id) : ruleset_id(ruleset_id), rule_id(rule_id){};

ActiveAction::ActiveAction(unsigned long ruleset_id, int rule_id, int shared_tag) : ruleset_id(ruleset_id), rule_id(rule_id), shared_tag(shared_tag){};

IStationaryQubit *ActiveAction::getResource(int required_index, int partner) {
  int i = 0;
  for (auto it = rule_resources->begin(); it != rule_resources->end(); ++it) {
    if (it->first == partner && !it->second->isLocked()) {
      if (i == required_index) return it->second;
      i++;
    }
  }
  return nullptr;
}

void ActiveAction::removeResource_fromRule(IStationaryQubit *qubit) {
  for (auto it = rule_resources->begin(); it != rule_resources->end(); ++it) {
    if (it->second == qubit) {
      rule_resources->erase(it);
      return;
    }
  }
}
cPacket *ActiveAction::generateError(const char *msg) {
  auto *error = new quisp::messages::Error();
  error->setError_text(msg);
  return error;
}

}  // namespace quisp::rules::active::actions
