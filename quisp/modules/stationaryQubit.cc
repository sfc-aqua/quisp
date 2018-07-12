/** \file stationaryQubit.cc
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/14
 *
 *  \brief stationaryQubit
 */
#include "stationaryQubit.h"
#include <vector>
#include <omnetpp.h>
#include <classical_messages_m.h>
#include <PhotonicQubit_m.h>

namespace quisp {
namespace modules {

Define_Module(stationaryQubit);

/**
 * \brief Initialize stationaryQubit
 *
 * Omnet called method to initialize objects.
 *
 */
void stationaryQubit::initialize()
{
    pauliXerr = false;
    pauliZerr = false;
    //nonPaulierr = false;
    //nonPaulierrTwo = false;
    NodeEntangledWith = -1;
    QNICEntangledWith = -1;
    QNICtypeEntangledWith = -1;

    // Get parameters from omnet
    stationaryQubit_address = par("stationaryQubit_address");
    node_address = par("node_address");
    qnic_address = par("qnic_address");
    qnic_type = par("qnic_type");
    std = par("std");
    setFree();

    /* e^(t/T1) energy relaxation, e^(t/T2) phase relaxation. Want to use only 1/10 of T1 and T2 in general.*/
}

/**
 * \brief cSimpleModule handleMessage function
 *
 * \param msg is the message
 */
void stationaryQubit::handleMessage(cMessage *msg){
    bubble("Got a photon!!");
    setBusy();
    send(msg, "tolens_quantum_port$o");
}

bool stationaryQubit::measure_X(){
    //Need to add noise here later

    return !par("GOD_Zerror");
}

/**
 *  Returns true if the measurement outcome was correct
 */
bool stationaryQubit::measure_Y(){
    //Need to add noise here later

    return !(par("GOD_Zerror") || par("GOD_Xerror"));
}

bool stationaryQubit::measure_Z(){
    //Need to add noise here later

    return !par("GOD_Xerror");
}

//Convert X to Z, and Z to X error. Therefore, Y error stays as Y.
void stationaryQubit::Hadamard_gate(){
    //Need to add noise here later

    bool z = par("GOD_Zerror");
    par("GOD_Zerror") = par("GOD_Xerror");
    par("GOD_Xerror") = z;
}

void stationaryQubit::Z_gate(){
    //Need to add noise here later
    par("GOD_Zerror") = !par("GOD_Zerror");
}

void stationaryQubit::X_gate(){
    //Need to add noise here later
    par("GOD_Xerror") = !par("GOD_Xerror");
}

void stationaryQubit::CNOT_gate(stationaryQubit *control_qubit){
    //Need to add noise here later

    if(control_qubit->par("GOD_Xerror")){
        par("GOD_Xerror") = !par("GOD_Xerror");//X error propagates from control to target. If an X error is already present, then it cancels out.
    }

    if(par("GOD_Zerror")){
        control_qubit->par("GOD_Zerror") = ! control_qubit->par("GOD_Zerror");//Z error propagates from target to control. If an Z error is already present, then it cancels out.
    }
}

void stationaryQubit::setBusy(){
    isBusy = true;
    emitted_time = simTime();
    par("photon_emitted_at") = emitted_time.dbl();

    // GUI part
    if(hasGUI()){
        getDisplayString().setTagArg("i", 1, "red");
    }
    par("isBusy") = true;
}

void stationaryQubit::setFree(){
    isBusy = false;
    emitted_time = -1;
    par("photon_emitted_at") = emitted_time.dbl();

    // GUI part
    if(hasGUI()){
        getDisplayString().setTagArg("i", 1, "blue");
    }
    par("isBusy") = false;
}

bool stationaryQubit::checkBusy(){
    Enter_Method("checkBusy()");
    return !!isBusy;
}

/**
 * \brief Generate photon entangled with the memory
 *
 * \warning Shouldn't we destroy a possibly existing photon object before?
 */
PhotonicQubit *stationaryQubit::generateEntangledPhoton(){
    Enter_Method("generateEntangledPhoton()");
    photon = new PhotonicQubit("Photon");

    //To simulate the actual physical entangled partner, not what the system thinks!!! we need this.
    photon->setNodeEntangledWith(node_address);//This photon is entangled with.... node_address = node's index
    photon->setQNICEntangledWith(qnic_address);//qnic_address != qnic_index. qnic_index is not unique because there are 3 types.
    photon->setStationaryQubitEntangledWith(stationaryQubit_address);//stationaryQubit_address = stationaryQubit's index
    photon->setQNICtypeEntangledWith(qnic_type);
    photon->setEntangled_with(this);
    return photon;
}

/**
 * \brief Emit photon
 *
 * \param pulse: 0 for nothing, 1 for first, 2 for last, 3 for first and last
 *
 * The stationary qubit shouldn't be already busy.
 */
void stationaryQubit::emitPhoton(int pulse)
{
    Enter_Method("emitPhoton()");
    if (checkBusy()) {
        error("Requested a photon emission to a busy qubit... this should not happen!");
        return;
    }
    PhotonicQubit *pk = generateEntangledPhoton();
    if (pulse & STATIONARYQUBIT_PULSE_BEGIN) pk->setFirst(true);
    if (pulse & STATIONARYQUBIT_PULSE_END) pk->setLast(true);
    if (pulse & STATIONARYQUBIT_PULSE_BOUND) pk->setKind(3);
    float jitter_timing = normal(0,std);
    float abso = fabs(jitter_timing);
    scheduleAt(simTime()+abso,pk); //cannot send back in time, so only positive lag
}

void stationaryQubit::setEntangledPartnerInfo(int node_address, int qnic_index, int qubit_index){
    //When BSA succeeds, this method gets invoked to store entanged partner information. This will also be send classically to the node afterwards.
    NodeEntangledWith = node_address;//Entangled pair's node-level address. -1 if not entangled
    QNICEntangledWith = qnic_index;//Entangled pair's QNIC-level address
    stationaryQubitEntangledWith = qubit_index;
    QNICtypeEntangledWith  = qnic_type;
}

void stationaryQubit::purify(stationaryQubit * resource_qubit) {
    resource_qubit->CNOT_gate(this);
    bool meas = resource_qubit->measure_Z();
    // communicate, values of measurement
    // probably need to store ours until receiving the partners'
    // if agree (truetrue or falsefalse), keep
}

} // namespace modules
} // namespace quisp
