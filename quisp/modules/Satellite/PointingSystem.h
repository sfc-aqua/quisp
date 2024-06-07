/** \file PointingSystem.h
 *
 *  \brief PointingSystem
 */
#pragma once

#include <omnetpp.h>
#include "channels/FSChannel.h"
#include "messages/visibility_messages_m.h"
#include "omnetpp/simtime.h"

using namespace omnetpp;
using namespace quisp::messages;

/** \class PointingSystem PointingSystem.cc
 *
 *  \brief PointingSystem
 */
namespace quisp::modules::Satellite {
class PointingSystem : public cSimpleModule {
 public:
  PointingSystem();
  ~PointingSystem();

 protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage *msg) override;
  void toggleVisibility();
  double orbital_period;
  double vis_start_coeff;
  double vis_end_coeff;
  utils::ComponentProvider provider;
};
}  // namespace quisp::modules::Satellite
