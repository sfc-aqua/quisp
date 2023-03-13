#include "EntangledPhotonPairSource.h"
#include "PhotonicQubit_m.h"
#include "omnetpp/ccontextswitcher.h"

using quisp::messages::PhotonicQubit;
using namespace omnetpp;

namespace quisp::modules {

Define_Module(EntangledPhotonPairSource);

StationaryQubit::StationaryQubit() : provider(utils::ComponentProvider{this}) {}

void EntangledPhotonPairSource::initialize() {
  emission_success_probability = par("error_rate").doubleValue();
  emission_x_error_rate = par("x_error_ratio").doubleValue();
  emission_y_error_rate = par("y_error_ratio").doubleValue();
  emission_z_error_rate = par("z_error_ratio").doubleValue();
  emission_jittering_standard_deviation = par("emission_jittering_standard_deviation").doubleValue();

  backend = provider.getQuantumBackend();
}

void EntangledPhotonPairSource::handleMessage(cMessage *msg) { send(msg, "to_quantum_port$o", msg->par("gate")); }

void EntangledPhotonPairSource::emitPhotons() {
  Enter_Method("emitPhotons()");
  auto *photon_1 = new PhotonicQubit("Photon_1");
  auto *photon_2 = new PhotonicQubit("Photon_2");
  auto *photon_1_ref = backend->getShortLiveQubit();
  auto *photon_2_ref = backend->getShortLiveQubit();
  photon_one_ref->noiselessH();
  photon_two_ref->noiselessCNOT(photon_one_ref);
  photon_one->setQubit_ref(photon_one_ref);
  photon_two->setQubit_ref(photon_two_ref);
  float jitter_timing = normal(0, emission_jittering_standard_deviation);
  float abso = fabs(jitter_timing);
  scheduleAt(simTime() + abso, photon_one);
  scheduleAt(simTime() + abso, photon_two);
}

cModule *EntangledPhotonPairSource::getEPPSNode() {
  // We know that Connection manager is not the EPPS, so start from the parent.
  cModule *currentModule = getParentModule();
  try {
    // Assumes the node in a network has a type SPDC
    cModuleType *QNodeType = cModuleType::get("modules.EPPS");
    while (currentModule->getModuleType() != QNodeType) {
      currentModule = currentModule->getParentModule();
    }
    return currentModule;
  } catch (std::exception &e) {
    error("No module with QNode type found. Have you changed the type name in ned file?");
    endSimulation();
  }
  return currentModule;
}

}  // namespace quisp::modules
