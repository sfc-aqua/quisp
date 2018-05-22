/** \file EPPS_pair_source.h
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/30
 *
 *  \brief EPPS_pair_source
 */
#ifndef MODULES_EPPS_PAIR_SOURCE_H_
#define MODULES_EPPS_PAIR_SOURCE_H_

#include <vector>
#include <omnetpp.h>
#include "../classical_messages_m.h"
#include "../PhotonicQubit_m.h"

using namespace omnetpp;

typedef struct _entangledPhotons{
  PhotonicQubit *qubitOne;
  PhotonicQubit *qubitTwo;
} entangledPhotons;

/** \class EPPS_pair_source EPPS_pair_source.h
 *  \todo Documentation of the class header.
 *
 *  \brief EPPS_pair_source
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

#endif /* MODULES_EPPS_PAIR_SOURCE_H_ */
