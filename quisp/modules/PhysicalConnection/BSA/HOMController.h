/** \file HOM_Controller.h
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/04/01
 *
 *  \brief HOMController
 */
#pragma once

#include <PhotonicQubit_m.h>
#include <messages/classical_messages.h>
#include <omnetpp.h>
#include <vector>

using namespace omnetpp;
using namespace quisp::messages;

namespace quisp {
namespace modules {

/** \class HOMController HOM_Controller.h
 *  \note How about if two nodes have imbalanced buffers?
 *        Maybe use unused qnic (which is ought to be used for another path)?
 *
 *  \brief HOMController
 */
class HOMController : public cSimpleModule {
 private:
  int address;
  int photon_detection_per_sec;  ///< The number of detectable photon in a second. This info is used to decide the number of photon in one trial.
  double speed_of_light_in_channel;  ///< Speed of light in optical fiber.
  cPar* c;

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
  HOMController();
};

}  // namespace modules
}  // namespace quisp
