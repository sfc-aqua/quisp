/** \file HoM_Controller.h
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/04/01
 *
 *  \brief HoMController
 */
#ifndef QUISP_MODULES_HOM_CONTROLLER_H_
#define QUISP_MODULES_HOM_CONTROLLER_H_

#include <PhotonicQubit_m.h>
#include <classical_messages_m.h>
#include <omnetpp.h>
#include <vector>

using namespace omnetpp;
using namespace quisp::messages;

namespace quisp {
namespace modules {

/** \class HoMController HoM_Controller.h
 *  \todo Documentation of the class header.
 *  \note How about if two nodes have imbalanced buffers?
 *        Maybe use unused qnic (which is ought to be used for another path)?
 *
 *  \brief HoMController
 */
class HoMController : public cSimpleModule {
 private:
  int address;
  int photon_detection_per_sec;
  std::vector<const char*> gates_here;
  // cMessage *generatePacket;
  double speed_of_light_in_channel;
  cPar* c;
  int time_out_count;
  int success_count = 0;
  // simsignal_t recog_resSignal;
 public:
  int neighbor_address;
  int neighbor_address_two;
  int neighbor_buffer;
  int neighbor_buffer_two;
  int max_buffer;
  double distance_to_neighbor;  // in km
  double distance_to_neighbor_two;  // in km
  double max_neighbor_distance;  // in km
  double accepted_burst_interval;  // in s

  int BSAtimingNotifier_type = 4;
  int PathSelection_type = 1;
  int PhotonicQubit_type = 100;

  bool receiver, passive;
  int qnic_index = -1;
  int qnic_address = -1;

  int* BSAresults;
  typedef std::map<int, bool> BSAresultTable;  // BSA trial index --> success or failure
  BSAresultTable results;

  bool handshake = false;
  double BSA_timeout = 1e-5;
  bool auto_resend_BSANotifier;
  double current_trial_id;

 protected:
  virtual void initialize(int stage) override;
  virtual int numInitStages() const override { return 1; };
  virtual void standaloneInitializer();
  virtual void internodeInitializer();
  virtual void handleMessage(cMessage* msg) override;
  virtual void BubbleText(const char* txt);
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
  // virtual void  finish();
 public:
  virtual void setMax_buffer(int buffer);
  HoMController();
};

}  // namespace modules
}  // namespace quisp

#endif /* QUISP_MODULES_HOM_CONTROLLER_H_ */
