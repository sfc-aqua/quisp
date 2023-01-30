/** \file BSA_Controller.h
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/04/01
 *
 *  \brief BSAController
 */
#pragma once

#include <PhotonicQubit_m.h>
#include <messages/classical_messages.h>
#include <modules/PhysicalConnection/BSA/types.h>
#include <omnetpp.h>
#include <vector>
#include "messages/link_generation_messages_m.h"

using namespace omnetpp;
using namespace quisp::messages;
using namespace quisp::physical::types;

namespace quisp::modules {

/** @class BSAController BSA_Controller.h
 *
 *  \brief This module takes the click event from BSA,
 *         compile the result and report back to QNode that sent the photons.
 *
 *         The controller can be in 2 operational modes.
 *           1) active mode
 *           2) passive mode
 *
 *  In the active mode, it will be responsible for deciding when the photons should come in.
 *  It will check the distance between two QNodes (possible one could be self), and decide
 *  on when the first photon should arrive. The result will be sent back in batches
 *  not on every photon pairs/single coming in.
 *
 *  In the passive mode, this assumes that the BSA is internal and EPPS will tell us
 *  how many photons will arrive, when the first one will arrive, and what the iterval is.
 */
class BSAController : public cSimpleModule {
 public:
  BSAController();

  void registerClickBatches(std::vector<BSAClickResult>& result);

 protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage* msg) override;

 private:
  BSMTimingNotification* generateFirstNotificationTiming(bool is_left);
  CombinedBSAresults* generateNextNotificationTiming(bool is_left);

  int getExternalAdressFromPort(int port);
  int getExternalQNICIndexFromPort(int port);

  // information for communications
  int address;
  int left_address;
  int left_qnic_index;
  int right_address;
  int right_qnic_index;

  // cache information for timing notification
  double offset_time_for_first_photon;

  // BSA characteristics
  double time_interval_between_photons;  ///< how separated should the photons be; is calculated by the dead time of the detector
  double speed_of_light_in_channel;  ///< Speed of light in optical fiber (in km per sec).
  utils::ComponentProvider provider;
};

}  // namespace quisp::modules
