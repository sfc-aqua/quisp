#include "WaitClause.h"

namespace quisp::rules::active::clauses {
// This never gets true.
bool WaitClause::check(std::multimap<int, IStationaryQubit *> &resource) { return false; };
}  // namespace quisp::rules::active::clauses
