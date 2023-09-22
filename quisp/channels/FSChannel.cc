/** \file QuantumChannel.cc
 *
 *  \brief QuantumChannel
 */
#include "FSChannel.h"

using namespace omnetpp;
namespace quisp::channels {


FSChannel::FSChannel() {};


Define_Channel(FSChannel);

cChannel::Result FSChannel::processMessage(cMessage *msg, const SendOptions &options, simtime_t t) {
    return {!getLOS(), getDelay()};
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





