/** \todo clean Clean code when it is simple. */
/** \todo doc Write doxygen documentation. */
#include <vector>
#include <omnetpp.h>
#include "../classical_messages_m.h"

using namespace omnetpp;

class ConnectionManager : public cSimpleModule
{
    private:
        int myAddress;
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};

Define_Module(ConnectionManager);


void ConnectionManager::initialize()
{
  EV<<"ConnectionManager booted\n";
}

void ConnectionManager::handleMessage(cMessage *msg){

}
