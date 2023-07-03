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
  virtual void checkNeighborsBuffer();
  virtual EPPSTimingNotification *generateNotifier(bool is_left);

 private:
 struct MSMQnicInfo {
    int address;
    std::vector<BSAClickResult> left_clicks;
    std::vector<BSAClickResult> right_clicks;
  };
  std::map<std::pair<int, int>, MSMQnicInfo> msm_info_map;


  double getTravelTimeFromPort(int port);
  int getExternalQNICIndexFromPort(int port);
  void handleCombinedBatchClickEventResults(CombinedBatchClickEventResults *combined_result);
  void sendCombinedBSAresults(std::pair<int, int> left_right_addr_pair);

  // information for communications
  int address;
  int left_addr;
  int left_qnic_index;
  int right_addr;
  int right_qnic_index;
  double left_travel_time;
  double right_travel_time;
  double max_acceptance_rate;
  double frequency;
  int number_of_photons;
  int number_of_sent_photons;
  EPPSNotificationTimeout *time_out_message;
  int time_out_count;
  simtime_t last_result_send_time;

  // EPPS characteristics
  EntangledPhotonPairSource *epps;
  utils::ComponentProvider provider;
  simtime_t first_notification_timer;
};

}  // namespace quisp::modules
