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

#include "Latch.h"

namespace quisp::modules::Satellite {

Define_Module(Latch);

void Latch::initialize()
{

}

void Latch::handleMessage(cMessage *msg)
{
    const char* in_gate = msg->getArrivalGate()->getName();
    if (!strcmp(in_gate,"ctrl")) {
        switch(msg->getKind()) {
        case 5:
            reset_ctrl(OPEN);
            unload_stack();
            break;
        case 6:
            reset_ctrl(CLOSED);
            break;
        case 1:
            toggle_ctrl();
            if (ctrl == OPEN) unload_stack();
            break;
        default:
            break;
        }
        delete msg;
    } else if (!strcmp(in_gate,"in")) {
        if (ctrl == OPEN) send(msg,"out");
        else {
            stack.push(msg);
        }
    }
}

void Latch::toggle_ctrl() {
    ctrl = LT_CTRL(!ctrl);
}

void Latch::reset_ctrl(LT_CTRL rst_val) {
    ctrl = rst_val;
}

void Latch::unload_stack() {
    while (!(stack.empty())) {
       cMessage* msg = stack.front();
       send(msg,"out");
       stack.pop();
    }
}

}
