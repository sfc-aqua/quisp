/** \file EPPS_pair_source.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/25
 *
 *  \brief EPPS_pair_source
 */
#include "EPPS_pair_source.h"

namespace quisp {
namespace modules {

Define_Module(EPPS_pair_source);

void EPPS_pair_source::initialize()
{
    error_rate = par("error_rate");
    Y_error_ratio = par("Y_error_ratio");
    X_error_ratio = par("X_error_ratio");
    Z_error_ratio = par("Z_error_ratio");
    emission_std = par("emission_std");
    frequency = par("frequency");
    EV<<"------------------"<<frequency<<" aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
}

void EPPS_pair_source::handleMessage(cMessage *msg){
    send(msg, "to_quantum_port$o",msg->par("gate"));
}

PhotonicQubit *EPPS_pair_source::generateEntangledPhotons(){
    Enter_Method("generateEntangledPhotons()");
    PhotonicQubit *photon_one = new PhotonicQubit();
    return photon_one;
    //PhotonicQubit *photon_two = new PhotonicQubit();
    //photon_one->addPar("gate") = 0;
    //photon_two->addPar("gate") = 1;
    //photon->setStationaryQubitEntangledWith(stationaryQubit_address);
    //entangledPhotons *qubits;
    //qubits->qubitTwo = photon_two;
    //qubits->qubitOne = photon_one;
    //return qubits;
}

void EPPS_pair_source::emitPhotons(){
    Enter_Method("emitPhotons()");
    PhotonicQubit *qubit = generateEntangledPhotons();
    qubit->addPar("gate") = 0;
    PhotonicQubit *qubitTwo = generateEntangledPhotons();
    qubitTwo->addPar("gate") = 1;
    float jitter_timing = normal(0,emission_std);
    float abso = fabs(jitter_timing);

    scheduleAt(simTime()+abso,qubit);
    scheduleAt(simTime()+abso,qubitTwo);
}

void EPPS_pair_source::BubbleText(const char* txt){
    if (hasGUI()) {
      char text[32];
      sprintf(text, "%s", txt);
      bubble(text);
    }
}

cModule* EPPS_pair_source::getEPPSNode(){
         cModule *currentModule = getParentModule();//We know that Connection manager is not the EPPS, so start from the parent.
         try{
             cModuleType *QNodeType =  cModuleType::get("networks.EPPS");//Assumes the node in a network has a type EPPS
             while(currentModule->getModuleType()!=QNodeType){
                 currentModule = currentModule->getParentModule();
             }
             return currentModule;
         }catch(std::exception& e){
             error("No module with QNode type found. Have you changed the type name in ned file?");
             endSimulation();
         }
         return currentModule;
}

double EPPS_pair_source::getEmissionFrequency(){
    Enter_Method("getEmissionFrequency()");
    EV<<"**********************Returning frequency"<<frequency;
    return frequency;
}

} // namespace modules
} // namespace quisp
