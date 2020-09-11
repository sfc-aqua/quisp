/** \file Condition.cc
 *
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief Condition
 */
#include "Condition.h"
#include <memory>

namespace quisp {
namespace rules {

/*
bool Condition::check(qnicResources *resources) const {
    EV<<"In condition...\n";
    bool satisfying = true;
    for (auto clause = cbegin(), end = cend(); clause != end; clause++){
        if (!(*clause)->check(resources)){
            satisfying = false;
            break;
        }
    }
    return satisfying;
}
*/

bool Condition::check(std::multimap<int, StationaryQubit*> resources) const {
  EV << "In condition...\n";
  bool satisfying = true;
  for (auto clause = cbegin(), end = cend(); clause != end; clause++) {
    if (!(*clause)->check(resources)) {
      satisfying = false;
      break;
    }
  }
  // std::cout<<"satisfying? = "<<satisfying<<" false = "<<false<<" true = "<<true<<"\n";
  return satisfying;
}

/*
bool Condition::checkTerminate(qnicResources *resources) const {
    bool satisfying = true;
    for (auto clause = cbegin(), end = cend(); clause != end; clause++){
        if (!(*clause)->checkTerminate(resources)){
            satisfying = false;
            break;
        }
    }
    return satisfying;
}*/

bool Condition::checkTerminate(std::multimap<int, StationaryQubit*> resources) const {
  bool satisfying = false;
  for (auto clause = cbegin(), end = cend(); clause != end; clause++) {
    if ((*clause)->checkTerminate(resources)) {
      satisfying = true;
      break;
    }
  }
  return satisfying;
}

}  // namespace rules
}  // namespace quisp
