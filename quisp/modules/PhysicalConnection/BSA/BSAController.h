/** \file BSA_Controller.h
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/04/01
 *
 *  \brief BSAController
 */
#pragma once

#include <PhotonicQubit_m.h>
#include <messages/classical_messages.h>
#include <omnetpp.h>
#include <vector>

using namespace omnetpp;
using namespace quisp::messages;

namespace quisp::modules {

/** @class BSAController BSA_Controller.h
 *
 *  \brief This module takes the click event from BSA,
 *         compile the result and report back to QNode that sent the photons.
 *
 *         The controller can be in 2 operational modes.
 *           1) active mode
 *           2) passive mode
 *
 *  In the active mode, it will be responsible for deciding when the photons should come in.
 *  It will check the distance between two QNodes (possible one could be self), and decide
 *  on when the first photon should arrive. The result will be sent back in batches
 *  not on every photon pairs/single coming in.
 *
 *  In the passive mode, this assumes that the BSA is internal and EPPS will tell us
 *  how many photons will arrive, when the first one will arrive, and what the iterval is.
 */
class BSAController : public cSimpleModule {
 private:
  int address;
  int photon_detection_per_sec;  ///< The number of detectable photon in a second. This info is used to decide the number of photon in one trial.
  double speed_of_light_in_channel;  ///< Speed of light in optical fiber.
  cPar* c;
  utils::ComponentProvider provider;

 public:
  int neighbor_address;  ///< Address of one of two neighbor node.
  int neighbor_address_two;  ///< Address of the other node from "neighbor address"
  int neighbor_buffer;  ///< The number of qubits in a qnic in the neighbor node
  int neighbor_buffer_two;  ///< The number of qubits in a qnic in the other neighbor node
  int max_buffer;  ///< Maximum number of qubits available for BSA process
  double distance_to_neighbor;  ///< Physical distance of fiber to the neighbor node (unit: km)
  double distance_to_neighbor_two;  ///< Physical distance of fiber to the other neighbor node (unit: km)
  double max_neighbor_distance;  ///< Store longer one of "distance_to_neighbor" and "distance_to_neighbor_two". max(distance_to_neighbor, distance_to_neighbor_two)(unit: km)
  double accepted_burst_interval;  ///< Calculated phton burst interval calculated by distance and light speed. (unit: s)

  int BSAtimingNotifier_type = 4;  ///< Type of packet

  bool receiver, passive;  ///< Type of QNIC. receiver: receive phton from counter part. passive: Not implemented yet. Will be used for MSM link.
  int qnic_index = -1;  ///< Index of qnic. If the qnic is internal (used in MM link), the index is -1. (default: -1)
  int qnic_address = -1;  ///< Address of qnic. If the qnic is internal (used in MM link), the index is -1. (default: -1)

  int* BSAresults;  ///< not used?
  typedef std::map<int, bool> BSAresultTable;  ///< A table to store the pair of BSA trial index --> success or failure
  BSAresultTable results;

  bool handshake = false;  ///< True: Return ack and negotiate the number of available qubits. False: Use maximum number of available qubits
  double bsa_notification_interval;  ///< Interval to send BSA notification

 protected:
  virtual void initialize(int stage) override;
  virtual int numInitStages() const override { return 1; };
  virtual void standaloneInitializer();
  virtual void internodeInitializer();
  virtual void handleMessage(cMessage* msg) override;
  virtual double calculateEmissionStartTime(double timing, double distance_to_node, double c);
  virtual double calculateTimeToTravel(double distance, double c);
  virtual BSMtimingNotifier* generateNotifier(double time, double speed_of_light_in_channel, double distance_to_neighbor, int destAddr, double accepted_burst_interval,
                                              int photon_detection_per_sec, int max_buffer);
  virtual CombinedBSAresults* generateNotifier_c(double time, double speed_of_light_in_channel, double distance_to_neighbor, int destAddr, double accepted_burst_interval,
                                                 int photon_detection_per_sec, int max_buffer);
  virtual cModule* getQNode();
  virtual void checkNeighborAddress(bool receiver);
  virtual void checkNeighborBuffer(bool receiver);
  virtual void updateIDE_Parameter(bool receiver);
  virtual void sendNotifiers();
  virtual void pushToBSAresults(bool attempt_success);
  virtual int getStoredBSAresultsSize();
  virtual void clearBSAresults();
  virtual void sendBSAresultsToNeighbors();

 public:
  virtual void setMax_buffer(int buffer);
  BSAController();
};

}  // namespace quisp::modules
