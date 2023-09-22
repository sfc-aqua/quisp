/** \file VisibilityChecker.cc
 *
 *  \brief VisibilityChecker
 */
#include "VisibilityChecker.h"
#include "channels/FSChannel.h"

using namespace quisp::channels;

namespace quisp::modules::Satellite {

Define_Module(VisibilityChecker);

VisibilityChecker::VisibilityChecker() {}

VisibilityChecker::~VisibilityChecker() {}


void VisibilityChecker::initialize() {
  is_satellite = this->getParentModule()->par("is_satellite");
  if (!is_satellite) {
      cMessage* msg = new cMessage("delete",0);
      scheduleAt(simTime(),msg);
      return;
  }
  orbital_period = double(par("orbital_period"));
  up_time = double(par("visibility_window"));
  down_time = orbital_period - up_time;
  is_visible = par("starts_visible");
  cMessage* msg = new cMessage("toggle",1);
  next_check_time = {is_visible? up_time : down_time};
  scheduleAt(simTime()+next_check_time,msg);

  GQ_ctrl* rst_lt = new GQ_ctrl();
  rst_lt->setCtrl_signal(is_visible);
  send(rst_lt,"ctrl");

  for (cModule::GateIterator i(this->getParentModule()); !i.end(); i++) {
         cGate* gate = *i;
         cChannel* chl = gate->getChannel();
         if (auto f_chl = dynamic_cast<FSChannel*>(chl)) {
         f_chl->setLOS(is_visible);
         }
  }
return;
}

void VisibilityChecker::handleMessage(cMessage *msg) {
  if (msg->getKind() == 0) {
      delete msg;
      deleteModule();
  } else if (msg->getKind() == 1) {
    toggleVisibility();
    next_check_time = {is_visible? up_time : down_time};
    scheduleAt(simTime()+next_check_time,msg);
  } else {
    bubble("Something unexpected arrived at the satellite's visibility checker...");
  };
  return;
};

void VisibilityChecker::toggleVisibility() {
    EV_INFO << "Satellite visibility now " << !is_visible;

    GQ_ctrl* for_lt_ctrl = new GQ_ctrl();
    for_lt_ctrl->setCtrl_signal(!is_visible);

    if (is_visible) send(for_lt_ctrl,"ctrl");
    is_visible = !is_visible;

    for (cModule::GateIterator i(this->getParentModule()); !i.end(); i++) {
        cGate* gate = *i;
        cChannel* chl = gate->getChannel();
        if (FSChannel* dr_chl = dynamic_cast<FSChannel*>(chl); dr_chl != nullptr) {
        dr_chl->setLOS(is_visible);
        }
    }
    if (is_visible) send(for_lt_ctrl,"ctrl");

}  // namespace quisp::modules
}
