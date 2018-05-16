#include "stationaryQubit.h"
#include <vector>
#include <omnetpp.h>
#include "../classical_messages_m.h"
#include "../PhotonicQubit_m.h"

using namespace omnetpp;

Define_Module(stationaryQubit);

void stationaryQubit::initialize()
{
    pauliXerr = false;
    pauliZerr = false;
    //nonPaulierr = false;
    //nonPaulierrTwo = false;
    NodeEntangledWith = -1;
    QNICEntangledWith = -1;
    stationaryQubit_address = par("stationaryQubit_address");
    node_address = par("node_address");
    qnic_address = par("qnic_address");
    std = par("std");
    setFree();
}

void stationaryQubit::handleMessage(cMessage *msg){
    bubble("Got a photon!!");
    setBusy();
    send(msg, "tolens_quantum_port$o");
}

void stationaryQubit::setBusy(){
    isBusy = true;
    if(hasGUI()){
        getDisplayString().setTagArg("i", 1, "red");
    }
    par("isBusy") = true;//For IDE
}

void stationaryQubit::setFree(){
    isBusy = false;
    if(hasGUI()){
        getDisplayString().setTagArg("i", 1, "blue");
    }
    par("isBusy") = false;//For IDE
}

bool stationaryQubit::checkBusy(){
    Enter_Method("checkBusy()");
    if(!isBusy){
        return false;
    }else{
        return true;
    }
}

PhotonicQubit *stationaryQubit::generateEntangledPhoton(){
    Enter_Method("generateEntangledPhoton()");
    photon = new PhotonicQubit("Photon");
    //To simulte the actual physical entangled partner, not what the system thinks!!! we need this.
    photon->setNodeEntangledWith(node_address);//This photon is entangled with....
    photon->setQNICEntangledWith(qnic_address);
    photon->setStationaryQubitEntangledWith(stationaryQubit_address);
    return photon;
}

void stationaryQubit::emitPhoton(int pulse)
{
    Enter_Method("emitPhoton()");
    if(!checkBusy()){
        PhotonicQubit *pk = generateEntangledPhoton();
        if(pulse == 1){
            pk->setFirst(true);
            pk->setKind(3);
        }
        else if(pulse == -1){
            pk->setLast(true);
            pk->setKind(3);
        }else if(pulse == 2){
            pk->setFirst(true);
            pk->setLast(true);
            pk->setKind(3);
        }
        float jitter_timing = normal(0,std);
        float abso = fabs(jitter_timing);
        scheduleAt(simTime()+abso,pk); //cannot send back in time, so only positive lag
    }else{
        error("Requested a photon emission to a busy qubit... this should not happen!");
    }

}

void stationaryQubit::setEntangledPartnerInfo(int node_address, int qnic_index, int qubit_index){
    //When BSA succeeds, this method gets invoked to store entanged partner information. This will also be send classically to the node afterwards.
    NodeEntangledWith = node_address;//Entangled pair's node-level address. -1 if not entangled
    QNICEntangledWith = qnic_index;//Entangled pair's QNIC-level address
    stationaryQubitEntangledWith = qubit_index;
}
