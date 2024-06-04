/** \file QuantumChannel.cc
 *
 *  \brief QuantumChannel
 */
#include "FSChannel.h"
#include <omnetpp.h>

using namespace omnetpp;
namespace channels {

FSChannel::FSChannel(){};

void FSChannel::initialize() {
  cDatarateChannel::initialize();
  const char *filename = par("distance_CSV").stringValue();
  dist_par = new CSVParser(filename);
  op.orbit_period = par("orbital_period");
  op.vis_start_time = dist_par->getLowestDatapoint();
  op.vis_end_time = dist_par->getHighestDatapoint();
}

Define_Channel(FSChannel);

cChannel::Result FSChannel::processMessage(cMessage *msg, const SendOptions &options, simtime_t t) {
  Result result;

  if (!checkLOS()) {
    result.discard = true;
    return result;
  }
  par("distance").setDoubleValue(dist_par->getPropertyAtTime(simTime().dbl()));
  par("delay").setDoubleValue(par("distance").doubleValue() / par("speed_of_light_in_FS").doubleValue());
  result = cDatarateChannel::processMessage(msg, options, t);
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
  const SimTime currentTime = fmod(simTime(), op.orbit_period);
  if (currentTime >= op.vis_start_time and currentTime <= op.vis_end_time) {
    return true;
  }
  return false;
}

double FSChannel::getDistanceAtTime(const simtime_t time) { return dist_par->getPropertyAtTime(time.dbl()); }

/** \fn getNext_check_time()
 *
 *  \brief When will this channel have visibility again? 0 if visible now
 *
 *
 */

SimTime FSChannel::getNext_check_time() {
  Enter_Method("next_check_time()");
  const SimTime current_time = fmod(simTime(), op.orbit_period);
  if (current_time >= op.vis_start_time and current_time <= op.vis_end_time) {
    return 0;
  }
  if (current_time >= op.vis_end_time) {  // Satellite already passed for this orbit
    return op.vis_start_time + op.orbit_period - current_time;
  }
  return op.vis_start_time - current_time;
}

void FSChannel::recalculateChannelParameters() {
  par("distance").setDoubleValue(dist_par->getPropertyAtTime(simTime().dbl()));
  if (par("CSV_varies_delay").boolValue()) par("delay").setDoubleValue(par("distance").doubleValue() / par("speed_of_light_in_FS").doubleValue());
}
}  // namespace channels
