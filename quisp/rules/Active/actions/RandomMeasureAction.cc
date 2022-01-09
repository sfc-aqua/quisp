#include "RandomMeasureAction.h"
#include <messages/classical_messages.h>
#include <modules/QRSA/RuleEngine/IRuleEngine.h>

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

  LinkTomographyResult *pk = new LinkTomographyResult;
  pk->setSrcAddr(src);
  pk->setDestAddr(dst);
  pk->setCount_id(current_count);
  pk->setPartner_address(src);  // Partner's partner is self/src
  pk->setKind(6);
  pk->setOutput_is_plus(o.outcome_is_plus);
  pk->setBasis(o.basis);
  pk->setGOD_clean(o.GOD_clean);
  if (current_count == max_count) {
    pk->setFinish(simTime() - start);
    pk->setMax_count(max_count);
  }
  return pk;
}
}  // namespace quisp::rules::active::actions
