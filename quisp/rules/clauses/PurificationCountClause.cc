#include "PurificationCountClause.h"

namespace quisp {
namespace rules {
namespace clauses {
bool PurificationCountClause::check(std::multimap<int, StationaryQubit*> resource) const {
  StationaryQubit* qubit = nullptr;
  // checkQnic();//This is not doing anything...

  /*
  qubit = getQubitPurified(resources, qnic_type, qnic_id, partner, num_purify_must);
  if(qubit != nullptr){
      return true;//There is a qubit that has been purified "num_purify_must" times.
  }else{
      return false;
  }*/
}
}  // namespace clauses
}  // namespace rules
}  // namespace quisp
