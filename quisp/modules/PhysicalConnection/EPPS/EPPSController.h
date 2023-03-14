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

 protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage *msg) override;
  virtual void checkNeighborsAddress();
  virtual void checkNeighborsDistance();
  virtual void checkNeighborsBSACapacity();
  virtual void checkNeighborsBuffer();
  virtual EPPStimingNotifier *generateNotifier(double time_to_travel, int dest_addr);
  virtual void startPump();

 private:
  double getTravelTimeFromPort(int port);
  int getExternalAdressFromPort(int port);

  // information for communications
  int address;
  int left_qnic_addr;
  int right_qnic_addr;
  double left_travel_time;
  double right_travel_time;
  double left_acceptance_rate;
  double right_acceptance_rate;
  double max_acceptance_rate;
  double frequency;

  // EPPS characteristics
  double timing_buffer;
  double speed_of_light_in_channel;
  utils::ComponentProvider provider;

  EmitPhotonRequest *emt;
  cMessage *generatePacket;
};

}  // namespace quisp::modules
