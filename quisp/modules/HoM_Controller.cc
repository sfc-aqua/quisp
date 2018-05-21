/** \file HoM_Controller.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/04/01
 *
 *  \brief HoM_Controller
 */
#include "HoM_Controller.h"

Define_Module(HoM_Controller);

HoM_Controller::HoM_Controller()
{

}

void HoM_Controller::initialize()
{
    handshake = false;
    BSA_timeout = 1e-6;
    address = par("address");
    receiver = par("receiver");
    passive = par("passive");
    if(!receiver && !passive){
        standaloneInitializer();//Other parameter settings
    }else if (receiver && !passive){
        internodeInitializer();//Other parameter settings
    }else if(passive){
        //Nothing to do. EPPS will take care of entanglement creation.
        //max_buffer also stays unknown, until this gets a message about that info from epps.
        //Therefore, if passive, max_buffer has to be update manually every time when you get a packet from epps.
        //It still needs to know who is the neighbor of this internal hom (a.k.a qnic)
        checkNeighborAddress(true);
    }else{
        error("Set receiver parameter of HoM to true or false.");
    }
}


void HoM_Controller::internodeInitializer(){
    checkNeighborAddress(true);
    checkNeighborBuffer(true);
    updateIDE_Parameter(true);

    accepted_burst_interval = (double)1/(double)photon_detection_per_sec;
    generatePacket = new cMessage("nextPacket");
    scheduleAt(simTime(),generatePacket);
}

void HoM_Controller::standaloneInitializer(){
    if(getParentModule()->gateSize("quantum_port")!=2){
        error("No more or less than 2 neighbors are allowed for HoM.",getParentModule()->gateSize("quantum_port"));
                endSimulation();
    }
    checkNeighborAddress(false);
    checkNeighborBuffer(false);
    updateIDE_Parameter(false);

    accepted_burst_interval = (double)1/(double)photon_detection_per_sec;
    generatePacket = new cMessage("nextPacket");
    scheduleAt(simTime(),generatePacket);
}

void HoM_Controller::sendNotifiers(){
     double time = calculateTimeToTravel(max_neighbor_distance,speed_of_light_in_channel);//When the packet reaches = simitme()+time
     BSMtimingNotifier *pk = generateNotifier(time, speed_of_light_in_channel, distance_to_neighbor, neighbor_address, accepted_burst_interval,photon_detection_per_sec, max_buffer);
     double first_nodes_timing = calculateEmissionStartTime(time,distance_to_neighbor,speed_of_light_in_channel);
     pk->setTiming_at(first_nodes_timing);//Tell neighboring nodes to shoot photons so that the first one arrives at BSA at the specified timing
     if(receiver){
         pk->setInternal_qnic(qnic_index);
     }

     BSMtimingNotifier *pkt = generateNotifier(time, speed_of_light_in_channel, distance_to_neighbor_two, neighbor_address_two, accepted_burst_interval,photon_detection_per_sec, max_buffer);
     double second_nodes_timing = calculateEmissionStartTime(time,distance_to_neighbor_two,speed_of_light_in_channel);
     pkt->setTiming_at(second_nodes_timing);//Tell neighboring nodes to shoot photons so that the first one arrives at BSA at the specified timing
     //If you want some uncertainty in timing calculation, maybe second_nodes_timing+uniform(-n,n) helps
     try{
         send(pk, "toRouter_port");//send to port out. connected to local routing module (routing.localIn).
         send(pkt, "toRouter_port");
     }catch(cTerminationException& e) {
         error("Error in HoM_Controller.cc. It does not have port named toRouter_port.");
         endSimulation();
     }catch (std::exception& e) {
         error("Error in HoM_Controller.cc. It does not have port named toRouter_port.");
         endSimulation();
     }

}


