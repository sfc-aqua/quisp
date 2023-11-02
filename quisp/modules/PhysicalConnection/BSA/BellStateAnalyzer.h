#pragma once

#include <omnetpp.h>

#include "PhotonicQubit_m.h"
#include "backends/Backends.h"
#include "backends/interfaces/IQubit.h"
#include "messages/BSA_ipc_messages_m.h"
#include "modules/PhysicalConnection/BSA/types.h"
#include "utils/ComponentProvider.h"

enum class BSAState : int { Idle = 0, FirstPortArrive, SecondPortArrive, Accepting, AcceptingFirstPort, AcceptingSecondPort };
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
  void resetState();

 protected:
  virtual void initialize() override;
  virtual void finish() override;
  virtual void handleMessage(omnetpp::cMessage *msg) override;

 private:
  void discardPhoton(PhotonRecord &photon);
  PhotonRecord getPhotonRecordFromMessage(messages::PhotonicQubit *);
  void processPhotonRecords();
  physical::types::BSAClickResult processIndistinguishPhotons(PhotonRecord &left_photon, PhotonRecord &right_photon);
  void measureSuccessfully(PhotonRecord &left_photon, PhotonRecord &right_photon, bool is_psi_plus);
  void validateProperties();

  // device parameters
  double collection_efficiency;  // might get deleted later if collection efficiency is implemented at StationaryQubit during emission
  double darkcount_probability;
  double detection_efficiency;
  omnetpp::simtime_t indistinguishability_window;  // Precision of photon arrivial time ~1.5ns

  // data members for processing
  BSAState state;
  std::vector<PhotonRecord> first_port_records;
  std::vector<PhotonRecord> second_port_records;
  utils::ComponentProvider provider;
  backends::IQuantumBackend *backend;

  // for testing and debugging
  long long no_error_count = 0;
  long long x_error_count = 0;
  long long y_error_count = 0;
  long long z_error_count = 0;

  // Coincidences signal - to count detector clicks
  int clicks = 0;
  simsignal_t clicks_in_batch = registerSignal("clicks");

};
}  // namespace quisp::modules
