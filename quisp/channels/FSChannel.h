/*
 * FSChannel.h
 *
 *  Created on: Sep 6, 2023
 *      Author: paolo
 */

#ifndef CHANNELS_FSCHANNEL_H_
#define CHANNELS_FSCHANNEL_H_

#include <omnetpp.h>
#include<messages/gatedqueue_messages_m.h>

using namespace omnetpp;
using namespace quisp::messages;

namespace quisp::channels {
class FSChannel : public cDatarateChannel {
 public:
    FSChannel();
    void setLOS(bool line_of_sight);
    void toggleLOS();
    bool getLOS();


 protected:
  cChannel::Result processMessage(cMessage *msg, const SendOptions &options, simtime_t t) override;

 private:
    bool line_of_sight;
};
};



#endif /* CHANNELS_FSCHANNEL_H_ */
