#include "RandomMeasureAction.h"
#include <messages/classical_messages.h>
#include <modules/QRSA/RuleEngine/IRuleEngine.h>
#include "base/TransferMessage.cc"

namespace quisp::rules::active::actions {

RandomMeasureAction::RandomMeasureAction(unsigned long ruleset_id, unsigned long rule_id, int owner_address, int partner, QNIC_type qnic_type, int qnic_id, int resource,
                                         int max_count)
    : ActiveAction(ruleset_id, rule_id), partner(partner), qnic_type(qnic_type), qnic_id(qnic_id), resource(resource), src(owner_address), dst(partner), max_count(max_count) {
  current_count = 0;
  start = simTime();
};

cPacket *RandomMeasureAction::run(cModule *re) {
  IStationaryQubit *qubit = nullptr;

  qubit = getResource(resource, partner);

  if (qubit == nullptr) {
    return generateError("Qubit not found for measurement.");
  }

  measurement_outcome o = qubit->measure_density_independent();
  current_count++;

  // Delete measured resource from the tracked list of resources.
  removeResource_fromRule(qubit);
  IRuleEngine *rule_engine = check_and_cast<IRuleEngine *>(re);
  rule_engine->freeConsumedResource(qnic_id, qubit, qnic_type);

  auto pk = base::generateLinkTomographyResult(src, dst, current_count, 4, o.outcome_is_plus, o.basis, o.GOD_clean, max_count, start);
  return pk;
}
}  // namespace quisp::rules::active::actions
