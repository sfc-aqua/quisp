/** \file HardwareMonitor.cc
 *  \todo org Organize namespaces
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/19
 *
 *  \brief HardwareMonitor
 */
#include "HardwareMonitor.h"

Define_Module(HardwareMonitor);

//Hm is also responsible for calculating the rssi/oka's protocol/fidelity calcu and give it to the rd
void HardwareMonitor::initialize()
{
  EV<<"HardwareMonitor booted\n";
  numQnic_rp = par("number_of_qnics_rp");// number of qnics connected to epps.
  numQnic_r = par("number_of_qnics_r");// number of qnics connected to internal hom.
  numQnic = par("number_of_qnics");// number of qnics connected to stand alone HoM or internal hom in the neighbor.
  ntable = prepareNeighborTable(ntable, numQnic);//Store which local qnic corresponds to which neighboring node
  ntable_rp = prepareNeighborTable_rp(ntable, numQnic_rp);
  EV<<"numQnic_r =========="<<numQnic_r<<"  and numQnic ========"<<numQnic<<"  and numQnic_rp ========"<<numQnic_rp<<"\n";
  //qtable = new QnicInfo[numQnic];
  //qtable = initializeQTable(numQnic, qtable);
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

int HardwareMonitor::checkNumBuff(int qnic_index, int qnic_type){
    Enter_Method("checkNumBuff()");

    cModule *qnode = nullptr;
    switch (qnic_type) {
      case 0:
        qnode = getQNode()->getSubmodule("qnic", qnic_index); break;
      case 1:
        qnode = getQNode()->getSubmodule("qnic_r", qnic_index); break;
      case 2:
        qnode = getQNode()->getSubmodule("qnic_rp", qnic_index); break;
      default:
        error("Only 3 qnic types are currently recognized....");
    }

    return qnode->par("numBuffer");
}

//Not in HM.....
int HardwareMonitor::checkNumFreeBuff(int qnic_index, int qnic_type){
    //qnic_type 0 = qnic, 1 = qnic_r, 2 = qnic_rp
    int num_free_resources = 0;
    Enter_Method("checkNumFreeBuff()");
    cModule *qnode = nullptr;
    switch (qnic_type) {
      //for when connection manager receives an BSMtimingNotifier
      case 0:
        qnode = getQNode()->getSubmodule("qnic", qnic_index); break;
      //for when connection manager receives an EPPStimingNotifier
      case 1:
        qnode = getQNode()->getSubmodule("qnic_r", qnic_index); break;
      //for when connection manager receives an EPPStimingNotifier
      case 2:
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
}

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
}


void HardwareMonitor::handleMessage(cMessage *msg){

}

HardwareMonitor::NeighborTable HardwareMonitor::prepareNeighborTable(NeighborTable ntable, int numQnic){
    //qnic_r does not need to know what the neighbor is.
    //This is because the internal Hom sends a request to its own connection manager, telling the internal qnic index it needs to run.

    cModule *qnode = getQNode();//Get the parent QNode that runs this connection manager.
    for (int i=0; i<numQnic; i++){//Travese through all local qnics to check where they are connected to. HoM and EPPS will be ignored in this case.
        int neighborNodeAddress = findNeighborAddress(i, qnode);//get the address of the QNode nearby.
        ntable[neighborNodeAddress] = i;
    }
    return ntable;
}

HardwareMonitor::NeighborTable HardwareMonitor::prepareNeighborTable_rp(NeighborTable ntable_rp, int numQnic_rp){
    cModule *qnode = getQNode();
        for (int i=0; i<numQnic_rp; i++){//Travese through all local qnics to check where they are connected to. HoM and EPPS will be ignored in this case.
            int neighborNodeAddress = findNeighborAddress_r(i, qnode);//get the address of the QNode nearby.
            ntable_rp[neighborNodeAddress] = i;
            EV<<"neighbor is......................................."<<neighborNodeAddress<<"\n";
        }
    return ntable_rp;
}

//This method finds out the address of the neighboring node with respect to the local qnic index.
int  HardwareMonitor::findNeighborAddress(int local_qnic_index, cModule *thisQNode){
    cModule *local_qnic = thisQNode->getSubmodule("qnic", local_qnic_index);
    cGate *gt = local_qnic->gate("qnic_quantum_port$o")->getNextGate();//qnic_quantum_port$o is connected to the node's outermost quantum_port
    EV<<"gt = "<<gt->getName()<<"\n";
    cGate *neighbor_gt = gt->getNextGate();
    EV<<"neighbor_gt = "<<neighbor_gt->getName()<<"\n";
    cModule *neighbor_node = neighbor_gt->getOwnerModule();//HoM, EPPS, QNode
    EV<<"neighbor_node = "<<neighbor_node->getName()<<"\n";

    neighborInfo neighbor_is_QNode = checkIfQNode(neighbor_node);//Check if it is QNode
    return neighbor_is_QNode.address;
}

int  HardwareMonitor::findNeighborAddress_r(int local_qnic_index, cModule *thisQNode){
    cModule *local_qnic = thisQNode->getSubmodule("qnic_rp", local_qnic_index);
    cGate *gt = local_qnic->gate("qnic_quantum_port$o")->getNextGate();//qnic_quantum_port$o is connected to the node's outermost quantum_port
    EV<<"gt = "<<gt->getName()<<"\n";
    cGate *neighbor_gt = gt->getNextGate();
    EV<<"neighbor_gt = "<<neighbor_gt->getName()<<"\n";
    cModule *neighbor_node = neighbor_gt->getOwnerModule();//HoM, EPPS, QNode
    EV<<"neighbor_node = "<<neighbor_node->getName()<<"\n";

    neighborInfo neighbor_is_QNode = checkIfQNode(neighbor_node);//Check if it is QNode
    return neighbor_is_QNode.address;
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

    neighborInfo inf;
    if(thisNode->getModuleType()!=QNodeType){//Not a Qnode!

        if(thisNode->getModuleType()== EPPSType || thisNode->getModuleType()==  HoMType){
            inf.isQNode=false;
            inf.type = thisNode->getModuleType();
            inf.address = thisNode->par("address");
            //return inf;
        }else{
            error("This simulator only recognizes the following network level node types: QNode, EPPS and HoM. Not %s",thisNode->getClassName());
            endSimulation();
        }
    }
    else{
        inf.isQNode=true;
        inf.type = thisNode->getModuleType();
        inf.address = thisNode->par("address");
        EV<<thisNode->getName()<<" does it have parameter address? Is it "<<inf.address<<"\n\n\n\n";
        //return inf; //It is a QNode
    }
    return inf;
}

HardwareMonitor::NeighborTable HardwareMonitor::passNeighborTable(){
    Enter_Method("passNeighborTable()");
    return ntable;
}

HardwareMonitor::NeighborTable HardwareMonitor::passNeighborTable_rp(){
    Enter_Method("passNeighborTable_rp()");
    return ntable_rp;
}
