#include "ActiveCondition.h"

namespace quisp::rules::active {

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

}  // namespace quisp::rules::active
