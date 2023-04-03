/** \file PhotonicSwitch.h
 *  \authors cldurand,takaakimatsuo
 *
 *  \brief PhotonicSwitch
 */

#pragma once
#include <omnetpp.h>

using namespace omnetpp;

namespace quisp::modules {

/** \class PhotonicSwitch PhotonicSwitch.cc
 *
 *  \brief PhotonicSwitch
 */
class PhotonicSwitch : public cSimpleModule {
 protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage *msg) override;
};

Define_Module(PhotonicSwitch);
}  // namespace quisp::modules
