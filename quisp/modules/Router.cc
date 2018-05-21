/** \todo clean Clean code when it is simple. */
/** \todo doc Write doxygen documentation. */
#include <map>
#include <omnetpp.h>
#include "../classical_messages_m.h" //Path selection: type = 1, Timing notifier for BMA: type = 4


using namespace omnetpp;

class Router : public cSimpleModule
{   private:
        int myAddress;

        typedef std::map<int, int> RoutingTable;  // destaddr -> gateindex
        RoutingTable rtable;

    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Router);

void Router::initialize()
{
       EV<<"Routing table initialized \n";
       myAddress = getParentModule()->par("address");

       //Topology creation for routing table
       cTopology *topo = new cTopology("topo");
       std::vector<std::string> nedTypes;
       //nedTypes.push_back(getParentModule()->getNedTypeName());//Push all module types to vector
       //EV << "NedTypes" <<getParentModule()->getNedTypeName() << "\n";
       //topo->extractByNedTypeName(nedTypes);//extract topology by Types. In this case, all nodes in the network
       topo->extractByParameter("includeInTopo");//Any node that has a parameter includeInTopo will be included in routing
       //EV << "cTopology found " << topo->getNumNodes() << " nodes\n";

       cTopology::Node *thisNode = topo->getNodeFor(getParentModule());//The parent node with this specific router
       int number_of_links_total = 0;

       //Initialize channel weights for all existing links.
       for (int x = 0; x < topo->getNumNodes(); x++) {//Traverse through all nodes
           //For Bidirectional channels, parameters are stored in LinkOut not LinkIn.
           for (int j = 0; j < topo->getNode(x)->getNumOutLinks(); j++) {//Traverse through all links from a specific node.
             //thisNode->disable();//You can also disable nodes or channels accordingly to represent broken hardwares
             double channel_cost = topo->getNode(x)->getLinkOut(j)->getLocalGate()->getChannel()->par("cost");//Get assigned cost for each channel written in .ned file
             topo->getNode(x)->getLinkOut(j)->setWeight(channel_cost);//Set channel weight
           }
       }

       for (int i = 0; i < topo->getNumNodes(); i++) {//Traverse through all the destinations from the thisNode
               if (topo->getNode(i) == thisNode)
                   continue;  // skip the node that is running this specific router app

               //Apply dijkstra to each node to find all shortest paths.
               topo->calculateWeightedSingleShortestPathsTo(topo->getNode(i));//Overwrites getNumPaths() and so on.
               //topo->calculateUnweightedSingleShortestPathsTo(topo->getNode(i));

               //Check the number of shortest paths towards the target node. This may be more than 1 if multiple paths have the same minimum cost.
               if (thisNode->getNumPaths() == 0)
                   continue;  // not connected

               cGate *parentModuleGate = thisNode->getPath(0)->getLocalGate();//Returns the next link/gate in the ith shortest paths towards the target node.
               int gateIndex = parentModuleGate->getIndex();
               int address = topo->getNode(i)->getModule()->par("address");
               rtable[address] = gateIndex;//Store gate index per destination from this node
               EV << "\n  Towards address " << address <<"("<< topo->getNode(i)->getModule()->getName() << ") gateIndex is " << gateIndex << endl;
      }
      delete topo;
}


void Router::handleMessage(cMessage *msg)
{
        //check the header of the received package
        header *pk = check_and_cast<header *>(msg);
        int destAddr = pk->getDestAddr();//read destination from the packet
        int who_are_you = pk->getKind();//read the type of packet
        //bubble("Message kind "<<message_type<<" received");
        EV<<"destAddr ===="<<destAddr;
        if (destAddr == myAddress && who_are_you == 1) {//If destination is this node: Path selection
            send(pk, "toApp");//send to Application locally
            return;
        }else if (destAddr == myAddress && dynamic_cast<BSMtimingNotifier *>(msg) != nullptr) {//Timing for BSM
            bubble("Timing Notifier from HoM (stand-alone or internal) received");
            send(pk, "rePort$o");//send to Application locally
            return;
        }else if (destAddr == myAddress && dynamic_cast<EPPStimingNotifier *>(msg) != nullptr) {//Timing for BSM
            bubble("Timing Notifier from EPPS received");
            send(pk, "rePort$o");//send to Application locally
            return;
        }

        //Check if packet is reachable
        RoutingTable::iterator it = rtable.find(destAddr);
        if (it == rtable.end()) {
            EV << "address " << destAddr << " unreachable, discarding packet " << pk->getName() << endl;
            delete pk;
            return;
        }

        int outGateIndex = (*it).second;
        EV << "forwarding packet " << pk->getName() << " on gate index " << outGateIndex << endl;
        pk->setHopCount(pk->getHopCount()+1);
        send(pk, "toQueue", outGateIndex);
}




