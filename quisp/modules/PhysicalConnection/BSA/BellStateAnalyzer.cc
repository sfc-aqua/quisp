/** \file BellStateAnalyzer.cc
 *  \authors cldurand,takaakimatsuo
 *
 *  \brief BellStateAnalyzer
 */
#include <PhotonicQubit_m.h>
#include <messages/classical_messages.h>
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
 *
 *  \brief BellStateAnalyzer
 */
class BellStateAnalyzer : public cSimpleModule {
 private:
  // for performance analysis
  long n_res = 0;  ///< The number of resources for performance analysis
  simsignal_t GOD_num_resSignal;  ///< The number of resources for signaling

  // parameters
  double darkcount_probability;
  bool left_last_photon_detected;
  bool right_last_photon_detected;

  // If this is true, send BSA finish and accumulated results to neigbor nodes.
  // If it's false, just send accumulate result in HOM Controller
  bool send_result;
  double required_precision;  ///< Precision of photon arrivial time // 1.5ns
  simtime_t left_arrived_at;

  bool left_photon_Xerr;
  bool left_photon_Zerr;
  bool left_photon_lost;
  StationaryQubit *left_statQubit_ptr;  ///< Instance of qubit memory of left node

  simtime_t right_arrived_at;
  bool right_photon_Xerr;
  bool right_photon_Zerr;
  bool right_photon_lost;
  StationaryQubit *right_statQubit_ptr;  ///< Instance of qubit memory of right node

  int count_X = 0, count_Y = 0, count_Z = 0, count_I = 0, count_L = 0, count_total = 0;  // for debug

  // True: Finish this trial of BSA
  bool this_trial_done = false;

  // The probability of BSA success. Maximum probability of success in linear optics is 0.5 and detector probability is 0.8.
  double BSAsuccess_rate = 0.5 * 0.8 * 0.8;
  int left_count, right_count = 0;
  int DEBUG_darkcount_left = 0;
  int DEBUG_darkcount_right = 0;
  int DEBUG_darkcount_both = 0;
  int DEBUG_success = 0;
  int DEBUG_total = 0;

 protected:
  virtual void initialize();
  virtual void handleMessage(cMessage *msg);
  virtual void forDEBUG_countErrorTypes(cMessage *msg);
  virtual void sendBSAresult(bool result, bool last);
  virtual void initializeVariables();
  virtual void GOD_setCompletelyMixedDensityMatrix();
  virtual void GOD_updateEntangledInfoParameters_of_qubits();
};

Define_Module(BellStateAnalyzer);

void BellStateAnalyzer::initialize() {
  GOD_num_resSignal = registerSignal("Num_Bell_state");

  darkcount_probability = par("darkcount_probability");
  required_precision = par("required_precision");
  left_arrived_at = -1;
  right_arrived_at = -1;
  left_last_photon_detected = false;
  right_last_photon_detected = false;
  send_result = false;
  left_photon_Xerr = false;
  left_photon_Zerr = false;
  right_photon_Xerr = false;
  right_photon_Zerr = false;
  left_statQubit_ptr = nullptr;
  right_statQubit_ptr = nullptr;
  right_photon_lost = false;
  left_photon_lost = false;
}

