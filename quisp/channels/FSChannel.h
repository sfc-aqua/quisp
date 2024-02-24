/** \file FSChannel.h
 *
 *  \brief Freespace channel
 *
 *  Loss model from 10.1038/s42005-022-01123-7.
 *  Base class for Free-space communication: this channel handles variable length and delay using a CSVParser.
 *  LOS-related methods are directly callable from outside since the pointing system is expected to be able to directly check whether there is visibility or not.
 *
 */

#ifndef CHANNELS_FSCHANNEL_H_
#define CHANNELS_FSCHANNEL_H_

#include <omnetpp.h>
#include <stdexcept>
#include "PhotonicQubit_m.h"
#include "omnetpp/cexception.h"
#include <cmath>
#include "CSVParser.h"

using namespace omnetpp;


struct ORBITAL_PARAMETERS {
    SimTime orbit_period = SIMTIME_MAX;
    SimTime vis_start_time = SIMTIME_ZERO;
    SimTime vis_end_time = SIMTIME_MAX;
};

namespace quisp::channels {
class FSChannel : public cDatarateChannel {
public:
    FSChannel();
    virtual void initialize() override;
    void set_orbit_parameters(double orb_period,double orb_vis_start_coeff, double orb_vis_end_coeff);
    virtual void recalculateChannelParameters();
    bool checkLOS();
    double getDistanceAtTime(const simtime_t time);
    virtual SimTime getNext_check_time();
private:
    ORBITAL_PARAMETERS op;
    CSVParser* dist_par;

 protected:
cChannel::Result processMessage(cMessage *msg, const SendOptions &options, simtime_t t) override;
};
};



#endif /* CHANNELS_FSCHANNEL_H_ */
