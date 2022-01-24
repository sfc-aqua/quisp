#include "Clause.h"

namespace quisp::rules {
EnoughResourceConditionClause::EnoughResourceConditionClause(int num_resource, int partner_address, double required_fidelity)
    : num_resource(num_resource), partner_addr(partner_address), required_fidelity(required_fidelity) {}
}  // namespace quisp::rules