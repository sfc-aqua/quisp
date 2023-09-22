/** \file QuantumChannel.cc
 *
 *  \brief QuantumChannel
 */
#include <omnetpp.h>
#include <stdexcept>
#include <unsupported/Eigen/MatrixFunctions>
#include "PhotonicQubit_m.h"
#include "omnetpp/cexception.h"
#include "FiberChannel.h"

using namespace Eigen;
using namespace omnetpp;
using namespace quisp::messages;

namespace quisp::channels {

/* The sum of Z, X and Y error rate equates to error_rate. Value could potentially between 0 ~ 1. */
struct channel_error_model {
  double error_rate;  // total error rate
  double z_error_rate;
  double x_error_rate;
  double y_error_rate;
  double loss_rate;
};

/** \class QuantumChannel QuantumChannel.cc
 *
 *  \brief QuantumChannel
 */
class QuantumChannel : public FiberChannel {
 public:
  QuantumChannel();
  // member variables
  channel_error_model err;
  double distance = 0;  // in km

 protected:
  virtual void initialize() override;
  virtual cChannel::Result processMessage(cMessage *msg, const SendOptions &options, simtime_t t) override;

 private:
  void validateParameters();
  MatrixXd transition_to_the_distance;
};

Define_Channel(QuantumChannel);

QuantumChannel::QuantumChannel() : transition_to_the_distance(5, 5) {}

void QuantumChannel::initialize() {
  FiberChannel::initialize();
  distance = par("distance");  // in km
  err.loss_rate = par("channel_loss_rate");
  err.x_error_rate = par("channel_x_error_rate");
  err.y_error_rate = par("channel_y_error_rate");
  err.z_error_rate = par("channel_z_error_rate");
  err.error_rate = err.x_error_rate + err.y_error_rate + err.z_error_rate + err.loss_rate;
  validateParameters();

  MatrixXd transition_matrix(5, 5);
  // clang-format off
  transition_matrix << 1 - err.error_rate,  err.x_error_rate,   err.z_error_rate,   err.y_error_rate,   err.loss_rate,
                       err.x_error_rate,    1 - err.error_rate, err.y_error_rate,   err.z_error_rate,   err.loss_rate,
                       err.z_error_rate,    err.y_error_rate,   1 - err.error_rate, err.x_error_rate,   err.loss_rate,
                       err.y_error_rate,    err.z_error_rate,   err.x_error_rate,   1 - err.error_rate, err.loss_rate,
                       0,                   0,                  0,                  0,                  1;
  // clang-format on

  MatrixPower<MatrixXd> transition_matrix_to_the_power(transition_matrix);
  transition_to_the_distance = transition_matrix_to_the_power(distance);
}

cChannel::Result QuantumChannel::processMessage(cMessage *msg, const SendOptions &options, simtime_t t) {
  PhotonicQubit *q = dynamic_cast<PhotonicQubit *>(msg);
  if (q == nullptr) {
    throw new cRuntimeError("something other than photonic qubit is sent through quantum channel");
  }

  MatrixXd probability_vector(1, 5);  // I, X, Z, Y, Photon Lost
  if (q->isLost()) {
    probability_vector << 0, 0, 0, 0, 1;  // Photon already lost due to the coupling lost.
  } else {
    probability_vector << 1, 0, 0, 0, 0;  // No error
  }
  MatrixXd output_probability_vector(1, 5);
  output_probability_vector = probability_vector * transition_to_the_distance;

  // |-- no error --|-- x_error --|-- z_error --|-- y_error --|-- lost --|
  double no_error_ceil = output_probability_vector(0, 0);
  double x_error_ceil = no_error_ceil + output_probability_vector(0, 1);
  double z_error_ceil = x_error_ceil + output_probability_vector(0, 2);
  double y_error_ceil = z_error_ceil + output_probability_vector(0, 3);
  double lost_ceil = y_error_ceil + output_probability_vector(0, 4);

  double rand = dblrand();
  if (rand < no_error_ceil) {
    // Qubit will end up with no error
  } else if (rand < x_error_ceil) {
    // X error
    q->getQubitRefForUpdate()->noiselessX();
    q->setXError(true);
  } else if (rand < z_error_ceil) {
    // Z error
    q->getQubitRefForUpdate()->noiselessZ();
    q->setZError(true);
  } else if (rand < y_error_ceil) {
    // Y error
    q->getQubitRefForUpdate()->noiselessX();
    q->getQubitRefForUpdate()->noiselessZ();
    q->setXError(true);
    q->setZError(true);
  } else {
    // photon is lost
    q->setLost(true);
  }

  return {false, getDelay(), 0};
}

void QuantumChannel::validateParameters() {
  if (err.error_rate < 0 || 1 < err.error_rate) {
    throw cRuntimeError("quantum channel has invalid total error rate");
  }
  if (err.x_error_rate < 0 || 1 < err.x_error_rate) {
    throw cRuntimeError("quantum channel has invalid x error rate");
  }
  if (err.y_error_rate < 0 || 1 < err.y_error_rate) {
    throw cRuntimeError("quantum channel has invalid y error rate");
  }
  if (err.z_error_rate < 0 || 1 < err.z_error_rate) {
    throw cRuntimeError("quantum channel has invalid z error rate");
  }
  if (err.loss_rate < 0 || 1 < err.loss_rate) {
    throw cRuntimeError("quantum channel has invalid loss rate");
  }
}

}  // namespace quisp::channels
