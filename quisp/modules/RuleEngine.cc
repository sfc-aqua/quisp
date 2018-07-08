/** \file RuleEngine.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/04/04
 *
 *  \brief RuleEngine
 */
#include "RuleEngine.h"
#include <modules/HardwareMonitor.h>

namespace quisp {
namespace modules {

Define_Module(RuleEngine);

void RuleEngine::initialize()
{
    //HardwareMonitor's neighbor table is checked in the initialization stage of the simulation
    //This assumes the topology never changes throughout the simulation.
    //If dynamic change in topology is required, recoding this is needed.
    cModule *hm = getParentModule()->getSubmodule("hm");
    hardware_monitor = check_and_cast<HardwareMonitor *>(hm);
    cModule *rt = getParentModule()->getSubmodule("rt");
    realtime_controller = check_and_cast<RealTimeController *>(rt);//Just for qubit free GUI update
    parentAddress = par("address");
    number_of_qnics_all = par("total_number_of_qnics");
    number_of_qnics = par("number_of_qnics");
    number_of_qnics_r = par("number_of_qnics_r");
    number_of_qnics_rp = par("number_of_qnics_rp");

    qnic_burst_trial_counter = new int[number_of_qnics_all];    //if there are 2 qnics, 1 qnic_r, and 2 qnic_rp, then trial_index[0~1] is assigned for qnics, trial_index[2~2] for qnic_r and trial_index[3~4] for qnic_rp....
    for(int i=0; i<number_of_qnics_all; i++){
       qnic_burst_trial_counter[i] = 0;
    }

    stable = initializeQubitStateTable(stable, QNIC_E);//state for qubits/qnics with MIM links
    stable_r = initializeQubitStateTable(stable_r, QNIC_R);//MM links
    stable_rp = initializeQubitStateTable(stable_rp, QNIC_RP);//MSM links

    tracker = new sentQubitIndexTracker[number_of_qnics_all];//Tracks which qubit was sent first, second and so on per qnic(r,rp)

    /*Initialize resource list by Age for the actual use of qubits in operations*/
    allResources = new qnicResources[QNIC_N];
    allResources[QNIC_E] = new EntangledPairs[number_of_qnics];
    allResources[QNIC_R] = new EntangledPairs[number_of_qnics_r];
    allResources[QNIC_RP] = new EntangledPairs[number_of_qnics_rp];

}

void RuleEngine::handleMessage(cMessage *msg){
        header *pk = check_and_cast<header *>(msg);


        if(dynamic_cast<EmitPhotonRequest *>(msg) != nullptr){//From self.
            EmitPhotonRequest *pk = check_and_cast<EmitPhotonRequest *>(msg);

            cModule *rtc = getParentModule()->getSubmodule("rt");
            RealTimeController *realtime_controller = check_and_cast<RealTimeController *>(rtc);

            if(burstTrial_outdated(pk->getTrial(), pk->getQnic_address())){//Terminate emission if trial is over already (e.g. the neighbor ran out of free qubits and the BSA already returned the results)
                delete msg;//Terminate bursting if this trial has finished already.
                return;
            }else{
                //Index the qnic and qubit index to the tracker.
                int qnic_address = pk->getQnic_address();
                QubitAddr_cons Addr(-1,pk->getQnic_index(),pk->getQubit_index());
                int nth_shot = tracker[qnic_address].size();
                tracker[qnic_address].insert(std::make_pair(nth_shot,Addr));//qubit with address Addr was shot in nth time. This list is ordered from old to new.
                int new_nth_shot = tracker[qnic_address].size();
                EV<<getQNode()->getFullName() <<": Emitted the "<<nth_shot<<" from qnic["<<qnic_address<<"]....tracker["<<qnic_address<<"] now size = "<<new_nth_shot;
            }
            // switch: Only bubble messages
            switch (pk->getKind()) {
              case STATIONARYQUBIT_PULSE_BEGIN:
                bubble("first.."); break;
              case STATIONARYQUBIT_PULSE_END:
                bubble("last.."); break;
              case STATIONARYQUBIT_PULSE_BOUND:
                bubble("first and last.."); break;
              default:
                bubble("order received!");
            }

            realtime_controller->EmitPhoton(pk->getQnic_index(),pk->getQubit_index(),(QNIC_type) pk->getQnic_type(),pk->getKind());
        }

        else if(dynamic_cast<CombinedBSAresults *>(msg) != nullptr){

            CombinedBSAresults *pk_result = check_and_cast<CombinedBSAresults *>(msg);
            BSMtimingNotifier *pk = check_and_cast<BSMtimingNotifier  *>(msg);
            bubble("trial over is set to true");
            //Set qubits free according to results
            //Also needs to send which qubit was which to the neighbor (not BSA). To update the QubitState table's entangled address.
            incrementBurstTrial(pk->getSrcAddr(), pk->getInternal_qnic_address(), pk->getInternal_qnic_index());
            EV<<"(if internal)The finished qnic["<<pk->getInternal_qnic_index()<<"] with address = "<<pk->getInternal_qnic_address()<<" has emitted tracker["<<pk->getInternal_qnic_address()<<"].size() = "<<tracker[pk->getInternal_qnic_address()].size()<<" photons \n";
            freeFailedQubits(pk->getSrcAddr(), pk->getInternal_qnic_address(), pk->getInternal_qnic_index(), pk_result);
            clearTrackerTable(pk->getSrcAddr(), pk->getInternal_qnic_address());//Clear tracker every end of burst trial. This keeps which qubit fired first, second, third and so on.


            //incrementBurstTrial(pk->getSrcAddr(), pk->getInternal_qnic_address(), pk->getInternal_qnic_index());
            if(pk->getInternal_qnic_index()==-1){//MIM, or the other node without internnal HoM of MM
                EV<<"This BSA request is non-internal\n";
                scheduleFirstPhotonEmission(pk, QNIC_E);
            }else{
                EV<<"This BSA request is internal\n";
                scheduleFirstPhotonEmission(pk, QNIC_R);
            }
        }

        else if(dynamic_cast<SchedulePhotonTransmissionsOnebyOne *>(msg) != nullptr){
            SchedulePhotonTransmissionsOnebyOne *pk = check_and_cast<SchedulePhotonTransmissionsOnebyOne *>(msg);
            EV<<getQNode()->getFullName()<<": Photon shooting is from qnic["<<pk->getQnic_index()<<"] with address="<<pk->getQnic_address();
            if(burstTrial_outdated(pk->getTrial(), pk->getQnic_address())){//Terminate emission if trial is over already (the neighbor ran out of free qubits)
                delete msg;
                return;
            }

            if(pk->getInternal_hom()==0){//for MIM
                shootPhoton(pk);
            }else{//for MM
                shootPhoton_internal(pk);
            }
        }

        else if(dynamic_cast<BSMtimingNotifier *>(msg) != nullptr && dynamic_cast<CombinedBSAresults *>(msg) == nullptr){//Bell pair generation timing syncronization from HoM
            bubble("timing received");
            BSMtimingNotifier *pk = check_and_cast<BSMtimingNotifier *>(msg);
            if(pk->getInternal_qnic_index()==-1){//MIM, or the other node without internnal HoM of MM
                EV<<"This BSA request is non-internal\n";
                scheduleFirstPhotonEmission(pk, QNIC_E);
            }else{
                EV<<"This BSA request is internal\n";
                scheduleFirstPhotonEmission(pk, QNIC_R);
            }
        }

        else if(dynamic_cast<EPPStimingNotifier *>(msg) != nullptr){
           bubble("EPPS");
           EPPStimingNotifier *pk = check_and_cast<EPPStimingNotifier *>(msg);
        }
    delete msg;
}




Interface_inf RuleEngine::getInterface_toNeighbor(int destAddr){
    Interface_inf inf;
    HardwareMonitor::NeighborTable::iterator it = ntable.find(destAddr);
    if (it == ntable.end())
        error("Interface to neighbor not found in neighbor table prepared by the Hardware Manager.... This should probably not happen now.");//Neighbor not found! This should not happen unless you simulate broken links in real time.
    else
        inf = (*it).second;//store gate index connected to the destination (BSA) node by refering to the neighbor table.
    return inf;
}


void RuleEngine::scheduleFirstPhotonEmission(BSMtimingNotifier *pk, QNIC_type qnic_type){

    SchedulePhotonTransmissionsOnebyOne *st = new SchedulePhotonTransmissionsOnebyOne;
    if(ntable.empty())//Just do this once, unless the network changes during the simulation.
        ntable = hardware_monitor->passNeighborTable();//Get neighbor table from Hardware Manager: neighbor address--> Interface_inf.

    int destAddr = pk->getSrcAddr();//The destination is where the request is generated (source of stand-alone or internal BSA node).
    int qnic_index, qnic_address;
    int numFree;
    cModule *qnic_pointer;

    switch (qnic_type) {
        case QNIC_E:
            {
                Interface_inf inf = getInterface_toNeighbor(destAddr);
                qnic_index = inf.qnic.index;
                qnic_address = inf.qnic.address;
            } // inf is not defined beyound this point
            numFree = countFreeQubits_inQnic(stable, qnic_index);//Refer the qubit state table. Check number of free qubits of qnic with index qnic_index.
            break;
        case QNIC_R:
            qnic_address = pk->getInternal_qnic_address();
            qnic_index = pk->getInternal_qnic_index();//If the BSA node is in this node, then obviously it is not in the neighbor table, 'cause it is inside it self. In that case, the gate index is stored in the packet.
            numFree = countFreeQubits_inQnic(stable_r, qnic_index);//Same as above, except the table is managed independently.
            st->setInternal_hom(1);//Mark request that the request is for internal BSA node. Default is 0.
            break;
        case QNIC_RP:
            error("This is not implemented yet");
            break;
        default:
            error("Only 3 qnic types are currently recognized....");
    }

    st->setQnic_index(qnic_index);
    st->setQnic_address(qnic_address);
    EV<<getQNode()->getFullName()<<": First photon shooting is from qnic["<<qnic_index<<"] with address="<<qnic_address;
    st->setInterval(pk->getInterval());
    st->setTiming(pk->getTiming_at());
    st->setTrial(qnic_burst_trial_counter[qnic_address]);//Keeps the burst counter. First burst index is 0.

    if(numFree>0)
        scheduleAt(simTime(), st);
    else{
        delete st;
        //error("This needs to be implemented (Is this needed if entangled particles get consumed properly?). When QNIC buffer is all busy in the 1st shot...");
        //All qubits are free when BSAtimingRequest is received by the node.
    }
}



bool RuleEngine::burstTrial_outdated(int this_trial, int qnic_address){
    bool stop_emitting = false;
    if(this_trial!=qnic_burst_trial_counter[qnic_address]){
        stop_emitting = true;
    } return stop_emitting;
}



void RuleEngine::shootPhoton_internal(SchedulePhotonTransmissionsOnebyOne *pk){

    if(countFreeQubits_inQnic(stable_r, pk->getQnic_index())==0){
        return;
    }

    int qubit_index;
    emt = new  EmitPhotonRequest();
    qubit_index = getOneFreeQubit_inQnic(stable_r, pk->getQnic_index());
    stable_r = setQubitBusy_inQnic(stable_r, pk->getQnic_index(),qubit_index);
    emt->setQubit_index(qubit_index);
    emt->setQnic_index(pk->getQnic_index());
    emt->setQnic_address(pk->getQnic_address());
    emt->setTrial(pk->getTrial());
    emt->setQnic_type(QNIC_R);

    if(pk->getNum_sent() == 0){//First shot!!!
            if(countFreeQubits_inQnic(stable_r, pk->getQnic_index())==0)
                emt->setKind(STATIONARYQUBIT_PULSE_BOUND);//First and last photon.
            else
                emt->setKind(STATIONARYQUBIT_PULSE_BEGIN);//First photon
            scheduleAt(simTime()+pk->getTiming(), emt);
    }else{
            if(countFreeQubits_inQnic(stable_r, pk->getQnic_index())==0)//If no more free qubit
                emt->setKind(STATIONARYQUBIT_PULSE_END);//last one
            else
                emt->setKind(0);//Just a photon in a burst. Not the beginning, nor the end.
            scheduleAt(simTime()+pk->getInterval(), emt);
    }
    scheduleNextEmissionEvent(pk->getQnic_index(),pk->getQnic_address(), pk->getInterval(), pk->getTiming(), pk->getNum_sent(), true, pk->getTrial());
}




//This method is for qnic (not qnic_r, qnic_rp).
void RuleEngine::shootPhoton(SchedulePhotonTransmissionsOnebyOne *pk){

    EV<<pk->getQnic_address()<<", "<<pk->getQnic_index();
    if(countFreeQubits_inQnic(stable, pk->getQnic_index())==0){
        return;
    }

    emt = new  EmitPhotonRequest();
    int qubit_index = getOneFreeQubit_inQnic(stable, pk->getQnic_index());
    stable = setQubitBusy_inQnic(stable, pk->getQnic_index(),qubit_index);
    emt->setQubit_index(qubit_index);
    emt->setQnic_address(pk->getQnic_address());
    emt->setTrial(pk->getTrial());
    emt->setQnic_index(pk->getQnic_index());
    emt->setQnic_type(QNIC_E);

    if(pk->getNum_sent() == 0){
        if(countFreeQubits_inQnic(stable, pk->getQnic_index())==0)
            emt->setKind(STATIONARYQUBIT_PULSE_BOUND);//First and last photon.
        else
            emt->setKind(STATIONARYQUBIT_PULSE_BEGIN);//First photon
        scheduleAt(simTime()+pk->getTiming(), emt);
    }else{
        if(countFreeQubits_inQnic(stable, pk->getQnic_index())==0)
            emt->setKind(STATIONARYQUBIT_PULSE_END);//last one
        else
            emt->setKind(0);//others
        scheduleAt(simTime()+pk->getInterval(), emt);
    }
    scheduleNextEmissionEvent(pk->getQnic_index(),pk->getQnic_address() , pk->getInterval(), pk->getTiming(), pk->getNum_sent(), false, pk->getTrial());
}


void RuleEngine::scheduleNextEmissionEvent(int qnic_index, int qnic_address, double interval, simtime_t timing, int num_sent, bool internal, int trial){
    SchedulePhotonTransmissionsOnebyOne *st = new SchedulePhotonTransmissionsOnebyOne;
    st->setQnic_index(qnic_index);
    st->setQnic_address(qnic_address);
    st->setInterval(interval);
    st->setTiming(timing);
    st->setNum_sent(num_sent+1);//increment
    st->setTrial(trial);
    if(internal)
        st->setInternal_hom(1);
    if(num_sent==0)//First scheduling must be adjusted to timing
        scheduleAt(simTime()+timing, st);
    else//from the second emission, 1 photon per interval
        scheduleAt(simTime()+interval, st);
}


RuleEngine::QubitStateTable RuleEngine::initializeQubitStateTable(QubitStateTable table,QNIC_type qnic_type){
    int qnics = -1;
    switch (qnic_type) {
        case QNIC_E:
            qnics = number_of_qnics; break;
        case QNIC_R:
            qnics = number_of_qnics_r; break;
        case QNIC_RP:
            qnics = number_of_qnics_rp; break;
        default:
            error("Dont put qnic_type except for 0,1 and 2");
    }

    int index = 0;
    for(int i=0; i<qnics; i++){
        for(int x=0; x<hardware_monitor->checkNumBuff(i,qnic_type); x++){
            QubitAddr this_qubit = {parentAddress, i, x};
            QubitAddr entangled_qubit = {-1, -1, -1};//Entangled address. The system may miss-track the actual entangled partner.  Initialized as -1 'cause no entangled qubits in the beginning
            QubitAddr actual = {-1, -1, -1};//Entangled address. This is the true physically entangled partner. If there!=actual, then any operation on the qubit is a mess!
            table[index] = {this_qubit,entangled_qubit,actual,false, simTime()};
            index++;
        }
    } return table;
}



//Just returns first index of free qubit.
int RuleEngine::getOneFreeQubit_inQnic(QubitStateTable table, int qnic_index){
    int free_index = -1;
       for(auto it = table.cbegin(); it != table.cend(); ++it){
            if(it->second.thisQubit_addr.qnic_index == qnic_index && it->second.isBusy == false){
               free_index = it->second.thisQubit_addr.qubit_index;//Just return the up-most qubit index in the qubit state table.
               break;
           }
       }
       if(free_index == -1)
           error("Free qubit not found in qnic. This should not happen because thd program checks it before this method. %d",qnic_index);//This should not happen because
       return free_index;
}

int RuleEngine::countFreeQubits_inQnic(QubitStateTable table, int qnic_index){
    int num_free = 0;
    for(auto it = table.cbegin(); it != table.cend(); ++it){
        if(it->second.thisQubit_addr.qnic_index == qnic_index && table[it->first].isBusy == false){
            num_free++;//count up free qubits in qnic[qnic_index]
        }
    }return num_free;
}

RuleEngine::QubitStateTable RuleEngine::setQubitBusy_inQnic(QubitStateTable table, int qnic_index, int qubit_index){
    for(auto it = table.cbegin(); it != table.cend(); ++it){
           if(it->second.isBusy == false && it->second.thisQubit_addr.qnic_index == qnic_index && it->second.thisQubit_addr.qubit_index == qubit_index){
                table[it->first].isBusy = true;//it->second.isBusy == true somehow works weird..... it does not properly assign the boolean
                break;
            }else if(it->second.isBusy == true && it->second.thisQubit_addr.qnic_index == qnic_index && it->second.thisQubit_addr.qubit_index == qubit_index){
                error("Trying to set a busy qubit busy. Only free qubits can do that. Something is wrong...");
            }
        }
       return table;
}


RuleEngine::QubitStateTable RuleEngine::setQubitFree_inQnic(QubitStateTable table, int qnic_index, int qubit_index){
    for(auto it = table.cbegin(); it != table.cend(); ++it){
           if(it->second.isBusy == true && it->second.thisQubit_addr.qnic_index == qnic_index && it->second.thisQubit_addr.qubit_index == qubit_index){
                table[it->first].isBusy = false;//it->second.isBusy == true somehow works weird..... it does not properly assign the boolean
                break;
            }else if(it->second.isBusy == false && it->second.thisQubit_addr.qnic_index == qnic_index && it->second.thisQubit_addr.qubit_index == qubit_index){
                error("Trying to set a free qubit free. Only busy qubits can do that. Something is wrong... ");
            }
    }return table;
}


void RuleEngine::incrementBurstTrial(int destAddr, int internal_qnic_address, int internal_qnic_index){
     int qnic_address = -1, qnic_index, qnic_type;
     if(internal_qnic_address==-1){//destination hom is outside this node.
         Interface_inf inf = getInterface_toNeighbor(destAddr);
         qnic_index = inf.qnic.index;
         qnic_address = inf.qnic.address;
         qnic_type = QNIC_E;
     }else{//destination hom is in the qnic in this node. This gets invoked when the request from internal hom is send from the same node.
         qnic_address = internal_qnic_address;
         qnic_index = internal_qnic_index;
         qnic_type = QNIC_R;
     }
    qnic_burst_trial_counter[qnic_address]++;//Increment the burst trial counter.
    //You dont need this unless you want to see how many trials have been dealt by each qnic via IDE.
    cModule *qnode = getQNode();
    switch (qnic_type) { // if ((qnic_type == QNIC_E) || (qnic_type == QNIC_R)) // if (qnic_type < QNIC_RP)
        case QNIC_E:
        case QNIC_R:
            qnode->getSubmodule(QNIC_names[qnic_type], qnic_index)->par("burst_trial_counter") = qnic_burst_trial_counter[qnic_address];
    }
}



//Only for MIM and MM
void RuleEngine::freeFailedQubits(int destAddr, int internal_qnic_address, int internal_qnic_index, CombinedBSAresults *pk_result){
    int list_size = pk_result->getList_of_failedArraySize();

    int qnic_index, qnic_address;
    QNIC_type qnic_type;
    if(internal_qnic_index==-1){//destination hom is outside this node.
           Interface_inf inf = getInterface_toNeighbor(destAddr);
           qnic_index = inf.qnic.index;
           qnic_address = inf.qnic.address;
           qnic_type = QNIC_E;
     }else{//destination hom is in the qnic in this node. This gets invoked when the request from internal hom is send from the same node.
           qnic_index = internal_qnic_index;
           qnic_address = internal_qnic_address;
           qnic_type = QNIC_R;
     }

    int num_emitted_in_this_burstTrial = tracker[qnic_address].size();
    EV<<"qnic["<<qnic_index<<"] with type = "<<qnic_type<<"address "<<qnic_address<<" has emitted"<<num_emitted_in_this_burstTrial<<" photons. \n";
    EV<<"num emitted from qnic["<<qnic_address<<"] is "<<num_emitted_in_this_burstTrial;
    for(auto it = tracker[qnic_address].cbegin(); it != tracker[qnic_address].cend(); ++it){
            EV<<it->first<<"th shot was from qnic["<<it->second.qnic_index<<"] qubit["<<it->second.qubit_index<<"] \n ???????????????????????????????????";
    }

    for(int i=0; i<list_size; i++){
        bool failed = pk_result->getList_of_failed(i);
        sentQubitIndexTracker::iterator it = tracker[qnic_address].find(i);//check ith shot's information (qnic, qubit index).
        if (it == tracker[qnic_address].end())
                error("Something is wrong with the tracker....%d th shot not recorded",i);//Neighbor not found! This should not happen unless you simulate broken links in real time.
        if(failed){
            EV<<i<<"th shot has failed.....that was qubit["<<it->second.qubit_index<<"] in qnic["<<it->second.qnic_index<<"]\n";
            realtime_controller->GUI_setQubitFree(it->second.qnic_index ,it->second.qubit_index, qnic_type);
            if(qnic_type==QNIC_E)
                stable = setQubitFree_inQnic(stable, it->second.qnic_index, it->second.qubit_index);
            else
                stable_r = setQubitFree_inQnic(stable_r, it->second.qnic_index, it->second.qubit_index);
        }else{
            //Keep the entangled qubit
            EV<<i<<"th shot has succeeded.....that was qubit["<<it->second.qubit_index<<"] in qnic["<<it->second.qnic_index<<"]\n";
            //Add this as an availabel resource
            //allResources[qnic_type][qnic_index] = ;
            QubitAddr Resource_Addr;
            Resource_Addr.node_address = parentAddress;
            Resource_Addr.qnic_index = qnic_index;
            Resource_Addr.qubit_index = it->second.qubit_index;
            allResources[qnic_type][qnic_index].insert(std::make_pair(destAddr/*QNode IP address*/,Resource_Addr));
            EV<<"There are "<<allResources[qnic_type][qnic_index].count(destAddr)<<" resources between this and "<<destAddr;
            //endSimulation();
        }
    }


    //Any qubit that has been shot while BSA result is actually on the way to the node, needs to be freed as well.
    if(num_emitted_in_this_burstTrial > list_size){
        EV<<num_emitted_in_this_burstTrial<<" shots fired, but only "<<list_size<<" results returned\n";
        for(int i=list_size; i<num_emitted_in_this_burstTrial; i++){
            sentQubitIndexTracker::iterator it = tracker[qnic_address].find(i);//check ith shot's information (qnic, qubit index).
            if (it == tracker[qnic_address].end())
                error("Wait.... something is wrong with the tracker....%d th shot not recorded",i);//Neighbor not found! This should not happen unless you simulate broken links in real time.
            realtime_controller->GUI_setQubitFree(it->second.qnic_index ,it->second.qubit_index, qnic_type);
            if(qnic_type==QNIC_E)
                stable = setQubitFree_inQnic(stable, it->second.qnic_index, it->second.qubit_index);
            else
                stable_r = setQubitFree_inQnic(stable_r, it->second.qnic_index, it->second.qubit_index);
        }
    }
}


void RuleEngine::clearTrackerTable(int destAddr,int internal_qnic_address){
    int qnic_address = -1;
        if(internal_qnic_address==-1){//destination hom is outside this node.
            Interface_inf inf = getInterface_toNeighbor(destAddr);
            qnic_address = inf.qnic.address;
        }else{//destination hom is in the qnic in this node. This gets invoked when the request from internal hom is send from the same node.
            qnic_address = internal_qnic_address;
        }
     if(qnic_address == -1)
         error("Failed clearing tracker of a qnic. This should not happen.");
     tracker[qnic_address].clear();
}


cModule* RuleEngine::getQNode(){
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


void RuleEngine::finish(){
    delete qnic_burst_trial_counter;
    delete realtime_controller;

}

} // namespace modules
} // namespace quisp
