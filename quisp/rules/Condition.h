/** \file Condition.h
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief Condition
 */
#ifndef QUISP_RULES_CONDITION_H_
#define QUISP_RULES_CONDITION_H_

#include <omnetpp.h>
#include <memory>
#include "Clause.h"

namespace quisp {
namespace rules {

/** \class Condition Condition.h
 *
 *  \brief Condition
 */
class Condition {
 public:
  void addClause(Clause* c);
  bool check(std::multimap<int, StationaryQubit*> resources) const;
  bool checkTerminate(std::multimap<int, StationaryQubit*> resources) const;

 protected:
  std::vector<Clause*> clauses;
};

}  // namespace rules
}  // namespace quisp

#endif  // QUISP_RULES_CONDITION_H_
