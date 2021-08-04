#pragma once

#include <map>
#include "Clause.h"

namespace quisp {
namespace rules {
namespace clauses {
class PurificationCountClause : public Clause {
 public:
  int num_purify_must;
  PurificationCountClause(int partner_addr, QNIC_type qnic_type, int qnic_id, int n_purify) : Clause(partner_addr, qnic_type, qnic_id) { num_purify_must = n_purify; };

  [[noreturn]] bool check(std::multimap<int, StationaryQubit*>) override;
};

}  // namespace clauses
}  // namespace rules
}  // namespace quisp
