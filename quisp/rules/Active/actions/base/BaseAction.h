
#pragma once

#include <modules/QNIC.h>
#include <modules/QUBIT.h>
#include <omnetpp.h>
#include <memory>

namespace quisp::rules::active::actions::base {

using quisp::modules::IStationaryQubit;
using quisp::modules::QNIC_type;

class BaseAction {
 public:
  BaseAction();
  virtual ~BaseAction(){};
  virtual void run() = 0;
  virtual void generateError() = 0;
};
}  // namespace quisp::rules::active::actions::base
