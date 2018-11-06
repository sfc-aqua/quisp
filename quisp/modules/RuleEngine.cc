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

using namespace rules;

void RuleEngine::initialize()
{
    //HardwareMonitor's neighbor table is checked in the initialization stage of the simulation
    //This assumes the topology never changes throughout the simulation.
    //If dynamic change in topology is required, recoding this is needed.
    cModule *hm = getParentModule()->getSubmodule("hm");
    hardware_monitor = check_and_cast<HardwareMonitor *>(hm);
    cModule *rt = getParentModule()->getSubmodule("rt");
    realtime_controller = check_and_cast<RealTimeController *>(rt);//Just for qubit color update and Pauli error elimination
    parentAddress = par("address");
    number_of_qnics_all = par("total_number_of_qnics");
    number_of_qnics = par("number_of_qnics");
    number_of_qnics_r = par("number_of_qnics_r");
    number_of_qnics_rp = par("number_of_qnics_rp");

    qnic_burst_trial_counter = new int[number_of_qnics_all];    //if there are 2 qnics, 1 qnic_r, and 2 qnic_rp, then trial_index[0~1] is assigned for qnics, trial_index[2~2] for qnic_r and trial_index[3~4] for qnic_rp....
    for(int i=0; i<number_of_qnics_all; i++){
       qnic_burst_trial_counter[i] = 0;
    }

    Busy_OR_Free_QubitState_table = new QubitStateTable[QNIC_N];
    Busy_OR_Free_QubitState_table[QNIC_E] = initializeQubitStateTable(Busy_OR_Free_QubitState_table[QNIC_E], QNIC_E);
    Busy_OR_Free_QubitState_table[QNIC_R] = initializeQubitStateTable(Busy_OR_Free_QubitState_table[QNIC_R], QNIC_R);
    Busy_OR_Free_QubitState_table[QNIC_RP] = initializeQubitStateTable(Busy_OR_Free_QubitState_table[QNIC_RP], QNIC_RP);

    tracker = new sentQubitIndexTracker[number_of_qnics_all];//Tracks which qubit was sent first, second and so on per qnic(r,rp)

    /*Initialize resource list by Age for the actual use of qubits in operations*/
    allResources = new qnicResources[QNIC_N];
    allResources[QNIC_E] = new EntangledPairs[number_of_qnics];
    allResources[QNIC_R] = new EntangledPairs[number_of_qnics_r];
    allResources[QNIC_RP] = new EntangledPairs[number_of_qnics_rp];

    //running_processes = new RuleSetPtr[QNIC_N];//One process per QNIC for now. No multiplexing.

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

        else if(dynamic_cast<PurificationResult *>(msg) != nullptr){

            PurificationResult *pkt = check_and_cast<PurificationResult *>(msg);
            //std::cout<<"Presult from node["<<pkt->getSrcAddr()<<"]\n";
            process_id purification_id;
            purification_result pr;
            purification_id.ruleset_id = pkt->getRuleset_id();
            purification_id.rule_id = pkt->getRule_id();
            purification_id.index = pkt->getAction_index();
            pr.id = purification_id;
            pr.outcome = pkt->getOutput_is_plus();

            QNIC_type my_qnic_type;
            int my_qnic_index = -1;
            for(auto it = ntable.cbegin(); it != ntable.cend(); ++it){
                if(it->second.neighborQNode_address == pkt->getSrcAddr()){
                    my_qnic_type = it->second.qnic.type;
                    my_qnic_index = it->second.qnic.index;
                    break;
                }
            }if(my_qnic_index == -1){
                error("2. Something is wrong when finding out local qnic address from neighbor address in ntable.");
            }
            //std::cout<<"Purification result is from node["<<pkt->getSrcAddr()<<"] rid="<< pkt->getRuleset_id()<<"Must be qnic["<<my_qnic_index<<" type="<<my_qnic_type<<"\n";
            check_Purification_Agreement(pr);
            //delete pkt;

        }

        else if(dynamic_cast<CombinedBSAresults *>(msg) != nullptr){
            //First, keep all the qubits that were successfully entangled, and reinitialize the failed ones.
            CombinedBSAresults *pk_result = check_and_cast<CombinedBSAresults *>(msg);
            BSMtimingNotifier *pk = check_and_cast<BSMtimingNotifier  *>(msg);
            bubble("trial over is set to true");
            //Set qubits free according to results
            //Also needs to send which qubit was which to the neighbor (not BSA but the neighboring QNode). To update the QubitState table's entangled address.
            incrementBurstTrial(pk->getSrcAddr(), pk->getInternal_qnic_address(), pk->getInternal_qnic_index());
            EV<<"(if internal)The finished qnic["<<pk->getInternal_qnic_index()<<"] with address = "<<pk->getInternal_qnic_address()<<" has emitted tracker["<<pk->getInternal_qnic_address()<<"].size() = "<<tracker[pk->getInternal_qnic_address()].size()<<" photons \n";
            //Updates free/busy of qubits, and also adds successfully entangled qubits as resources.
            freeFailedQubits_and_AddAsResource(pk->getSrcAddr(), pk->getInternal_qnic_address(), pk->getInternal_qnic_index(), pk_result);
            clearTrackerTable(pk->getSrcAddr(), pk->getInternal_qnic_address());//Clear tracker every end of burst trial. This keeps which qubit was fired first, second, third and so on only for that trial.


            //Second, schedule the next burst by referring to the received timing information.
            int qnic_address, qnic_type;
            int qnic_index, neighborQNodeAddress;
            if(pk->getInternal_qnic_address()==-1){//destination hom is outside this node.
                   Interface_inf inf = getInterface_toNeighbor(pk->getSrcAddr());
                   qnic_index = inf.qnic.index;
                   qnic_address = inf.qnic.address;
                   qnic_type = QNIC_E;
                   //neighborQNodeAddress = inf.neighborQNode_address;
             }else{//destination hom is in the qnic in this node. This gets invoked when the request from internal hom is send from the same node.
                   qnic_index = pk->getInternal_qnic_index();
                   qnic_address = pk->getInternal_qnic_address();
                   qnic_type = QNIC_R;
             }

            for (EntangledPairs::iterator it =  allResources[qnic_type][qnic_index].begin(); it != allResources[qnic_type][qnic_index].end(); it++)
                EV << it->first << " => " << it->second << '\n';
            EV<< "****************************************\n";

            //Schedule next burst
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
        else if(dynamic_cast<LinkTomographyRuleSet *>(msg) != nullptr){
           //Received a tomography rule set.
           LinkTomographyRuleSet *pk = check_and_cast<LinkTomographyRuleSet *>(msg);
           process p;
           p.ownner_addr = pk->getRuleSet()->owner;
           p.working_partner_addr = pk->getRuleSet()->entangled_partner;
           p.RuleSet = pk->getRuleSet();
           int process_id = rp.size();//This is temporary because it will not be unique when processes have been deleted.
           EV<<"Ruleset arrived id="<<p.RuleSet->ruleset_id<<"\n";
           EV<<"Process size is ...."<<p.RuleSet->size()<<"\n";

           if(p.RuleSet->size()>0){
               rp.insert(std::make_pair(process_id, p));
               EV<<"New process arrived !\n";

               //traverseThroughAllProcesses(int qnic_type, int qnic_index);
               //error("die");

           }else{
               error("Empty rule set...");
           }
        }
        //traverseThroughAllProcesses2();
        delete msg;


}







void RuleEngine::check_Purification_Agreement(purification_result pr){

    //std::cout<<"check_Purification_Agreement: "<<pr.id.ruleset_id<<"\n";
    //std::cout<<"rp size = "<<rp.size()<<"\n";

    bool ruleset_running = false;
    for(auto it = rp.cbegin(), next_it = rp.cbegin(); it != rp.cend(); it = next_it){
               next_it = it; ++next_it;
               RuleSet* process = it->second.RuleSet;//One Process. From top to bottom.
               if(process->ruleset_id == pr.id.ruleset_id){
                   ruleset_running = true;
                   break;
               }
    }
    if(rp.size()==0 || !ruleset_running){
        //Already finished process. delete the table and ignore the result.
        return;
    }else{
        auto ret = Purification_table.equal_range(pr.id.ruleset_id);//Find all resource in qytpe/qid entangled with partner.
        //If the RuleSet has been deleted already, do not do anything.


        for (auto it=ret.first; it!=ret.second; it++) {
            if(it->second.id.rule_id == pr.id.rule_id && it->second.id.index == pr.id.index){
                //std::cout<<"Rule_id="<<pr.id.rule_id<<", index="<<pr.id.index<<"\n";
                //std::cout<<"node["<<parentAddress<<"] Rule found: Discard/Keep purification.\n";
                if(it->second.outcome == pr.outcome){
                //Outcomes agreed. Keep the entangled pair.
                    Unlock_resource_and_upgrade_stage(pr.id.ruleset_id, pr.id.rule_id, pr.id.index);
                }else{
                //Discard
                    //std::cout<<"node["<<parentAddress<<"] discaard ";
                    Unlock_resource_and_discard(pr.id.ruleset_id, pr.id.rule_id, pr.id.index);
                }
                Purification_table.erase(it);
                return;
            }
        }
    }
}


void RuleEngine::Unlock_resource_and_upgrade_stage(unsigned long ruleset_id, int rule_id, int index){
    bool ok = false;
    for(auto it = rp.cbegin(), next_it = rp.cbegin(); it != rp.cend(); it = next_it){//In a particular RuleSet
            next_it = it; ++next_it;
            if(it->second.RuleSet->ruleset_id == ruleset_id){//Find the corresponding ruleset.
                RuleSet* process = it->second.RuleSet;//One Process. From top to bottom.
                for (auto rule=process->cbegin(), end=process->cend(); rule!=end; rule++){//Traverse through rules
                    if((*rule)->rule_index == rule_id){//Find the corresponding rule.
                        for (auto qubit=(*rule)->resources.begin(); qubit!=(*rule)->resources.end(); ++qubit) {
                            if(qubit->second->action_index == index){
                                //Correct resource found! Need to unlock and stage up the resource to the next rule.
                                qubit->second->Unlock();
                                //std::cout<<"node["<<parentAddress<<"] Upgrade Unlock "<<qubit->second<<"\n";
                                stationaryQubit *q = qubit->second;
                                (*rule)->resources.erase(qubit);//Erase this from resource list
                                rule++;
                                if(rule==end){
                                    error("Rule came to end after operation (e.g. purification) success");
                                }
                                int rsc_index = (*rule)->resources.size();
                                (*rule)->resources.insert(std::make_pair(rsc_index, q));
                                ok = true;
                                return;
                            }
                        }
                    }
                }
            }
    }
    if(!ok){
        error("Upgrade: Resource in rule not found....");
    }
}


void RuleEngine::Unlock_resource_and_discard(unsigned long ruleset_id, int rule_id, int index){
    bool ok = false;
    for(auto it = rp.cbegin(), next_it = rp.cbegin(); it != rp.cend(); it = next_it){//In a particular RuleSet
            next_it = it; ++next_it;
            if(it->second.RuleSet->ruleset_id == ruleset_id){//Find the corresponding ruleset.
                RuleSet* process = it->second.RuleSet;//One Process. From top to bottom.
                for (auto rule=process->cbegin(), end=process->cend(); rule!=end; rule++){//Traverse through rules
                    if((*rule)->rule_index == rule_id){//Find the corresponding rule.
                        for (auto qubit=(*rule)->resources.begin(); qubit!=(*rule)->resources.end(); ++qubit) {
                            //std::cout<<".....node["<<qubit->second->node_address<<" qnic["<<qubit->second->qnic_index<<"]" << qubit->second<<"\n";
                            if(qubit->second->action_index == index){
                                //Correct resource found! Need to unlock and stage up the resource to the next rule.
                                //qubit->second->Unlock();
                                //std::cout<<"Purification Failed Discard "<<qubit->second<<"\n";
                                QNIC_type qt = (QNIC_type)qubit->second->qnic_type;
                                qubit->second->par("GOD_Xerror")=false;
                                qubit->second->par("GOD_Zerror")=false;
                                //std::cout<<"node["<<qubit->second->node_address<<"]"<<qubit->second<<" X = "<<qubit->second->par("GOD_Xerror").str()<<" Z = "<<qubit->second->par("GOD_Zerror").str()<<"\n";
                                //std::cout<<"Rule id = "<<qubit->second->rs<<"\n";
                                //std::cout<<"Freeing qnic["<<qubit->second->qnic_index<<"]"<<"qnic type="<<qt<<" btw addr="<<qubit->second->qnic_address<<"\n";

                                freeConsumedResource(qubit->second->qnic_index, qubit->second, qt);//Remove from entangled resource list.
                                (*rule)->resources.erase(qubit);//Erase this from resource list                                                               ok = true;
                                return;
                            }
                        }
                    }
                }
            }
    }
    if(!ok){
        error("Discard: Resource in rule not found....");
    }
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


Interface_inf RuleEngine::getInterface_toNeighbor_Internal(int local_qnic_address){
    Interface_inf inf;
    for (auto i = ntable.begin(); i != ntable.end(); i++){
        if (i == ntable.end())
            error("Interface to neighbor not found in neighbor table prepared by the Hardware Manager.... This should probably not happen now.");//Neighbor not found! This should not happen unless you simulate broken links in real time.
        if(i->second.qnic.address == local_qnic_address)
            inf = (*i).second;
    }
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
            numFree = countFreeQubits_inQnic(Busy_OR_Free_QubitState_table[QNIC_E], qnic_index);//Refer the qubit state table. Check number of free qubits of qnic with index qnic_index.
            break;
        case QNIC_R:
            qnic_address = pk->getInternal_qnic_address();
            qnic_index = pk->getInternal_qnic_index();//If the BSA node is in this node, then obviously it is not in the neighbor table, 'cause it is inside it self. In that case, the gate index is stored in the packet.
            numFree = countFreeQubits_inQnic(Busy_OR_Free_QubitState_table[QNIC_R], qnic_index);//Same as above, except the table is managed independently.
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

    if(countFreeQubits_inQnic(Busy_OR_Free_QubitState_table[QNIC_R], pk->getQnic_index())==0){
        return;
    }

    int qubit_index;
    emt = new  EmitPhotonRequest();
    qubit_index = getOneFreeQubit_inQnic(Busy_OR_Free_QubitState_table[QNIC_R], pk->getQnic_index());
    Busy_OR_Free_QubitState_table[QNIC_R] = setQubitBusy_inQnic(Busy_OR_Free_QubitState_table[QNIC_R], pk->getQnic_index(),qubit_index);
    emt->setQubit_index(qubit_index);
    emt->setQnic_index(pk->getQnic_index());
    emt->setQnic_address(pk->getQnic_address());
    emt->setTrial(pk->getTrial());
    emt->setQnic_type(QNIC_R);

    if(pk->getNum_sent() == 0){//First shot!!!
            if(countFreeQubits_inQnic(Busy_OR_Free_QubitState_table[QNIC_R], pk->getQnic_index())==0)
                emt->setKind(STATIONARYQUBIT_PULSE_BOUND);//First and last photon.
            else
                emt->setKind(STATIONARYQUBIT_PULSE_BEGIN);//First photon
            scheduleAt(simTime()+pk->getTiming(), emt);
    }else{
            if(countFreeQubits_inQnic(Busy_OR_Free_QubitState_table[QNIC_R], pk->getQnic_index())==0)//If no more free qubit
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
    if(countFreeQubits_inQnic(Busy_OR_Free_QubitState_table[QNIC_E], pk->getQnic_index())==0){
        return;
    }

    emt = new  EmitPhotonRequest();
    int qubit_index = getOneFreeQubit_inQnic(Busy_OR_Free_QubitState_table[QNIC_E], pk->getQnic_index());
    Busy_OR_Free_QubitState_table[QNIC_E] = setQubitBusy_inQnic(Busy_OR_Free_QubitState_table[QNIC_E], pk->getQnic_index(),qubit_index);
    emt->setQubit_index(qubit_index);
    emt->setQnic_address(pk->getQnic_address());
    emt->setTrial(pk->getTrial());
    emt->setQnic_index(pk->getQnic_index());
    emt->setQnic_type(QNIC_E);

    if(pk->getNum_sent() == 0){
        if(countFreeQubits_inQnic(Busy_OR_Free_QubitState_table[QNIC_E], pk->getQnic_index())==0)
            emt->setKind(STATIONARYQUBIT_PULSE_BOUND);//First and last photon.
        else
            emt->setKind(STATIONARYQUBIT_PULSE_BEGIN);//First photon
        scheduleAt(simTime()+pk->getTiming(), emt);
    }else{
        if(countFreeQubits_inQnic(Busy_OR_Free_QubitState_table[QNIC_E], pk->getQnic_index())==0)
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
            //QubitAddr entangled_qubit = {-1, -1, -1};//Entangled address. The system may miss-track the actual entangled partner.  Initialized as -1 'cause no entangled qubits in the beginning
            //QubitAddr actual = {-1, -1, -1};//Entangled address. This is the true physically entangled partner. If there!=actual, then any operation on the qubit is a mess!
            //table[index] = {this_qubit,entangled_qubit,actual,false, simTime()};
            table[index] = {this_qubit, false, simTime()};//Only stores which qubit is busy or free, and when it became busy.
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
                table[it->first].isBusy = true;
                break;
            }else if(it->second.isBusy == true && it->second.thisQubit_addr.qnic_index == qnic_index && it->second.thisQubit_addr.qubit_index == qubit_index){
                error("Trying to set a busy qubit busy. Only free qubits can do that. Something is wrong...");
            }
        }
       return table;
}


RuleEngine::QubitStateTable RuleEngine::setQubitFree_inQnic(QubitStateTable table, int qnic_index, int qubit_index){
    for(auto it = table.cbegin(); it != table.cend(); ++it){
        //std::cout<<it->first<<" table = "<<table[it->first].isBusy<<"\n";
           if(it->second.isBusy == true && it->second.thisQubit_addr.qnic_index == qnic_index && it->second.thisQubit_addr.qubit_index == qubit_index){
                table[it->first].isBusy = false;
                break;
            }else if(it->second.isBusy == false && it->second.thisQubit_addr.qnic_index == qnic_index && it->second.thisQubit_addr.qubit_index == qubit_index){
                //std::cout<<"isBusy = "<<table[it->first].isBusy<<"\n";
                //std::cout<<"Busy = "<<(it->second.isBusy==false)<<" && "<<(it->second.thisQubit_addr.qnic_index == qnic_index)<<" && "<<(it->second.thisQubit_addr.qubit_index == qubit_index)<<"\n";
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
void RuleEngine::freeFailedQubits_and_AddAsResource(int destAddr, int internal_qnic_address, int internal_qnic_index, CombinedBSAresults *pk_result){
    int list_size = pk_result->getList_of_failedArraySize();
    int qnic_index, qnic_address,neighborQNodeAddress = -1;
    QNIC_type qnic_type;

    if(internal_qnic_index==-1){//destination hom is outside this node.
           Interface_inf inf = getInterface_toNeighbor(destAddr);
           neighborQNodeAddress = inf.neighborQNode_address;//Because we need the address of the neighboring QNode, not BSA!
           qnic_index = inf.qnic.index;/*Only unique inside the same qnic_type.*/
           qnic_address = inf.qnic.address;/*Unique address*/
           qnic_type = QNIC_E;
     }else{//destination hom is in the qnic in this node. This gets invoked when the request from internal hom is send from the same node.
           qnic_index = internal_qnic_index;
           qnic_address = internal_qnic_address;
           qnic_type = QNIC_R;
           neighborQNodeAddress = getInterface_toNeighbor_Internal(qnic_address).neighborQNode_address;
     }

    int num_emitted_in_this_burstTrial = tracker[qnic_address].size();
    //EV<<"qnic["<<qnic_index<<"] with type = "<<qnic_type<<"address "<<qnic_address<<" has emitted"<<num_emitted_in_this_burstTrial<<" photons. \n";
    //EV<<"num emitted from qnic["<<qnic_address<<"] is "<<num_emitted_in_this_burstTrial;
    /*for(auto it = tracker[qnic_address].cbegin(); it != tracker[qnic_address].cend(); ++it){
            EV<<it->first<<"th shot was from qnic["<<it->second.qnic_index<<"] qubit["<<it->second.qubit_index<<"] \n ???????????????????????????????????";
    }*/
    int success_num = 0;
    for(int i=0; i<list_size; i++){
        bool failed = pk_result->getList_of_failed(i);
        sentQubitIndexTracker::iterator it = tracker[qnic_address].find(i);//check ith shot's information (qnic, qubit index).
        if (it == tracker[qnic_address].end())
                error("Something is wrong with the tracker....%d th shot not recorded",i);//Neighbor not found! This should not happen unless you simulate broken links in real time.
        if(failed){
            //std::cout<<"node["<<parentAddress<<"] failed!\n";
            //EV<<i<<"th shot has failed.....that was qubit["<<it->second.qubit_index<<"] in qnic["<<it->second.qnic_index<<"]\n";
            //realtime_controller->ReInitialize_StationaryQubit(it->second.qnic_index ,it->second.qubit_index, qnic_type);//Re-initialize the qubit. Pauli errors will be eliminated, and the color of the qubit in the GUI changes to blue.
            //Busy_OR_Free_QubitState_table[qnic_type] = setQubitFree_inQnic(Busy_OR_Free_QubitState_table[qnic_type], it->second.qnic_index, it->second.qubit_index);

            freeResource(it->second.qnic_index, it->second.qubit_index, qnic_type);
        }else{
            //std::cout<<"node["<<parentAddress<<"] success!\n";
            //Keep the entangled qubits
            EV<<i<<"th shot has succeeded.....that was qubit["<<it->second.qubit_index<<"] in qnic["<<it->second.qnic_index<<"] node addr["<<it->first<<"] \n";
            //Add this as an available resource
            stationaryQubit * qubit = check_and_cast<stationaryQubit*>(getQNode()->getSubmodule(QNIC_names[qnic_type],qnic_index)->getSubmodule("statQubit",it->second.qubit_index));
            //std::cout<<"node["<<parentAddress<<"] qnic["<<qnic_address<<"] entanglement success"<<qubit<<"\n";
            //std::cout<<"Available resource"<<qubit<<" isBusy = "<<qubit->isBusy<<"\n";
            allResources[qnic_type][qnic_index].insert(std::make_pair(neighborQNodeAddress/*QNode IP address*/,qubit));//Add qubit as available resource between NeighborQNodeAddress.
            success_num++;
            //EV<<"There are "<<allResources[qnic_type][qnic_index].count(neighborQNodeAddress)<<" resources between this and "<<destAddr<<"\n";
        }
    }

    //Any qubit that has been shot while BSA result is actually on the way to the node, needs to be freed as well.
    if(num_emitted_in_this_burstTrial > list_size){
        EV<<num_emitted_in_this_burstTrial<<" shots fired, but only "<<list_size<<" results returned\n";
        for(int i=list_size; i<num_emitted_in_this_burstTrial; i++){
            sentQubitIndexTracker::iterator it = tracker[qnic_address].find(i);//check ith shot's information (qnic, qubit index).
            if (it == tracker[qnic_address].end())
                error("Wait.... something is wrong with the tracker....%d th shot not recorded",i);//Neighbor not found! This should not happen unless you simulate broken links in real time.
            //realtime_controller->ReInitialize_StationaryQubit(it->second.qnic_index ,it->second.qubit_index, qnic_type);
            //Busy_OR_Free_QubitState_table[qnic_type] = setQubitFree_inQnic(Busy_OR_Free_QubitState_table[qnic_type], it->second.qnic_index, it->second.qubit_index);
            freeResource(it->second.qnic_index, it->second.qubit_index, qnic_type);
        }
    }
    //std::cout<<"success num = "<<success_num<<"\n";
    ResourceAllocation(qnic_type, qnic_index);
    traverseThroughAllProcesses2();//New resource added to QNIC with qnic_type qnic_index.

}

void RuleEngine::freeResource(int qnic_index/*The actual index. Not address. This with qnic_type makes the id unique.*/, int qubit_index, QNIC_type qnic_type){
    realtime_controller->ReInitialize_StationaryQubit(qnic_index ,qubit_index, qnic_type, false);
    Busy_OR_Free_QubitState_table[qnic_type] = setQubitFree_inQnic(Busy_OR_Free_QubitState_table[qnic_type], qnic_index, qubit_index);
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

double RuleEngine::predictResourceFidelity(QNIC_type qnic_type, int qnic_index, int entangled_node_address, int resource_index) {
    return uniform(.6,.9);
}

//Invoked whenever a new resource (entangled with neighbor) has been created.
//Allocates those resources to a particular ruleset, from top to bottom (all of it).
void RuleEngine::ResourceAllocation(int qnic_type, int qnic_index){

    if(!(rp.size()>0)){// If no ruleset running, do nothing.
        return;
    }

    for(auto it = rp.cbegin(), next_it = rp.cbegin(); it != rp.cend(); it = next_it){//In a particular RuleSet
        next_it = it; ++next_it;
        RuleSet* process = it->second.RuleSet;//One Process. From top to bottom.
        int ruleset_id = process->ruleset_id;
        int resource_entangled_with_address = process->entangled_partner;

        if(process->empty()){
            error("RuleSet with no Rule found. Probably not what you want!");
        }

        int assigned = 0;
        for (auto it =  allResources[qnic_type][qnic_index].cbegin(), next_it =  allResources[qnic_type][qnic_index].cbegin(); it !=  allResources[qnic_type][qnic_index].cend(); it = next_it){
             next_it = it; ++next_it;
             if(!it->second->isAllocated() && resource_entangled_with_address == it->first){
                 //Free resource that has not been assigned to any ruleset.
                 int index = process->front()->resources.size();
                 process->front()->resources.insert(std::make_pair(index,it->second));//Assign resource to the 1st Rule.
                 int rule_id = process->front()->rule_index;
                 //it->second->Lock(ruleset_id, rule_id);
                 it->second->Allocate();
                 assigned++;
             }
        }
        //std::cout<<parentAddress<<"Assigned = "<<assigned<<"\n";
    }

}



void RuleEngine::traverseThroughAllProcesses2(){

    int number_of_process = rp.size();//Number of running processes (in all QNICs).


    if(number_of_process==0){
        return;
    }

    for(auto it = rp.cbegin(), next_it = rp.cbegin(); it != rp.cend(); it = next_it){
            next_it = it; ++next_it;
            RuleSet* process = it->second.RuleSet;//One Process. From top to bottom.
            EV<<"Checking first process.... process "<<process->size()<<"\n";
            for (auto rule=process->cbegin(), end=process->cend(); rule!=end; rule++){

                    bool process_done = false;
                    //std::cout<<parentAddress<<": Running first Condition & Action now\n";
                    bool terminate_this_rule = false;

                    while(true){
                        if(!((*rule)->resources.size()>0)){
                            break;//No more resource left for now.
                        }
                        //std::cout<<"module["<<parentAddress<<"]\n";
                        cPacket *pk = (*rule)->checkrun(this);//Do something on qubits entangled with resource_entangled_with_address.

                        if(pk!=nullptr){
                            //Feedback to another node required
                            if (dynamic_cast<LinkTomographyResult *>(pk)!= nullptr){
                                //The cPacket *pk is a single packet forwarded to the neighbor. But this node's HardwareMonitor also needs to store the result.
                                LinkTomographyResult *pk_t = check_and_cast<LinkTomographyResult *>(pk);
                                LinkTomographyResult *pk_for_self = pk_t->dup();
                                pk_for_self->setPartner_address(pk_t->getDestAddr());
                                pk_for_self->setDestAddr(pk_t->getSrcAddr());
                                //std::cout<<"time = "<<pk_t->getFinish()<<"\n";
                                /*if(pk_t->getFinish()!=-1){
                                    error("It is...");
                                }*/
                                send(pk,"RouterPort$o");
                                send(pk_for_self,"RouterPort$o");
                            }else if(dynamic_cast<PurificationResult *>(pk)!= nullptr){
                                //error("error");
                                PurificationResult *pkt = check_and_cast<PurificationResult *>(pk);
                                process_id purification_id;
                                purification_result pr;
                                pkt->setSrcAddr(parentAddress);
                                purification_id.ruleset_id = pkt->getRuleset_id();
                                purification_id.rule_id = pkt->getRule_id();
                                purification_id.index = pkt->getAction_index();
                                pr.id = purification_id;
                                pr.outcome = pkt->getOutput_is_plus();
                                Purification_table.insert(std::make_pair(purification_id.ruleset_id, pr));
                                //delete pk;
                                send(pkt,"RouterPort$o");

                            }else if (dynamic_cast<Error *>(pk)!= nullptr){
                                Error *err = check_and_cast<Error *>(pk);
                                error(err->getError_text());
                                delete pk;
                            }else if(dynamic_cast<ConditionNotSatisfied *>(pk)!= nullptr){
                                //Condition does not meet. Go to next rule. e.g. Fidelity is good enough by doing purification. Next could be swap.
                                delete pk;
                                break;
                            }else{
                                delete pk;
                                //error("Unknown return packet from action.");
                            }
                        }else{
                            error("Pk nullptr");
                        }

                        //std::cout<<"Is it done?";
                        process_done = (*rule)->checkTerminate();//The entire process is done. e.g. enough measurement for tomography.
                        if(process_done){//Delete rule set if done
                            //std::cout<<"!!!!!!!!!!!!!!!!!!!!! TERMINATING!!!!!!!!!!!!!!!!!!!!!!!!!";
                            std::cout<<"RuleSet_id="<<process->ruleset_id<<"\n";
                            //todo:Also need to deallocate resources!!!!!!!!!!!!not implemented yet.
                            process->destroyThis();//Destroy ruleset object
                            rp.erase(it);//Erase rule set from map.
                            terminate_this_rule = true;//Flag to get out from outer loop
                            std::cout<<"node["<<parentAddress<<"]:RuleSet deleted.\n";
                            break;//get out from this for loop.
                        }



                    }//While
                    if(process_done){
                        break;
                    }
            }//For

    }//For loop


}

/*
void RuleEngine::traverseThroughAllProcesses(RuleEngine *re, int qnic_type, int qnic_index){
    int testing = rp.size();//Number of running processes (in all QNICs).
    EV<<"running processes = "<<testing<<"\n";

    if(rp.size()>0){
        for(auto it = rp.cbegin(), next_it = rp.cbegin(); it != rp.cend(); it = next_it){
            next_it = it; ++next_it;
            RuleSet* process = it->second.RuleSet;//One Process. From top to bottom.
            int resource_entangled_with_address = process->entangled_partner;//
            EV<<"Checking first process.... process "<<process->size()<<"\n";
            if(allResources[qnic_type][qnic_index].count(resource_entangled_with_address)>0){//If a resource exists
                for (auto rule=process->cbegin(), end=process->cend(); rule!=end; rule++){
                    bool process_done;
                    EV<<"Running first Condition & Action now\n";
                    bool terminate_this_rule = false;

                    while(true){
                        if(allResources[qnic_type][qnic_index].count(resource_entangled_with_address)==0){
                            break;//No more resource left for now.
                        }
                        cPacket *pk = (*rule)->checkrun(re, allResources, qnic_type, qnic_index,resource_entangled_with_address);//Do something on qubits entangled with resource_entangled_with_address.

                        if(pk!=nullptr){
                            //Feedback to another node required
                            if (dynamic_cast<LinkTomographyResult *>(pk)!= nullptr){
                                //The cPacket *pk is a single packet forwarded to the neighbor. But this node's HardwareMonitor also needs to store the result.
                                LinkTomographyResult *pk_t = check_and_cast<LinkTomographyResult *>(pk);
                                LinkTomographyResult *pk_for_self = pk_t->dup();
                                pk_for_self->setPartner_address(pk_t->getDestAddr());
                                pk_for_self->setDestAddr(pk_t->getSrcAddr());
                                send(pk,"RouterPort$o");
                                send(pk_for_self,"RouterPort$o");
                            }else if (dynamic_cast<Error *>(pk)!= nullptr){
                                Error *err = check_and_cast<Error *>(pk);
                                error(err->getError_text());
                            }
                        }

                        process_done = (*rule)->checkTerminate(allResources, qnic_type, qnic_index,resource_entangled_with_address);//The entire process is done. e.g. enough measurement for tomography.
                        if(process_done){//Delete rule set if done
                            process->destroyThis();//Destroy rule set object
                            rp.erase(it);//Erase rule set from map.
                            terminate_this_rule = true;//Flag to get out from outer loop
                            break;//get out from this for loop.
                        }

                        if(dynamic_cast<ConditionNotSatisfied *>(pk)!= nullptr){
                            break;//Condition does not meet. Go to next rule. e.g. Fidelity is good enough by doing purification. Next could be swap.
                        }

                    }//While
                    if(process_done){
                        break;
                    }
                }//For
            }//If
        }//For loop
   }else{
       EV<<"No process running\n";
   }

}*/

void RuleEngine::freeConsumedResource(int qnic_index/*Not the address!!!*/, stationaryQubit *qubit, QNIC_type qnic_type){

    realtime_controller->ReInitialize_StationaryQubit(qnic_index ,qubit->par("stationaryQubit_address"), qnic_type, true);
    Busy_OR_Free_QubitState_table[qnic_type] = setQubitFree_inQnic(Busy_OR_Free_QubitState_table[qnic_type], qnic_index, qubit->par("stationaryQubit_address"));

    for (auto it =  allResources[qnic_type][qnic_index].cbegin(), next_it =  allResources[qnic_type][qnic_index].cbegin(); it !=  allResources[qnic_type][qnic_index].cend(); it = next_it){
      next_it = it; ++next_it;
      if (it->second == qubit){
          //std::cout<<"Let's delete this qubit!"<<it->second<<"\n";
          allResources[qnic_type][qnic_index].erase(it);    // or "it = m.erase(it)" since C++11
          return;
      }
    }
}




} // namespace modules
} // namespace quisp
