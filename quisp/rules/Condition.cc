/** \file Condition.cc
 *
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief Condition
 */
#include "Condition.h"

namespace quisp::rules {

void Condition::addClause(Clause *c) { clauses.push_back(c); }

bool Condition::check(std::multimap<int, IStationaryQubit *> resources) const {
  for (auto &clause : clauses) {
    if (!clause->check(resources)) {
      return false;
    }
  }
  return true;
}

bool Condition::checkTerminate(std::multimap<int, IStationaryQubit *> resources) const {
  for (auto &clause : clauses) {
    if (clause->checkTerminate(resources)) {
      return true;
    }
  }
  return false;
}

}  // namespace quisp::rules
