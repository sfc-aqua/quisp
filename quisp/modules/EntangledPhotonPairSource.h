/** \file EntangledPhotonPairSource.h
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/30
 *
 *  \brief EntangledPhotonPairSource
 */
#ifndef QUISP_MODULES_EPPS_H_
#define QUISP_MODULES_EPPS_H_

#include <PhotonicQubit_m.h>
#include <classical_messages_m.h>
#include <omnetpp.h>
#include <vector>

using namespace omnetpp;
using namespace quisp::messages;

namespace quisp {
namespace modules {

typedef struct {
  PhotonicQubit* qubitOne;
  PhotonicQubit* qubitTwo;
} entangledPhotons;

/** \class EntangledPhotonPairSource EntangledPhotonPairSource.h
 *
 *  \brief Entangled Photons Pairs Source
 *
 *  \see https://www.nist.gov/information-technology-laboratory/entangled-photon-pair-sources
 */
class EntangledPhotonPairSource : public cSimpleModule {
 private:
  // int myAddress;
  double error_rate;
  double emission_std;
  double Y_error_ratio;
  double X_error_ratio;
  double Z_error_ratio;

 protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage* msg) override;
  virtual void BubbleText(const char* txt);
  virtual PhotonicQubit* generateEntangledPhotons();
  virtual cModule* getSPDCNode();

 public:
  double frequency;
  virtual double getEmissionFrequency();
  virtual void emitPhotons();
};

}  // namespace modules
}  // namespace quisp

#endif /* QUISP_MODULES_EPPS_H_ */
