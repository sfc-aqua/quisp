/*
 * FSChannel.h
 *
 *  \brief Freespace channel
 *
 *  Loss model from 10.1038/s42005-022-01123-7.
 *  Base class for Free-space communication: this channel handles variable length and delay using a OrbitalDataParser.
 *  LOS-related methods are directly callable from outside since the pointing system is expected to be able to directly check whether there is visibility or not.
 *
 */

#pragma once

#include <math.h>
#include <messages/ospf_messages_m.h>
#include <omnetpp.h>
#include <cmath>
#include <stdexcept>
#include "PhotonicQubit_m.h"
#include "omnetpp/cexception.h"
#include "utils/OrbitalDataParser.h"

using namespace omnetpp;
using namespace quisp::messages;

struct ORBITAL_PARAMETERS {
  SimTime orbit_period = SIMTIME_MAX;
  SimTime vis_start_time = SIMTIME_ZERO;
  SimTime vis_end_time = SIMTIME_MAX;
};

namespace channels {
class FSChannel : public cDatarateChannel {
 public:
  FSChannel();
  void set_orbit_parameters(double orb_period, double orb_vis_start_coeff, double orb_vis_end_coeff);
  bool checkLOS();
  double getDistanceAtTime(const simtime_t time);
  SimTime getNext_check_time();

 private:
  ORBITAL_PARAMETERS op;
  OrbitalDataParser *dist_par;

 protected:
  virtual void initialize() override;
  cChannel::Result processMessage(cMessage *msg, const SendOptions &options, simtime_t t) override;
  virtual void recalculateChannelParameters();

 private:
  bool line_of_sight;
};
};  // namespace channels
