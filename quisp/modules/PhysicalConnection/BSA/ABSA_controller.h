#ifndef QUISP_MODULES_ABSA_CONTROLLER_H_
#define QUISP_MODULES_ABSA_CONTROLLER_H_

#include <PhotonicQubit_m.h>
#include <classical_messages_m.h>
#include <omnetpp.h>
#include <vector>

using namespace omnetpp;
using namespace quisp::messages;

namespace quisp {
namespace modules {

/** \class ABSAController ABSA_Controller.h
 *  \todo Documentation of the class header.
 *  \note How about if two nodes have imbalanced buffers?
 *        Maybe use unused qnic (which is ought to be used for another path)?
 *
 *  \brief ABSAController
 */
class ABSAController : public cSimpleModule {
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

  int ABSAtimingNotifier_type = 4;
  int PathSelection_type = 1;
  int PhotonicQubit_type = 100;

  bool receiver, passive;
  int qnic_index = -1;
  int qnic_address = -1;

  int* ABSAresults;
  typedef std::map<int, bool> ABSAresultTable;
  ABSAresultTable results;

  bool handshake = false;
  double ABSA_timeout = 1e-5;
  bool auto_resend_ABSANotifier;
  double current_trial_id;

 protected:
  virtual void initialize(int stage) override;
  virtual int numInitStages() const override { return 1; };
  virtual void standaloneInitializer();
  virtual void handleMessage(cMessage* msg) override;
  virtual void BubbleText(const char* txt);
  virtual double calculateEmissionStartTime(double timing, double distance_to_node, double c);
  virtual double calculateTimeToTravel(double distance, double c);
  virtual ABSMtimingNotifier* generateNotifier(double time, double speed_of_light_in_channel, double distance_to_neighbor, int destAddr, double accepted_burst_interval,
                                              int photon_detection_per_sec, int max_buffer);
  virtual CombinedABSAresults* generateNotifier_c(double time, double speed_of_light_in_channel, double distance_to_neighbor, int destAddr, double accepted_burst_interval,
                                                 int photon_detection_per_sec, int max_buffer);
  virtual cModule* getQNode();
  virtual void checkNeighborAddress();
  virtual void checkNeighborBuffer();
  virtual void updateIDE_Parameter();
  virtual void sendNotifiers();
  virtual void pushToABSAresults(bool attempt_success);
  virtual int getStoredABSAresultsSize();
  virtual void clearABSAresults();
  virtual void sendABSAresultsToNeighbors();
  // virtual void  finish();
 public:
  virtual void setMax_buffer(int buffer);
  ABSAController();
};

}  // namespace modules
}  // namespace quisp

#endif /* QUISP_MODULES_HOM_CONTROLLER_H_ */
