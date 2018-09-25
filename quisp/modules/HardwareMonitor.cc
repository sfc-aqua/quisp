/** \file HardwareMonitor.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/19
 *
 *  \brief HardwareMonitor
 */
#include "HardwareMonitor.h"
#include "classical_messages_m.h"
#include <sstream>
#include <string>

namespace quisp {
namespace modules {

using namespace rules;

Define_Module(HardwareMonitor);

//Hm is also responsible for calculating the rssi/oka's protocol/fidelity calcu and give it to the rd
void HardwareMonitor::initialize(int stage)
{
  EV<<"HardwareMonitor booted\n";
  numQnic_rp = par("number_of_qnics_rp");// number of qnics connected to epps.
  numQnic_r = par("number_of_qnics_r");// number of qnics connected to internal hom.
  numQnic = par("number_of_qnics");// number of qnics connected to stand alone HoM or internal hom in the neighbor.
  numQnic_total = numQnic + numQnic_r + numQnic_rp;
  ntable = prepareNeighborTable(ntable, numQnic_total);
  do_link_level_tomography = par("link_tomography");
  num_measure = par("num_measure");
  myAddress = par("address");
  std::stringstream ss;
  for(auto it = ntable.cbegin(); it != ntable.cend(); ++it){
      ss << it->first << "(d)->(i)" << it->second.qnic.index <<", ";
  }
  std::string s = ss.str();
  par("ntable") = s;

  //qtable = new QnicInfo[numQnic];
  //qtable = initializeQTable(numQnic, qtable);

  if(do_link_level_tomography && stage == 1){
      for(auto it = ntable.cbegin(); it != ntable.cend(); ++it){
          if(myAddress > it->second.neighborQNode_address){//You dont want 2 separate tomography processes to run for each link. Not a very good solution, but makes sure that only 1 request per link is generated.
              EV<<"Generating tomography rules... for node "<<it->second.neighborQNode_address<<"\n";

              LinkTomographyRequest *pk = new LinkTomographyRequest;
              pk->setDestAddr(it->second.neighborQNode_address);
              pk->setSrcAddr(myAddress);
              pk->setKind(6);
              send(pk,"RouterPort$o");
          }
      }
  }

}

void HardwareMonitor::handleMessage(cMessage *msg){
    if(dynamic_cast<LinkTomographyRequest *>(msg) != nullptr){
        LinkTomographyRequest *request = check_and_cast<LinkTomographyRequest *>(msg);


        LinkTomographyAck *pk = new LinkTomographyAck;
        pk->setSrcAddr(myAddress);
        pk->setDestAddr(request->getSrcAddr());
        pk->setKind(6);
        QNIC_type qnic_type;
        int qnic_index = -1;
        for(auto it = ntable.cbegin(); it != ntable.cend(); ++it){
            if(it->second.neighborQNode_address == request->getSrcAddr()){
                qnic_type = it->second.qnic.type;
                qnic_index = it->second.qnic.index;
                break;
            }
        }if(qnic_index == -1){
            error("1. Something is wrong when finding out local qnic address from neighbor address in ntable.");
        }
        pk->setQnic_index(qnic_index);
        pk->setQnic_type(qnic_type);

        send(pk,"RouterPort$o");

    }else if(dynamic_cast<LinkTomographyAck *>(msg) != nullptr){

        LinkTomographyAck *ack = check_and_cast<LinkTomographyAck *>(msg);

        int partner_address = ack->getSrcAddr();
        QNIC_type partner_qnic_type = ack->getQnic_type();
        int partner_qnic_index = ack->getQnic_index();

        QNIC_type my_qnic_type;
        int my_qnic_index = -1;

        for(auto it = ntable.cbegin(); it != ntable.cend(); ++it){
            if(it->second.neighborQNode_address == ack->getSrcAddr()){
                my_qnic_type = it->second.qnic.type;
                my_qnic_index = it->second.qnic.index;
                break;
            }
        }if(my_qnic_index == -1){
            error("2. Something is wrong when finding out local qnic address from neighbor address in ntable.");
        }

        //For this and partner node.
        SendLinkTomographyRuleSet(myAddress,partner_address, my_qnic_type, my_qnic_index);
        SendLinkTomographyRuleSet(partner_address,myAddress, partner_qnic_type, partner_qnic_index);

    }

}

void HardwareMonitor::SendLinkTomographyRuleSet(int my_address, int partner_address, QNIC_type qnic_type, int qnic_index){

    LinkTomographyRuleSet *pk = new LinkTomographyRuleSet;
            pk->setDestAddr(my_address);
            pk->setSrcAddr(partner_address);
            pk->setNumber_of_measuring_resources(num_measure);
            pk->setKind(6);

            //Empty RuleSet
            RuleSet* tomography_RuleSet = new RuleSet(my_address,partner_address);//Tomography between this node and the sender of Ack.
            //-------------
            //-First rule-
            Rule* Random_measure_tomo = new Rule();//Let's make nodes select measurement basis randomly, because it it easier.
            Condition* total_measurements = new Condition();//Technically, there is no condition because an available resource is guaranteed whenever the rule is ran.
            Clause* measure_count_clause = new MeasureCountClause(num_measure, partner_address, qnic_type , qnic_index, 0);//3000 measurements in total. There are 3*3 = 9 patterns of measurements. So each combination must perform 3000/9 measurements.
            total_measurements->addClause(measure_count_clause);
            Random_measure_tomo->setCondition(total_measurements);
            quisp::rules::Action* measure = new RandomMeasureAction(partner_address, qnic_type , qnic_index, 0);//Measure the local resource between it->second.neighborQNode_address.
            Random_measure_tomo->setAction(measure);
            //---------
            //Add the rule to the RuleSet
            tomography_RuleSet->addRule(Random_measure_tomo);
            //---------------------------
            pk->setRuleSet(tomography_RuleSet);
            //send(pk, "RuleEnginePort$o");
            //send(pk, "RuleEnginePort$o");
            send(pk,"RouterPort$o");



}


/*
//Table for tracking which buffer is assigned for what job
HardwareMonitor::QnicInfo* HardwareMonitor::initializeQTable(int numQnic, QnicInfo *qtable)
{
    for(int i=0; i<numQnic; i++){//per qnic
        for(int x=0; x<checkNumBuff(i,false); x++){//per stationary qubit in the qnic
            stationaryQubitInfo inf;
                 inf.isBusy = false;
                 inf.assigned_job = -1;//Job is from 0 ~ n.
                 inf.qnic_index = i;
                 inf.qubit_index = x;
                 inf.entangled_inf.buffer_index = -1;
                 inf.entangled_inf.node_address = -1;
                 inf.entangled_inf.qnic_index = -1;
            qtable[i][x] = inf; //[qnic_index][qubit_index] = inf
        }
    }
    return qtable;
}*/

int HardwareMonitor::checkNumBuff(int qnic_index, QNIC_type qnic_type){
    Enter_Method("checkNumBuff()");

    cModule *qnode = nullptr;
    if (qnic_type>=QNIC_N) error("Only 3 qnic types are currently recognized...."); // avoid segfaults <3
    qnode = getQNode()->getSubmodule(QNIC_names[qnic_type], qnic_index);
    return qnode->par("numBuffer");
}

/*
//Not in HM.....
int HardwareMonitor::checkNumFreeBuff(int qnic_index, int qnic_type){
    //qnic_type 0 = qnic, 1 = qnic_r, 2 = qnic_rp
    int num_free_resources = 0;
    Enter_Method("checkNumFreeBuff()");
    cModule *qnode = nullptr;
    switch (qnic_type) {
      //for when connection manager receives an BSMtimingNotifier
      case EMITTER_QNIC:
        qnode = getQNode()->getSubmodule("qnic", qnic_index); break;
      //for when connection manager receives an EPPStimingNotifier
      case RECEIVER_QNIC:
        qnode = getQNode()->getSubmodule("qnic_r", qnic_index); break;
      //for when connection manager receives an EPPStimingNotifier
      case PASSIVE_RECEIVER_QNIC:
        qnode = getQNode()->getSubmodule("qnic_rp", qnic_index); break;
      default:
        error("Only 3 qnic types are currently recognized....");
    }

    int maxBuff = qnode->par("numBuffer");
    for(int i=0; i<maxBuff; i++){
        cModule *qubit = qnode->getSubmodule("statQubit", i);
        if(!qubit->par("isBusy")){
            num_free_resources++;
        }
    }
    return num_free_resources;
}*/

Interface_inf HardwareMonitor::getInterface_inf_fromQnicAddress(int qnic_index, QNIC_type qnic_type){
    cModule *local_qnic;
    if (qnic_type>=QNIC_N) error("Only 3 qnic types are currently recognized...."); // avoid segfaults <3
    local_qnic = getQNode()->getSubmodule(QNIC_names[qnic_type], qnic_index);//QNIC itself
    Interface_inf inf;
    inf.qnic.pointer = local_qnic;
    inf.qnic.address = local_qnic->par("self_qnic_address");//Extract from QNIC parameter
    inf.qnic.index = qnic_index;
    inf.qnic.type = qnic_type;
    inf.buffer_size = local_qnic->par("numBuffer");

    //Just read link cost from channel parameter for now as a dummy (or as an initialization).
    //int cost = local_qnic->gate("qnic_quantum_port$o")->getNextGate()->getChannel()->par("cost");//This is false because the channel may only be between the node and HOM.
    inf.link_cost = 1;//Dummy it up. This cost must be the cost based on the neighboring QNode (excluding SPDC and HOM nodes)

    return inf;
}

connection_setup_inf HardwareMonitor::return_setupInf(int qnic_address){
    Enter_Method("return_setupInf()");
    connection_setup_inf inf = {
        .qnic = {
            .type = QNIC_N,
            .index = -1,
        },
        .neighbor_address = -1,
        .quantum_link_cost = -1
    };
    for(auto it = ntable.cbegin(); it != ntable.cend(); ++it){
        if(it->second.qnic.address == qnic_address){
            inf.qnic.type = it->second.qnic.type;
            inf.qnic.index = it->second.qnic.index;
            inf.neighbor_address = it->second.neighborQNode_address;
            //cModule *node = getModuleByPath("network.HoM");
            inf.quantum_link_cost = it->second.link_cost;
            break;
        }
    }
    return inf;
}


/*
//Not in HM......
int* HardwareMonitor::checkFreeBuffSet(int qnic_index, int *list_of_free_resources, int qnic_type){
    if(qnic_type<0 || qnic_type >2){
        error("Only 3 qnic types are currently recognized....");
    }

    int index = 0;//index for array
    for(int i=0; i<checkNumBuff(qnic_index,qnic_type); i++){//Traverse through all qubits
        try{
        cModule *qnic = nullptr;
        if(qnic_type==0)
            qnic = getQNode()->getSubmodule("qnic", qnic_index);//for qnic, which is connected to stand-alone HoM
        else if (qnic_type==1)
            qnic = getQNode()->getSubmodule("qnic_r", qnic_index);//for qnic with internal hom
        else
            qnic = getQNode()->getSubmodule("qnic_rp", qnic_index);//for when connection manager receives an EPPStimingNotifier
        cModule *qubit = qnic->getSubmodule("statQubit", i);
        stationaryQubit *q = check_and_cast<stationaryQubit *>(qubit);
            if(!q->checkBusy()){//If free qubit
                list_of_free_resources[i] = index;//store the index (i) of qubit in the list
                index++;
            }
        }catch(std::exception& e){
                error("statQubit not found.");
                endSimulation();
        }
    }
    //EV<<"index is ....."<<index<<"\n";
    return list_of_free_resources;
}*/




//This neighbor table includes all neighbors of qnic, qnic_r and qnic_rp
HardwareMonitor::NeighborTable HardwareMonitor::prepareNeighborTable(NeighborTable ntable, int total_numQnic){
    cModule *qnode = getQNode();//Get the parent QNode that runs this connection manager.
        for (int index=0; index<numQnic; index++){//Travese through all local qnics to check where they are connected to. HoM and EPPS will be ignored in this case.
            Interface_inf inf = getInterface_inf_fromQnicAddress(index, QNIC_E);
            neighborInfo n_inf = findNeighborAddress(inf.qnic.pointer);
            int neighborNodeAddress = n_inf.address;//get the address of the Node nearby.
            inf.neighborQNode_address = n_inf.neighborQNode_address;
            ntable[neighborNodeAddress] = inf;
        }
        for (int index=0; index<numQnic_r; index++){
            Interface_inf inf = getInterface_inf_fromQnicAddress(index, QNIC_R);
            neighborInfo n_inf = findNeighborAddress(inf.qnic.pointer);
            int neighborNodeAddress = n_inf.address;//get the address of the Node nearby.
            inf.neighborQNode_address = n_inf.neighborQNode_address;
            ntable[neighborNodeAddress] = inf;
        }
        for (int index=0; index<numQnic_rp; index++){
            Interface_inf inf = getInterface_inf_fromQnicAddress(index, QNIC_RP);
            neighborInfo n_inf = findNeighborAddress(inf.qnic.pointer);
            int neighborNodeAddress = n_inf.address;//get the address of the Node nearby.
            inf.neighborQNode_address = n_inf.neighborQNode_address;
            ntable[neighborNodeAddress] = inf;
        }
        return ntable;
}


//This method finds out the address of the neighboring node with respect to the local unique qnic addres.
neighborInfo  HardwareMonitor::findNeighborAddress(cModule *qnic_pointer){
    cGate *gt = qnic_pointer->gate("qnic_quantum_port$o")->getNextGate();//qnic_quantum_port$o is connected to the node's outermost quantum_port
    //EV<<"gt = "<<gt->getName()<<"\n";
    cGate *neighbor_gt = gt->getNextGate();
    //EV<<"neighbor_gt = "<<neighbor_gt->getName()<<"\n";
    cModule *neighbor_node = neighbor_gt->getOwnerModule();//Ownner could be HoM, EPPS, QNode
    //EV<<"neighbor_node = "<<neighbor_node->getName()<<"\n";
    neighborInfo neighbor_is_QNode = checkIfQNode(neighbor_node);
    return neighbor_is_QNode;
}

cModule* HardwareMonitor::getQNode(){
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

neighborInfo HardwareMonitor::checkIfQNode(cModule *thisNode){

    neighborInfo inf;//Return this
    if(thisNode->getModuleType()!=QNodeType){//Not a Qnode!

        if(thisNode->getModuleType()==HoMType){
            EV<<thisNode->getModuleType()->getFullName()<<" == "<<HoMType->getFullName()<<"\n";
            inf.isQNode=false;
            int address_one = thisNode->getSubmodule("Controller")->par("neighbor_address");
            int address_two = thisNode->getSubmodule("Controller")->par("neighbor_address_two");
            int myaddress = par("address");
            EV<<"\n myaddress = "<<myaddress<<", address = "<<address_one<<", address_two = "<<address_two<<" in "<<thisNode->getSubmodule("Controller")->getFullName()<<"\n";
            //endSimulation();
            if(address_one==myaddress){
                inf.neighborQNode_address = address_two;
            }else if(address_two==myaddress){
                inf.neighborQNode_address = address_one;
            }else{
                //endSimulation();
                //EV<<"address _one = "<<address_one<<", address_two = "<<address_two;
                //error("Something is wrong with tracking the neighbor address. It is here.");
            }
        }else if(thisNode->getModuleType()== SPDCType){
            error("TO BE IMPLEMENTED");
        }else{
            error("This simulator only recognizes the following network level node types: QNode, EPPS and HoM. Not %s",thisNode->getClassName());
            endSimulation();
        }
    }
    else{
        inf.isQNode=true;
        inf.neighborQNode_address = thisNode->par("address");
    }
    inf.type = thisNode->getModuleType();
    inf.address = thisNode->par("address");
    return inf;
}

HardwareMonitor::NeighborTable HardwareMonitor::passNeighborTable(){
    Enter_Method("passNeighborTable()");
    return ntable;
}

} // namespace modules
} // namespace quisp
