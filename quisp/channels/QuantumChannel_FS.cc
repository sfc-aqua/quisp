/** \file QuantumChannel.cc
 *
 *  \brief QuantumChannel
 */
#include <omnetpp.h>
#include <stdexcept>
#include "PhotonicQubit_m.h"
#include <math.h>
#include "FSChannel.h"


using namespace omnetpp;
using namespace quisp::messages;


namespace channels {

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

    double distance = 0;  // in m
    double lambda = 0;
    double Dt = 0;
    double Dr = 0;
    double r0 = 0;
    double beta = 0;
    double A0 = 0;

    //calculated in the code from the parameters above
    double theta_diff = 0;
    double theta_atm = 0;
    double Aatm = 0;
    double attenuation_dB = 0;
    double attenuation_rate = 0;
};

Define_Channel(QuantumChannel_FS);

QuantumChannel_FS::QuantumChannel_FS() {}



void QuantumChannel_FS::initialize() {
  FSChannel::initialize();
  distance = par("distance");  // in m


}

cChannel::Result QuantumChannel_FS::processMessage(cMessage *msg, const SendOptions &options, simtime_t t) {
  PhotonicQubit *q = dynamic_cast<PhotonicQubit *>(msg);
  if (q == nullptr) {
    throw new cRuntimeError("something other than photonic qubit is sent through quantum channel");
  }

  if (!getLOS()) q->setLost(true);
  return {false,getDelay(),0};
  }

void QuantumChannel_FS::validateParameters() {

}

double QuantumChannel_FS::calculateLossRate() {
    lambda = par("wavelength");
    Dt = par("transmitter_telescope_diameter");
    Dr = par("receiver_telescope_diameter");
    r0 = par("Fried_parameter");
    beta = par("elevation_angle");
    A0 = par("atmospheric_attenuation_zenith");

    theta_diff = 2.44*lambda/Dt;
    theta_atm = 2.1*lambda/r0;
    Aatm = A0/sin(beta);
    attenuation_dB = ((pow(theta_diff,2) + pow(theta_atm,2))/(pow(Dr,2))) * pow(distance,2) * pow(10,Aatm/10); // from 10.1038/s42005-022-01123-7
    attenuation_rate = 1/pow(10,attenuation_dB/10);
    return attenuation_rate;
}


}  // namespace quisp::channels
