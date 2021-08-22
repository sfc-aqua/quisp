#include "WaitClause.h"

namespace quisp {
namespace rules {
namespace clauses {
// This never gets true.
bool WaitClause::check(std::multimap<int, IStationaryQubit*> resource) { return false; };
}  // namespace clauses
}  // namespace rules
}  // namespace quisp
