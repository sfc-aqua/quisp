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
    if(par("GOD_Zerror")){
        return false;//Wrong measurement outcome
    }else{
        return true;//X err does not affect X measurement
    }
}

bool stationaryQubit::measure_Y(){
    if(par("GOD_Zerror") || par("GOD_Xerror")){
        return false;//Wrong measurement outcome
    }else{
        return true;//Y error does not affect the measurement outcome
    }
}

bool stationaryQubit::measure_Z(){
    if(par("GOD_Xerror")){
        return false;//Wrong measurement outcome
    }else{
        return true;//X error does not affect the measurement outcome
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

} // namespace modules
} // namespace quisp
