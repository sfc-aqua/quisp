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
class RoutingDaemon : public cSimpleModule
{
    private:
        int myAddress;
        typedef std::map<int, int> RoutingTable;  // destaddr -> gateindex
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
/*
        //Topology creation for routing table
        cTopology *topo = new cTopology("topo");
        std::vector<std::string> nedTypes;
        //nedTypes.push_back(getParentModule()->getNedTypeName());//Push all module types to vector
        //EV << "NedTypes" <<getParentModule()->getNedTypeName() << "\n";
        //topo->extractByNedTypeName(nedTypes);//extract topology by Types. In this case, all nodes in the network
        topo->extractByParameter("includeInTopo");//Any node that has a parameter includeInTopo will be included in routing
        //EV << "cTopology found " << topo->getNumNodes() << " nodes\n";

        cTopology::Node *thisNode = topo->getNodeFor(getParentModule()->getParentModule());//The parent node with this specific router

        int number_of_links_total = 0;

        //Initialize channel weights for all existing links.
        for (int x = 0; x < topo->getNumNodes(); x++) {//Traverse through all nodes
            //For Bidirectional channels, parameters are stored in LinkOut not LinkIn.
            for (int j = 0; j < topo->getNode(x)->getNumOutLinks(); j++) {//Traverse through all links from a specific node.
              //thisNode->disable();//You can also disable nodes or channels accordingly to represent broken hardwares
              double channel_cost = topo->getNode(x)->getLinkOut(j)->getLocalGate()->getChannel()->par("cost");//Get assigned cost for each channel written in .ned file
              cChannelType *QChannelType =  cChannelType::get("networks.QuantumChannel");
              if(topo->getNode(x)->getLinkOut(j)->getLocalGate()->getChannel()->getChannelType() == QChannelType){
                  EV<<"\n"<<thisNode->getModule()->getFullName()<<"!!!!!For_Quantum!!!!!!!! topo->getNode("<<x<<"):"<<topo->getNode(x)->getModule()->getFullName()<<" channel"<<topo->getNode(x)->getLinkOut(j)->getLocalGate()->getChannel()->getChannelType()<<" has cost"<<channel_cost<<"\n";
                  topo->getNode(x)->getLinkOut(j)->setWeight(channel_cost);//Set channel weight
              }else{
                  EV<<"Ignoring classical \n";
                  topo->getNode(x)->getLinkOut(j)->setWeight(100000000000);//Set channel weight
              }

            }
        }
        for (int i = 0; i < topo->getNumNodes(); i++) {//Traverse through all the destinations from the thisNode
                if (topo->getNode(i) == thisNode)
                    continue;  // skip the node that is running this specific router app


                //Apply dijkstra to each node to find all shortest paths.
                topo->calculateWeightedSingleShortestPathsTo(topo->getNode(i));//Overwrites getNumPaths() and so on.
                EV<<"Num path = "<<thisNode->getNumPaths()<<" to node "<<topo->getNode(i)->getModule()->getFullName()<<"\n";
                //Check the number of shortest paths towards the target node. This may be more than 1 if multiple paths have the same minimum cost.
                if (thisNode->getNumPaths() == 0){
                    EV<<"No path available from this Routing Module";
                    continue;  // not connected
                }


                cGate *parentModuleGate = thisNode->getPath(0)->getLocalGate();//Returns the next link/gate in the ith shortest paths towards the target node.
                int gateIndex = parentModuleGate->getIndex();
                int address = topo->getNode(i)->getModule()->par("address");
                qrtable[address] = gateIndex;//Store gate index per destination from this node
                EV << "\n  Quantum : Towards address " << address <<"("<< topo->getNode(i)->getModule()->getName() << ")"<<parentModuleGate->getFullName()<<"gateIndex is " << gateIndex << endl;

       }
       delete topo;
*/


}

void RoutingDaemon::handleMessage(cMessage *msg){

}

} // namespace modules
} // namespace quisp
