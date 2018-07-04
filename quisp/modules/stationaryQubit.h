/** \file stationaryQubit.h
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/14
 *
 *  \brief stationaryQubit
 */
#ifndef QUISP_MODULES_STATIONARYQUBIT_H_
#define QUISP_MODULES_STATIONARYQUBIT_H_

#include <PhotonicQubit_m.h>

using namespace omnetpp;
using namespace quisp::messages;

namespace quisp {
namespace modules {

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
        /** Address and type of qNIC in node. */
        int QNICEntangledWith;
        int QNICtypeEntangledWith;
        /** Index of Qubit in qNIC. */
        int stationaryQubitEntangledWith;
        /** Photon emitted at*/
        simtime_t emitted_time = -1;
        /** Stationary qubit last updated at*/
        simtime_t updated_time = -1;

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

        /**
         * \brief Single Qubit X measurement.
         * \param If a Z error, which affects the X-measurement, is present, then returns false. Otherwise it returns true. This is only for simulating error propagations.
         * New errors only occur when wrong measurement result is delivered for feed-forward (The error on the measured qubit propagates to the byproduct gate target qubit).
         */
        virtual bool measure_X();

        /**
         * \brief Single Qubit Y measurement.
         * \param If a Z error OR an X error, which affects the Y-measurement, is present, then returns false. Otherwise it returns true. This is only for simulating error propagations.
         * New errors only occur when wrong measurement result is delivered for feed-forward (The error on the measured qubit propagates to the byproduct gate target qubit).
         */
        virtual bool measure_Y();

        /**
         * \brief Single Qubit Z measurement.
         * \param If an X error, which affects the Z-measurement, is present, then returns false. Otherwise it returns true. This is only for simulating error propagations.
         * New errors only occur when wrong measurement result is delivered for feed-forward (The error on the measured qubit propagates to the byproduct gate target qubit).
         */
        virtual bool measure_Z();

        /**
         * \brief Two qubit CNOT gate.
         * \param Need to specify the control qubit as an argument.
         */
        virtual void CNOT(stationaryQubit *control_qubit);
        /**
          * \brief Single qubit Hadamard gate
          * \param X error transforms to Z, and vise-versa.
          */
        virtual void Hadamard();

    private:
        /** @name Self address
         *  @{                   */
        int stationaryQubit_address;
        int node_address;
        int qnic_address;
        int qnic_type;
        //@}
        PhotonicQubit *photon;

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual PhotonicQubit *generateEntangledPhoton();
        virtual void setBusy();
        virtual void setEntangledPartnerInfo(int node_address, int qnic_index, int qubit_index);
};

} // namespace modules
} // namespace quisp

#endif /* QUISP_MODULES_STATIONARYQUBIT_H_ */
