#pragma once
#include "ActiveClause.h"

namespace quisp {
namespace rules {
namespace active {

/** \class Condition Condition.h
 *
 *  \brief Condition
 */
class ActiveCondition {
 public:
  void addClause(ActiveClause* c);
  bool check(std::multimap<int, IStationaryQubit*>& resources) const;
  bool checkTerminate(std::multimap<int, IStationaryQubit*>& resources) const;

  std::vector<ActiveClause*> clauses;
};

}  // namespace active
}  // namespace rules
}  // namespace quisp
