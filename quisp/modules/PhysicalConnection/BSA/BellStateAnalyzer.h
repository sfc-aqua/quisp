#pragma once

#include <omnetpp.h>
#include "BSAController.h"
#include "PhotonicQubit_m.h"
#include "backends/interfaces/IQubit.h"
#include "modules/PhysicalConnection/BSA/types.h"
#include "omnetpp/simtime_t.h"

using namespace quisp::physical::types;

enum class BSAState : int { Idle = 0, Accepting, AcceptingFirstPort, AcceptingSecondPort };
enum class PortNumber : int { First = 0, Second };

struct PhotonRecord {
  quisp::backends::abstract::IQubit *qubit_ref;
  omnetpp::simtime_t arrival_time;
  PortNumber from_port;
  bool is_lost;
  bool is_first;
  bool is_last;
};

namespace quisp::modules {
class BellStateAnalyzer : public omnetpp::cSimpleModule {
 public:
  BellStateAnalyzer();

 protected:
  virtual void initialize() override;
  virtual void finish() override;
  virtual void handleMessage(omnetpp::cMessage *msg) override;

 private:
  void registerClickBatches();
  void discardPhoton(PhotonRecord &photon);
  PhotonRecord getPhotonRecordFromMessage(messages::PhotonicQubit *);
  void processPhotonRecords();
  BSAClickResult processIndistinguishPhotons(PhotonRecord &left_photon, PhotonRecord &right_photon);
  void measureSuccessfully(PhotonRecord &left_photon, PhotonRecord &right_photon, bool is_psi_plus);
  void validateProperties();

  // device parameters
  double collection_efficiency;
  double darkcount_probability;
  double detection_efficiency;
  double indistinguishability_window;  // Precision of photon arrivial time ~1.5ns

  BSAState state;
  BSAController *controller;

  // data structures for processing
  std::vector<PhotonRecord> first_port_records;
  std::vector<PhotonRecord> second_port_records;
};
}  // namespace quisp::modules
