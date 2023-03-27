package networks;

import ned.DatarateChannel;
import modules.*;
import channels.*;
import modules.Backend.Backend;
import modules.Logger.Logger;
import modules.SharedResourceHolder.SharedResourceHolder;

//
// TODO auto-generated type
//
network Simple_constant_quantum_cost
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        **.buffers = default(30);
        **.distance = 20 km;
        @display("bgb=746,327");

    submodules:
        backend: Backend;
        logger: Logger;
        sharedResourceHolder: SharedResourceHolder;
        endnode[3]: QNode {
            address = 10000000+index;
            node_type = "EndNode";
            @display("i=COMP;p=480,88");
        }
        repeater[3]: QNode {
            address = sizeof(endnode) + index;
            node_type = "Repeater";
            @display("i=REP1G;p=445,236");
        }
        BSA[6]: BSANode {
            address = sizeof(endnode) +sizeof(repeater) + index;
            @display("p=560,137");
        }
        router[1]: QNode {
            address = sizeof(endnode) +sizeof(repeater) +sizeof(BSA) + index;
            node_type = "Router";
            @display("i=RTR;p=357,144");
        }
    connections:
        endnode[0].port++ <--> ClassicalChannel {  cost = 20; } <--> BSA[0].port++;
        BSA[0].port++ <--> ClassicalChannel <--> repeater[0].port++;
        repeater[0].port++ <--> ClassicalChannel <--> BSA[1].port++;
        BSA[1].port++ <--> ClassicalChannel <--> router[0].port++;

        endnode[1].port++ <--> ClassicalChannel <--> BSA[2].port++;
        BSA[2].port++ <--> ClassicalChannel <--> repeater[1].port++;
        repeater[1].port++ <--> ClassicalChannel <--> BSA[3].port++;
        BSA[3].port++ <--> ClassicalChannel <--> router[0].port++;

        endnode[2].port++ <--> ClassicalChannel <--> BSA[4].port++;
        BSA[4].port++ <--> ClassicalChannel <--> repeater[2].port++;
        repeater[2].port++ <--> ClassicalChannel <--> BSA[5].port++;
        BSA[5].port++ <--> ClassicalChannel <--> router[0].port++;

        endnode[0].quantum_port++ <--> QuantumChannel <--> BSA[0].quantum_port++;
        BSA[0].quantum_port++ <--> QuantumChannel <--> repeater[0].quantum_port++;
        repeater[0].quantum_port++ <--> QuantumChannel <--> BSA[1].quantum_port++;
        BSA[1].quantum_port++ <--> QuantumChannel <--> router[0].quantum_port++;

        endnode[1].quantum_port++ <--> QuantumChannel <--> BSA[2].quantum_port++;
        BSA[2].quantum_port++ <--> QuantumChannel <--> repeater[1].quantum_port++;
        repeater[1].quantum_port++ <--> QuantumChannel <--> BSA[3].quantum_port++;
        BSA[3].quantum_port++ <--> QuantumChannel <--> router[0].quantum_port++;

        endnode[2].quantum_port++ <--> QuantumChannel <--> BSA[4].quantum_port++;
        BSA[4].quantum_port++ <--> QuantumChannel <--> repeater[2].quantum_port++;
        repeater[2].quantum_port++ <--> QuantumChannel <--> BSA[5].quantum_port++;
        BSA[5].quantum_port++ <--> QuantumChannel <--> router[0].quantum_port++;
}
