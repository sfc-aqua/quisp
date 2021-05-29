/** \file BellStateAnalyzer.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *
 *  \brief BellStateAnalyzer
 */
#include <PhotonicQubit_m.h>
#include <classical_messages_m.h>
#include <modules/QRSA/HardwareMonitor/IHardwareMonitor.h>
#include <omnetpp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <vector>

using namespace omnetpp;
using namespace quisp::messages;

namespace quisp {
namespace modules {

/** \class BellStateAnalyzer BellStateAnalyzer.cc
 *  \todo Documentation of the class header.
 *
 *  \brief BellStateAnalyzer
 */
class BellStateAnalyzer : public cSimpleModule {
 private:
  // for performance analysis
  int n_res = 0;
  int trials = 0;
  simsignal_t GOD_num_resSignal;
  std::string BSA_perf_output_filename;
  std::vector<simtime_t> creation_time;
  simsignal_t average_num_trialSignal;
  std::vector<int> number_of_trials;
  int nwidth = 0;
  int duration = 1;
  // parameters
  double darkcount_probability;
  double loss_rate;
  double error_rate;
  // bool left_clicked;
  // bool right_click;
  bool left_last_photon_detected;
  bool right_last_photon_detected;
  bool send_result;
  double required_precision;  // 1.5ns
  simtime_t left_arrived_at;
  int left_photon_origin_node_address;
  int left_photon_origin_qnic_address;
  int left_photon_origin_qnic_type;
  int left_photon_origin_qubit_address;
  bool left_photon_Xerr;
  bool left_photon_Zerr;
  StationaryQubit *left_statQubit_ptr;
  simtime_t right_arrived_at;
  int right_photon_origin_node_address;
  int right_photon_origin_qnic_address;
  int right_photon_origin_qnic_type;
  int right_photon_origin_qubit_address;
  bool right_photon_Xerr;
  bool right_photon_Zerr;
  bool right_photon_lost;
  bool left_photon_lost;
  StationaryQubit *right_statQubit_ptr;
  int count_X = 0, count_Y = 0, count_Z = 0, count_I = 0, count_L = 0, count_total = 0;  // for debug
  // bool handshake = false;
  bool this_trial_done = false;
  double BSAsuccess_rate = 0.5 * 0.8 * 0.8;  // detector probability = 0.8
  int left_count, right_count = 0;
  int DEBUG_darkcount_left = 0;
  int DEBUG_darkcount_right = 0;
  int DEBUG_darkcount_both = 0;
  int DEBUG_success = 0;
  int DEBUG_total = 0;

