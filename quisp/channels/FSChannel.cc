/** \file QuantumChannel.cc
 *
 *  \brief QuantumChannel
 */
#include <omnetpp.h>
#include "FSChannel.h"

using namespace omnetpp;
namespace quisp::channels {


FSChannel::FSChannel() {};

void FSChannel::initialize() {
  cDatarateChannel::initialize();
}


Define_Channel(FSChannel);

cChannel::Result FSChannel::processMessage(cMessage *msg, const SendOptions &options, simtime_t t) {
    return {!getLOS(), getDelay(), 0};
}

void FSChannel::setLOS(bool LOS) {
    line_of_sight = LOS;
}

void FSChannel::toggleLOS() {
    line_of_sight = !line_of_sight;
}

bool FSChannel::getLOS() {
    return line_of_sight;
}


}





