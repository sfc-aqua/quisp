/** \file Clause.h
 *  \authors cldurand
 *  \date 2018/07/03
 *
 *  \brief Clause
 */
#ifndef QUISP_RULES_CLAUSE_H_
#define QUISP_RULES_CLAUSE_H_

#include <omnetpp.h>
#include <modules/QNIC.h>

using namespace quisp::modules;

namespace quisp {
namespace rules {

/** \class Clause Clause.h
 *
 *  \brief Clause
 */
class Clause {
    protected:
        int partner; /**< Identifies entanglement partner. */
        QNIC_type qnic_type;
        int qnic_id;
        int resource; /**< Identifies qubit */

    public:
        Clause(int partner, int resource) : Clause(partner, QNIC_N, -1, resource) {};
        Clause(int part, QNIC_type qt, int qi, int res) {
            partner = part;
            qnic_type = qt;
            qnic_id = qi;
            resource = res;
        };
        virtual int check() const = 0;
};

class FidelityClause : public Clause {
    protected:
        double threshold;

    public:
        FidelityClause(int partner, int resource, double fidelity) : Clause(partner, resource) {
            threshold = fidelity;
        };
        int check() const override;
};

class XErrClause : public Clause {};

} // namespace rules
} // namespace quisp

#endif//QUISP_RULES_CLAUSE_H_
