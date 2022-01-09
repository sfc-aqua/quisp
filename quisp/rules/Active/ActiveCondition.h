#pragma once
#include "ActiveClause.h"

namespace quisp::rules::active {
class ActiveCondition {
 public:
  void addClause(ActiveClause* c);
  bool check(std::multimap<int, IStationaryQubit*>& resources) const;
  bool checkTerminate(std::multimap<int, IStationaryQubit*>& resources) const;

  std::vector<ActiveClause*> clauses;
};

}  // namespace quisp::rules::active
