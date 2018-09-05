/** \file Action.h
 *  \authors cldurand
 *  \date 2018/06/25
 *
 *  \brief Action
 */
#ifndef QUISP_RULES_ACTION_H_
#define QUISP_RULES_ACTION_H_

#include <omnetpp.h>
#include <modules/QNIC.h>
#include <modules/QUBIT.h>

using namespace quisp::modules;

namespace quisp {
namespace rules {

/** \class Action Action.h
 *
 *  \brief Action
 */
class Action {
  public:
    virtual void run(qnicResources *resources) = 0;
};

class SwappingAction : public Action {
    protected:
        // First partner
        int left_partner;
        QNIC_type left_qnic_type;
        int left_qnic_id;
        int left_resource;
        // Second partner
        int right_partner;
        QNIC_type right_qnic_type;
        int right_qnic_id;
        int right_resource;

    public:
        SwappingAction(
                int lp, QNIC_type lqt, int lqi, int lr,
                int rp, QNIC_type rqt, int rqi, int rr
                ) {
            left_partner = lp;
            left_qnic_type = lqt;
            left_qnic_id = lqi;
            left_resource = lr;
            right_partner = rp;
            right_qnic_type = rqt;
            right_qnic_id = rqi;
            right_resource = rr;
        };

        void run(qnicResources *resources) override;
};

class PurifyAction : public Action {
    protected:
        int partner; /**< Identifies entanglement partner. */
        QNIC_type qnic_type;
        int qnic_id;
        int resource; /**< Identifies qubit */
        int trash_resource;

    public:
        PurifyAction(int part, QNIC_type qt, int qi, int res, int tres) {
            partner = part;
            qnic_type = qt;
            qnic_id = qi;
            resource = res;
            trash_resource = tres;
        };

        void run(qnicResources *resources) override;
};

} // namespace rules
} // namespace quisp

#endif//QUISP_RULES_ACTION_H_
