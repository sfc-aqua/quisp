#pragma once

#include <messages/classical_messages.h>
#include <omnetpp.h>
#include <utils/ComponentProvider.h>
#include <vector>
#include "PhotonicQubit_m.h"
#include "backends/Backends.h"
#include "backends/interfaces/IQubit.h"
#include "modules/PhysicalConnection/BSA/types.h"
#include "modules/QNIC/StationaryQubit/IStationaryQubit.h"

namespace quisp::modules {

class EntangledPhotonPairSource : public omnetpp::cSimpleModule {
 private:
  // device parameters
  double emission_success_probability;
  double emission_jittering_standard_deviation;
  double emission_x_error_rate;
  double emission_y_error_rate;
  double emission_z_error_rate;

  utils::ComponentProvider provider;
  IQuantumBackend* backend;

 protected:
  virtual void initialize() override;
  virtual void handleMessage(omnetpp::cMessage* msg) override;
  virtual void finish() override;

 public:
  EntangledPhotonPairSource();
  ~EntangledPhotonPairSource();
  virtual void emitPhotons();
};

}  // namespace quisp::modules
