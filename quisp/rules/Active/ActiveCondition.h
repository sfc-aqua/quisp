/** \file Condition.h
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief Condition
 */
#ifndef QUISP_RULES_CONDITION_H_
#define QUISP_RULES_CONDITION_H_

#include "ActiveClause.h"

namespace quisp {
namespace rules {

/** \class Condition Condition.h
 *
 *  \brief Condition
 */
class ActiveCondition {
 public:
  void addClause(ActiveClause* c);
  bool check(std::multimap<int, IStationaryQubit*>& resources) const;
  bool checkTerminate(std::multimap<int, IStationaryQubit*>& resources) const;

  std::vector<ActiveClause*> clauses;
};

}  // namespace rules
}  // namespace quisp

#endif  // QUISP_RULES_CONDITION_H_
