/** \file RuleEngine.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/04/04
 *
 *  \brief RuleEngine
 */
#include "RuleEngine.h"

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

    qnic_job_index = new int[number_of_qnics_all];    //if there are 2 qnics, 1 qnic_r, and 2 qnic_rp, then trial_index[0~1] is assigned for qnics, trial_index[2~2] for qnic_r and trial_index[3~4] for qnic_rp....
    for(int i=0; i<number_of_qnics_all; i++){
       qnic_job_index[i] = 0;
    }

    stable = initializeQubitStateTable(stable, 0);//state for qubits/qnics with MIM links
    stable_r = initializeQubitStateTable(stable_r, 1);//MM links
    stable_rp = initializeQubitStateTable(stable_rp, 2);//MSM links

    tracker = new sentQubitIndexTracker[number_of_qnics_all];//Sent qubit index tracker needs to be prepared per qnic(r,rp)
}

void RuleEngine::handleMessage(cMessage *msg){
        header *pk = check_and_cast<header *>(msg);

        if(dynamic_cast<EmitPhotonRequest *>(msg) != nullptr){//From self.
            EmitPhotonRequest *pk = check_and_cast<EmitPhotonRequest *>(msg);
            cModule *rtc = getParentModule()->getSubmodule("rt");
            RealTimeController *realtime_controller = check_and_cast<RealTimeController *>(rtc);
            EV<<"Emitting photon..... from qnic["<<(int)pk->getQnic_index()<<"] \n";
            EV<<"qnic index = "<<pk->getQnic_index()<<" qubit index = "<<pk->getQubit_index()<<" qnic type = "<<pk->getQnic_type()<<"\n";

            if(qnicJob_outdated(pk->getTrial(), pk->getQnic_index(), pk->getQnic_type())){//Terminate emission if trial is over already (the neighbor ran out of free qubits)
                delete msg;
                return;
            }else{
                //Index the qnic and qubit index to the tracker.
                int global_qnic_index = getQNICjob_index_for_this_qnic(pk->getQnic_index(),pk->getQnic_type());
                QubitAddr_cons Addr(-1,pk->getQnic_index(),pk->getQubit_index());
                int nth_shot = tracker[global_qnic_index].size();
                tracker[global_qnic_index].insert(std::make_pair(nth_shot,Addr));
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
            realtime_controller->EmitPhoton(pk->getQnic_index(),pk->getQubit_index(),pk->getQnic_type(),pk->getKind());
        }

        else if(dynamic_cast<CombinedBSAresults *>(msg) != nullptr){

            CombinedBSAresults *pk_result = check_and_cast<CombinedBSAresults *>(msg);
            BSMtimingNotifier *pk = check_and_cast<BSMtimingNotifier  *>(msg);
            bubble("trial over is set to true");
            //Set qubits free according to results
            //Also needs to send which qubit was which to the neighbor (not BSA). To update the QubitState table's entangled address.
            incrementTrial(pk->getSrcAddr(), pk->getInternal_qnic());
            freeFailedQubits(pk->getSrcAddr(), pk->getInternal_qnic(), pk_result);
            clearTrackerTable(pk->getSrcAddr(), pk->getInternal_qnic());

            if(pk->getInternal_qnic()==-1){//MIM, or the other node without internnal HoM of MM
                EV<<"This BSA request is non-internal\n";
                scheduleFirstPhotonEmission(pk, 0);
            }else{
                EV<<"This BSA request is internal\n";
                scheduleFirstPhotonEmission(pk, 1);
            }
        }

        else if(dynamic_cast<SchedulePhotonTransmissionsOnebyOne *>(msg) != nullptr){
            SchedulePhotonTransmissionsOnebyOne *pk = check_and_cast<SchedulePhotonTransmissionsOnebyOne *>(msg);
            if(pk->getInternal_hom()==0){//for MIM
                if(qnicJob_outdated(pk->getTrial(), pk->getQnic_index(), 0)){//Terminate emission if trial is over already (the neighbor ran out of free qubits)
                    delete msg;
                    return;
                }
                shootPhoton(pk);
            }else{//for MM
                if(qnicJob_outdated(pk->getTrial(), pk->getQnic_index(), 1)){//Terminate emission if trial is over already (the neighbor ran out of free qubits)
                    delete msg;
                    return;
                }
                shootPhoton_internal(pk);
            }
        }

        else if(dynamic_cast<BSMtimingNotifier *>(msg) != nullptr && dynamic_cast<CombinedBSAresults *>(msg) == nullptr){//Bell pair generation timing syncronization from HoM
            bubble("timing received");
            BSMtimingNotifier *pk = check_and_cast<BSMtimingNotifier *>(msg);
            if(pk->getInternal_qnic()==-1){//MIM, or the other node without internnal HoM of MM
                EV<<"This BSA request is non-internal\n";
                scheduleFirstPhotonEmission(pk, 0);
            }else{
                EV<<"This BSA request is internal\n";
                scheduleFirstPhotonEmission(pk, 1);
            }
        }

        else if(dynamic_cast<EPPStimingNotifier *>(msg) != nullptr){
           bubble("EPPS");
           //EPPStimingNotifier *pk = check_and_cast<EPPStimingNotifier *>(msg);
        }
    delete msg;
}

void RuleEngine::clearTrackerTable(int destAddr, int internal_qnic_index){

    int qnic_index = -1, qnic_type;
    if(internal_qnic_index==-1){//destination hom is outside this node.
        qnic_index = getQnicIndex_toNeighbor(destAddr);
        qnic_type = 0;
    }else{//destination hom is in the qnic in this node. This gets invoked when the request from internal hom is send from the same node.
        qnic_index = internal_qnic_index;
        qnic_type = 1;
    }
     int global_qnic_index = getQNICjob_index_for_this_qnic(qnic_index,qnic_type);
     tracker[global_qnic_index].clear();
}

void RuleEngine::incrementTrial(int destAddr, int internal_qnic_index){
     int qnic_index = -1, qnic_type;
     if(internal_qnic_index==-1){//destination hom is outside this node.
         qnic_index = getQnicIndex_toNeighbor(destAddr);
         qnic_type = 0;
     }else{//destination hom is in the qnic in this node. This gets invoked when the request from internal hom is send from the same node.
         qnic_index = internal_qnic_index;
         qnic_type = 1;
     }
    int job_index = getQNICjob_index_for_this_qnic(qnic_index ,qnic_type);
    qnic_job_index[job_index]++;
    //Just so that you can check how many jobs has been dealt by each qnic via IDE.
    cModule *qnode = getQNode();
    if(qnic_type == 0){
        qnode->getSubmodule("qnic", qnic_index)->par("job_index") = qnic_job_index[job_index];
    }else if(qnic_type==1){
        qnode->getSubmodule("qnic_r", qnic_index)->par("job_index") = qnic_job_index[job_index];
    }
}

int RuleEngine::getQNICjob_index_for_this_qnic(int qnic_index, int qnic_type){
    if (qnic_type<0 || qnic_type>2) error("Unknown qnic type");
    int index = qnic_index;
    if (qnic_type>0) index += number_of_qnics;
    if (qnic_type>1) index += number_of_qnics_r;
    return index;
}

RuleEngine::QubitStateTable RuleEngine::initializeQubitStateTable(QubitStateTable table,int qnic_type){
    int qnics = -1;
    if(qnic_type == 0){//MIM
        qnics = number_of_qnics;
    }else if(qnic_type ==1){//MM
        qnics = number_of_qnics_r;
    }else if(qnic_type ==2){//MSM
        qnics = number_of_qnics_rp;
    }else{
        error("Dont put qnic_type except for 0,1 and 2");
    }

    int index = 0;
    for(int i=0; i<qnics; i++){
        for(int x=0; x<hardware_monitor->checkNumBuff(i,qnic_type); x++){
            QubitAddr here = {parentAddress, i, x};
            QubitAddr there = {-1, -1, -1};//Entangled address. The system may miss-track the actual entangled partner.  Initialized as -1 'cause no entangled qubits in the beginning
            QubitAddr actual = {-1, -1, -1};//Entangled address. This is the true physically entangled partner. If there!=actual, then any operation on the qubit is a mess!
            table[index] = {here,there,actual,false, simTime()};
            index++;
        }
    } return table;
}

bool RuleEngine::qnicJob_outdated(int job_index, int qnic_index, int qnic_type){
    bool stop_emitting = false;
    int current_job_index = getQNICjob_index_for_this_qnic(qnic_index, qnic_type);
    if(job_index!=/*trial_index*/qnic_job_index[current_job_index]){
        stop_emitting = true;
    } return stop_emitting;
}

//Only for MIM and MM
void RuleEngine::freeFailedQubits(int destAddr, int internal_qnic_index, CombinedBSAresults *pk_result){
    int list_size = pk_result->getList_of_failedArraySize();

    int qnic_index, qnic_type;
    if(internal_qnic_index==-1){//destination hom is outside this node.
           qnic_index = getQnicIndex_toNeighbor(destAddr);
           qnic_type = 0;
     }else{//destination hom is in the qnic in this node. This gets invoked when the request from internal hom is send from the same node.
           qnic_index = internal_qnic_index;
           qnic_type = 1;
     }
    int global_qnic_index = getQNICjob_index_for_this_qnic(qnic_index,qnic_type);
    //QubitAddr_cons Addr(-1,pk->getQnic_index(),pk->getQubit_index());
    int shot_fired = tracker[global_qnic_index].size();
    for (auto it = tracker[global_qnic_index].begin(); it != tracker[global_qnic_index].end(); it++){
        EV<<"QNIC["<<it->second.qnic_index<<"]: "<<it->first<<"th shot is from qubit["<<it->second.qubit_index<<"]\n";
    }

    for(int i=0; i<list_size; i++){
        bool failed = pk_result->getList_of_failed(i);
        sentQubitIndexTracker::iterator it = tracker[global_qnic_index].find(i);//check ith shot's information (qnic, qubit index).
        if (it == tracker[global_qnic_index].end())
                error("Something is wrong with the tracker....%d th shot not recorded",i);//Neighbor not found! This should not happen unless you simulate broken links in real time.

        if(failed){
            EV<<i<<"th shot has failed.....that was qubit["<<it->second.qubit_index<<"] in qnic["<<it->second.qnic_index<<"\n";
            realtime_controller->GUI_setQubitFree(it->second.qnic_index ,it->second.qubit_index, qnic_type);
            if(qnic_type==0)
                stable = setQubitFree(stable, it->second.qnic_index, it->second.qubit_index);
            else
                stable_r = setQubitFree(stable_r, it->second.qnic_index, it->second.qubit_index);
        }else{
            EV<<i<<"th shot has succeeded.....that was qubit["<<it->second.qubit_index<<"] in qnic["<<it->second.qnic_index<<"\n";
        }
    }

    //Any qubit that has been shot while BSA result is actually on the way to the node, needs to be freed as well.
    if(shot_fired > list_size){
        EV<<shot_fired<<" shots fired, but only "<<list_size<<" results returned\n";
        for(int i=list_size; i<shot_fired; i++){
            sentQubitIndexTracker::iterator it = tracker[global_qnic_index].find(i);//check ith shot's information (qnic, qubit index).
            if (it == tracker[global_qnic_index].end())
                error("Wait.... something is wrong with the tracker....%d th shot not recorded",i);//Neighbor not found! This should not happen unless you simulate broken links in real time.
            realtime_controller->GUI_setQubitFree(it->second.qnic_index ,it->second.qubit_index, qnic_type);
            if(qnic_type==0)
                stable = setQubitFree(stable, it->second.qnic_index, it->second.qubit_index);
            else
                stable_r = setQubitFree(stable_r, it->second.qnic_index, it->second.qubit_index);
        }//endSimulation();
    }
}

void RuleEngine::scheduleNextEmissionEvent(int qnic_index, double interval, simtime_t timing, int num_sent, bool internal, int trial){
    SchedulePhotonTransmissionsOnebyOne *st = new SchedulePhotonTransmissionsOnebyOne;
    st->setQnic_index(qnic_index);
    st->setInterval(interval);
    st->setTiming(timing);
    st->setNum_sent(num_sent+1);
    st->setTrial(trial);
    if(internal)
        st->setInternal_hom(1);
    if(num_sent==0)//First scheduling must be adjusted to timing
        scheduleAt(simTime()+timing, st);
    else//from the second emission, 1 photon per interval
        scheduleAt(simTime()+interval, st);
}

void RuleEngine::shootPhoton_internal(SchedulePhotonTransmissionsOnebyOne *pk){

    if(getFreeBufferSize_stateTable(stable_r, pk->getQnic_index())==0){
        return;
    }

    if(pk->getNum_sent() == 0){//Firts shot!!!
            emt = new  EmitPhotonRequest();
            int qubit_index;
            qubit_index = getOneFreeQubit(stable_r, pk->getQnic_index());
            stable_r = setQubitBusy(stable_r, pk->getQnic_index(),qubit_index);
            emt->setQubit_index(qubit_index);
            emt->setQnic_index(pk->getQnic_index());
            if(getFreeBufferSize_stateTable(stable_r, pk->getQnic_index())==0){
                emt->setKind(STATIONARYQUBIT_PULSE_BOUND);//First and last photon.
            }else{
                emt->setKind(STATIONARYQUBIT_PULSE_BEGIN);//First photon
            }
            emt->setTrial(pk->getTrial());
            emt->setQnic_type(1);
            scheduleAt(simTime()+pk->getTiming(), emt);

            scheduleNextEmissionEvent(pk->getQnic_index(), pk->getInterval(), pk->getTiming(), pk->getNum_sent(), true, pk->getTrial());
   }else{

       emt = new  EmitPhotonRequest();
       int qubit_index;
       qubit_index = getOneFreeQubit(stable_r, pk->getQnic_index());
       stable_r = setQubitBusy(stable_r, pk->getQnic_index(),qubit_index);
       emt->setQubit_index(qubit_index);
       emt->setTrial(pk->getTrial());
       emt->setQnic_index(pk->getQnic_index());
       if(getFreeBufferSize_stateTable(stable_r, pk->getQnic_index())==0){//If no more free qubit
           emt->setKind(STATIONARYQUBIT_PULSE_END);//last one
       }else {
           emt->setKind(0);//others
       }
       emt->setQnic_type(1);
       scheduleAt(simTime()+pk->getInterval(), emt);
       EV<<"Is Internal:  Currently "<<getFreeBufferSize_stateTable(stable, pk->getQnic_index())<<" remaining....";
       if(getFreeBufferSize_stateTable(stable_r, pk->getQnic_index())!=0){//This may not be right... If more than 1 qubit got freed after some operation...
           scheduleNextEmissionEvent(pk->getQnic_index(), pk->getInterval(), pk->getTiming(), pk->getNum_sent(), true, pk->getTrial());
       }
   }
}

//This method is for qnic (not qnic_r, qnic_rp).
void RuleEngine::shootPhoton(SchedulePhotonTransmissionsOnebyOne *pk){
    if(getFreeBufferSize_stateTable(stable, pk->getQnic_index())==0){
        return;
    }

    if(pk->getNum_sent() == 0){
        emt = new  EmitPhotonRequest();
        int qubit_index;
        qubit_index = getOneFreeQubit(stable, pk->getQnic_index());
        stable = setQubitBusy(stable, pk->getQnic_index(),qubit_index);
        emt->setQubit_index(qubit_index);
        emt->setTrial(pk->getTrial());//inherit the trial/job index
        emt->setQnic_index(pk->getQnic_index());
        if(getFreeBufferSize_stateTable(stable, pk->getQnic_index())==0){
            emt->setKind(STATIONARYQUBIT_PULSE_BOUND);//First and last photon.
        }else{
            emt->setKind(STATIONARYQUBIT_PULSE_BEGIN);//First photon
        }
        emt->setQnic_type(0);
        scheduleAt(simTime()+pk->getTiming(), emt);
        scheduleNextEmissionEvent(pk->getQnic_index(), pk->getInterval(), pk->getTiming(), pk->getNum_sent(), false, pk->getTrial());
    }else{
        emt = new  EmitPhotonRequest();
        int qubit_index;
        qubit_index = getOneFreeQubit(stable, pk->getQnic_index());
        stable = setQubitBusy(stable, pk->getQnic_index(),qubit_index);
        emt->setQubit_index(qubit_index);
        emt->setTrial(pk->getTrial());
        emt->setQnic_index(pk->getQnic_index());

        if(getFreeBufferSize_stateTable(stable, pk->getQnic_index())==0){
            emt->setKind(STATIONARYQUBIT_PULSE_END);//last one
        }else {
            emt->setKind(0);//others
        }
        emt->setQnic_type(0);
        scheduleAt(simTime()+pk->getInterval(), emt);
        EV<<"Not Internal:  Currently "<<getFreeBufferSize_stateTable(stable, pk->getQnic_index())<<" remaining....";

        if(getFreeBufferSize_stateTable(stable, pk->getQnic_index())!=0){
            scheduleNextEmissionEvent(pk->getQnic_index(), pk->getInterval(), pk->getTiming(), pk->getNum_sent(), false, pk->getTrial());
        }
    }
}

int RuleEngine::getQnicIndex_toNeighbor(int destAddr){
    int qnic_index = -1;
    HardwareMonitor::NeighborTable::iterator it = ntable.find(destAddr);
    if (it == ntable.end())
        error("qnic index to neighbor not found....");//Neighbor not found! This should not happen unless you simulate broken links in real time.
    else
        qnic_index = (*it).second;//store gate index connected to the destination (BSA) node by refering to the neighbor table.
    return qnic_index;
}

void RuleEngine::scheduleFirstPhotonEmission(BSMtimingNotifier *pk, int qnic_type){

    SchedulePhotonTransmissionsOnebyOne *st = new SchedulePhotonTransmissionsOnebyOne;
    if(ntable.empty())//Just do this once, unless the network changes during the simulation.
        ntable = hardware_monitor->passNeighborTable();//Ask hm to fill in neighbor table: neighbor address-->local gate index. Only for MIM and MM links

    int destAddr = pk->getSrcAddr();//The destination is where the request is generated (source of stand-alone or internal BSA node).
    int qnic_index = -1;
    if(qnic_type == 0)//MIM
        qnic_index = getQnicIndex_toNeighbor(destAddr);
    else if(qnic_type == 1)//MM
        qnic_index = pk->getInternal_qnic();;//If the BSA node is in this node, then obviously it is not in the neighbor table, 'cause it is inside it self. In that case, the gate index is stored in the packet.
    if(qnic_index == -1)
        error("something wrong... qnic index to destination not found");

    int numFree;
    if(qnic_type == 0){//MIM
        numFree = getFreeBufferSize_stateTable(stable, qnic_index);//Refer the qubit state table. Check number of free qubits of qnic with index qnic_index.
        EV<<"This first schedule is non-internal ....free="<<numFree<<" in qnic["<<qnic_index<<"]\n";
    }else{//MM
        numFree = getFreeBufferSize_stateTable(stable_r, qnic_index);//Same as above, except the table is managed independently.
        EV<<"!!!!This is first schedule internal... qnic type == "<<qnic_type<<" free="<<numFree<<"\n";
        st->setInternal_hom(1);//Mark request that the request is for internal BSA node.
    }
    st->setQnic_index(qnic_index);
    st->setInterval(pk->getInterval());
    st->setTiming(pk->getTiming_at());
    int index = getQNICjob_index_for_this_qnic(qnic_index ,qnic_type);

    st->setTrial(qnic_job_index[index]);
    if(numFree>0)
        scheduleAt(simTime(), st);
    else{
        delete st;
        //error("This needs to be implemented. When QNIC buffer is all busy in the 1st shot...");
        //All qubits are free when BSAtimingRequest is received by the node.
    }
}

//Just returns first index of free qubit.
int RuleEngine::getOneFreeQubit(QubitStateTable table, int qnic_index){
    int free_index = -1;
       for(auto it = table.cbegin(); it != table.cend(); ++it){
           //EV<<"free? = "<<it->second.isBusy<<" qubit index with"<<it->second.thisQubit_addr.qubit_index<<"\n";
            if(it->second.thisQubit_addr.qnic_index == qnic_index && it->second.isBusy == false){
               free_index = it->second.thisQubit_addr.qubit_index;//Just return the up-most qubit index in the qubit state table.

               break;
           }
       }
       if(free_index == -1)
           error("free qubit not found? %d",qnic_index);//Doesnt have to be an error actually.... just for now.
       return free_index;
}

int RuleEngine::getFreeBufferSize_stateTable(QubitStateTable table, int qnic_index){
    int num_free = 0;
    for(auto it = table.cbegin(); it != table.cend(); ++it){
        if(it->second.thisQubit_addr.qnic_index == qnic_index &&  table[it->first].isBusy == false){
            num_free++;//count up free qubits in qnic[qnic_index]
        }
    }
    return num_free;
}

RuleEngine::QubitStateTable RuleEngine::setQubitBusy(QubitStateTable table, int qnic_index, int qubit_index){
    for(auto it = table.cbegin(); it != table.cend(); ++it){
           if(it->second.isBusy == false && it->second.thisQubit_addr.qnic_index == qnic_index && it->second.thisQubit_addr.qubit_index == qubit_index){
                table[it->first].isBusy = true;//it->second.isBusy == true somehow works weird..... it does not properly assign the boolean
                break;
            }else if(it->second.isBusy == true && it->second.thisQubit_addr.qnic_index == qnic_index && it->second.thisQubit_addr.qubit_index == qubit_index){
                error("Something is wrong with tracking busy of each qubit. ");
            }
        }
       return table;
}

RuleEngine::QubitStateTable RuleEngine::setQubitFree(QubitStateTable table, int qnic_index, int qubit_index){
    for(auto it = table.cbegin(); it != table.cend(); ++it){
           if(it->second.isBusy == true && it->second.thisQubit_addr.qnic_index == qnic_index && it->second.thisQubit_addr.qubit_index == qubit_index){
                table[it->first].isBusy = false;//it->second.isBusy == true somehow works weird..... it does not properly assign the boolean
                break;
            }else if(it->second.isBusy == false && it->second.thisQubit_addr.qnic_index == qnic_index && it->second.thisQubit_addr.qubit_index == qubit_index){
                error("Something is wrong with tracking busy of each qubit when freeing. ");
            }
        }
       return table;
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
    delete qnic_job_index;
    delete realtime_controller;

}

} // namespace modules
} // namespace quisp
