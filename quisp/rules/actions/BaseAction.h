/** \file BaseAction.h
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief Action
 */

#pragma once

#include <modules/QNIC.h>
#include <modules/QUBIT.h>
#include <omnetpp.h>
#include <memory>

namespace quisp {
namespace rules {
namespace actions {

using quisp::modules::QNIC_type;
using quisp::modules::StationaryQubit;

class Action {
 public:
  virtual ~Action(){};
  std::multimap<int, StationaryQubit*>* rule_resources;
  unsigned long ruleset_id;
  int rule_id;  // Used to make the lock_id unique, together with purification_count.
  // int resource_index = 0;// for check the index of resource.
  // virtual cPacket* run(cModule *re, qnicResources *resources) = 0;
  virtual cPacket* run(cModule* re) = 0;
  virtual StationaryQubit* getResource_fromTop(int required_index);
  virtual StationaryQubit* getResource_fromTop_with_partner(int required_index, int partner);
  virtual int checkNumResource();
  virtual void removeResource_fromRule(StationaryQubit* qubit);
  // virtual StationaryQubit* getQubit(qnicResources* resources, QNIC_type qtype, int qid, int partner, int res_id);
};
typedef std::unique_ptr<Action> pAction;

}  // namespace actions
}  // namespace rules
}  // namespace quisp
