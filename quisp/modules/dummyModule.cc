/*
 * dummyModule.cc
 *
 *  Created on: 2018/03/25
 *      Author: takaakimatsuo
 */




#include <vector>
#include <omnetpp.h>
#include "../classical_messages_m.h"
#include "../PhotonicQubit_m.h"



using namespace omnetpp;

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

