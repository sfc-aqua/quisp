package networks;

import ned.DatarateChannel;
import modules.*;
import channels.*;
import modules.Backend.Backend;
import modules.Logger.Logger;

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
        endnode[3]: QNode {
            address = 10000000+index;
            nodeType = "EndNode";
            @display("i=COMP;p=480,88");
        }
        repeater[3]: QNode {
            address = sizeof(endnode) + index;
            nodeType = "Repeater";
            @display("i=REP1G;p=445,236");
        }
        HOM[6]: HOM {
            address = sizeof(endnode) +sizeof(repeater) + index;
            @display("p=560,137");
        }
        router[1]: QNode {
            address = sizeof(endnode) +sizeof(repeater) +sizeof(HOM) + index;
            nodeType = "Router";
            @display("i=RTR;p=357,144");
        }
    connections:
        endnode[0].port++ <--> ClassicalChannel {  cost = 20; } <--> HOM[0].port++;
        HOM[0].port++ <--> ClassicalChannel <--> repeater[0].port++;
        repeater[0].port++ <--> ClassicalChannel <--> HOM[1].port++;
        HOM[1].port++ <--> ClassicalChannel <--> router[0].port++;

        endnode[1].port++ <--> ClassicalChannel <--> HOM[2].port++;
        HOM[2].port++ <--> ClassicalChannel <--> repeater[1].port++;
        repeater[1].port++ <--> ClassicalChannel <--> HOM[3].port++;
        HOM[3].port++ <--> ClassicalChannel <--> router[0].port++;

        endnode[2].port++ <--> ClassicalChannel <--> HOM[4].port++;
        HOM[4].port++ <--> ClassicalChannel <--> repeater[2].port++;
        repeater[2].port++ <--> ClassicalChannel <--> HOM[5].port++;
        HOM[5].port++ <--> ClassicalChannel <--> router[0].port++;

        endnode[0].quantum_port++ <--> QuantumChannel <--> HOM[0].quantum_port++;
        HOM[0].quantum_port++ <--> QuantumChannel <--> repeater[0].quantum_port++;
        repeater[0].quantum_port++ <--> QuantumChannel <--> HOM[1].quantum_port++;
        HOM[1].quantum_port++ <--> QuantumChannel <--> router[0].quantum_port++;

        endnode[1].quantum_port++ <--> QuantumChannel <--> HOM[2].quantum_port++;
        HOM[2].quantum_port++ <--> QuantumChannel <--> repeater[1].quantum_port++;
        repeater[1].quantum_port++ <--> QuantumChannel <--> HOM[3].quantum_port++;
        HOM[3].quantum_port++ <--> QuantumChannel <--> router[0].quantum_port++;

        endnode[2].quantum_port++ <--> QuantumChannel <--> HOM[4].quantum_port++;
        HOM[4].quantum_port++ <--> QuantumChannel <--> repeater[2].quantum_port++;
        repeater[2].quantum_port++ <--> QuantumChannel <--> HOM[5].quantum_port++;
        HOM[5].quantum_port++ <--> QuantumChannel <--> router[0].quantum_port++;
}
