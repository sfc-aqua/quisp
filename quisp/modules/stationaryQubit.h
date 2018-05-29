/** \file stationaryQubit.h
 *  \todo org Organize namespaces
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/14
 *
 *  \brief stationaryQubit
 */
#ifndef MODULES_STATIONARYQUBIT_H_
#define MODULES_STATIONARYQUBIT_H_
#include <PhotonicQubit_m.h>
using namespace omnetpp;

#define STATIONARYQUBIT_PULSE_BEGIN 0x01
#define STATIONARYQUBIT_PULSE_END   0x02
#define STATIONARYQUBIT_PULSE_BOUND (STATIONARYQUBIT_PULSE_BEGIN|STATIONARYQUBIT_PULSE_END)

/** \class stationaryQubit stationaryQubit.h
 *
 *  \brief stationaryQubit
 */
class stationaryQubit : public cSimpleModule
{
    public:
        /** @name Errors
         *  @{
         */
        bool pauliXerr; /**< Bit flip error */
        bool pauliZerr; /**< Phase error. */
        /* For future use.
         * Completely mixed states, etc. */
        //bool nonPaulierr;
        //bool nonPaulierrTwo;
        //@}

        /** @name Entangled partner address
         *  @{                                  */
        /** Address node, or -1. */
        int NodeEntangledWith;
        /** Number of qNIC in node. */
        int QNICEntangledWith;
        /** Index of Qubit in qNIC. */
        int stationaryQubitEntangledWith;
        //@}

        /** Stationary Qubit is free or reserved. */
        bool isBusy;
        /** Standard deviation */
        double std;

        virtual bool checkBusy();
        virtual void setFree();

        /**
         * \brief Emit photon.
         * \param pulse is 1 for the beginning of the burst, 2 for the end.
         */
        virtual void emitPhoton(int pulse);

    private:
        /** @name Self address
         *  @{                   */
        int stationaryQubit_address;
        int node_address;
        int qnic_address;
        //@}
        PhotonicQubit *photon;

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual PhotonicQubit *generateEntangledPhoton();
        virtual void setBusy();
        virtual void setEntangledPartnerInfo(int node_address, int qnic_index, int qubit_index);
};

#endif /* MODULES_BUFFERQUBIT_H_ */
