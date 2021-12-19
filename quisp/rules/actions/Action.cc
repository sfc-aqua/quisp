/** \file Action.cc
 *
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief Action
 */
#include <messages/base_messages_m.h>
#include <omnetpp.h>
#include "BaseAction.h"

namespace quisp::rules::actions {

IStationaryQubit *Action::getResource(int required_index, int partner) {
  int i = 0;
  for (auto it = (*rule_resources).begin(); it != (*rule_resources).end(); ++it) {
    if (it->first == partner && !it->second->isLocked()) {
      if (i == required_index) return it->second;
      i++;
    }
  }
  return nullptr;
}

void Action::removeResource_fromRule(IStationaryQubit *qubit) {
  for (auto it = (*rule_resources).begin(), next_it = (*rule_resources).begin(); it != (*rule_resources).end(); it = next_it) {
    next_it = it;
    ++next_it;
    if (it->second == qubit) {
      (*rule_resources).erase(it);
      break;
    }
  }
}
cPacket *Action::generateError(const char *msg) {
  auto *error = new quisp::messages::Error();
  error->setError_text(msg);
  return error;
}

}  // namespace quisp::rules::actions
