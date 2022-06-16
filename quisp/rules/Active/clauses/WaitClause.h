#pragma once

#include "ActiveClause.h"

namespace quisp::rules::active::clauses {
class WaitClause : public ActiveClause {
 public:
  WaitClause() : ActiveClause(){};
  bool check(std::multimap<int, IStationaryQubit*>&) override;
  bool checkTerminate(std::multimap<int, IStationaryQubit*>&) const override { return false; };
};

}  // namespace quisp::rules::active::clauses
