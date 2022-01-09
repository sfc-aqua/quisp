#include "PurificationCountClause.h"

namespace quisp::rules::active::clauses {
bool PurificationCountClause::check(std::multimap<int, IStationaryQubit *> &resource) {
  throw omnetpp::cRuntimeError("PurificationCountClause class has not been implemented yet");
}
}  // namespace quisp::rules::active::clauses