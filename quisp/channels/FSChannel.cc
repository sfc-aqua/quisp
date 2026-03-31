/** \file FSChannel.cc
 *
 *  \brief Freespace channel
 *
 *
 */

#include "FSChannel.h"

using namespace omnetpp;
namespace quisp::channels {

FSChannel::FSChannel(){};

Define_Channel(FSChannel);

void FSChannel::initialize() {
  cDatarateChannel::initialize();
  const char *filename = par("distance_CSV").stringValue();
  dist_par = new CSVParser(filename);
  op.orbit_period = par("orbital_period");
  op.vis_start_time = dist_par->getLowestDatapoint();
  op.vis_end_time = dist_par->getHighestDatapoint();
}

cChannel::Result FSChannel::processMessage(cMessage *msg, const SendOptions &options, simtime_t t) {
  Result result;

  if (!checkLOS() and !dynamic_cast<OspfPacket *>(msg)) {
    result.discard = true;
  } else {
    recalculateChannelParameters();
    result = cDatarateChannel::processMessage(msg, options, t);
  }
  return result;
}

bool FSChannel::checkLOS() {
  Enter_Method("checkLOS()");
  const SimTime currentTime = fmod(simTime(), op.orbit_period);
  if (currentTime >= op.vis_start_time and currentTime <= op.vis_end_time) {
    return true;
  }
  return false;
}

double FSChannel::getDistanceAtTime(const simtime_t time) {
  recalculateChannelParameters();
  return dist_par->getPropertyAtTime(time.dbl());
}

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
}  // namespace quisp::channels