void HoM_Controller::handleMessage(cMessage *msg){
    if(msg == generatePacket){
        sendNotifiers();
    }else if(dynamic_cast<BSAresult *>(msg) != nullptr){
        bubble("BSAresult accumulated");
        BSAresult *pk = check_and_cast<BSAresult *>(msg);
        pushToBSAresults(pk->getEntangled());
        int stored = getStoredBSAresultsSize();
        char moge[sizeof(stored)];

        sprintf(moge, "%d", stored);
        bubble(moge);
        /*if(getStoredBSAresultsSize() == max_buffer && handshake==true){
            bubble("All results stored!");
            sendBSAresultsToNeighbors();
            clearBSAresults();
        }else{

        }*/
    }else if(dynamic_cast<BSAfinish *>(msg) != nullptr){
        bubble("BSAresult accumulated");
        BSAfinish *pk = check_and_cast<BSAfinish *>(msg);
        pushToBSAresults(pk->getEntangled());
        int stored = getStoredBSAresultsSize();
        char moge[sizeof(stored)];
        sprintf(moge, "%d", stored);
        bubble(moge);

        bubble("done");
        sendBSAresultsToNeighbors();//memory leak
        clearBSAresults();
        //Schedule a checker with a time-out t, to see if both actually sent something.
        //Worst case is, when both have no free qubit, and no qubits get transmitted. In that case, this module needs to recognize that problem, and reschedule/resend the request after a cetrain time.
    }
    delete msg;
}


void HoM_Controller::checkNeighborAddress(bool receiver){
    if(receiver){
        try{
            qnic_index = getParentModule()->getParentModule()->par("self_qnic_address");
            neighbor_address = getQNode()->par("address");
            neighbor_address_two =  getParentModule()->gate("quantum_port$o",1)->getNextGate()->getNextGate()->getNextGate()->getOwnerModule()->par("address");
            distance_to_neighbor = getParentModule()->par("internal_distance");
            distance_to_neighbor_two = getParentModule()->gate("quantum_port$o",1)->getNextGate()->getNextGate()->getChannel()->par("distance");
            max_neighbor_distance = std::max(distance_to_neighbor,distance_to_neighbor_two);
        }catch (std::exception& e) {
            error("Error in HoM_Controller.cc when getting neighbor addresses. Check internodeInitializer.");
            endSimulation();
        }
    }else{
        try{
            neighbor_address =  getParentModule()->gate("quantum_port$o",0)->getNextGate()->getOwnerModule()->par("address");
            neighbor_address_two =  getParentModule()->gate("quantum_port$o",1)->getNextGate()->getOwnerModule()->par("address");
            distance_to_neighbor = getParentModule()->gate("quantum_port$o",0)->getChannel()->par("distance");
            distance_to_neighbor_two = getParentModule()->gate("quantum_port$o",1)->getChannel()->par("distance");
            max_neighbor_distance = std::max(distance_to_neighbor,distance_to_neighbor_two);
        }catch (std::exception& e) {
            error("Error in HoM_Controller.cc. Your stand-alone HoM module may not connected to the neighboring node (quantum_port).");
            endSimulation();
        }
    }
}

void HoM_Controller::checkNeighborBuffer(bool receiver){
    if(receiver){
        try{
            neighbor_buffer =  getParentModule()->getParentModule()->par("numBuffer");
            neighbor_buffer_two = getParentModule()->gate("quantum_port$o",1)->getNextGate()->getNextGate()->getNextGate()->getNextGate()->getOwnerModule()->par("numBuffer");
            max_buffer = std::min(neighbor_buffer,neighbor_buffer_two);//Both nodes should transmit the same amount of photons.
        }catch (std::exception& e) {
            error("Error in HoM_Controller.cc. HoM couldnt find parameter numBuffer in the neighbor's qnic.");
            endSimulation();
        }
    }else{
        try{
            neighbor_buffer =  getParentModule()->gate("quantum_port$o",0)->getNextGate()->getNextGate()->getOwnerModule()->par("numBuffer");
            neighbor_buffer_two =  getParentModule()->gate("quantum_port$o",1)->getNextGate()->getNextGate()->getOwnerModule()->par("numBuffer");
            max_buffer = std::min(neighbor_buffer,neighbor_buffer_two);//Both nodes should transmit the same amount of photons.
        }catch (std::exception& e) {
            error("Error in HoM_Controller.cc. HoM couldnt find parameter numBuffer in the neighbor's qnic.");
            endSimulation();
        }
    }
}

