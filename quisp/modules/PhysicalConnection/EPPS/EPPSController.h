/** \file EPPSController.h
 *
 *  \brief EPPSController
 */
#pragma once

#include <PhotonicQubit_m.h>
#include <messages/classical_messages.h>
#include <omnetpp.h>
#include <vector>
#include "EntangledPhotonPairSource.h"
#include "omnetpp/simtime.h"

using namespace omnetpp;
using namespace quisp::messages;

namespace quisp::modules {
/** \class EPPSController EPPSController.cc
 *
 *  \brief EPPSController
 */
class EPPSController : public cSimpleModule {
 public:
  EPPSController();
  ~EPPSController();
  int getExternalAdressFromPort(int port);

 protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage *msg) override;
  virtual void finish() override;
  virtual void checkNeighborsBSACapacity();
  virtual EPPSTimingNotification *generateNotifier(bool is_left);

 private:
  double getTravelTimeFromPort(int port);
  int getExternalQNICIndexFromPort(int port);

  // information for communications
  int address;
  int left_addr;
  int left_qnic_index;
  int right_addr;
  int right_qnic_index;
  simtime_t left_travel_time;
  simtime_t right_travel_time;
  simtime_t time_interval_between_photons;
  double frequency;
  simtime_t emit_time;
  EPPSNotificationTimeout *time_out_message;
  int time_out_count;
  simtime_t last_result_send_time;
  bool neighbor_buffer_is_full = false;
  bool stopping_epps_emission = false;

  // EPPS characteristics
  EntangledPhotonPairSource *epps;
  utils::ComponentProvider provider;
  simtime_t first_notification_timer;
};

}  // namespace quisp::modules
