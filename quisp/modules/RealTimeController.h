/** \todo clean Clean code when it is simple. */
/** \todo doc Write doxygen documentation. */
/*
 * RealTimeController.h
 *
 *  Created on: 2018/03/19
 *      Author: takaakimatsuo
 */

#ifndef MODULES_REALTIMECONTROLLER_H_
#define MODULES_REALTIMECONTROLLER_H_
#include <vector>
#include <omnetpp.h>
#include "../classical_messages_m.h"
using namespace omnetpp;

class RealTimeController : public cSimpleModule
{
    private:
        int myAddress;
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        virtual cModule* getQNode();
    public:
        virtual void EmitPhoton(int qnic_index ,int qubit_index, int qnic_type, int pulse);
        virtual void GUI_setQubitFree(int qnic_index ,int qubit_index, int qnic_type);
};




#endif /* MODULES_REALTIMECONTROLLER_H_ */
