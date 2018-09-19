/** \file Condition.h
 *  \authors cldurand
 *  \date 2018/06/25
 *
 *  \brief Condition
 */
#ifndef QUISP_RULES_CONDITION_H_
#define QUISP_RULES_CONDITION_H_

#include "Clause.h"
#include <omnetpp.h>
#include <memory>

namespace quisp {
namespace rules {

/** \class Condition Condition.h
 *
 *  \brief Condition
 */
class Condition : std::list<pClause> {
    public:
        void addClause(Clause * c) { push_back(pClause(c)); };
        void addClause(pClause& c) { push_back(pClause(std::move(c))); };
        bool check(qnicResources * resources) const;
};
typedef std::unique_ptr<Condition> pCondition;

} // namespace rules
} // namespace quisp

#endif//QUISP_RULES_CONDITION_H_
