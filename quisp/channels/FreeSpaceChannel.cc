/** \file QuantumChannel.cc
 *
 *  \brief Freespace channel
 *
 *
 */

#include "FreeSpaceChannel.h"
#include <omnetpp.h>

using namespace omnetpp;
namespace quisp::channels {

FreeSpaceChannel::FreeSpaceChannel(){};

void FreeSpaceChannel::initialize() {
  cDatarateChannel::initialize();
  parameter_distance = &par("distance");
  parameter_delay = &par("delay");
  speed_of_light_in_freespace = par("speed_of_light_in_freespace").doubleValueInUnit("m");
  const char *filename = par("distance_csv").stringValue();
  csv_varies_delay = par("csv_varies_delay").boolValue();
  dist_parser = new OrbitalDataParser(filename);
  op.orbit_period = par("orbital_period");
  op.vis_start_time = dist_parser->getLowestDatapoint();
  op.vis_end_time = dist_parser->getHighestDatapoint();
}

Define_Channel(FreeSpaceChannel);

cChannel::Result FreeSpaceChannel::processMessage(cMessage *msg, const SendOptions &options, simtime_t t) {
  if (!isRecipientVisible() and !dynamic_cast<OspfPacket *>(msg)) {
    Result result;
    result.discard = true;
    return result;
  }
  recalculateChannelParameters();
  return cDatarateChannel::processMessage(msg, options, t);
}

bool FreeSpaceChannel::isRecipientVisible() {
  Enter_Method("isRecipientVisible()");
  const SimTime currentTime = fmod(simTime(), op.orbit_period);
  return (currentTime >= op.vis_start_time and currentTime <= op.vis_end_time);
}

double FreeSpaceChannel::getDistanceAtTime(const simtime_t time) {
  recalculateChannelParameters();
  return dist_parser->getPropertyAtTime(time.dbl());
}

SimTime FreeSpaceChannel::getNextCheckTime() {
  Enter_Method("getNextCheckTime()");
  const SimTime current_time = fmod(simTime(), op.orbit_period);
  if (current_time >= op.vis_start_time and current_time <= op.vis_end_time) {
    return 0;
  }
  if (current_time >= op.vis_end_time) {  // Satellite already passed for this orbit
    return op.vis_start_time + op.orbit_period - current_time;
  }
  return op.vis_start_time - current_time;
}

void FreeSpaceChannel::recalculateChannelParameters() {
  parameter_distance->setDoubleValue(dist_parser->getPropertyAtTime(simTime().dbl()) / 1000);  // km
  if (csv_varies_delay) parameter_delay->setDoubleValue(parameter_distance->doubleValueInUnit("m") / speed_of_light_in_freespace);
}
}  // namespace quisp::channels
