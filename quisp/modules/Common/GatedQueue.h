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
#include "modules/Logger/LoggerBase.h"
#include "utils/ComponentProvider.h"

using namespace omnetpp;
using namespace quisp::messages;

namespace quisp::modules {

class GatedQueue : public Queue, public Logger::LoggerBase
{
  public:
    GatedQueue();
    ~GatedQueue() {}
  protected:
    simtime_t next_check_time = 0;
    virtual void handleMessage(cMessage *msg) override;
    void initialize() override;
    utils::ComponentProvider provider;
//Logger::ILogger* logger = provider.getLogger();
  private:
    bool pending_vcr = false;
};

Define_Module(GatedQueue);


} //namespace

#endif
