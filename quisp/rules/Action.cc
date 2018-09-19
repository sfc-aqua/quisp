/** \file Action.cc
 *
 *  \authors cldurand
 *  \date 2018/06/25
 *
 *  \brief Action
 */
#include "Action.h"
#include "tools.h"

namespace quisp {
namespace rules {

int SwappingAction::run(qnicResources* resources) {
        stationaryQubit *lqubit = NULL, *rqubit = NULL;
        lqubit = getQubit(resources,
                left_qnic_type, left_qnic_id, left_partner, left_resource);
        rqubit = getQubit(resources,
                right_qnic_type, right_qnic_id, right_partner, right_resource);
        if ((lqubit) && (rqubit)) {
            // do swapping on lqubit and rqubit TODO
            return 0;
        }
        // error
    }

int PurifyAction::run(qnicResources* resources) {
    stationaryQubit *qubit = NULL, *trash_qubit = NULL;
    qubit = getQubit(resources,qnic_type,qnic_id,partner,resource);
    trash_qubit = getQubit(resources,qnic_type,qnic_id,partner,trash_resource);
    if ((qubit) && (trash_qubit)) {
        // do purification where trash_qubit is in the measured pair TODO
        return 0;
    }
    // error
}

int RandomMeasureAction::run(qnicResources* resources) {
    EV<<"Measuring qubit now.";
    return 1000;
    // error
}

} // namespace rules
} // namespace quisp
