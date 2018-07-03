/** \file Clause.h
 *  \authors cldurand
 *  \date 2018/07/03
 *
 *  \brief Clause
 */
#ifndef QUISP_RULES_CLAUSE_H_
#define QUISP_RULES_CLAUSE_H_

#include <omnetpp.h>

namespace quisp {
namespace rules {

/** \class Clause Clause.h
 *
 *  \brief Clause
 */
class Clause {
    protected:
        int target; /**< Identifies qubit */

    public:
        Clause(int t) { target = t; };
        virtual int check() = 0;
};

class FidelityClause : public Clause {
    public:
        FidelityClause(int t) : Clause(t) {};
        int check() override;
};

class XErrClause : public Clause {};

} // namespace rules
} // namespace quisp

#endif//QUISP_RULES_CLAUSE_H_
