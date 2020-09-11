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
class Condition : std::list<pClause> {
 public:
  void addClause(Clause* c) { push_back(pClause(c)); };
  void addClause(pClause& c) { push_back(pClause(std::move(c))); };
  // bool check(qnicResources * resources) const;
  bool check(std::multimap<int, StationaryQubit*> resources) const;
  // bool checkTerminate(qnicResources * resources) const;
  bool checkTerminate(std::multimap<int, StationaryQubit*> resources) const;
};
typedef std::unique_ptr<Condition> pCondition;

}  // namespace rules
}  // namespace quisp

#endif  // QUISP_RULES_CONDITION_H_
