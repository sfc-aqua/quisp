/**
* \file GatedQueue.h
*
* \brief Queue, modified to query the pointing system before sending messages to the outside.
*
*/

#ifndef __QUISP_GATEDQUEUE_H_
#define __QUISP_GATEDQUEUE_H_

#include <omnetpp.h>
#include "Queue.h"
#include "messages/visibility_messages_m.h"
#include "messages/link_generation_messages_m.h"

using namespace omnetpp;
using namespace quisp::messages;

namespace quisp::modules {

class GatedQueue : public Queue
{
  protected:
    simtime_t next_check_time = 0;
    simtime_t last_polling_time = -1;
    virtual void handleMessage(cMessage *msg) override;
    void initialize() override;
    void startTransmitting(cMessage *msg) override;
  private:
    bool pending_vcr = false;
};

} //namespace

#endif
