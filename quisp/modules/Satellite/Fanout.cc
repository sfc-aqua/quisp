#include "Fanout.h"

namespace quisp::modules {

Define_Module(Fanout);

void Fanout::initialize()
{
    // TODO - Generated method body
}

void Fanout::handleMessage(cMessage *msg)
{
    for (cModule::GateIterator it(this); !it.end(); ++it) {
        cGate* gate = *it;
        if (gate->getType() == cGate::OUTPUT) {
            cMessage* cpy = msg->dup();
            send(cpy,gate);
        }
    }
    delete msg;
}

} //namespace
