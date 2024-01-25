/** \file QuantumChannel.cc
 *
 *  \brief QuantumChannel
 */
#include "FiberChannel.h"

using namespace omnetpp;

namespace quisp::channels {



FiberChannel::FiberChannel() {}

void FiberChannel::initialize() {
    cDatarateChannel::initialize();
}

cChannel::Result FiberChannel::processMessage(cMessage *msg, const SendOptions &options, simtime_t t) {
  return {false, getDelay(), calculateDuration(msg)};
}


}  // namespace quisp::channels