/**
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
    bubble("Next round!");
  }

  if (msg->arrivedOn("fromHOM_quantum_port$i", 0)) {
    left_arrived_at = simTime();
    left_statQubit_ptr = const_cast<StationaryQubit *>(check_and_cast<const StationaryQubit *>(photon->getEntangled_with()));
    left_photon_Xerr = photon->getPauliXerr();
    left_photon_Zerr = photon->getPauliZerr();
    left_photon_lost = photon->getPhotonLost();
    if (photon->getFirst()) {
      left_last_photon_detected = false;
    }
    if (photon->getLast()) {
      left_last_photon_detected = true;
    }
    left_count++;
  } else if (msg->arrivedOn("fromHOM_quantum_port$i", 1)) {
    right_arrived_at = simTime();
    right_statQubit_ptr = const_cast<StationaryQubit *>(check_and_cast<const StationaryQubit *>(photon->getEntangled_with()));
    right_photon_Xerr = photon->getPauliXerr();
    right_photon_Zerr = photon->getPauliZerr();
    right_photon_lost = photon->getPhotonLost();
    if (photon->getFirst()) {
      right_last_photon_detected = false;
    }
    if (photon->getLast()) {
      right_last_photon_detected = true;
    }
    right_count++;
  } else {
    error("This shouldn't happen....! Only 2 connections to the BSA allowed");
  }

  if ((right_last_photon_detected || left_last_photon_detected)) {
    send_result = true;
  }

  // Just for debugging purpose
  forDEBUG_countErrorTypes(msg);

  double difference = (left_arrived_at - right_arrived_at).dbl();

  if (this_trial_done == true) {
    bubble("dumping result");
    // No need to do anything. Just ignore the BSA result for this shot 'cause the trial is over and photons will only arrive from a single node anyway.
    delete msg;
    return;
  } else if ((left_arrived_at != -1 && right_arrived_at != -1) && std::abs(difference) <= (required_precision)) {
    // Both arrived perfectly fine

    // Even if we have 2 photons, whether we success entangling the qubits or not is probablistic.
    double rand = dblrand();
    double darkcount_left = dblrand();
    double darkcount_right = dblrand();

    if ((rand < BSAsuccess_rate && !right_photon_lost && !left_photon_lost) /*No qubit lost*/ ||
        (!right_photon_lost && left_photon_lost && darkcount_left < darkcount_probability) /*Got rigt, darkcount left*/ ||
        (right_photon_lost && !left_photon_lost && darkcount_right < darkcount_probability) /*Got left, darkcount right*/ ||
        (right_photon_lost && left_photon_lost && darkcount_left < darkcount_probability && darkcount_right < darkcount_probability) /*Darkcount right left*/) {
      if (!right_photon_lost && (left_photon_lost && darkcount_left <= darkcount_probability)) {
        DEBUG_darkcount_left++;
        GOD_setCompletelyMixedDensityMatrix();
        sendBSAresult(false, send_result);
      } else if (!left_photon_lost && (right_photon_lost && darkcount_right <= darkcount_probability)) {
        DEBUG_darkcount_right++;
        GOD_setCompletelyMixedDensityMatrix();
        sendBSAresult(false, send_result);
      } else if ((left_photon_lost && darkcount_left <= darkcount_probability) && (right_photon_lost && darkcount_right <= darkcount_probability)) {
        DEBUG_darkcount_both++;
        GOD_setCompletelyMixedDensityMatrix();
        sendBSAresult(false, send_result);
      } else {
        bubble("Success...!");
        DEBUG_success++;
        GOD_updateEntangledInfoParameters_of_qubits();

        // succeeded because both reached, and both clicked
        sendBSAresult(false, send_result);
      }
    } else {
      // we also need else if for darkcount....
      bubble("Failed...!");
      // just failed because only 1 detector clicked while both reached
      sendBSAresult(true, send_result);
    }
    DEBUG_total++;

    initializeVariables();

  } else if ((left_arrived_at != -1 && right_arrived_at != -1) && std::abs(difference) > (required_precision)) {
    // Both qubits arrived, but the timing was bad.
    bubble("Emission Timing Failed");
    initializeVariables();
    sendBSAresult(true, send_result);
  } else {
    // Just waiting for the other qubit to arrive.
    bubble("Waiting...");
  }

  delete msg;
}

void BellStateAnalyzer::initializeVariables() {
  left_arrived_at = -1;
  right_arrived_at = -1;
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
  if (!sendresults) {
    BSAresult *pk = new BSAresult("BsaResult");
    pk->setEntangled(result);
    send(pk, "toHOMController_port");
  } else {
    // Was the last photon. End pulse detected.
    BSAfinish *pk = new BSAfinish("BsaFinish");
    pk->setKind(7);
    pk->setEntangled(result);
    send(pk, "toHOMController_port");
    bubble("trial done now");
    this_trial_done = true;
  }
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

void BellStateAnalyzer::GOD_setCompletelyMixedDensityMatrix() {
  left_statQubit_ptr->setCompletelyMixedDensityMatrix();
  right_statQubit_ptr->setCompletelyMixedDensityMatrix();
}

/* Error on flying qubit with a successful BSA propagates to its original stationary qubit. */
void BellStateAnalyzer::GOD_updateEntangledInfoParameters_of_qubits() {
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
}

}  // namespace modules
}  // namespace quisp
