#include "MeasureCountClause.h"

namespace quisp {
namespace rules {
namespace clauses {
bool MeasureCountClause::check(std::multimap<int, StationaryQubit*> resources) {
  if (current_count < max_count) {
    current_count++;
    return true;
  }
  return false;
}

bool MeasureCountClause::checkTerminate(std::multimap<int, StationaryQubit*> resources) const {
  bool done = false;
  if (current_count >= max_count) {
    done = true;
  }
  return done;
}

}  // namespace clauses
}  // namespace rules
}  // namespace quisp
