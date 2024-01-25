/*
 * Queue.h
 *
 *  Created on: Sep 17, 2020
 *      Author: zigen
 */

#ifndef MODULES_QUEUE_H_
#define MODULES_QUEUE_H_

#include <omnetpp.h>
#include <stdio.h>
#include <string.h>

using namespace omnetpp;


class Queue : public cSimpleModule {
 protected:
  long frame_capacity;
  cQueue queue;
  cMessage *end_transmission_event;
  bool is_busy;

  simsignal_t qlen_signal;
  simsignal_t busy_signal;
  simsignal_t queuing_time_signal;
  simsignal_t drop_signal;
  simsignal_t tx_bytes_signal;
  simsignal_t rx_bytes_signal;
  virtual void initialize() override;
  virtual void finish() override;
  virtual void handleMessage(cMessage *msg) override;
  virtual void refreshDisplay() const override;
  virtual void startTransmitting(cMessage *msg);
};

Define_Module(Queue);
#endif /* MODULES_QUEUE_H_ */
