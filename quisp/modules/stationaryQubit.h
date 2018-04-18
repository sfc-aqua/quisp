/*
 * bufferQubit.h
 *
 *  Created on: 2018/03/14
 *      Author: takaakimatsuo
 */

#ifndef MODULES_STATIONARYQUBIT_H_
#define MODULES_STATIONARYQUBIT_H_
#include "../PhotonicQubit_m.h"
using namespace omnetpp;


class stationaryQubit : public cSimpleModule
{
    public:
        bool pauliXerr;//Bit flip error
        bool pauliZerr;//Phase error
        bool nonPaulierr;//completely mixed and so on.
        bool nonPaulierrTwo;
        int NodeEntangledWith;//Entangled pair's node-level address. -1 if not entangled
        int QNICEntangledWith;//Entangled pair's QNIC-level address
        int stationaryQubitEntangledWith;//Entangled pair's bufferQubit-level address
        bool isBusy;//free or reserved
        double std;

        virtual bool checkBusy();
        virtual bool emitPhoton(int pulse);
        virtual void setFree();
    private:
        int stationaryQubit_address;
        int node_address;
        int qnic_address;
        PhotonicQubit *photon;

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual PhotonicQubit *generateEntangledPhoton();
        virtual void setBusy();
        virtual void setEntangledPartnerInfo(int node_address, int qnic_index, int qubit_index);
};


#endif /* MODULES_BUFFERQUBIT_H_ */
