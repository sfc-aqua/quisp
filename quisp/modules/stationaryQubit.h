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
        int NodeEntangledWith;//Entangled pair's node-level (global) address. -1 if not entangled
        int QNICEntangledWith;//Entangled pair's QNIC-level INDEX
        int stationaryQubitEntangledWith;//Entangled pair's bufferQubit-level INDEX
        bool isBusy;//free or reserved
        double std;//STANDARD DEVIATION

        virtual bool checkBusy();
        virtual void emitPhoton(int pulse);//int pulse = 1 indicates the beginning of the burst, -1 is the end.
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
