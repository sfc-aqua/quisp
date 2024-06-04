/*
 * FSChannel.h
 *
 *  Created on: Sep 6, 2023
 *      Author: paolo
 */

#pragma once

#include <omnetpp.h>
#include <stdexcept>
#include "PhotonicQubit_m.h"
#include "omnetpp/cexception.h"
#include "utils/CSVParser.h"
#include <math.h>

using namespace omnetpp;

struct ORBITAL_PARAMETERS {
  SimTime orbit_period = SIMTIME_MAX;
  SimTime vis_start_time = SIMTIME_ZERO;
  SimTime vis_end_time = SIMTIME_MAX;
};

namespace channels {
class FSChannel : public cDatarateChannel {
 public:
    FSChannel();
    void set_orbit_parameters(double orb_period,double orb_vis_start_coeff, double orb_vis_end_coeff);
    bool checkLOS();
    double getDistanceAtTime(const simtime_t time);
    SimTime getNext_check_time();
private:
    ORBITAL_PARAMETERS op;
    CSVParser* dist_par;

 protected:
  virtual void initialize() override;
  cChannel::Result processMessage(cMessage *msg, const SendOptions &options, simtime_t t) override;
  virtual void recalculateChannelParameters();

 private:
    bool line_of_sight;
};
};



