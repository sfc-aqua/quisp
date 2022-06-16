#include "MeasureCountClause.h"

namespace quisp::rules::active::clauses {
bool MeasureCountClause::check(std::multimap<int, IStationaryQubit *> &resources) {
  if (current_count < max_count) {
    current_count++;
    return true;
  }
  return false;
}

bool MeasureCountClause::checkTerminate(std::multimap<int, IStationaryQubit *> &resources) const {
  bool done = false;
  if (current_count >= max_count) {
    done = true;
  }
  return done;
}

}  // namespace quisp::rules::active::clauses
