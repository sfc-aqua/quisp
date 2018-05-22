/** \file RealTimeController.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/19
 *
 *  \brief RealTimeController
 */
#include "RealTimeController.h"
#include "stationaryQubit.h"

Define_Module(RealTimeController);

void RealTimeController::initialize()
{
  EV<<"RealTimeController booted\n";
}

void RealTimeController::handleMessage(cMessage *msg){

}

void RealTimeController::EmitPhoton(int qnic_index ,int qubit_index, int qnic_type, int pulse){
    Enter_Method("EmitPhoton()");
    cModule *qnode = getQNode();//Get the parent QNode that runs this RC.
    try{
        //EV<<"EmitPhoton for qnic["<<qnic_index<<"] and qubit["<<qubit_index<<"]\n\n\n";
        cModule *qubit = nullptr;
        switch (qnic_type) {
          case 0:
            qubit = qnode->getSubmodule("qnic", qnic_index)->getSubmodule("statQubit", qubit_index); break;
          case 1:
            qubit = qnode->getSubmodule("qnic_r", qnic_index)->getSubmodule("statQubit", qubit_index); break;
          case 2:
            qubit = qnode->getSubmodule("qnic_rp", qnic_index)->getSubmodule("statQubit", qubit_index); break;
          default:
            error("Only 3 qnic types are currently recognized....");
        }
        stationaryQubit *q  = check_and_cast<stationaryQubit *>(qubit);
        q->emitPhoton(pulse);
    }catch(std::exception& e){
        error("Some error occured in RealTimeController. Maybe the qnic/statQubit couldnt be found. Have you changed the namings?");
    }
}

cModule* RealTimeController::getQNode(){
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

void RealTimeController::GUI_setQubitFree(int qnic_index ,int qubit_index, int qnic_type){
    bool success;
    cModule *qnode = getQNode();//Get the parent QNode that runs this RC.
    try{
        cModule *qubit = nullptr;
        switch (qnic_type) {
          case 0:
            qubit = qnode->getSubmodule("qnic", qnic_index)->getSubmodule("statQubit", qubit_index); break;
          case 1:
            qubit = qnode->getSubmodule("qnic_r", qnic_index)->getSubmodule("statQubit", qubit_index); break;
          case 2:
            qubit = qnode->getSubmodule("qnic_rp", qnic_index)->getSubmodule("statQubit", qubit_index); break;
          default:
            error("Only 3 qnic types are currently recognized....");
        }
        stationaryQubit *q  = check_and_cast<stationaryQubit *>(qubit);
        q->setFree();
    }catch(std::exception& e){
            error("Some error occured in RealTimeController. Maybe the qnic/statQubit couldnt be found. Have you changed the namings?");
    }
}
