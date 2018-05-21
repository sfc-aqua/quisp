/** \file Application.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/14
 *
 *  \brief Application
 */
#include <vector>
#include <omnetpp.h>
#include "../classical_messages_m.h"

using namespace omnetpp;

/** \class Application Application.cc
 *
 *  \brief Application
 */
class Application : public cSimpleModule
{
    private:
        int myAddress;
        cMessage *generatePacket; //Not the actual packet. Local message to invoke Events
        cPar *sendIATime;
        bool isBusy;//Already requested a path selection for a Quantum app
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        virtual void BubbleText(const char* txt);
        virtual cModule* getQNode();

    public:
        Application();
        int getAddress();
};

Define_Module(Application);

Application::Application()
{
    generatePacket = nullptr;
}

void Application::initialize()
{
       //read from ned
       myAddress = getParentModule()->par("address");
       sendIATime = &par("sendIaTime");  // volatile parameter
       cModule *qnode = getQNode();
       std::string nodetype = qnode->par("nodeType");
        if(/*myAddress == 4 ||*/ myAddress == 1){//This should be NodeType = EndNode
            //EV<<"In Application source node!\n";
            //generatePacket = new cMessage("nextPacket");
            //scheduleAt(sendIATime->doubleValue(), generatePacket);
            //scheduleAt(simTime(),generatePacket);
        }else{
            EV<<"Not in source!"<<getParentModule()->getName()<<" Address = "<<myAddress<<"\n";
        }
}

void Application::handleMessage(cMessage *msg){
    if(msg == generatePacket){
        header *pk = new header("PathRequest");
        pk->setSrcAddr(1);//packet source setting
        pk->setDestAddr(3);//packet destination setting
        pk->setKind(1);
        send(pk, "toRouter");//send to port out. connected to local routing module (routing.localIn).
        scheduleAt(simTime() + sendIATime->doubleValue(), generatePacket);
        //scheduleAt(simTime() + 10, generatePacket);//In 10 seconds, another msg send gets invoked
    }
    else if(msg->getKind()==1 && strcmp("PathRequest", msg->getName())==0){
        BubbleText("Path Request received!");

        EV << "Deleting path request\n";
    }
    else{//A message was reached from another node to here
        delete msg;
        //cModule *mod = getSimulation()->getModule(4);
        //int ad = mod->par("address");
        //QNode *aa = check_and_cast<QNode*>(mod);//Cast not working
        //EV<<"------------------------------"<<mod->getModuleType()<<"\n";

        EV << "Deleting msg\n";
    }
}

void Application::BubbleText(const char* txt){
    if (hasGUI()) {
      char text[32];
      sprintf(text, "%s", txt);
      bubble(text);
    }
}

int Application::getAddress()
{
    return myAddress;
}

cModule* Application::getQNode(){
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


