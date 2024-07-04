/** \file PointingSystem.cc
 *
 *  \brief PointingSystem
 */
#include "PointingSystem.h"
#include "messages/visibility_messages_m.h"
#include "channels/FSChannel.h"

using namespace quisp::channels;

namespace quisp::modules::Satellite {

Define_Module(PointingSystem);

PointingSystem::PointingSystem() {}

PointingSystem::~PointingSystem() {}


void PointingSystem::initialize() {
  //Setting the FSChannels' orbital parameters
orbital_period = par("orbital_period");
vis_start_coeff = par("vis_start_coeff");
vis_end_coeff = par("vis_end_coeff");
  if (getParentModule()->par("is_satellite")){
    for (cModule::GateIterator i(this->getParentModule()); !i.end(); i++) {
         cGate* gate = *i;

         cChannel* chl = {gate->getType() == cGate::OUTPUT? gate->getChannel() : gate->getPreviousGate()->getChannel()};


         if (auto f_chl = dynamic_cast<FSChannel*>(chl)) {
         f_chl->set_orbit_parameters(orbital_period,vis_start_coeff, vis_end_coeff);
         }
  }
  }
return;
}

void PointingSystem::handleMessage(cMessage *msg) {
  if (auto vcr = dynamic_cast<VisCheckRequest *>(msg)) {
      VisCheckOutcome* vco = new VisCheckOutcome();
      const char* gate_to_check = vcr->getOut_gate();
      int gtc_index = vcr->getIndex();
      cChannel* chl = getParentModule()->gate(gate_to_check,gtc_index)->getChannel();
      if (auto* fs_chl = dynamic_cast<FSChannel*>(chl)) {
          SimTime next_check_time = fs_chl->getNext_check_time();
          vco->setNext_check_time(next_check_time.dbl());
      } else {
      EV << "WARNING: checking visibility along a fiber channel. Seems weird.";
      vco->setNext_check_time(0);
      }
      send(vco,"ans");
  delete vcr;
  }
  //delete msg;
  return;
};


}  // namespace quisp::modules
