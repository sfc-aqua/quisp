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
#include "messages/link_generation_messages_m.h"
#include "messages/ospf_messages_m.h"
#include "messages/visibility_messages_m.h"
#include "utils/ComponentProvider.h"

using namespace omnetpp;
using namespace quisp::messages;

namespace quisp::modules {

class GatedQueue : public Queue {
 public:
  GatedQueue();
  ~GatedQueue();

 protected:
  simtime_t next_check_time = 0;
  simtime_t last_polling_time = -1;
  virtual void handleMessage(cMessage *msg) override;
  utils::ComponentProvider provider;

 private:
  bool pending_vcr = false;
};

Define_Module(GatedQueue);

}  // namespace quisp::modules

#endif
