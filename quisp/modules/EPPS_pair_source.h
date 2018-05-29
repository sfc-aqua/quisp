/** \file EPPS_pair_source.h
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/30
 *
 *  \brief EPPS_pair_source
 */
#ifndef QUISP_MODULES_EPPS_PAIR_SOURCE_H_
#define QUISP_MODULES_EPPS_PAIR_SOURCE_H_

#include <vector>
#include <omnetpp.h>
#include <classical_messages_m.h>
#include <PhotonicQubit_m.h>

using namespace omnetpp;

namespace quisp {
namespace modules {

typedef struct _entangledPhotons {
  PhotonicQubit *qubitOne;
  PhotonicQubit *qubitTwo;
} entangledPhotons;

/** \class EPPS_pair_source EPPS_pair_source.h
 *
 *  \brief Entangled Photons Pairs Source
 *
 *  \see https://www.nist.gov/information-technology-laboratory/entangled-photon-pair-sources
 */
class EPPS_pair_source : public cSimpleModule
{
    private:
        int myAddress;
        double error_rate;
        double emission_std;
        double Y_error_ratio;
        double X_error_ratio;
        double Z_error_ratio;

    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        virtual void BubbleText(const char* txt);
        virtual PhotonicQubit* generateEntangledPhotons();
        virtual cModule* getEPPSNode();

    public:
        double frequency;
        virtual double getEmissionFrequency();
        virtual void emitPhotons();
};

} // namespace modules
} // namespace quisp

#endif /* QUISP_MODULES_EPPS_PAIR_SOURCE_H_ */
