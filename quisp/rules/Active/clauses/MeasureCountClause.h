#pragma once

#include <map>
#include "ActiveClause.h"

namespace quisp {
namespace rules {
namespace clauses {
class MeasureCountClause : public ActiveClause {
 public:
  int max_count;
  int current_count = 0;
  MeasureCountClause(int _max_count, int partner_addr, QNIC_type qnic_type, int qnic_id, int resource) : ActiveClause(partner_addr, qnic_type, qnic_id, resource) {
    max_count = _max_count;
  };
  MeasureCountClause(int _max_count) : ActiveClause() { max_count = _max_count; };
  bool check(std::multimap<int, IStationaryQubit*>&) override;
  bool checkTerminate(std::multimap<int, IStationaryQubit*>&) const override;
};

}  // namespace clauses
}  // namespace rules
}  // namespace quisp