 protected:
  virtual void initialize();
  virtual void finish();
  virtual void handleMessage(cMessage *msg);
  virtual bool isPhotonLost(cMessage *msg);
  virtual void forDEBUG_countErrorTypes(cMessage *msg);
  virtual void sendBSAresult(bool result, bool last);
  virtual void initializeVariables();
  virtual void GOD_setCompletelyMixedDensityMatrix();
  virtual void GOD_updateEntangledInfoParameters_of_qubits();
};

Define_Module(BellStateAnalyzer);

void BellStateAnalyzer::initialize() {
  // performance analysis
  GOD_num_resSignal = registerSignal("Num_Bell_state");
  // initialize parameters
  darkcount_probability = par("darkcount_probability");
  loss_rate = par("loss_rate");
  error_rate = par("error_rate");
  // duration = par("duration");
  required_precision = par("required_precision");
  left_arrived_at = -1;
  right_arrived_at = -1;
  left_last_photon_detected = false;
  right_last_photon_detected = false;
  send_result = false;
  left_photon_origin_node_address = -1;
  left_photon_origin_qnic_address = -1;
  left_photon_origin_qubit_address = -1;
  left_photon_origin_qnic_type = -1;
  right_photon_origin_node_address = -1;
  right_photon_origin_qnic_address = -1;
  right_photon_origin_qubit_address = -1;
  right_photon_origin_qnic_type = -1;
  left_photon_Xerr = false;
  left_photon_Zerr = false;
  right_photon_Xerr = false;
  right_photon_Zerr = false;
  left_statQubit_ptr = nullptr;
  right_statQubit_ptr = nullptr;
  right_photon_lost = false;
  left_photon_lost = false;
}

/*
 * Execute the BSA operation.
 * Input: msg is a "photon", with a few bits of info of its status.  msg arrives even if photon is lost; this msg will
 * indicate that.  Photon is assumed to be entangled with a stationary memory somewhere.  Photon has been updated to
 * include errors from the channel just prior to this call.  The memory does not need to be updated for memory
 * errors either before or during this operation; memory errors are only applied when gates are applied to that qubit or
 * when it is measured.
 * Output: none
 * Side effects: based on results of the BSA op, the density matrices of the two partner qubits are modified.
 * If the entanglement succeeds, each d.m. is updated with a pointer to its new entangled partner (our so-called "god channel"),
 * but the two d.m.s are _not_ merged into a single two-qubit d.m., allowing the sim to continue updating them
 * individually with errors as necessary.  If entanglement fails, the qubits are left independent.
 * Called twice: each photon arriving @BSA triggers this.  First one sets things provisionally using variables
 * local to this object (the BSA itself), second one completes and updates the actual qubits.
 */
void BellStateAnalyzer::handleMessage(cMessage *msg) {
  PhotonicQubit *photon = check_and_cast<PhotonicQubit *>(msg);
  if (photon->getFirst() && this_trial_done == true) {  // Next round started
    this_trial_done = false;
    left_arrived_at = -1;
    right_arrived_at = -1;
    right_last_photon_detected = false;
    left_last_photon_detected = false;
    send_result = false;
    right_count = 0;
    left_count = 0;
    EV << "------------------Next round!\n";
    bubble("Next round!");
  }

  if (msg->arrivedOn("fromHoM_quantum_port$i", 0)) {
    left_arrived_at = simTime();
    left_photon_origin_node_address = photon->getNodeEntangledWith();
    left_photon_origin_qnic_address = photon->getQNICEntangledWith();
    left_photon_origin_qubit_address = photon->getStationaryQubitEntangledWith();
    left_photon_origin_qnic_type = photon->getQNICtypeEntangledWith();
    left_statQubit_ptr = check_and_cast<StationaryQubit *>(photon->getEntangled_with());
    left_photon_Xerr = photon->getPauliXerr();
    left_photon_Zerr = photon->getPauliZerr();
    left_photon_lost = photon->getPhotonLost();
    // photon->setGODfree();
    if (photon->getFirst()) {
      left_last_photon_detected = false;
      // send_result = false;
    }
    if (photon->getLast()) {
      left_last_photon_detected = true;
      // send_result = true;
    }
    left_count++;
    // EV<<"Photon from Left arrived at = "<<simTime()<<"\n";
  } else if (msg->arrivedOn("fromHoM_quantum_port$i", 1)) {
    right_arrived_at = simTime();
    right_photon_origin_node_address = photon->getNodeEntangledWith();
    right_photon_origin_qnic_address = photon->getQNICEntangledWith();
    right_photon_origin_qubit_address = photon->getStationaryQubitEntangledWith();
    right_photon_origin_qnic_type = photon->getQNICtypeEntangledWith();
    // right_statQubit_ptr = photon->getEntangled_with();
    right_statQubit_ptr = check_and_cast<StationaryQubit *>(photon->getEntangled_with());
    right_photon_Xerr = photon->getPauliXerr();
    right_photon_Zerr = photon->getPauliZerr();
    right_photon_lost = photon->getPhotonLost();
    if (photon->getFirst()) {
      right_last_photon_detected = false;
      // send_result = false;
    }
    if (photon->getLast()) {
      right_last_photon_detected = true;
      // send_result = true;
    }
    right_count++;
    // EV<<"Right = "<<simTime()<<"\n";
  } else {
    error("This shouldn't happen....! Only 2 connections to the BSA allowed");
  }

  if ((right_last_photon_detected || left_last_photon_detected)) {
    send_result = true;
  }

  // Just for debugging purpose
  forDEBUG_countErrorTypes(msg);

  double difference = (left_arrived_at - right_arrived_at).dbl();  // Difference in arrival time
  // EV<<"!!!!!!!!!!!!!!!!!!!!!!!!!!this_trial_done == "<<this_trial_done<<"\n";
  if (this_trial_done == true) {
    bubble("dumping result");
    // No need to do anything. Just ignore the BSA result for this shot 'cause the trial is over and photons will only arrive from a single node anyway.
    delete msg;
    return;
  } else if ((left_arrived_at != -1 && right_arrived_at != -1) && std::abs(difference) <= (required_precision)) {
    // Both arrived perfectly fine
    // bool lost = isPhotonLost(msg);

    double rand = dblrand();  // Even if we have 2 photons, whether we success entangling the qubits or not is probablistic.
    double darkcount_left = dblrand();
    double darkcount_right = dblrand();

    if ((rand < BSAsuccess_rate && !right_photon_lost && !left_photon_lost) /*No qubit lost*/ ||
        (!right_photon_lost && left_photon_lost && darkcount_left < darkcount_probability) /*Got rigt, darkcount left*/ ||
        (right_photon_lost && !left_photon_lost && darkcount_right < darkcount_probability) /*Got left, darkcount right*/ ||
        (right_photon_lost && left_photon_lost && darkcount_left < darkcount_probability && darkcount_right < darkcount_probability) /*Darkcount right left*/) {
      if (!right_photon_lost && (left_photon_lost && darkcount_left <= darkcount_probability)) {
        // error("Dark count :)");
        DEBUG_darkcount_left++;
        // std::cout<<"CM Entangling "<<left_statQubit_ptr->getFullName()<<" in "<<left_statQubit_ptr->getParentModule()->getFullName()<<"in
        // node["<<left_statQubit_ptr->node_address<<"] with "<<right_statQubit_ptr->getFullName()<<" in "<<left_statQubit_ptr->getParentModule()->getFullName()<<"in
        // node["<<right_statQubit_ptr->node_address<<"]\n";
        GOD_setCompletelyMixedDensityMatrix();
        sendBSAresult(false, send_result);
      } else if (!left_photon_lost && (right_photon_lost && darkcount_right <= darkcount_probability)) {
        // error("Dark count :)");
        // std::cout<<"CM Entangling "<<left_statQubit_ptr->getFullName()<<" in "<<left_statQubit_ptr->getParentModule()->getFullName()<<"in
        // node["<<left_statQubit_ptr->node_address<<"] with "<<right_statQubit_ptr->getFullName()<<" in "<<left_statQubit_ptr->getParentModule()->getFullName()<<"in
        // node["<<right_statQubit_ptr->node_address<<"]\n";
        DEBUG_darkcount_right++;
        GOD_setCompletelyMixedDensityMatrix();
        sendBSAresult(false, send_result);
      } else if ((left_photon_lost && darkcount_left <= darkcount_probability) && (right_photon_lost && darkcount_right <= darkcount_probability)) {
        // error("Dark count :)");
        // std::cout<<"CM Entangling "<<left_statQubit_ptr->getFullName()<<" in "<<left_statQubit_ptr->getParentModule()->getFullName()<<"in
        // node["<<left_statQubit_ptr->node_address<<"] with "<<right_statQubit_ptr->getFullName()<<" in "<<left_statQubit_ptr->getParentModule()->getFullName()<<"in
        // node["<<right_statQubit_ptr->node_address<<"]\n";
        DEBUG_darkcount_both++;
        GOD_setCompletelyMixedDensityMatrix();
        sendBSAresult(false, send_result);
      } else {
        bubble("Success...!");
        DEBUG_success++;
        GOD_updateEntangledInfoParameters_of_qubits();
        sendBSAresult(false, send_result);  // succeeded because both reached, and both clicked
      }

    }  // we also need else if for darkcount....
    else {
      bubble("Failed...!");
      // EV<<"rand = "<<rand<<" <"<<BSAsuccess_rate;

      // std::cout<<"Failed Entangling "<<left_statQubit_ptr->getFullName()<<" in "<<left_statQubit_ptr->getParentModule()->getFullName()<<"in
      // node["<<left_statQubit_ptr->node_address<<"] with "<<right_statQubit_ptr->getFullName()<<" in "<<right_statQubit_ptr->getParentModule()->getFullName()<<"in
      // node["<<right_statQubit_ptr->node_address<<"]\n";

      sendBSAresult(true, send_result);  // just failed because only 1 detector clicked while both reached
    }
    DEBUG_total++;

    initializeVariables();

  } else if ((left_arrived_at != -1 && right_arrived_at != -1) && std::abs(difference) > (required_precision)) {
    // Both qubits arrived, but the timing was bad.
    bubble("Emission Timing Failed");
    initializeVariables();
    sendBSAresult(true, send_result);
  } else {
    bubble("Waiting...");
    /*if(photon->getLast() && (left_count == 0 || right_count == 0)){//This is wrong, because it will ignore the 2nd photon arrival if both of the photons are the first and last.
        //sendBSAresult(true,send_result);
        bubble("Ehhh");
        EV<<"left_count = "<<left_count<<", right_count = "<<right_count;
    }*/
    // Just waiting for the other qubit to arrive.
  }

  delete msg;
}

void BellStateAnalyzer::initializeVariables() {
  left_arrived_at = -1;
  left_photon_origin_node_address = -1;
  left_photon_origin_qnic_address = -1;
  left_photon_origin_qubit_address = -1;
  left_photon_origin_qnic_type = -1;
  right_arrived_at = -1;
  right_photon_origin_node_address = -1;
  right_photon_origin_qnic_address = -1;
  right_photon_origin_qubit_address = -1;
  right_photon_origin_qnic_type = -1;
  left_photon_lost = false;
  left_photon_lost = false;
  right_photon_Xerr = false;
  right_photon_Zerr = false;
  left_photon_Xerr = false;
  left_photon_Zerr = false;
  left_count = 0;
  right_count = 0;
  left_statQubit_ptr = nullptr;
  right_statQubit_ptr = nullptr;
}

void BellStateAnalyzer::sendBSAresult(bool result, bool sendresults) {
  // result could be false positive (actually ok but recognized as ng),
  // false negative (actually ng but recognized as ok) due to darkcount
  // true positive and true negative is no problem.
  // std::cout<<"send?="<<sendresults<<"___________________________________\n";
  if (!sendresults) {
    BSAresult *pk = new BSAresult("BsaResult");
    // std::cout<<"send result to HoM___\n";
    pk->setEntangled(result);
    send(pk, "toHoMController_port");
  } else {  // Was the last photon. End pulse detected.
    BSAfinish *pk = new BSAfinish("BsaFinish");
    pk->setKind(7);
    // std::cout<<"send last result to HoM___\n";
    pk->setEntangled(result);
    send(pk, "toHoMController_port");
    bubble("trial done now");
    this_trial_done = true;
    // EV<<"!!!!!!!!!!!!!!!over!!!!!!!!!!!this_trial_done == "<<this_trial_done<<"\n";
  }
}

void BellStateAnalyzer::finish() {
  std::cout << "total = " << DEBUG_total << "\n";
  std::cout << "Success = " << DEBUG_success << "\n";
  std::cout << "darkcount_count_left = " << DEBUG_darkcount_left << ", darkcount_count_right =" << DEBUG_darkcount_right << ", darkcount_count_both = " << DEBUG_darkcount_both
            << "\n";
  std::cout << "total BSA performance"
            << "\n";
  // filename for recoding bsa performance
  // std::string file_name = BSA_perf_output_filename;
  // int file_size = file_name.size();
  // create file
  std::string time_duration = std::to_string(duration);
  std::string file_name = "num_trials" + time_duration;
  std::ofstream bsa_stats(file_name, std::ios_base::app);

  // 1. Bell pair creation time (average and std)
  // receive photons - apply BSM - return result
  // bsa_stats<<"s\n";
  for (int i = 0; i < number_of_trials.size(); i++) {
    bsa_stats << number_of_trials[i] << "\n";
  }
  // bsa_stats<<"f\n";
  // 2. The number of bell pairs in total
  bsa_stats.close();
}

void BellStateAnalyzer::forDEBUG_countErrorTypes(cMessage *msg) {
  PhotonicQubit *q = check_and_cast<PhotonicQubit *>(msg);
  if (q->getPauliXerr() && q->getPauliZerr()) {
    count_Y++;
  } else if (q->getPauliXerr() && !q->getPauliZerr()) {
    count_X++;
  } else if (!q->getPauliXerr() && q->getPauliZerr()) {
    count_Z++;
  } else if (q->getPhotonLost()) {
    count_L++;
  } else {
    count_I++;
  }
  count_total++;
  EV << "Y%=" << (double)count_Y / (double)count_total << ", X%=" << (double)count_X / (double)count_total << ", Z%=" << (double)count_Z / (double)count_total
     << ", L%=" << (double)count_L / (double)count_total << ", I% =" << (double)count_I / (double)count_total << "\n";
}

bool BellStateAnalyzer::isPhotonLost(cMessage *msg) {
  PhotonicQubit *q = check_and_cast<PhotonicQubit *>(msg);
  if (q->getPhotonLost()) {
    return true;  // Lost
  } else {
    return false;
  }
  delete msg;
}

void BellStateAnalyzer::GOD_setCompletelyMixedDensityMatrix() {
  // error("Hrtr");
  // std::cout<<"Darkcount CM "<<left_statQubit_ptr<<", "<<right_statQubit_ptr<<"\n";
  left_statQubit_ptr->setCompletelyMixedDensityMatrix();
  right_statQubit_ptr->setCompletelyMixedDensityMatrix();
}

/*Error on flying qubit with a successful BSA propagates to its original stationary qubit. */
void BellStateAnalyzer::GOD_updateEntangledInfoParameters_of_qubits() {
  // std::cout<<"Entangling "<<left_statQubit_ptr->getFullName()<<" in "<<left_statQubit_ptr->getParentModule()->getFullName()<<"in node["<<left_statQubit_ptr->node_address<<"]
  // with "<<right_statQubit_ptr->getFullName()<<" in "<<right_statQubit_ptr->getParentModule()->getFullName()<<"in node["<<right_statQubit_ptr->node_address<<"]\n";

  left_statQubit_ptr->setEntangledPartnerInfo(right_statQubit_ptr);
  // If Photon had an X error, Add X error to the stationary qubit.
  if (left_photon_Xerr) left_statQubit_ptr->addXerror();
  if (left_photon_Zerr) left_statQubit_ptr->addZerror();

  right_statQubit_ptr->setEntangledPartnerInfo(left_statQubit_ptr);
  if (right_photon_Xerr) right_statQubit_ptr->addXerror();
  if (right_photon_Zerr) right_statQubit_ptr->addZerror();
  if (right_statQubit_ptr->entangled_partner == nullptr || left_statQubit_ptr->entangled_partner == nullptr) {
    std::cout << "Entangling failed\n";
    error("Entangling failed");
  }
  n_res++;
  emit(GOD_num_resSignal, n_res);
  // std::cout<<right_statQubit_ptr<<", node["<<right_statQubit_ptr->node_address<<"] from qnic["<<right_statQubit_ptr->qnic_index<<"]\n";
  // std::cout<<(bool)(right_statQubit_ptr->entangled_partner==nullptr)<<" Right Entangled if ("<<false<<")\n";
  // std::cout<<left_statQubit_ptr<<", node["<<left_statQubit_ptr->node_address<<"] from qnic["<<left_statQubit_ptr->qnic_index<<"]\n";
  // std::cout<<(bool)(left_statQubit_ptr->entangled_partner==nullptr)<<" Left Entangled if ("<<false<<")\n";
}

}  // namespace modules
}  // namespace quisp
