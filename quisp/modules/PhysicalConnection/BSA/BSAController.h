/** \file BSA_Controller.h
 *
 *  \brief BSAController
 */
#pragma once

#include <omnetpp.h>
#include <vector>
#include "PhotonicQubit_m.h"
#include "messages/BSA_ipc_messages_m.h"
#include "messages/classical_messages.h"
#include "messages/link_generation_messages_m.h"
#include "modules/PhysicalConnection/BSA/types.h"
#include "modules/QNIC.h"

using namespace omnetpp;
using namespace quisp::messages;

namespace quisp::modules {

struct BsaQNicId {
  QNIC_type type;
  int index;
  int parent_node_addr;
};

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
  ~BSAController();
  int getExternalAdressFromPort(int port);
  void cancelBSMTimeOut();

 protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage* msg) override;
  virtual void finish() override;

 private:
  BSMTimingNotification* generateFirstNotificationTiming(bool is_left);
  CombinedBSAresults* generateNextNotificationTiming(bool is_left);

  int getExternalQNICIndexFromPort(int port);
  double calculateOffsetTimeFromDistance();
  double getTravelTimeFromPort(int port);
  double getExternalDistanceFromPort(int port);
  BsaQNicId getExternalQNICInfoFromPort(int port);
  void sendMeasurementResults(BatchClickEvent* msg);

  // information for communications
  int address;
  BsaQNicId left_qnic;
  BsaQNicId right_qnic;
  double left_travel_time;
  double right_travel_time;

  // cache information for timing notification
  double offset_time_for_first_photon;
  BSMNotificationTimeout* time_out_message;
  std::vector<BSAClickResult> click_results;
  int time_out_count;

  // BSA characteristics
  double time_interval_between_photons;  ///< how separated should the photons be; is calculated by the dead time of the detector
  double speed_of_light_in_channel;  ///< Speed of light in optical fiber (in km per sec).
  utils::ComponentProvider provider;

  // testing and debugging members
  simtime_t last_result_send_time = 0;
};

}  // namespace quisp::modules
