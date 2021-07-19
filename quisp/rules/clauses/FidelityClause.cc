#include "FidelityClause.h"
#include "omnetpp/cexception.h"

namespace quisp {
namespace rules {
namespace clauses {
[[noreturn]] bool FidelityClause::check(std::multimap<int, StationaryQubit*> resource) const {
  StationaryQubit* qubit = nullptr;
  throw omnetpp::cRuntimeError("FidelityClause class has not implemented yet");
  /*checkQnic();//This is not doing anything...
  if(qubit = getQubit(resources, qnic_type, qnic_id, partner, resource)){
      return (qubit->getFidelity() >= threshold);
  }
  return false;*/
}

bool FidelityClause::checkTerminate(std::multimap<int, StationaryQubit*>) const { return false; };
}  // namespace clauses
}  // namespace rules
}  // namespace quisp
