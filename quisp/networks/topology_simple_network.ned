package networks;

import ned.DatarateChannel;
import ned.IdealChannel;

import modules.*;
import modules.Backend.Backend;
import modules.Logger.Logger;
import modules.SharedResource.SharedResource;
import channels.*;

network Simple_MIM
{
    parameters:
        **.speed_of_light_in_fiber = 208189.206944 km;
        **.speed_of_light_in_FS = 299792.458 km;

    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        EndNode1: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=98,62,m,5,60,60");
        }
        EndNode2: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP;p=268,62,m,5,60,60");
        }
        BSA: BSANode {
            address = 3;
            @display("p=184,85,m,5,60,60");
        }

    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA.port++;
        BSA.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> EndNode2.port++;
        EndNode1.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA.quantum_port++;
        BSA.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> EndNode2.quantum_port++;

}

network Simple_MM
{
    parameters:
        **.speed_of_light_in_fiber = 208189.206944 km;

    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        EndNode1: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=104,48,m,5,60,60");
        }
        EndNode2: QNode {
            address = 2;
            is_initiator = true;
            node_type = "EndNode";
            @display("i=COMP;p=248,39,m,5,60,60");
        }

    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 1km; } <--> EndNode2.port++;
        EndNode1.quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> EndNode2.quantum_port_receiver++;
}

network Simple_MM_SAT
{
    parameters:
        **.speed_of_light_in_FS = 299792.458 km;

    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        EndNode1: QNode_Sat {
            address = 1;
            is_satellite = true;
            node_type = "EndNode";
            @display("i=COMP;p=196,35,m,5,60,60");
        }
        EndNode2: QNode_Sat {
            address = 2;
            is_satellite = false;
            is_initiator = true;
            node_type = "EndNode";
            @display("i=COMP;p=295,201,m,5,60,60");
        }

    connections:
        EndNode1.port++ <--> ClassicalChannel_FS {  distance = 1km; } <--> EndNode2.port++;
        EndNode1.quantum_port++ <--> QuantumChannel_FS {  distance = 1km; } <--> EndNode2.quantum_port_receiver++;
}

network three_node_MIM
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
        BSA1: BSANode {
            address = 2;
            node_type = "BSA";
            @dispaly("p=42,150");
            @display("p=158,86");
        }
        BSA2: BSANode {
            address = 4;
            node_type = "BSA";
            @dispaly("p=42,150");
            @display("p=371,86");
        }
    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA1.port++;
        Repeater.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA1.port++;
        Repeater.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA2.port++;
        EndNode2.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA2.port++;

        EndNode1.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA1.quantum_port++;
        Repeater.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA1.quantum_port++;
        Repeater.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA2.quantum_port++;
        EndNode2.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA2.quantum_port++;
}

network three_node_MM
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
    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 1km; } <--> Repeater.port++;
        Repeater.port++ <--> ClassicalChannel {  distance = 1km; } <--> EndNode2.port++;

        EndNode1.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> Repeater.quantum_port_receiver++;
        Repeater.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> EndNode2.quantum_port_receiver++;
}
