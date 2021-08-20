#include "FidelityClause.h"
#include "omnetpp/cexception.h"

namespace quisp {
namespace rules {
namespace clauses {
[[noreturn]] bool FidelityClause::check(std::multimap<int, IStationaryQubit*> resource) { throw omnetpp::cRuntimeError("FidelityClause class has not been implemented yet"); }

bool FidelityClause::checkTerminate(std::multimap<int, IStationaryQubit*>) const {
  return false;
};
}  // namespace clauses
}  // namespace rules
}  // namespace quisp
