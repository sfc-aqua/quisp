/** \file RuleEngine.h
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/04/04
 *
 *  \brief RuleEngine
 */
#ifndef MODULES_RULEENGINE_H_
#define MODULES_RULEENGINE_H_

#include <vector>
#include <omnetpp.h>
#include "../classical_messages_m.h"
#include "stationaryQubit.h"
#include "RealTimeController.h"
#include "HardwareMonitor.h"
#include "HoM_Controller.h"

using namespace omnetpp;

struct QubitAddr_cons{
     QubitAddr_cons(const int node, const int qnic, const int qubit)
     : node_address(node), qnic_index(qnic), qubit_index(qubit) {}

    //QubitAddr(int node_addr, int qnic_index, int qubit_index):node_address(node_addr),qnic_index(qnic_index),qubit_index(qubit_index){}
    int node_address;
    int qnic_index;
    int qubit_index;
};

struct QubitAddr{
    //QubitAddr(int node_addr, int qnic_index, int qubit_index):node_address(node_addr),qnic_index(qnic_index),qubit_index(qubit_index){}
    int node_address;
    int qnic_index;
    int qubit_index;
};

struct QubitState{
    //QubitState(int qubit_address, int qubit_index, int qnic_index, int node_address, bool busy, simtime_t time):addr(node_address,qnic_index, qubit_index), entangled_addr(node_address,qnic_index, qubit_index), isBusy(busy), timestamp(time){}

    QubitAddr thisQubit_addr;
    QubitAddr entangled_addr;//The entangled partner recognized. This could be wrong due to an error.
    QubitAddr entangled_addr_actual;//The actual entangled partner
    //If entangled_addr != entangled_addr_actual, then operations do not do anything intended.
    bool isBusy;
    simtime_t timestamp;
};

/** \class RuleEngine RuleEngine.h
 *  \todo Documentation of the class header.
 *  \note The Connection Manager responds to connection requests received from other nodes.
 *        Connection setup, so a regular operation but not high bandwidth, relatively low constraints.
 *        Connections from nearest neighbors only.
 *        Connection manager needs to know which qnic is connected to where, which QNode not HoM/EPPS.
 *
 *  \brief RuleEngine
 */
class RuleEngine : public cSimpleModule
{
    public:
        int parentAddress;//Parent QNode's address
        EmitPhotonRequest *emt;
        HardwareMonitor::NeighborTable ntable;
        int number_of_qnics_all;//qnic,qnic_r,_qnic_rp
        int number_of_qnics;
        int number_of_qnics_r;
        int number_of_qnics_rp;
        typedef std::map<int, QubitState> QubitStateTable;
        typedef std::map<int, QubitAddr_cons> sentQubitIndexTracker;//nth shot -> node/qnic/qubit index (node addr not needed actually)
        //Although qnic index is in QubitAddr, lest make int qnic_index -> QubisState to lessen the search
        QubitStateTable stable, stable_r, stable_rp;
        sentQubitIndexTracker* tracker;
        HardwareMonitor *hardware_monitor;
        RealTimeController *realtime_controller;
        int* qnic_burst_trial_counter;
        typedef std::map<int,bool> trial_tracker;//trial index, false or true (that trial is over or not)
    protected:
        virtual void initialize() override;
        virtual void finish() override;
        virtual void handleMessage(cMessage *msg) override;
        virtual cModule* getQNode();
        virtual int countFreeQubits_inQnic(QubitStateTable table, int qnic_index);
        virtual int getOneFreeQubit_inQnic(QubitStateTable table, int qnic_index);
        virtual QubitStateTable setQubitBusy_inQnic(QubitStateTable table, int qnic_index, int qubit_index);
        virtual QubitStateTable setQubitFree_inQnic(QubitStateTable table, int qnic_index, int qubit_index);
        virtual QubitStateTable initializeQubitStateTable(QubitStateTable temp, int qnic_type);
        virtual void scheduleFirstPhotonEmission( BSMtimingNotifier *pk, int qnic_type);
        virtual void shootPhoton(SchedulePhotonTransmissionsOnebyOne * pk);
        //virtual int getQNICjob_index_for_this_qnic(int qnic_index, int qnic_type);
        virtual void incrementBurstTrial(int destAddr, int internal_qnic_address, int internal_qnic_index);
        virtual void shootPhoton_internal(SchedulePhotonTransmissionsOnebyOne * pk);
        virtual bool burstTrial_outdated(int this_trial, int qnic_address);
        //virtual int getQnicIndex_toNeighbor(int destAddr);
        virtual Interface_inf getInterface_toNeighbor(int destAddr);
        virtual void scheduleNextEmissionEvent(int qnic_index, int qnic_address, double interval, simtime_t timing, int num_sent, bool internal, int trial);
        virtual void freeFailedQubits(int destAddr, int internal_qnic_address, int internal_qnic_index, CombinedBSAresults *pk_result);
        virtual void clearTrackerTable(int destAddr, int internal_qnic_address);
};

#endif /* MODULES_RULEENGINE_H_ */
