#pragma once

#include <omnetpp.h>
#include "BSAController.h"
#include "PhotonicQubit_m.h"
#include "backends/interfaces/IQubit.h"
#include "modules/PhysicalConnection/BSA/types.h"
#include "omnetpp/simtime_t.h"

enum class BSAState : int { Idle = 0, Accepting, AcceptingFirstPort, AcceptingSecondPort };
enum class PortNumber : int { First = 0, Second };

struct PhotonRecord {
  quisp::backends::abstract::IQubit *qubit_ref;
  omnetpp::simtime_t arrival_time;
  PortNumber from_port;
  bool is_lost;
  bool is_first;
  bool is_last;
  bool has_x_error;
  bool has_z_error;
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
  simtime_t indistinguishability_window;  // Precision of photon arrivial time ~1.5ns

  BSAState state;

  // data structures for processing
  std::vector<PhotonRecord> first_port_records;
  std::vector<PhotonRecord> second_port_records;
  std::vector<BSAClickResult> click_results;

  // for testing and debugging
  long long no_error_count = 0;
  long long x_error_count = 0;
  long long y_error_count = 0;
  long long z_error_count = 0;
};
}  // namespace quisp::modules
