/** \todo clean Clean code when it is simple. */
/** \todo doc Write doxygen documentation. */
/*
 * EPPS_pair_source.h
 *
 *  Created on: 2018/03/30
 *      Author: takaakimatsuo
 */

#ifndef MODULES_EPPS_PAIR_SOURCE_H_
#define MODULES_EPPS_PAIR_SOURCE_H_

#include <vector>
#include <omnetpp.h>
#include "../classical_messages_m.h"
#include "../PhotonicQubit_m.h"

using namespace omnetpp;

typedef struct entangledPhotons{
  PhotonicQubit *qubitOne;
  PhotonicQubit *qubitTwo;
};

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
