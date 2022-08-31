
#pragma once

#include <modules/QNIC.h>
#include <modules/QUBIT.h>
#include <omnetpp.h>
#include <memory>

namespace quisp::rules::active::actions::base {

using namespace quisp::messages;
using quisp::modules::IStationaryQubit;
using quisp::modules::QNIC_type;

class BaseAction {
 public:
  BaseAction(int dst, unsigned long ruleset_id, int rule_id, int shared_tag) : dst(dst), ruleset_id(ruleset_id), rule_id(rule_id), shared_tag(shared_tag){};
  virtual ~BaseAction(){};
  int dst;
  unsigned long ruleset_id;
  int rule_id;
  int shared_tag;
};
}  // namespace quisp::rules::active::actions::base
