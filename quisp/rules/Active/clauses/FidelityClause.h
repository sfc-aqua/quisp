#pragma once

#include <map>
#include "ActiveClause.h"

namespace quisp::rules::active::clauses {
class FidelityClause : public ActiveClause {
 protected:
  double threshold;

 public:
  FidelityClause(int partner, int resource, double fidelity) : ActiveClause(partner, resource) { threshold = fidelity; };
  FidelityClause(int part, QNIC_type qt, int qi, int res, double fidelity) : ActiveClause(part, qt, qi, res) { threshold = fidelity; };
  [[noreturn]] bool check(std::multimap<int, IStationaryQubit*>&) override;
  bool checkTerminate(std::multimap<int, IStationaryQubit*>&) const override;
};
}  // namespace quisp::rules::active::clauses
