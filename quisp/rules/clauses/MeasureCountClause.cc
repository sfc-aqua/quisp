#include "MeasureCountClause.h"

namespace quisp {
namespace rules {
namespace clauses {
bool MeasureCountClause::check(std::multimap<int, StationaryQubit*> resources) const {
  if (current_count < max_count) {
    current_count++;  // Increment measured counter.
    // std::cout<<"Measurement count is now "<<current_count<<" < "<<max_count<<"\n";
    return true;
  } else {
    // std::cout<<"Count is enough\n";
    return false;
  }
}

bool MeasureCountClause::checkTerminate(std::multimap<int, StationaryQubit*> resources) const {
  bool done = false;
  if (current_count >= max_count) {
    // EV<<"TRUE: Current count = "<<current_count<<" >=  "<<max_count<<"(max)\n";
    done = true;
  }
  return done;
}

}  // namespace clauses
}  // namespace rules
}  // namespace quisp
