/** \file QuantumChannel_FS.cc
 *
 *  \brief Free Space Quantum Channel
 */

#include <unsupported/Eigen/MatrixFunctions>
#include "CSVParser.h"
#include "FSChannel.h"

using namespace omnetpp;
using namespace Eigen;
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

/** \class QuantumChannel_FS QuantumChannel_FS.cc
 *
 *  \brief QuantumChannel_FS
 */
class QuantumChannel_FS : public FSChannel {
 public:
  QuantumChannel_FS();

 protected:
  virtual void initialize() override;
  virtual cChannel::Result processMessage(cMessage *msg, const SendOptions &options, simtime_t t) override;

 private:
  void validateParameters();
  double calculateLossRate();
  void recalculateChannelParameters() override;
  Matrix<double, 5, 5> transition_matrix;
  channel_error_model err;
  CSVParser *Aatm_CSV;

  // Loss model - see 10.1038/s42005-022-01123-7
  double distance = 0;  // in m
  double lambda = 0;
  double Dt = 0;
  double Dr = 0;
  double r0 = 0;
  double Aatm = 1;

  // calculated in the code from the parameters above
  double theta_diff = 0;
  double theta_atm = 0;
  double loss_rate = 0;
  double attenuation_rate = 0;

  // statistics
  //  simsignal_t channel_length = registerSignal("channel_length");
  //  simsignal_t channel_delay = registerSignal("channel_delay");
  //  simsignal_t channel_t = registerSignal("channel_t");
  //  simsignal_t channel_t_dB = registerSignal("channel_t_dB");
};

Define_Channel(QuantumChannel_FS);

QuantumChannel_FS::QuantumChannel_FS() {}

void QuantumChannel_FS::initialize() {
  FSChannel::initialize();
  distance = par("distance");
  Aatm_CSV = new CSVParser(par("Aatm_CSV"));
  err.loss_rate = calculateLossRate();
  err.x_error_rate = par("channel_x_error_rate");
  err.y_error_rate = par("channel_y_error_rate");
  err.z_error_rate = par("channel_z_error_rate");
  err.error_rate = err.x_error_rate + err.y_error_rate + err.z_error_rate + err.loss_rate;
  validateParameters();

  //clang-format off
  transition_matrix << 1 - err.error_rate, err.x_error_rate, err.z_error_rate, err.y_error_rate, err.loss_rate, err.x_error_rate, 1 - err.error_rate, err.y_error_rate,
      err.z_error_rate, err.loss_rate, err.z_error_rate, err.y_error_rate, 1 - err.error_rate, err.x_error_rate, err.loss_rate, err.y_error_rate, err.z_error_rate,
      err.x_error_rate, 1 - err.error_rate, err.loss_rate, 0, 0, 0, 0, 1;
  // clang-format on
}

cChannel::Result QuantumChannel_FS::processMessage(cMessage *msg, const SendOptions &options, simtime_t t) {
  recalculateChannelParameters();
  PhotonicQubit *q = dynamic_cast<PhotonicQubit *>(msg);
  if (checkLOS()) {
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
    output_probability_vector = probability_vector * transition_matrix;

    // |-- no error --|-- x_error --|-- z_error --|-- y_error --|-- lost --|
    double no_error_ceil = output_probability_vector(0, 0);
    double x_error_ceil = no_error_ceil + output_probability_vector(0, 1);
    double z_error_ceil = x_error_ceil + output_probability_vector(0, 2);
    double y_error_ceil = z_error_ceil + output_probability_vector(0, 3);

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
  } else
    q->setLost(true);

  return {false, getDelay(), 0};
}

void QuantumChannel_FS::validateParameters() {
  if (err.error_rate < 0 || 1 < err.error_rate) {
    throw cRuntimeError("quantum channel has invalid total error rate. If this is a free space channel, check that you are in far-field of the transmitting telescope.");
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
    throw cRuntimeError("quantum channel has invalid loss rate. If this is a free space channel, check that you are in far-field of the transmitting telescope.");
  }
}

double QuantumChannel_FS::calculateLossRate() {
  distance = par("distance");
  lambda = par("wavelength");
  Dt = par("transmitter_telescope_diameter");
  Dr = par("receiver_telescope_diameter");
  r0 = par("Fried_parameter");

  // hard-coded values from 10.1038/s42005-022-01123-7
  theta_diff = 1.27 * lambda / Dt;
  theta_atm = 2.1 * lambda / r0;
  attenuation_rate = ((pow(theta_diff, 2) + pow(theta_atm, 2)) / (pow(Dr, 2))) * pow(distance, 2) * Aatm;  // from 10.1038/s42005-022-01123-7
  loss_rate = 1 - 1 / attenuation_rate;

  // emit(channel_t,1/attenuation_rate);
  // emit(channel_t_dB,10*log10(1/attenuation_rate));

  return loss_rate;
}

void QuantumChannel_FS::recalculateChannelParameters() {
  FSChannel::recalculateChannelParameters();
  Aatm = Aatm_CSV->getPropertyAtTime(simTime().dbl());
  err.loss_rate = calculateLossRate();
  err.error_rate = err.x_error_rate + err.y_error_rate + err.z_error_rate + err.loss_rate;
  validateParameters();

  //clang-format off
  transition_matrix << 1 - err.error_rate, err.x_error_rate, err.z_error_rate, err.y_error_rate, err.loss_rate, err.x_error_rate, 1 - err.error_rate, err.y_error_rate,
      err.z_error_rate, err.loss_rate, err.z_error_rate, err.y_error_rate, 1 - err.error_rate, err.x_error_rate, err.loss_rate, err.y_error_rate, err.z_error_rate,
      err.x_error_rate, 1 - err.error_rate, err.loss_rate, 0, 0, 0, 0, 1;
  // clang-format on

  // emit(channel_length,par("distance").doubleValue());
  // emit(channel_delay,getDelay());
  // emit(channel_att,attenuation_rate);
  // emit(channel_att_dB,10*log10(attenuation_rate));
}

}  // namespace quisp::channels
