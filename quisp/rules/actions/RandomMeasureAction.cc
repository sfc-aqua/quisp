#include "RandomMeasureAction.h"
#include <messages/classical_messages.h>
#include <modules/QRSA/RuleEngine/IRuleEngine.h>

namespace quisp {
namespace rules {
namespace actions {

RandomMeasureAction::RandomMeasureAction(int part, QNIC_type qt, int qi, int res, int srcAddr, int max) {
  partner = part;
  dst = part;
  qnic_type = qt;
  qnic_id = qi;
  resource = res;
  src = srcAddr;
  current_count = 0;
  max_count = max;
  start = simTime();
};

cPacket *RandomMeasureAction::run(cModule *re) {
  IStationaryQubit *qubit = nullptr;

  qubit = getResource_fromTop_with_partner(resource, partner);

  if (qubit == nullptr) {
    Error *pk = new Error;
    pk->setError_text("Qubit not found for measurement.");
    return pk;
  } else {
    measurement_outcome o = qubit->measure_density_independent();
    current_count++;

    // Delete measured resource from the tracked list of resources.
    removeResource_fromRule(qubit);  // Remove from resource list in this Rule.
    IRuleEngine *rule_engine = check_and_cast<IRuleEngine *>(re);
    rule_engine->freeConsumedResource(qnic_id, qubit, qnic_type);  // Remove from entangled resource list.
    // Deleting done

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
}
}  // namespace actions
}  // namespace rules
}  // namespace quisp
