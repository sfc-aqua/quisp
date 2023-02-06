package networks;

import modules.*;
import channels.*;
import ned.IdealChannel;
import ned.DatarateChannel;
import modules.Backend.Backend;
import modules.Logger.Logger;

network two_node_MIM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=56,202");
        }
        EndNode2: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP;p=313,202");
        }
        BSA: BSANode {
            address = 3;
            node_type = "BSA";
            @dispaly("p=42,150");
            @display("p=185,137");
        }

    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA.port++;
        EndNode2.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA.port++;

        EndNode1.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA.quantum_port++;
        EndNode2.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA.quantum_port++;
}

network two_node_MM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=56,202");
        }
        EndNode2: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP;p=313,202");
        }

    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 1km; } <--> EndNode2.port++;
        EndNode1.quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> EndNode2.quantum_port_receiver++;
}

network two_node_fake_MM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=56,202");
        }
        EndNode2: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP;p=313,202");
        }
        HOM: BSANode {
            address = 3;
            node_type = "BSA";
            @dispaly("p=42,150");
            @display("p=185,137");
        }

    connections:
        EndNode1.port++ <--> ClassicalChannel { distance = 1km; } <--> HOM.port++;
        EndNode2.port++ <--> ClassicalChannel { distance = 0km; } <--> HOM.port++;

        EndNode1.quantum_port++ <--> QuantumChannel { distance = 1km; } <--> HOM.quantum_port++;
        EndNode2.quantum_port++ <--> QuantumChannel { distance = 0km; } <--> HOM.quantum_port++;
}
