#ifndef __QUISP_GATEDQUEUE_H_
#define __QUISP_GATEDQUEUE_H_

#include <omnetpp.h>
#include "Queue.h"

using namespace omnetpp;

class GatedQueue : public Queue
{
  protected:
    virtual void handleMessage(cMessage *msg) override;
    void initialize() override;
    void setGate_open(const bool ctrl_signal);
  private:
    bool gate_open = false;
    cMessage* visibility_established;

};


#endif
