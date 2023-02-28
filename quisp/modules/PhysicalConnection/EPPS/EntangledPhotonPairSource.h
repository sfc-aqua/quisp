#pragma once

#include <omnetpp.h>
#include "EPPSController.cc"
#include "PhotonicQubit_m.h"
#include "backends/Backends.h"
#include "backends/interfaces/IQubit.h"
#include <messages/classical_messages.h>
#include <utils/ComponentProvider.h>
#include "modules/PhysicalConnection/BSA/types.h"
#include "modules/QNIC/StationaryQubit/IStationaryQubit.h"
#include <vector>

namespace quisp::modules{

class EntangledPhotonPairSource : public omnetpp::cSimpleModule {
 private:
  // device parameters
  double emission_success_probability;
  double emission_jittering_standard_deviation;
  double emission_x_error_rate;
  double emission_y_error_rate;
  double emission_z_error_rate;

  utils::ComponentProvider provider;
  IQuantumBackend *backend;
  
 protected:
  virtual void initialize() override;
  virtual void handleMessage(omnetpp::cMessage* msg) override;
  virtual void BubbleText(const char* txt);
  virtual messages::PhotonicQubit *generatePhoton();
  void entanglePhotons(messages::PhotonicQubit *photon_one, messages::PhotonicQubit *photon_two);
  virtual void entanglePhotons();
  virtual omnetpp::cModule* getEPPSNode();

 public:
  virtual void emitPhotons();
};

}  // namespace quisp::modules
