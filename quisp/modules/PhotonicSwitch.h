/** \file PhotonicSwitch.h
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *
 *  \brief PhotonicSwitch
 */

#ifndef MODULES_PHOTONICSWITCH_H_
#define MODULES_PHOTONICSWITCH_H_

#include <PhotonicQubit_m.h>
#include <classical_messages_m.h>
#include <omnetpp.h>
#include <vector>

using namespace omnetpp;

namespace quisp {
namespace modules {

/** \class PhotonicSwitch PhotonicSwitch.cc
 *  \todo Documentation of the class header.
 *
 *  \brief PhotonicSwitch
 */
class PhotonicSwitch : public cSimpleModule {
 private:
  int myAddress;
  cMessage *generatePacket;  // Not the actual packet. Local message to invoke Events
  cPar *sendIATime;
  bool isBusy;  // Already requested a path selection for a Quantum app
 protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage *msg) override;
  virtual void BubbleText(const char *txt);
  virtual void checkGateNumber();
  virtual void checkQubitNumber();
  virtual void checkAndsetNeighborAddress();
  virtual cModule *getQNode();

 public:
  PhotonicSwitch();
  int getAddress();
  virtual void Reserve();
  virtual void ReleaseReservation();
  virtual bool isReserved();
};
}  // namespace modules
}  // namespace quisp

Define_Module(PhotonicSwitch);

#endif MODULES_PHOTONICSWITCH_H_
