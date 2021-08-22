/** \file Action.cc
 *
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief Action
 */
#include "messages/classical_messages.h"
#include <omnetpp.h>
#include "BaseAction.h"

namespace quisp {
namespace rules {
namespace actions {

int Action::checkNumResource() { return (*rule_resources).size(); }

// required_index: 0 is the top one, 1 is the 2nd top one, and so on.
IStationaryQubit *Action::getResource_fromTop(int required_index) {
  int resource_index = 0;
  IStationaryQubit *pt = nullptr;

  for (auto it = (*rule_resources).begin(); it != (*rule_resources).end(); ++it) {
    if (it->second->isLocked()) {
      // Ignore locked resource
    } else if (resource_index == required_index && !it->second->isLocked()) {
      pt = it->second;
      break;
    } else {
      resource_index++;
    }
  }
  return pt;
}

IStationaryQubit *Action::getResource_fromTop_with_partner(int required_index, int partner) {
  // here
  int resource_index = 0;
  IStationaryQubit *pt = nullptr;

  for (auto it = (*rule_resources).begin(); it != (*rule_resources).end(); ++it) {
    if (it->second->isLocked()) {
      // Ignore locked resource
    } else if (it->first == partner && !it->second->isLocked()) {
      pt = it->second;
      break;
    } else {
      resource_index++;
    }
  }
  return pt;
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

}  // namespace actions
}  // namespace rules
}  // namespace quisp
