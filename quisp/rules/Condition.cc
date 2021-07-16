/** \file Condition.cc
 *
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief Condition
 */
#include "Condition.h"
#include <memory>

namespace quisp {
namespace rules {

void Condition::addClause(Clause *c) { clauses.push_back(c); }

bool Condition::check(std::multimap<int, StationaryQubit *> resources) const {
  bool satisfying = true;
  for (auto &clause : clauses) {
    if (!clause->check(resources)) {
      satisfying = false;
      break;
    }
  }
  return satisfying;
}

bool Condition::checkTerminate(std::multimap<int, StationaryQubit *> resources) const {
  bool satisfying = false;
  for (auto &clause : clauses) {
    if (clause->checkTerminate(resources)) {
      satisfying = true;
      break;
    }
  }
  return satisfying;
}

}  // namespace rules
}  // namespace quisp
