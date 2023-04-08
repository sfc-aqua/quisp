/** \file PhotonicSwitch.cc
 *  \authors cldurand,takaakimatsuo
 *
 *  \brief PhotonicSwitch
 */
#include "PhotonicSwitch.h"

namespace quisp::modules {

void PhotonicSwitch::initialize() {}

void PhotonicSwitch::handleMessage(cMessage *msg) { send(msg, "to_bsa$o"); }

}  // namespace quisp::modules
