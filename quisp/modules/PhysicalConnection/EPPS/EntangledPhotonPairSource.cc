#include "EntangledPhotonPairSource.h"
#include "PhotonicQubit_m.h"

using quisp::messages::PhotonicQubit;
using namespace omnetpp;

namespace quisp::modules {

Define_Module(EntangledPhotonPairSource);
EntangledPhotonPairSource::EntangledPhotonPairSource() : provider(utils::ComponentProvider{this}) {}

EntangledPhotonPairSource::~EntangledPhotonPairSource() {}

void EntangledPhotonPairSource::finish() {}

void EntangledPhotonPairSource::initialize() {
  emission_success_probability = par("emission_success_probability").doubleValue();
  emission_x_error_rate = par("emission_x_error_rate").doubleValue();
  emission_y_error_rate = par("emission_y_error_rate").doubleValue();
  emission_z_error_rate = par("emission_z_error_rate").doubleValue();
  emission_jittering_standard_deviation = par("emission_jittering_standard_deviation").doubleValue();

  backend = provider.getQuantumBackend();
}

/**
 * \brief handle PhotonicQubit generated by StationaryQubit itself
 *
 * \param msg is the PhotonicQubit message
 */
void EntangledPhotonPairSource::handleMessage(cMessage *msg) {
  if (!msg->isSelfMessage()) {
    throw cRuntimeError("EntangledPhotonPairSource::handleMessage: message from outside is not expected");
  }
  int port = 0;
  if (strcmp(msg->getName(), "RightPhoton")) port = 1;
  double rand = dblrand();
  if (rand < (1 - emission_success_probability)) {
    PhotonicQubit *pk = check_and_cast<PhotonicQubit *>(msg);
    pk->setLost(true);
    send(pk, "quantum_port$o", port);
  } else {
    send(msg, "quantum_port$o", port);
  }
}

void EntangledPhotonPairSource::emitPhotons(int pulse) {
  Enter_Method("emitPhotons()");
  auto *left_photon = new PhotonicQubit("LeftPhoton");
  auto *right_photon = new PhotonicQubit("RightPhoton");
  auto *left_photon_ref = backend->getShortLiveQubit();
  auto *right_photon_ref = backend->getShortLiveQubit();
  left_photon_ref->noiselessH();
  left_photon_ref->noiselessCNOT(right_photon_ref);
  left_photon->setQubit_ref(left_photon_ref);
  right_photon->setQubit_ref(right_photon_ref);
  left_photon->setGraphState(left_photon_ref->graphState().c_str());
  right_photon->setGraphState(right_photon_ref->graphState().c_str());
  if (pulse & ENTANGLEDPHOTONPAIRSOURCE_PULSE_BEGIN) {
    left_photon->setFirst(true);
    right_photon->setFirst(true);
  }
  if (pulse & ENTANGLEDPHOTONPAIRSOURCE_PULSE_END) {
    left_photon->setLast(true);
    right_photon->setLast(true);
  }
  if (pulse & ENTANGLEDPHOTONPAIRSOURCE_PULSE_BOUND) {
    left_photon->setKind(3);
    right_photon->setKind(3);
  }
  float jitter_timing = normal(0, emission_jittering_standard_deviation);
  float abso = fabs(jitter_timing);
  scheduleAt(simTime() + abso, left_photon);
  scheduleAt(simTime() + abso, right_photon);
}

}  // namespace quisp::modules