void HoM_Controller::updateIDE_Parameter(bool receiver){
    try{
        photon_detection_per_sec = par("photon_detection_per_sec");
        par("neighbor_address") = neighbor_address;
        par("neighbor_address_two") = neighbor_address_two;
        par("distance_to_neighbor") = distance_to_neighbor;
        par("distance_to_neighbor_two") = distance_to_neighbor_two;
        par("max_neighbor_distance") = max_neighbor_distance;
        par("max_buffer") = max_buffer;
        c = &par("distance_of_light_in_fiber_per_sec");
        speed_of_light_in_channel = c->doubleValue();//per sec
        if(receiver){
            getParentModule()->par("qnic_index") = qnic_index;
        }
    }
    catch(std::exception& e){
        error("photon_detection_per_sec is missing as a HoM_Controller parameter. Or maybe you should specify **.distance_of_light_in_fiber_per_sec = (number)km in .ini file.");
    }
}

BSMtimingNotifier* HoM_Controller::generateNotifier(double time, double speed_of_light_in_channel, double distance_to_neighbor, int destAddr, double accepted_burst_interval,int photon_detection_per_sec, int max_buffer){
           BSMtimingNotifier *pk = new BSMtimingNotifier();
           //pk->setNumber_of_qubits(max_buffer);
           if(handshake==false)
               pk->setNumber_of_qubits(-1);//if -1, neighbors will keep shooting photons anyway.
           else
               pk->setNumber_of_qubits(max_buffer);
           pk->setSrcAddr(getParentModule()->par("address"));//packet source setting
           pk->setDestAddr(destAddr);
           pk->setKind(BSAtimingNotifier_type);
           pk->setInterval(accepted_burst_interval);
           pk->setAccepted_photons_per_sec(photon_detection_per_sec);//If very high, all photons can nearly be sent here(to BSA module) from neighboring nodes simultaneously
           double timing = calculateEmissionStartTime(time,distance_to_neighbor,speed_of_light_in_channel);
           pk->setTiming_at(timing);//Tell neighboring nodes to shoot photons so that the first one arrives at BSA at the specified timing
           return pk;
}

CombinedBSAresults* HoM_Controller::generateNotifier_c(double time, double speed_of_light_in_channel, double distance_to_neighbor, int destAddr, double accepted_burst_interval,int photon_detection_per_sec, int max_buffer){
           CombinedBSAresults *pk = new CombinedBSAresults();
           //pk->setNumber_of_qubits(max_buffer);
           if(handshake==false)
               pk->setNumber_of_qubits(-1);//if -1, neighbors will keep shooting photons anyway.
           else
               pk->setNumber_of_qubits(max_buffer);
           pk->setSrcAddr(getParentModule()->par("address"));//packet source setting
           pk->setDestAddr(destAddr);
           pk->setKind(BSAtimingNotifier_type);
           pk->setInterval(accepted_burst_interval);
           pk->setAccepted_photons_per_sec(photon_detection_per_sec);//If very high, all photons can nearly be sent here(to BSA module) from neighboring nodes simultaneously
           double timing = calculateEmissionStartTime(time,distance_to_neighbor,speed_of_light_in_channel);
           pk->setTiming_at(timing);//Tell neighboring nodes to shoot photons so that the first one arrives at BSA at the specified timing
           return pk;
}


double HoM_Controller::calculateEmissionStartTime(double time, double distance_to_node, double c){
    //distance_to_node is the distance to HoM to self.

    double self_timeToTravel = calculateTimeToTravel(distance_to_node,c);
    if((self_timeToTravel) != time){//If shorter distance, then the node needs to wait a little for the other node with the longer distance
            return (time-self_timeToTravel)*2;//Waiting time
    }else{
        return 0;//No need to wait
    }
}

double HoM_Controller::calculateTimeToTravel(double distance, double c){
    return (distance/c);
}

void HoM_Controller::BubbleText(const char* txt){
    if (hasGUI()) {
      char text[32];
      sprintf(text, "%s", txt);
      bubble(text);
    }
}

