#pragma once

#include <map>
#include "Clause.h"

namespace quisp {
namespace rules {
namespace clauses {
class PurificationCountClause : public Clause {
 public:
  int num_purify_must;
  // int mutable current_count;
  PurificationCountClause(int part, QNIC_type qt, int qi, int n_purify) : Clause(part, qt, qi) {  // May not need this
    // max_count = max;
    // current_count = 0;
    num_purify_must = n_purify;
  };

  bool check(std::multimap<int, StationaryQubit*>) const override;
};

}  // namespace clauses
}  // namespace rules
}  // namespace quisp
