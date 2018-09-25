/** \file HardwareMonitor.h
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/19
 *
 *  \brief HardwareMonitor
 */
#ifndef QUISP_MODULES_HARDWAREMONITOR_H_
#define QUISP_MODULES_HARDWAREMONITOR_H_

#include <vector>
#include <omnetpp.h>
#include <modules/stationaryQubit.h>
#include <modules/QNIC.h>
#include "classical_messages_m.h"

using namespace omnetpp;

namespace quisp {
namespace modules {

typedef struct _neighborInfo{
    bool isQNode;
    cModuleType *type;
    int address;//May be QNode, SPDC, HOM
    int index;
    int neighborQNode_address;//QNode (May be across SDPC or HOM node)
} neighborInfo;

typedef QNIC_id entangledWith;

typedef struct _stationaryQubitInfo{
    int qnic_index;
    int qubit_index;
    bool isBusy;//Reserved or free to use
    int assigned_job;//Maybe useful for bufferspace multiplexing and so on. Indicates which job this qubit is assigned for if isBusy is true.
    entangledWith entangled_inf;
} stationaryQubitInfo;

typedef struct _Interface_inf{
    //QubitAddr(int node_addr, int qnic_index, int qubit_index):node_address(node_addr),qnic_index(qnic_index),qubit_index(qubit_index){}
    QNIC qnic;
    double initial_fidelity = -1;/*Oka's protocol?*/
    int buffer_size;
    double link_cost;
    int neighborQNode_address;
    int neighborQNode_qnic_type;
    QNIC neighbor_qnic;
} Interface_inf;

typedef struct _For_connection_setup{
    QNIC_id qnic;
    int neighbor_address;
    int quantum_link_cost;
} connection_setup_inf;

/** \class HardwareMonitor HardwareMonitor.h
 *  \todo Documentation of the class header.
 *
 *  \brief HardwareMonitor
 */

class HardwareMonitor : public cSimpleModule
{
    private:
        int myAddress;
        int numQnic, numQnic_r, numQnic_rp, numQnic_total;
        cModuleType *QNodeType =  cModuleType::get("networks.QNode");
        cModuleType *SPDCType =  cModuleType::get("networks.SPDC");
        cModuleType *HoMType =  cModuleType::get("networks.HoM");
        bool do_link_level_tomography = false;
        int num_measure;
    public:
        //typedef std::map<int,Interface_inf> Interfaces;//qnic_index -> Interface{qnic_type, initial_fidelity...}
        typedef std::map<int,Interface_inf> NeighborTable;//qnic_index -> Interface{qnic_type, initial_fidelity...}
        NeighborTable ntable;
        typedef std::map<int, stationaryQubitInfo> QnicInfo;  // stationary qubit index -> state
        QnicInfo *qtable;
        virtual NeighborTable passNeighborTable();
        virtual int checkNumBuff(int qnic_index, QNIC_type qnic_type);//returns the total number of qubits
        virtual connection_setup_inf return_setupInf(int qnic_address);
        //virtual int* checkFreeBuffSet(int qnic_index, int *list_of_free_resources, QNIC_type qnic_type);//returns the set of free resources
        //virtual int checkNumFreeBuff(int qnic_index, QNIC_type qnic_type);//returns the number of free qubits
    protected:
        virtual void initialize(int stage) override;
        virtual void handleMessage(cMessage *msg) override;
        virtual int numInitStages() const override {return 2;};
        virtual NeighborTable prepareNeighborTable(NeighborTable ntable, int numQnic);
        virtual neighborInfo checkIfQNode(cModule *thisNode);
        virtual cModule* getQNode();
        virtual neighborInfo findNeighborAddress(cModule *qnic_pointer);
        virtual Interface_inf getInterface_inf_fromQnicAddress(int qnic_index, QNIC_type qnic_type);
        virtual void sendLinkTomographyRuleSet(int my_address,int partner_address, QNIC_type qnic_type, int qnic_index);

        //virtual QnicInfo* initializeQTable(int numQnic, QnicInfo *qtable);
};

} // namespace modules
} // namespace quisp

#endif /* QUISP_MODULES_HARDWAREMONITOR_H_ */
