/** \file PointingSystem.cc
 *
 *  \brief PointingSystem
 */
#include "PointingSystem.h"
#include "channels/FreeSpaceChannel.h"
#include "messages/visibility_messages_m.h"

using namespace quisp::channels;

namespace quisp::modules::Satellite {

Define_Module(PointingSystem);

PointingSystem::PointingSystem() : provider(utils::ComponentProvider{this}) {}

PointingSystem::~PointingSystem() {}

void PointingSystem::initialize() {}

void PointingSystem::handleMessage(cMessage* msg) {
  if (dynamic_cast<VisibilityMessage*>(msg)) {
    if (auto vcr = dynamic_cast<VisCheckRequest*>(msg)) {
      VisCheckOutcome* vco = new VisCheckOutcome();
      const char* gate_to_check = vcr->getOut_gate();
      int gtc_index = vcr->getIndex();
      cChannel* chl = getParentModule()->gate(gate_to_check, gtc_index)->getChannel();
      if (auto* fs_chl = dynamic_cast<FreeSpaceChannel*>(chl)) {
        SimTime next_check_time = fs_chl->getNextCheckTime();
        vco->setNextCheckTime(next_check_time.dbl());
      } else {
        EV << "WARNING: checking visibility along a fiber channel. Seems weird.";
        vco->setNextCheckTime(0);
      }
      send(vco, "ans");
      delete vcr;
    }
  } else
    throw(cRuntimeError("Unexpected Message at Pointing System!"));
  return;
};

}  // namespace quisp::modules::Satellite
