/** \file QuantumChannel.cc
 *  \authors takaakimatsuo
 *
 *  \brief QuantumChannel
 */
#include <PhotonicQubit_m.h>
#include <omnetpp.h>
#include <unsupported/Eigen/MatrixFunctions>
#include <vector>

using namespace Eigen;
using namespace omnetpp;
using namespace quisp::messages;

namespace quisp {
namespace channels {

/*The sum of Z,X and Y error rate equates to pauli_error_rate. Value could potentially between 0 ~ 1. */
struct channel_error_model {
  double pauli_error_rate;  // Overall error rate
  double Z_error_rate;
  double X_error_rate;
  double Y_error_rate;
};

/** \class QuantumChannel QuantumChannel.cc
 *
 *  \brief QuantumChannel
 */
class QuantumChannel : public cDatarateChannel {
 public:
  channel_error_model err;
  double photon_loss_rate;
  double distance = 0;  // in km
 private:
  double No_error_ceil;
  double X_error_ceil;
  double Y_error_ceil;
  double Z_error_ceil;
  double Lost_ceil;
  int DEBUG_darkcount_count = 0;
  MatrixXd Q_to_the_distance;
  virtual void initialize() override;
  virtual cChannel::Result processMessage(cMessage *msg, const SendOptions &options, simtime_t t) override;

 public:
  QuantumChannel();
};

Define_Channel(QuantumChannel)

    QuantumChannel::QuantumChannel()
    : Q_to_the_distance(5, 5) {}

void QuantumChannel::initialize() {
  cDatarateChannel::initialize();
  distance = par("distance");  // in km
  photon_loss_rate = par("channel_loss_rate");
  err.X_error_rate = par("channel_x_error_rate");
  err.Y_error_rate = par("channel_y_error_rate");
  err.Z_error_rate = par("channel_z_error_rate");
  err.pauli_error_rate = err.X_error_rate + err.Y_error_rate + err.Z_error_rate + photon_loss_rate;

  MatrixXd Transition_matrix(5, 5);

  Transition_matrix << 1 - err.pauli_error_rate, err.X_error_rate, err.Z_error_rate, err.Y_error_rate, photon_loss_rate, err.X_error_rate, 1 - err.pauli_error_rate,
      err.Y_error_rate, err.Z_error_rate, photon_loss_rate, err.Z_error_rate, err.Y_error_rate, 1 - err.pauli_error_rate, err.X_error_rate, photon_loss_rate, err.Y_error_rate,
      err.Z_error_rate, err.X_error_rate, 1 - err.pauli_error_rate, photon_loss_rate, 0, 0, 0, 0, 1;

  MatrixPower<MatrixXd> Apow(Transition_matrix);
  Q_to_the_distance = Apow(distance);
}

cChannel::Result QuantumChannel::processMessage(cMessage *msg, const SendOptions &options, simtime_t t) {
  try {
    PhotonicQubit *q = check_and_cast<PhotonicQubit *>(msg);

    bool lost = q->isLost();

    // The photon may have an error when emitted.
    MatrixXd Initial_condition(1, 5);  // I, X, Z, Y, Photon Lost
    if (lost) {
      Initial_condition << 0, 0, 0, 0, 1;  // Photon already lost. Maybe by emission time. Not implemented though.
    } else {
      Initial_condition << 1, 0, 0, 0, 0;  // No error
    }
    MatrixXd Output_condition(1, 5);
    Output_condition = Initial_condition * Q_to_the_distance;

    No_error_ceil = Output_condition(0, 0);
    X_error_ceil = No_error_ceil + Output_condition(0, 1);
    Z_error_ceil = X_error_ceil + Output_condition(0, 2);
    Y_error_ceil = Z_error_ceil + Output_condition(0, 3);
    Lost_ceil = Y_error_ceil + Output_condition(0, 4);
    // Gives a random double between 0.0 ~ 1.0
    double rand = dblrand();
    if (rand < No_error_ceil) {
      // Qubit will end up with no error
    } else if (No_error_ceil <= rand && rand < X_error_ceil && (No_error_ceil != X_error_ceil)) {
      // X error
      q->getQubitRefForUpdate()->gateX();
    } else if (X_error_ceil <= rand && rand < Z_error_ceil && (X_error_ceil != Z_error_ceil)) {
      // Z error
      q->getQubitRefForUpdate()->gateZ();
    } else if (Z_error_ceil <= rand && rand < Y_error_ceil && (Z_error_ceil != Y_error_ceil)) {
      // Y error
      q->getQubitRefForUpdate()->gateY();
    } else {
      // Photon was lost
      DEBUG_darkcount_count++;
      q->setLost(true);
    }
  } catch (std::exception &e) {
    EV << "Only PhotonicQubit is allowed in quantum channel";
  }
  return cChannel::Result();
}

}  // namespace channels
}  // namespace quisp
