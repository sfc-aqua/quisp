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

namespace quisp::rules::actions {

using quisp::modules::IStationaryQubit;
using quisp::modules::QNIC_type;

class ActiveAction {
 public:
  ActiveAction(unsigned long ruleset_id, unsigned long rule_id);
  virtual ~ActiveAction(){};
  std::multimap<int, IStationaryQubit*>* rule_resources;
  unsigned long ruleset_id;
  unsigned long rule_id;  // Used to make the lock_id unique, together with purification_count.
  virtual cPacket* run(cModule* re) = 0;
  virtual IStationaryQubit* getResource(int required_index, int partner);
  virtual void removeResource_fromRule(IStationaryQubit* qubit);
  cPacket* generateError(const char* msg);
};
}  // namespace quisp::rules::actions
