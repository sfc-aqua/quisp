/** \file PhotonicSwitch.h
 *  \authors cldurand,takaakimatsuo
 *
 *  \brief PhotonicSwitch
 */

#ifndef MODULES_PHOTONICSWITCH_H_
#define MODULES_PHOTONICSWITCH_H_

#include <PhotonicQubit_m.h>
#include <messages/classical_messages.h>
#include <omnetpp.h>
#include <vector>

using namespace omnetpp;

namespace quisp {
namespace modules {

/** \class PhotonicSwitch PhotonicSwitch.cc
 *
 *  \brief PhotonicSwitch
 */
class PhotonicSwitch : public cSimpleModule {
 private:
  int my_address;
  bool is_busy;  // Already requested a path selection for a Quantum app

 protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage *msg) override;
  virtual void ensureCorrespondingNeighborAddress();
  virtual cModule *getQNode();
  void reserve();
  void release();
  bool isReserved();
  int getAddress();
};

Define_Module(PhotonicSwitch);
}  // namespace modules
}  // namespace quisp

#endif  // MODULES_PHOTONICSWITCH_H_
