package networks;

import ned.DatarateChannel;
import ned.IdealChannel;

import modules.*;
import modules.Backend.Backend;
import modules.Logger.Logger;
import modules.SharedResource.SharedResource;
import channels.*;

network MIM_MSM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        @display("bgb=541,254");
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        EndNode1: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=56,202");
        }
        EndNode2: QNode {
            address = 5;
            node_type = "EndNode";
            @display("i=COMP;p=473,202");
        }
        Repeater: QNode {
            address = 3;
            node_type = "Repeater";
            @display("i=REP1G;p=264,203");
        }
        BSA: BSANode {
            address = 2;
            node_type = "BSA";
            @display("p=158,86");
        }
        EPPS: EPPSNode {
            address = 4;
            node_type = "EPPS";
            @display("p=371,86");
        }
    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA.port++;
        Repeater.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA.port++;
        Repeater.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> EPPS.port++;
        EndNode2.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> EPPS.port++;

        EndNode1.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA.quantum_port++;
        Repeater.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA.quantum_port++;
        Repeater.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 0.5km; } <--> EPPS.quantum_port++;
        EndNode2.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 0.5km; } <--> EPPS.quantum_port++;
}
network MIM_MSM_long
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        @display("bgb=541,254");
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        EndNode1: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=56,202");
        }
        EndNode2: QNode {
            address = 5;
            node_type = "EndNode";
            @display("i=COMP;p=473,202");
        }
        Repeater: QNode {
            address = 3;
            node_type = "Repeater";
            @display("i=REP1G;p=264,203");
        }
        BSA: BSANode {
            address = 2;
            node_type = "BSA";
            @display("p=158,86");
        }
        EPPS: EPPSNode {
            address = 4;
            node_type = "EPPS";
            @display("p=371,86");
        }
    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA.port++;
        Repeater.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA.port++;
        Repeater.port++ <--> ClassicalChannel {  distance = 10km; } <--> EPPS.port++;
        EndNode2.port++ <--> ClassicalChannel {  distance = 10km; } <--> EPPS.port++;

        EndNode1.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA.quantum_port++;
        Repeater.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA.quantum_port++;
        Repeater.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 10km; } <--> EPPS.quantum_port++;
        EndNode2.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 10km; } <--> EPPS.quantum_port++;
}

network MIM_only
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        @display("bgb=541,254");
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        EndNode1: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=56,202");
        }
        EndNode2: QNode {
            address = 5;
            node_type = "EndNode";
            @display("i=COMP;p=473,202");
        }
        Repeater: QNode {
            address = 3;
            node_type = "Repeater";
            @display("i=REP1G;p=264,203");
        }
        BSA: BSANode {
            address = 2;
            node_type = "BSA";
            @display("p=158,86");
        }
        BSA2: BSANode {
            address = 4;
            node_type = "BSA";
            @display("p=158,86");
        }
    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA.port++;
        Repeater.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA.port++;
        Repeater.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA2.port++;
        EndNode2.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA2.port++;

        EndNode1.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA.quantum_port++;
        Repeater.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA.quantum_port++;
        Repeater.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA2.quantum_port++;
        EndNode2.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA2.quantum_port++;
}

network MIM_only_long
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        @display("bgb=541,254");
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        EndNode1: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=56,202");
        }
        EndNode2: QNode {
            address = 5;
            node_type = "EndNode";
            @display("i=COMP;p=473,202");
        }
        Repeater: QNode {
            address = 3;
            node_type = "Repeater";
            @display("i=REP1G;p=264,203");
        }
        BSA: BSANode {
            address = 2;
            node_type = "BSA";
            @display("p=158,86");
        }
        BSA2: BSANode {
            address = 4;
            node_type = "BSA";
            @display("p=158,86");
        }
    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA.port++;
        Repeater.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA.port++;
        Repeater.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA2.port++;
        EndNode2.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA2.port++;

        EndNode1.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA.quantum_port++;
        Repeater.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA.quantum_port++;
        Repeater.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA2.quantum_port++;
        EndNode2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA2.quantum_port++;
}

network MSM_only
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        @display("bgb=541,254");
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        EndNode1: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=56,202");
        }
        EndNode2: QNode {
            address = 5;
            node_type = "EndNode";
            @display("i=COMP;p=473,202");
        }
        Repeater: QNode {
            address = 3;
            node_type = "Repeater";
            @display("i=REP1G;p=264,203");
        }
        EPPS1: EPPSNode {
            address = 2;
            node_type = "EPPS";
            @display("p=158,86");
        }
        EPPS2: EPPSNode {
            address = 4;
            node_type = "EPPS";
            @display("p=158,86");
        }
    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> EPPS1.port++;
        Repeater.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> EPPS1.port++;
        Repeater.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> EPPS2.port++;
        EndNode2.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> EPPS2.port++;

        EndNode1.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 0.5km; } <--> EPPS1.quantum_port++;
        Repeater.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 0.5km; } <--> EPPS1.quantum_port++;
        Repeater.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 0.5km; } <--> EPPS2.quantum_port++;
        EndNode2.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 0.5km; } <--> EPPS2.quantum_port++;
}

network MSM_only_long
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        @display("bgb=541,254");
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        EndNode1: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=56,202");
        }
        EndNode2: QNode {
            address = 5;
            node_type = "EndNode";
            @display("i=COMP;p=473,202");
        }
        Repeater: QNode {
            address = 3;
            node_type = "Repeater";
            @display("i=REP1G;p=264,203");
        }
        EPPS1: EPPSNode {
            address = 2;
            node_type = "EPPS";
            @display("p=158,86");
        }
        EPPS2: EPPSNode {
            address = 4;
            node_type = "EPPS";
            @display("p=158,86");
        }
    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 10km; } <--> EPPS1.port++;
        Repeater.port++ <--> ClassicalChannel {  distance = 10km; } <--> EPPS1.port++;
        Repeater.port++ <--> ClassicalChannel {  distance = 10km; } <--> EPPS2.port++;
        EndNode2.port++ <--> ClassicalChannel {  distance = 10km; } <--> EPPS2.port++;

        EndNode1.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 10km; } <--> EPPS1.quantum_port++;
        Repeater.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 10km; } <--> EPPS1.quantum_port++;
        Repeater.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 10km; } <--> EPPS2.quantum_port++;
        EndNode2.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 10km; } <--> EPPS2.quantum_port++;
}
