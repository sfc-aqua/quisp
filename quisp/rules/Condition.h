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

namespace quisp {
namespace rules {

/** \class Condition Condition.h
 *
 *  \brief Condition
 */
class Condition {
    private:
        std::list<Clause*> clauses;

    public:
        int check() const;
};

} // namespace rules
} // namespace quisp

#endif//QUISP_RULES_CONDITION_H_
