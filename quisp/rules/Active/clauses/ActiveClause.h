#pragma once

#include <modules/QNIC.h>
#include <modules/QUBIT.h>
#include <omnetpp.h>
#include <map>

using namespace quisp::modules;

namespace quisp::rules::active::clauses {

class ActiveClause {
 protected:
  int partner; /**< Identifies entanglement partner. */
  QNIC_type qnic_type;
  int qnic_id;
  int resource; /**< Identifies qubit */

 public:
  ActiveClause(){};
  ActiveClause(int partner_addr, int resource) : ActiveClause(partner_addr, QNIC_N, -1, resource){};
  ActiveClause(int partner_addr, QNIC_type qnic_type, int qnic_id) : ActiveClause(partner_addr, qnic_type, qnic_id, 0){};
  ActiveClause(int partner_addr, QNIC_type _qnic_type, int _qnic_id, int _resource) {
    partner = partner_addr;
    qnic_type = _qnic_type;
    qnic_id = _qnic_id;
    resource = _resource;
  };
  virtual ~ActiveClause() {}
  // if the condition is satisfied, return true, otherwise return false.
  virtual bool check(std::multimap<int, IStationaryQubit*>&) = 0;
  virtual bool checkTerminate(std::multimap<int, IStationaryQubit*>&) const = 0;
};

}  // namespace quisp::rules::active::clauses
