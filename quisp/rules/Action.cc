#include "Action.h"

namespace quisp::rules {

Purification::Purification(PurType purification_type, int partner_addr, QNIC_type qnic_type, int qnic_id)
    : Action(partner_addr, qnic_type, qnic_id), purification_type(purification_type) {}

EntanglementSwapping::EntanglementSwapping(SwapType swapping_type, int partner_addr, QNIC_type qnic_type, int qnic_id)
    : Action(partner_addr, qnic_type, qnic_id), swapping_type(swapping_type) {}

Wait::Wait(int partner_addr, QNIC_type qnic_type, int qnic_id) : Action(partner_addr, qnic_type, qnic_id) {}

Tomography::Tomography(int num_measurement, int partner_addr, QNIC_type qnic_type, int qnic_id) : Action(partner_addr, qnic_type, qnic_id), num_measurement(num_measurement) {}
}  // namespace quisp::rules