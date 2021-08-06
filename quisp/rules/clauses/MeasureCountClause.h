#pragma once

#include <map>
#include "Clause.h"

namespace quisp {
namespace rules {
namespace clauses {
class MeasureCountClause : public Clause {
 public:
  int max_count;
  int current_count = 0;
  MeasureCountClause(int _max_count, int partner_addr, QNIC_type qnic_type, int qnic_id, int resource) : Clause(partner_addr, qnic_type, qnic_id, resource) {
    max_count = _max_count;
  };
  MeasureCountClause(int _max_count) : Clause() { max_count = _max_count; };
  bool check(std::multimap<int, StationaryQubit*>) override;
  bool checkTerminate(std::multimap<int, StationaryQubit*>) const override;
};

}  // namespace clauses
}  // namespace rules
}  // namespace quisp
