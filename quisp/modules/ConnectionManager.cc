/** \file ConnectionManager.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *
 *  \brief ConnectionManager
 */
#include <vector>
#include <omnetpp.h>
#include "RoutingDaemon.h"
#include "HardwareMonitor.h"
#include <classical_messages_m.h>

using namespace omnetpp;
using namespace quisp::messages;

namespace quisp {
namespace modules {

/** \class ConnectionManager ConnectionManager.cc
 *  \todo Documentation of the class header.
 *
 *  \brief ConnectionManager
 */
class ConnectionManager : public cSimpleModule
{
    private:
        int myAddress;
        RoutingDaemon *routingdaemon;
        HardwareMonitor *hardwaremonitor;
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};

Define_Module(ConnectionManager);

void ConnectionManager::initialize()
{
  EV<<"ConnectionManager booted\n";
  cModule *rd = getParentModule()->getSubmodule("rd");
  routingdaemon = check_and_cast<RoutingDaemon *>(rd);
  cModule *hm = getParentModule()->getSubmodule("hm");
  hardwaremonitor = check_and_cast<HardwareMonitor *>(hm);
  myAddress = par("address");
}

void ConnectionManager::handleMessage(cMessage *msg){

    if(dynamic_cast<ConnectionSetupRequest *>(msg)!= nullptr){
       ConnectionSetupRequest *pk = check_and_cast<ConnectionSetupRequest *>(msg);

       int actual_dst = pk->getActual_destAddr();

       if(actual_dst == myAddress){
           //In Destination node
           //Need to create rule sets. Feel free to change things accordingly.
           int stack_size = pk->getStack_of_QNodeIndexesArraySize();//Should be the same as pk->getStack_of_linkCostsArraySize()
           for(int i = 0; i<stack_size; i++){
               EV<<"\nThis is one of the stacked QNode addresses....."<<pk->getStack_of_QNodeIndexes(i)<<"\n";
           }
           for(int i = 0; i<stack_size; i++){
               //The link cost is just a dummy variable (constant 1 for now and how it is set in a bad way (read from the channel but from only 1 channels from Src->BSA and ignoring BSA->Dest).
               //If you need to test with different costs, try changing the value.
               //But we need to implement actual link-tomography for this eventually.
               EV<<"\nThis is one of the stacked link costs....."<<pk->getStack_of_linkCosts(i)<<"\n";
           }

           error("Yay!");
           return;
       }else{
           int local_qnic_address_to_actual_dst = routingdaemon->return_QNIC_address_to_destAddr(actual_dst);
           if(local_qnic_address_to_actual_dst==-1){//is not found
               error("QNIC to destination not found");
           }else{
               //Use the QNIC address to find the next hop QNode, by asking the Hardware Monitor (neighbor table).
               EV<<"\n"<<local_qnic_address_to_actual_dst<<"|||||||||||||||||||||||||||||||||||||||||||||||||\n";
               connection_setup_inf inf = hardwaremonitor->return_setupInf(local_qnic_address_to_actual_dst);
               int num_accumulated_nodes = pk->getStack_of_QNodeIndexesArraySize();
               int num_accumulated_costs = pk->getStack_of_linkCostsArraySize();

               //Update information and send it to the next Qnode.
               pk->setDestAddr(inf.neighbor_address);
               pk->setSrcAddr(myAddress);
               pk->setStack_of_QNodeIndexesArraySize(num_accumulated_nodes+1);
               pk->setStack_of_linkCostsArraySize(num_accumulated_costs+1);
               pk->setStack_of_QNodeIndexes(num_accumulated_nodes, myAddress);
               pk->setStack_of_linkCosts(num_accumulated_costs, inf.quantum_link_cost);

               send(pk,"RouterPort$o");

           }
       }

    }


}

} // namespace modules
} // namespace quisp
