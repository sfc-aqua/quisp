/** \file Condition.cc
 *
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief Condition
 */
#include "ActiveCondition.h"

namespace quisp::rules {

void ActiveCondition::addClause(ActiveClause *c) { clauses.push_back(c); }

bool ActiveCondition::check(std::multimap<int, IStationaryQubit *> &resources) const {
  for (auto &clause : clauses) {
    if (!clause->check(resources)) {
      return false;
    }
  }
  return true;
}

bool ActiveCondition::checkTerminate(std::multimap<int, IStationaryQubit *> &resources) const {
  for (auto &clause : clauses) {
    if (clause->checkTerminate(resources)) {
      return true;
    }
  }
  return false;
}

}  // namespace quisp::rules
