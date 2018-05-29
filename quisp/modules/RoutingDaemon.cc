/** \file RoutingDaemon.cc
 *  \todo org Organize namespaces
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *
 *  \brief RoutingDaemon
 */
#include <vector>
#include <omnetpp.h>
#include "../classical_messages_m.h"

using namespace omnetpp;

/** \class RoutingDaemon RoutingDaemon.cc
 *  \todo Documentation of the class header.
 *
 *  \brief RoutingDaemon
 */
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
