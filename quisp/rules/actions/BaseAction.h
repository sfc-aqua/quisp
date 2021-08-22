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

using quisp::modules::IStationaryQubit;
using quisp::modules::QNIC_type;

class Action {
 public:
  virtual ~Action(){};
  std::multimap<int, IStationaryQubit*>* rule_resources;
  unsigned long ruleset_id;
  unsigned long rule_id;  // Used to make the lock_id unique, together with purification_count.
  // int resource_index = 0;// for check the index of resource.
  // virtual cPacket* run(cModule *re, qnicResources *resources) = 0;
  virtual cPacket* run(cModule* re) = 0;
  virtual IStationaryQubit* getResource_fromTop(int required_index);
  virtual IStationaryQubit* getResource(int required_index, int partner);
  virtual int checkNumResource();
  virtual void removeResource_fromRule(IStationaryQubit* qubit);
  // virtual StationaryQubit* getQubit(qnicResources* resources, QNIC_type qtype, int qid, int partner, int res_id);
};
}  // namespace actions
}  // namespace rules
}  // namespace quisp
