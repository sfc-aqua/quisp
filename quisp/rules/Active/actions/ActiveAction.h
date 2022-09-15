/** \file ActiveAction.h
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

namespace quisp::modules {
class RuleEngine;
}
namespace quisp::rules::active::actions {

using quisp::modules::IStationaryQubit;
using quisp::modules::QNIC_type;

class ActiveAction {
 public:
  ActiveAction(unsigned long ruleset_id, int rule_id);
  ActiveAction(unsigned long ruleset_id, int rule_id, int shared_tag);
  virtual ~ActiveAction(){};
  std::multimap<int, IStationaryQubit*>* rule_resources;
  unsigned long ruleset_id;
  int rule_id;  // Used to make the lock_id unique, together with purification_count.
  int shared_tag;
  virtual cPacket* run(quisp::modules::RuleEngine* re) = 0;
  virtual IStationaryQubit* getResource(int required_index, int partner);
  virtual void removeResource_fromRule(IStationaryQubit* qubit);
  cPacket* generateError(const char* msg);
};
}  // namespace quisp::rules::active::actions
