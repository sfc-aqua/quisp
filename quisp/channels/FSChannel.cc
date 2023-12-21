/** \file FSChannel.cc
 *
 *  \brief Freespace channel
 *
 *  Loss model from 10.1038/s42005-022-01123-7.
 *  ORBITAL_PARAMETERS are to be set on init by one of the connected modules. LOS = Line Of Sight.
 *  LOS-related methods are directly callable from outside since the pointing system is expected to be able to directly check whether there is visibility or not.
 *
 */

#include "FSChannel.h"

using namespace omnetpp;
namespace quisp::channels {


FSChannel::FSChannel() {};


Define_Channel(FSChannel);

void FSChannel::initialize() {
    cDatarateChannel::initialize();
    const char* filename = par("distance_CSV").stringValue();
    dist_par = new CSVParser(filename);
    op.orbit_period = par("orbital_period");
    op.vis_start_time = dist_par->getLowestDatapoint();
    op.vis_end_time = dist_par->getHighestDatapoint();
}

cChannel::Result FSChannel::processMessage(cMessage *msg, const SendOptions &options, simtime_t t) {
    Result result;

    if (!checkLOS()) {
        result.discard = true;
    } else {
    recalculateChannelParameters();
    result = cDatarateChannel::processMessage(msg, options, t);
    }
    return result;
}

/** \fn checkLOS()
 *
 *  \brief Check if one end of the channel can see the other, i.e. we can send msg
 *
 *
 */

bool FSChannel::checkLOS() {
    Enter_Method("checkLOS()");
    const SimTime currentTime = fmod(simTime(),op.orbit_period);
    if (currentTime >= op.vis_start_time and currentTime <= op.vis_end_time) {
        return true;
    }
    return false;
}

double FSChannel::getDistanceAtTime(const simtime_t time) {
    return dist_par->getPropertyAtTime(time.dbl());
}

/** \fn set_orbit_parameters(double orb_period,double orb_vis_start_coeff, double orb_vis_end_coeff)
 *
 *  \brief Set visibility parameters: period in s, 0<=orb_vis_start_coeff<=orb_vis_end_coeff<=1, the two coeffs represent fractions of orb_period
 *
 *
 */

//void FSChannel::set_orbit_parameters(double orb_period,double orb_vis_start_coeff, double orb_vis_end_coeff) {
//    Enter_Method("set_orbit_parameters()");
//    op.orbit_period = SimTime(orb_period);
//    op.vis_start_time = SimTime(orb_vis_start_coeff*orb_period);
//    op.vis_end_time = SimTime(orb_vis_end_coeff*orb_period);
//    return;
//}

/** \fn getNext_check_time()
 *
 *  \brief When will this channel have visibility again? 0 if visible now
 *
 *
 */

SimTime FSChannel::getNext_check_time() {
    Enter_Method("next_check_time()");
    const SimTime current_time = fmod(simTime(),op.orbit_period);
    if (current_time >= op.vis_start_time and current_time <= op.vis_end_time) {
       return 0;
    }
    if (current_time >= op.vis_end_time) { //Satellite already passed for this orbit
        return op.vis_start_time + op.orbit_period - current_time;
    }
    return op.vis_start_time - current_time;
}

void FSChannel::recalculateChannelParameters() {
    par("distance").setDoubleValue(dist_par->getPropertyAtTime(simTime().dbl()));
    if (par("CSV_varies_delay").boolValue()) par("delay").setDoubleValue(par("distance").doubleValue()/par("speed_of_light_in_FS").doubleValue());
}
}




