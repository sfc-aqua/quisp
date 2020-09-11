/** \file RuleSet.cc
 *
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief RuleSet
 */
#include "RuleSet.h"

namespace quisp {
namespace rules {

void RuleSet::finalize() {
  for (auto rule = this->cbegin(), end = this->cend(); rule != end; rule++) {
  }
}

}  // namespace rules
}  // namespace quisp
