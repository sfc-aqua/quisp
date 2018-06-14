/*
 * RoutingDaemon.h
 *
 *  Created on: 2018/06/12
 *      Author: takaakimatsuo
 */

#ifndef MODULES_ROUTINGDAEMON_H_
#define MODULES_ROUTINGDAEMON_H_

#include <omnetpp.h>

using namespace omnetpp;


/** \class RoutingDaemon RoutingDaemon.cc
 *  \todo Documentation of the class header.
 *
 *  \brief RoutingDaemon
 */

namespace quisp {
namespace modules {


typedef struct _QNIC_identifier{
    //QubitAddr(int node_addr, int qnic_index, int qubit_index):node_address(node_addr),qnic_index(qnic_index),qubit_index(qubit_index){}
    cModule *qnic_pointer;
    int qnic_type;/*0 = qnic, 1 = qnic_r, 2 = qnic_rp*/
    int qnic_index;/*Index inside qnic || qnic_rp || qnic_r. Used for accessing the module.*/
    int qnic_address;/*Unique address for qnic, qnic_r, qnic_rp. This may not be used.*/
} QNIC;

class RoutingDaemon : public cSimpleModule
{
    private:
        int myAddress;
        typedef std::map<int, QNIC> RoutingTable;  // destaddr -> {gate_index (We need this to access qnic, but it is not unique because we have 3 types of qnics), qnic_address (unique)}
        RoutingTable qrtable;
    protected:
        virtual void initialize(int stage) override;
        virtual void handleMessage(cMessage *msg) override;
        virtual int numInitStages() const override {return 3;};
    public:
        virtual int return_QNIC_address_to_destAddr(int destAddr);
};

}
}


#endif /* MODULES_ROUTINGDAEMON_H_ */
