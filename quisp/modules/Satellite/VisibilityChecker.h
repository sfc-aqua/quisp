/** \file VisibilityChecker.h
 *
 *  \brief VisibilityChecker
 */
#pragma once.modules.Satellite;

#include <omnetpp.h>
#include "omnetpp/simtime.h"
#include "channels/FSChannel.h"

using namespace omnetpp;

/** \class VisibilityChecker VisibilityChecker.cc
 *
 *  \brief VisibilityChecker: Crude, duty-cycle based model for the satellite orbiting in and out of sight.
 */
namespace quisp::modules::Satellite {
class VisibilityChecker : public cSimpleModule {
 public:
  VisibilityChecker();
  ~VisibilityChecker();

 protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage *msg) override;
  void toggleVisibility();
  double orbital_period;
  double up_time;
  double down_time;
  bool is_satellite;
  bool is_visible;
  double next_check_time;
};
}
