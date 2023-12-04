/** \file FSChannel.h
 *
 *  \brief Freespace channel
 *
 *  Loss model from 10.1038/s42005-022-01123-7.
 *  ORBITAL_PARAMETERS are to be set on init by one of the connected modules.
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
    void initialize() override;
    void set_orbit_parameters(double orb_period,double orb_vis_start_coeff, double orb_vis_end_coeff);
    virtual void recalculateChannelParameters();
    bool checkLOS();
    SimTime getNext_check_time();
private:
    ORBITAL_PARAMETERS op;
    CSVParser* dist_par;

 protected:
cChannel::Result processMessage(cMessage *msg, const SendOptions &options, simtime_t t) override;
};
};



#endif /* CHANNELS_FSCHANNEL_H_ */
