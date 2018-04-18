#include <vector>
#include <omnetpp.h>
#include "../classical_messages_m.h"

using namespace omnetpp;

class RoutingDaemon : public cSimpleModule
{
    private:
        int myAddress;
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};

Define_Module(RoutingDaemon);


void RoutingDaemon::initialize()
{
  EV<<"Routing Daemon booted\n";
}

void RoutingDaemon::handleMessage(cMessage *msg){

}