cModule* HoM_Controller::getQNode(){
         cModule *currentModule = getParentModule();//We know that Connection manager is not the QNode, so start from the parent.
         try{
             cModuleType *QNodeType =  cModuleType::get("networks.QNode");//Assumes the node in a network has a type QNode
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





void HoM_Controller::pushToBSAresults(bool attempt_success){
    results[getStoredBSAresultsSize()] = attempt_success;
}
int HoM_Controller::getStoredBSAresultsSize(){
    return results.size();
}
void HoM_Controller::clearBSAresults(){
    results.clear();
}
void HoM_Controller::sendBSAresultsToNeighbors(){

    if(!passive){
        CombinedBSAresults *pk, *pkt;
       // pk = new CombinedBSAresults();
       // pkt = new CombinedBSAresults();

        double time = calculateTimeToTravel(max_neighbor_distance,speed_of_light_in_channel);//When the packet reaches = simitme()+time
        pk = generateNotifier_c(time, speed_of_light_in_channel, distance_to_neighbor, neighbor_address, accepted_burst_interval,photon_detection_per_sec, max_buffer);
        double first_nodes_timing = calculateEmissionStartTime(time,distance_to_neighbor,speed_of_light_in_channel);
        pk->setTiming_at(first_nodes_timing);//Tell neighboring nodes to shoot photons so that the first one arrives at BSA at the specified timing


        pk->setSrcAddr(address);
        pk->setDestAddr(neighbor_address);
        pk->setList_of_failedArraySize(getStoredBSAresultsSize());
        pk->setKind(5);
        if(receiver){
                   pk->setInternal_qnic(qnic_index);
        }

        pkt = generateNotifier_c(time, speed_of_light_in_channel, distance_to_neighbor_two, neighbor_address_two, accepted_burst_interval,photon_detection_per_sec, max_buffer);
        double second_nodes_timing = calculateEmissionStartTime(time,distance_to_neighbor_two,speed_of_light_in_channel);
        pkt->setTiming_at(second_nodes_timing);//Tell neighboring nodes to shoot photons so that the first one arrives at BSA at the specified timing
        EV<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!list of failed size = "<<getStoredBSAresultsSize()<<"\n";
        pkt->setSrcAddr(address);
        pkt->setDestAddr(neighbor_address_two);
        pkt->setList_of_failedArraySize(getStoredBSAresultsSize());
        pkt->setKind(5);

        for(auto it : results ){
           int index = it.first;
           bool entangled = it.second;
           pk->setList_of_failed(index, entangled);
           pkt->setList_of_failed(index, entangled);
        }
        send(pk,"toRouter_port");
        send(pkt,"toRouter_port");

    }else{
        CombinedBSAresults_epps *pk, *pkt;
        pk = new CombinedBSAresults_epps();
        pkt = new CombinedBSAresults_epps();

        pk->setSrcAddr(address);
        pk->setDestAddr(neighbor_address);
        pk->setList_of_failedArraySize(getStoredBSAresultsSize());
        pk->setKind(6);

        pkt->setSrcAddr(address);
        pkt->setDestAddr(neighbor_address_two);
        pkt->setList_of_failedArraySize(getStoredBSAresultsSize());
        pkt->setKind(6);

        EV<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!list of failed size = "<<getStoredBSAresultsSize()<<"\n";

        for(auto it : results ){
           int index = it.first;
           bool entangled = it.second;
           pk->setList_of_failed(index, entangled);
           pkt->setList_of_failed(index, entangled);
        }
        send(pk,"toRouter_port");
        send(pkt,"toRouter_port");
    }
}


//When the BSA is passive, it does not know how many qubits to emit (because it depends on the neighbor's).
//Therefore, the EPPS sends a classical packet that includes such information.
//When CM receives it, it will also have to update the max_buffer of HoM_Controller, to know when the emission end and send the classical BSAresults to the neighboring EPPS.
void HoM_Controller::setMax_buffer(int buffer){
    Enter_Method("setMax_buffer()");
    if(!passive){
        return;
    }else{
        max_buffer = buffer;
        par("max_buffer") = buffer;
    }
}
/*
void HoM_Controller::finish(){

}*/








