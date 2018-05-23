/** \file HardwareMonitor.h
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/19
 *
 *  \brief HardwareMonitor
 */
#ifndef MODULES_HARDWAREMONITOR_H_
#define MODULES_HARDWAREMONITOR_H_

#define PASSIVE_EMITTER_QNIC 1//qnic
#define ACTIVE_RECEIVER_QNIC 2//qnic_r
#define PASSIVE_RECEIVER_QNIC 3//qnic_rp


#include <vector>
#include <omnetpp.h>
#include "../classical_messages_m.h"
#include "stationaryQubit.h"

using namespace omnetpp;

typedef struct _neighborInfo{
    bool isQNode;
    cModuleType *type;
    int address;
} neighborInfo;

typedef struct _entangledWith{
    int node_address;
    int qnic_index;
    int buffer_index;
} entangledWith;

typedef struct _stationaryQubitInfo{
    int qnic_index;
    int qubit_index;
    bool isBusy;//Reserved or free to use
    int assigned_job;//Maybe useful for bufferspace multiplexing and so on. Indicates which job this qubit is assigned for if isBusy is true.
    entangledWith entangled_inf;
} stationaryQubitInfo;

typedef struct _Interface_inf{
    //QubitAddr(int node_addr, int qnic_index, int qubit_index):node_address(node_addr),qnic_index(qnic_index),qubit_index(qubit_index){}
    int qnic_type;
    double initial_fidelity;
} Interface_inf;

/** \class HardwareMonitor HardwareMonitor.h
 *  \todo Documentation of the class header.
 *
 *  \brief HardwareMonitor
 */


class HardwareMonitor : public cSimpleModule
{
    private:
        int myAddress;
        int numQnic;
        int numQnic_r;
        int numQnic_rp;
        cModuleType *QNodeType =  cModuleType::get("networks.QNode");
        cModuleType *EPPSType =  cModuleType::get("networks.EPPS");
        cModuleType *HoMType =  cModuleType::get("networks.HoM");
    public:
        typedef std::map<int,Interface_inf> Interfaces;//qnic_index -> Interface{qnic_type, initial_fidelity...}
        typedef std::map<int,int> NeighborTable;
        NeighborTable ntable;
        typedef std::map<int, stationaryQubitInfo> QnicInfo;  // stationary qubit index -> state
        QnicInfo *qtable;
        virtual NeighborTable passNeighborTable();
        virtual int checkNumBuff(int qnic_index, int qnic_type);//returns the total number of qubits
        virtual int* checkFreeBuffSet(int qnic_index, int *list_of_free_resources, int qnic_type);//returns the set of free resources
        virtual int checkNumFreeBuff(int qnic_index, int qnic_type);//returns the number of free qubits
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        virtual NeighborTable prepareNeighborTable(NeighborTable ntable, int numQnic);
        virtual neighborInfo checkIfQNode(cModule *thisNode);
        virtual cModule* getQNode();
        virtual int findNeighborAddress(int local_qnic_index, cModule *thisQNode);
        //virtual QnicInfo* initializeQTable(int numQnic, QnicInfo *qtable);
};

#endif /* MODULES_HARDWAREMONITOR_H_ */
