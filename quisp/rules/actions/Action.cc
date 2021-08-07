/** \file Action.cc
 *
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief Action
 */
#include <classical_messages_m.h>
#include <omnetpp.h>
#include "BaseAction.h"

namespace quisp {
namespace rules {
namespace actions {

int Action::checkNumResource() { return (*rule_resources).size(); }

// required_index: 0 is the top one, 1 is the 2nd top one, and so on.
StationaryQubit *Action::getResource_fromTop(int required_index) {
  int resource_index = 0;
  StationaryQubit *pt = nullptr;

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

StationaryQubit *Action::getResourceFromTopWithPartner(int required_index, int partner) {
  // here
  StationaryQubit *pt = nullptr;

  std::vector<StationaryQubit *> available_entanglements_with_partner;
  // 1. take partners
  for (auto it = (*rule_resources).begin(); it != (*rule_resources).end(); ++it) {
    if (it->first == partner && !it->second->isLocked()) {
      available_entanglements_with_partner.push_back(it->second);
    }
  }
  // 2. check the index
  for (int i = 0; i < available_entanglements_with_partner.size(); i++) {
    if (i == required_index && !available_entanglements_with_partner.at(i)->isLocked()) {
      pt = available_entanglements_with_partner.at(i);
    }
  }
  return pt;
}

void Action::removeResource_fromRule(StationaryQubit *qubit) {
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
