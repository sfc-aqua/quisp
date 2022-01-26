#include "Clause.h"

namespace quisp::rules {
EnoughResourceConditionClause::EnoughResourceConditionClause(int num_resource, double required_fidelity, int partner_addr, QNIC_type qnic_type, int qnic_id)
    : Clause(partner_address, qnic_type, qnic_id), num_resource(num_resource), required_fidelity(required_fidelity) {}

MeasureCountConditionClause::MeasureCountConditionClause(int num_measurement, int partner_addr, QNIC_type qnic_type, int qnic_id) : Clause(partner_addr, qnic_type, qnic_id) {}

FidelityConditionClause::FidelityConditionClause(double required_fidelity, int partner_addr, QNIC_type qnic_type, int qnic_id) : Clause(partner_addr, qnic_type, qnic_id) {}

WaitConditionClause::WaitConditionClause(int partner_addr, QNIC_type qnic_type, int qnic_id) : Clause(partner_addr, qnic_type, qnic_id) {}

}  // namespace quisp::rules