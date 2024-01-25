//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Transceiver.h"
#include <messages/gatedqueue_messages_m.h>
#include<iostream>

Define_Module(Transceiver);

using namespace messages;

void Transceiver::initialize()
{
    received_photon_ID = registerSignal("received_photon");
    if (par("start")) {
        for (int i=0;i<100;i++) {
        std::ostringstream msgname;
        msgname << "prova" << i;
        cPacket* msg = new OspfHelloPacket(msgname.str().c_str(),2);
        scheduleAt(SimTime(i*300,SIMTIME_MS),msg);
        }
    }
}

void Transceiver::handleMessage(cMessage *msg)
{
    if (msg->getKind() == 2) {
    emit(received_photon_ID,1);
    cPacket* notification = new cPacket(msg->getName(),8);
    scheduleAfter(SimTime(20,SIMTIME_MS),notification);
    delete msg;
    }
    else if (msg->getKind() == 8) {
        cPacket* to_send = new cPacket(msg->getName(),2);
        send(to_send,"p2");
        delete msg;
    }
    else bubble("Monkey business at the tranceiver...");
}
