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

#include "Router.h"

Define_Module(Router);

using namespace omnetpp;

void Router::initialize()
{
    // TODO - Generated method body
}

void Router::handleMessage(cMessage* msg)
{
    const char* ingate = msg->getArrivalGate()->getName();
    if (!strcmp(ingate,"from_vc")) {
//        if (msg->getKind() == 1) {
            cMessage* msg_cpy = msg->dup();
            send(msg,"to_outside");
            send(msg_cpy,"to_latch_ctrl");
//                }
//            else if ((msg->getKind() == 5) || (msg->getKind() == 6)) {
//            send(msg,"to_latch_ctrl");
//            }
    }
    else if (!strcmp(ingate,"from_outside")) {
        if (msg->getKind() == 1 || msg->getKind() == 5 || msg->getKind() == 6) {
            send(msg,"to_latch_ctrl");
        }
        else if (msg->getKind() == 2) {
            send(msg,"to_transceiver");
        }
    } else if (!strcmp(ingate,"from_latch")) {
        send(msg,"to_outside");
        } else bubble("router received something unexpected...");
}
