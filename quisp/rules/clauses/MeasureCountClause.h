#pragma once

#include <map>
#include "Clause.h"

namespace quisp {
namespace rules {
namespace clauses {
class MeasureCountClause : public Clause {
 public:
  int max_count;
  int mutable current_count;
  MeasureCountClause(int max, int part, QNIC_type qt, int qi, int res) : Clause(part, qt, qi, res) {  // May not need this
    max_count = max;
    current_count = 0;
  };
  MeasureCountClause(int max) : Clause() {
    max_count = max;
    current_count = 0;
  };
  // bool check(qnicResources *resources) const override;
  // bool checkTerminate(qnicResources *resources) const override;
  bool check(std::multimap<int, StationaryQubit*>) const override;
  bool checkTerminate(std::multimap<int, StationaryQubit*>) const override;
  // void increment(){current_count++;};
};

}  // namespace clauses
}  // namespace rules
}  // namespace quisp
