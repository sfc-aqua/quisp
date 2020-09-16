/*
 * Queue.h
 *
 *  Created on: Sep 17, 2020
 *      Author: zigen
 */

#ifndef MODULES_QUEUE_H_
#define MODULES_QUEUE_H_

#include <PhotonicQubit_m.h>
#include <classical_messages_m.h>
#include <omnetpp.h>
#include <stdio.h>
#include <string.h>

using namespace omnetpp;

namespace quisp {
namespace modules {

/** \class Queue Queue.cc
 *  \todo Documentation of the class header.
 *
 *  \brief Queue
 */
class Queue : public cSimpleModule {
 private:
  long frameCapacity;
  cQueue queue;
  cMessage *endTransmissionEvent;
  bool isBusy;

  simsignal_t qlenSignal;
  simsignal_t busySignal;
  simsignal_t queueingTimeSignal;
  simsignal_t dropSignal;
  simsignal_t txBytesSignal;
  simsignal_t rxBytesSignal;

 public:
  Queue();

 protected:
  virtual void initialize() override;
  virtual void finish() override;
  virtual void handleMessage(cMessage *msg) override;
  virtual void refreshDisplay() const override;
  virtual void startTransmitting(cMessage *msg);
};

Define_Module(Queue);
}  // namespace modules
}  // namespace quisp
#endif /* MODULES_QUEUE_H_ */
