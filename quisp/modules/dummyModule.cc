/** \file dummyModule.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/25
 *
 *  \brief dummyModule
 */
#include <vector>
#include <omnetpp.h>
#include "../classical_messages_m.h"
#include "../PhotonicQubit_m.h"

using namespace omnetpp;

/** \class dummyModule dummyModule.cc
 *  \todo Documentation of the class header.
 *
 *  \brief dummyModule
 */
class dummyModule : public cSimpleModule
{
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};

Define_Module(dummyModule);

void dummyModule::initialize()
{

}

void dummyModule::handleMessage(cMessage *msg){
    delete msg;
}
