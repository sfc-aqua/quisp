#pragma once

#include <map>
#include "Clause.h"

namespace quisp {
namespace rules {
namespace clauses {
class FidelityClause : public Clause {
 protected:
  double threshold;

 public:
  FidelityClause(int partner, int resource, double fidelity) : Clause(partner, resource) { threshold = fidelity; };
  FidelityClause(int part, QNIC_type qt, int qi, int res, double fidelity) : Clause(part, qt, qi, res) { threshold = fidelity; };
  // bool check(qnicResources *resources) const override;
  // bool checkTerminate(qnicResources *resources) const override {return 0;} ;
  [[noreturn]] bool check(std::multimap<int, StationaryQubit*>) const override;
  bool checkTerminate(std::multimap<int, StationaryQubit*>) const override;
};
}  // namespace clauses
}  // namespace rules
}  // namespace quisp
