#pragma once

#include "Clause.h"

namespace quisp {
namespace rules {
namespace clauses {
class WaitClause : public Clause {
 public:
  WaitClause() : Clause() {};
  bool check(std::multimap<int, IStationaryQubit*>) override;
  bool checkTerminate(std::multimap<int, IStationaryQubit*>) const override { return false; };
};

}  // namespace clauses
}  // namespace rules
}  // namespace quisp
