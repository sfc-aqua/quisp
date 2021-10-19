#pragma once

#include <map>
#include "Clause.h"

namespace quisp {
namespace rules {
namespace clauses {

class EnoughResourceClause : public Clause {
 protected:
  int num_resource_required;
  int partner;

 public:
  EnoughResourceClause(int partner_addr, int num_res) : Clause() {
    num_resource_required = num_res;
    partner = partner_addr;
  };
  bool check(std::multimap<int, IStationaryQubit*>) override;
  bool checkTerminate(std::multimap<int, IStationaryQubit*>) const override { return false; };
};
}  // namespace clauses

}  // namespace rules
}  // namespace quisp
