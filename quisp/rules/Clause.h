/** \file Clause.h
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/07/03
 *
 *  \brief Clause
 */
#ifndef QUISP_RULES_CLAUSE_H_
#define QUISP_RULES_CLAUSE_H_

#include <omnetpp.h>
#include <modules/QNIC.h>
#include <modules/QUBIT.h>
#include <memory>

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
        Clause() {};
        Clause(int partner, int resource) : Clause(partner, QNIC_N, -1, resource) {};
        Clause(int part, QNIC_type qt, int qi, int res) {
            partner = part;
            qnic_type = qt;
            qnic_id = qi;
            resource = res;
        };
        Clause(int part, QNIC_type qt, int qi) {
                    partner = part;
                    qnic_type = qt;
                    qnic_id = qi;
        };
        void setQnic(QNIC_type qt, int qi) {
            //if (qt >= QNIC_N) omnetpp::error("Not that many QNIC types.");
            //if (qi < 0) omnetpp::error("Negative qnic index.");
            qnic_type = qt;
            qnic_id = qi;
        };
        void checkQnic() const {
            //if (qnic_type >= QNIC_N) omnetpp::error("Not that many QNIC types.");
            //if (qnic_id < 0) omnetpp::error("Negative qnic index.");
        };
        virtual bool check(qnicResources *resources) const = 0;
        virtual bool check(std::map<int,stationaryQubit*>) const = 0;
        virtual bool checkTerminate(qnicResources *resources) const = 0;
        virtual bool checkTerminate(std::map<int,stationaryQubit*>) const = 0;
        //virtual stationaryQubit* getQubit(qnicResources* resources, QNIC_type qtype, int qid, int partner, int res_id) const = 0;
};

typedef std::unique_ptr<Clause> pClause;

class FidelityClause : public Clause {
    protected:
        double threshold;

    public:
        FidelityClause(int partner, int resource, double fidelity) : Clause(partner, resource) {
            threshold = fidelity;
        };
        FidelityClause(int part, QNIC_type qt, int qi, int res, double fidelity)
        : Clause(part, qt, qi, res) {
            threshold = fidelity;
        };
        bool check(qnicResources *resources) const override;
        bool checkTerminate(qnicResources *resources) const override {return 0;} ;
        bool check(std::map<int,stationaryQubit*>) const override;
        bool checkTerminate(std::map<int,stationaryQubit*>) const override {return 0;};
};



class NoClause : public Clause {


    public:
        NoClause() : Clause() {

        };
        bool check(qnicResources *resources) const override {return true;};
        bool checkTerminate(qnicResources *resources) const override {return false;} ;
        bool check(std::map<int,stationaryQubit*>) const override {return true;};
        bool checkTerminate(std::map<int,stationaryQubit*>) const override {return false;};
};


class MeasureCountClause : public Clause {
    public:
        int max_count;
        int mutable current_count;
        MeasureCountClause(int max, int part, QNIC_type qt, int qi, int res) : Clause(part, qt, qi, res) {//May not need this
            max_count = max;
            current_count = 0;
        };
        MeasureCountClause(int max) : Clause() {
            max_count = max;
            current_count = 0;
         };
        bool check(qnicResources *resources) const override;
        bool checkTerminate(qnicResources *resources) const override;
        bool check(std::map<int,stationaryQubit*>) const override;
        bool checkTerminate(std::map<int,stationaryQubit*>) const override;
        //void increment(){current_count++;};
};

class PurificationCountClause : public Clause {
    public:
        int num_purify_must;
        //int mutable current_count;
        PurificationCountClause(int part, QNIC_type qt, int qi, int n_purify) : Clause(part, qt, qi) {//May not need this
            //max_count = max;
            //current_count = 0;
            num_purify_must = n_purify;
        };

        bool check(qnicResources *resources) const override;
        bool checkTerminate(qnicResources *resources) const override;
        bool check(std::map<int,stationaryQubit*>) const override;
        //void increment(){current_count++;};
};


class XErrClause : public Clause {};

} // namespace rules
} // namespace quisp

#endif//QUISP_RULES_CLAUSE_H_
