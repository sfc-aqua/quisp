/** \file EntangledPhotonPairSource.cc
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/25
 *
 *  \brief EntangledPhotonPairSource
 */
#include "../EPPS/EntangledPhotonPairSource.h"

namespace quisp {
namespace modules {

Define_Module(EntangledPhotonPairSource);

void EntangledPhotonPairSource::initialize() {
  error_rate = par("error_rate");
  Y_error_ratio = par("Y_error_ratio");
  X_error_ratio = par("X_error_ratio");
  Z_error_ratio = par("Z_error_ratio");
  emission_std = par("emission_std");
  frequency = par("frequency");
  EV << "------------------" << frequency << " aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
}

void EntangledPhotonPairSource::handleMessage(cMessage *msg) { send(msg, "to_quantum_port$o", msg->par("gate")); }

PhotonicQubit *EntangledPhotonPairSource::generateEntangledPhotons() {
  Enter_Method("generateEntangledPhotons()");
  PhotonicQubit *photon_one = new PhotonicQubit("Photon");
  return photon_one;
  // PhotonicQubit *photon_two = new PhotonicQubit();
  // photon_one->addPar("gate") = 0;
  // photon_two->addPar("gate") = 1;
  // photon->setStationaryQubitEntangledWith(stationaryQubit_address);
  // entangledPhotons *qubits;
  // qubits->qubitTwo = photon_two;
  // qubits->qubitOne = photon_one;
  // return qubits;

  // Enter_Method("generateEntangledPhoton()");
  // auto *photon = new PhotonicQubit("Photon");
  // // To simulate the actual physical entangled partner, not what the system thinks!!! we need this.

  // // This photon is entangled with.... node_address = node's index
  // photon->setNodeEntangledWith(node_address);

  // // qnic_address != qnic_index. qnic_index is not unique because there are 3 types.
  // photon->setQNICEntangledWith(qnic_address);

  // // stationaryQubit_address = StationaryQubit's index
  // photon->setStationaryQubitEntangledWith(stationaryQubit_address);
  // photon->setQNICtypeEntangledWith(qnic_type);
  // photon->setEntangled_with(this);
  // return photon;
}

void EntangledPhotonPairSource::emitPhotons(bool isFirst, bool isLast) {
  Enter_Method("emitPhotons()");
  // PhotonicQubit *qubit = generateEntangledPhotons();
  PhotonicQubit *qubit = new PhotonicQubit("Photon");
  qubit->addPar("gate") = 0;
  // PhotonicQubit *qubitTwo = generateEntangledPhotons();
  PhotonicQubit *qubitTwo = new PhotonicQubit("Photon");
  qubitTwo->addPar("gate") = 1;

  qubit->setEntangled_photon(qubitTwo);
  qubit->setIs_entangled_with_photon(true);
  qubit->setFirst(isFirst);
  qubit->setLast(isLast);
  qubitTwo->setEntangled_photon(qubit);
  qubitTwo->setIs_entangled_with_photon(true);
  qubitTwo->setFirst(isFirst);
  qubitTwo->setLast(isLast);

  float jitter_timing = normal(0, emission_std);
  float abso = fabs(jitter_timing);

  scheduleAt(simTime() + abso, qubit);
  scheduleAt(simTime() + abso, qubitTwo);
}

void EntangledPhotonPairSource::BubbleText(const char *txt) {
  if (hasGUI()) {
    char text[32];
    sprintf(text, "%s", txt);
    bubble(text);
  }
}

cModule *EntangledPhotonPairSource::getSPDCNode() {
  // We know that Connection manager is not the SPDC, so start from the parent.
  cModule *currentModule = getParentModule();
  try {
    // Assumes the node in a network has a type SPDC
    cModuleType *QNodeType = cModuleType::get("modules.SPDC");
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

double EntangledPhotonPairSource::getEmissionFrequency() {
  Enter_Method("getEmissionFrequency()");
  EV << "**********************Returning frequency" << frequency;
  return frequency;
}

}  // namespace modules
}  // namespace quisp
