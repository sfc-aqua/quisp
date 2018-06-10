/** \file RoutingDaemon.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *
 *  \brief RoutingDaemon
 */
#include <vector>
#include <omnetpp.h>
#include <classical_messages_m.h>

using namespace omnetpp;

namespace quisp {
namespace modules {

/** \class RoutingDaemon RoutingDaemon.cc
 *  \todo Documentation of the class header.
 *
 *  \brief RoutingDaemon
 */

typedef struct _QNIC_identifier{
    //QubitAddr(int node_addr, int qnic_index, int qubit_index):node_address(node_addr),qnic_index(qnic_index),qubit_index(qubit_index){}
    cModule *qnic_pointer;
    int qnic_type;/*0 = qnic, 1 = qnic_r, 2 = qnic_rp*/
    int qnic_index;/*Index inside qnic || qnic_rp || qnic_r. Used for accessing the module.*/
    int qnic_address;/*Unique address for qnic, qnic_r, qnic_rp. This may not be used.*/
    double initial_fidelity = -1;/*Oka's protocol?*/
    int buffer_size;
} Interface_inf;

class RoutingDaemon : public cSimpleModule
{
    private:
        int myAddress;
        typedef std::map<int, int> RoutingTable;  // destaddr -> {gate_index (We need this to access qnic, but it is not unique because we have 3 types of qnics), qnic_address (unique)}
        RoutingTable qrtable;
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};

Define_Module(RoutingDaemon);

void RoutingDaemon::initialize()
{


  EV<<"Routing Daemon booted\n";

  EV<<"Routing table initialized \n";
        myAddress = getParentModule()->par("address");

        //Topology creation for routing table
        cTopology *topo = new cTopology("topo");
        cMsgPar *yes = new cMsgPar();
        yes->setStringValue("yes");
        topo->extractByParameter("includeInTopo",yes->str().c_str());//Any node that has a parameter includeInTopo will be included in routing
        //EV << "cTopology found " << topo->getNumNodes() << " nodes\n";
        if(topo->getNumNodes()==0 || topo==nullptr){//If no node with the parameter & value found, do nothing.
                 return;
        }


        cTopology::Node *thisNode = topo->getNodeFor(getParentModule()->getParentModule());//The parent node with this specific router

        int number_of_links_total = 0;



        //Initialize channel weights for all existing links.
        for (int x = 0; x < topo->getNumNodes(); x++) {//Traverse through all nodes
            //For Bidirectional channels, parameters are stored in LinkOut not LinkIn.
            for (int j = 0; j < topo->getNode(x)->getNumOutLinks(); j++) {//Traverse through all links from a specific node.
                //thisNode->disable();//You can also disable nodes or channels accordingly to represent broken hardwares
                EV<<"\n thisNode is "<< topo->getNode(x)->getModule()->getFullName() <<" has "<<topo->getNode(x)->getNumOutLinks()<<" links \n";
                double channel_cost = topo->getNode(x)->getLinkOut(j)->getLocalGate()->getChannel()->par("cost");//Get assigned cost for each channel written in .ned file

                EV<<topo->getNode(x)->getLinkOut(j)->getLocalGate()->getChannel()->getFullName()<<" =? "<<"QuantumChannel"<<"\n";
                if(strcmp(topo->getNode(x)->getLinkOut(j)->getLocalGate()->getChannel()->getFullName(),"QuantumChannel")==0){
                    //Ignore classical link in quantum routing table
                    topo->getNode(x)->getLinkOut(j)->setWeight(channel_cost);//Set channel weight
                }else{
                    //Otherwise, keep the quantum channels and set the weight
                    topo->getNode(x)->getLinkOut(j)->disable();
                }
            }
        }

        for (int i = 0; i < topo->getNumNodes(); i++) {//Traverse through all the destinations from the thisNode
                if (topo->getNode(i) == thisNode)
                    continue;  // skip the node that is running this specific router app
                //Apply dijkstra to each node to find all shortest paths.
                topo->calculateWeightedSingleShortestPathsTo(topo->getNode(i));//Overwrites getNumPaths() and so on.

                //Check the number of shortest paths towards the target node. This may be more than 1 if multiple paths have the same minimum cost.
                if (thisNode->getNumPaths() == 0)
                    continue;  // not connected

                cGate *parentModuleGate = thisNode->getPath(0)->getLocalGate();//Returns the next link/gate in the ith shortest paths towards the target node.
                int gateIndex = parentModuleGate->getIndex();
                int address = topo->getNode(i)->getModule()->par("address");
                qrtable[address] = gateIndex;//Store gate index per destination from this node
                EV <<"\n  Quantum: Towards address " << address <<"("<< topo->getNode(i)->getModule()->getName() << ")"<<parentModuleGate->getFullName()<<"gateIndex is " << gateIndex << "cost ="<< thisNode->getPath(0)->getWeight() << endl;
               // EV << "\n  Towards address " << address <<"("<< topo->getNode(i)->getModule()->getName() << ") gateIndex is " << gateIndex << endl;
       }

       delete topo;


}

void RoutingDaemon::handleMessage(cMessage *msg){

}

} // namespace modules
} // namespace quisp
