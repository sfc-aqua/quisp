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

network Simple_MSM
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
            @display("i=COMP;p=98,62,m,5,60,60");
        }
        EndNode2: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP;p=268,62,m,5,60,60");
        }
        EPPS: EPPSNode {
            address = 3;
            @display("p=184,85,m,5,60,60");
        }

    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> EPPS.port++;
        EPPS.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> EndNode2.port++;
        EndNode1.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 0.5km; } <--> EPPS.quantum_port++;
        EPPS.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> EndNode2.quantum_port_receiver_passive++;
}

network Simple_MSM_SAT
{
    parameters:
        **.speed_of_light_in_FS = 299792.458 km;
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        EndNode1: QNode_Sat {
            address = 1;
            node_type = "EndNode";
            is_satellite = false;
            is_initiator = true;
            @display("i=COMP;p=101,264,m,5,60,60");
        }
        EndNode2: QNode_Sat {
            address = 2;
            node_type = "EndNode";
            is_satellite = false;
            @display("i=COMP;p=273,264,m,5,60,60");
        }
        EPPS: EPPSNode_Sat {
            address = 3;
            @display("p=184,85,m,5,60,60");
        }

    connections:
        EndNode1.port++ <--> ClassicalChannel_FS {  distance = 100km; } <--> EPPS.port++;
        EPPS.port++ <--> ClassicalChannel_FS {  distance = 100km; } <--> EndNode2.port++;
        EndNode1.quantum_port_receiver_passive++ <--> QuantumChannel_FS {  distance = 100km; } <--> EPPS.quantum_port++;
        EPPS.quantum_port++ <--> QuantumChannel_FS {  distance = 100km; } <--> EndNode2.quantum_port_receiver_passive++;
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
        EndNode1.port++ <--> ClassicalChannel_FS {  distance = 400km; } <--> EndNode2.port++;
        EndNode1.quantum_port++ <--> QuantumChannel_FS {  distance = 400km; } <--> EndNode2.quantum_port_receiver++;
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
        EndNode1.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> Repeater.port++;
        Repeater.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> EndNode2.port++;

        EndNode1.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> Repeater.quantum_port_receiver++;
        Repeater.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> EndNode2.quantum_port_receiver++;
}

network three_node_MSM
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
            @display("p=371,86");
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

network n_node_MSM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        @display("bgb=541,254");
        int numNodes = default(10);
        int numRepeaters = numNodes - 2;
        int lastRepeaterIndex = numRepeaters - 1;
        int numEPPSs = numRepeaters + 1;
        double classicalDistance @unit(km) = default(1.0km);
        double quantumDistance @unit(km) = default(1.0km);

    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        Repeater[numNodes - 2]: QNode {
            address = index + 2;
            node_type = "Repeater";
            @display("i=REP1G");
        }
        EndNode[2]: QNode {
            address = index;
            node_type = "EndNode";
            @display("i=COMP");
        }
        EPPS[numEPPSs]: EPPSNode {
            address = index + parent.numNodes;
            node_type = "EPPS";
        }
    connections:
        EndNode[0].port++ <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> EPPS[0].port++;
        EPPS[0].port++ <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> Repeater[0].port++;
        EndNode[0].quantum_port_receiver_passive++ <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> EPPS[0].quantum_port++;
        EPPS[0].quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> Repeater[0].quantum_port_receiver_passive++;

        Repeater[i].port++ <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> EPPS[i+1].port++ for i=0..numRepeaters - 2;
        EPPS[i+1].port++ <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> Repeater[i+1].port++ for i=0..numRepeaters - 2;
        Repeater[i].quantum_port_receiver_passive++ <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> EPPS[i+1].quantum_port++ for i=0..numRepeaters - 2;
        EPPS[i+1].quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> Repeater[i+1].quantum_port_receiver_passive++ for i=0..numRepeaters - 2;

        EndNode[1].port++ <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> EPPS[sizeof(EPPS)-1].port++;
        EPPS[sizeof(EPPS)-1].port++ <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> Repeater[lastRepeaterIndex].port++;

        EndNode[1].quantum_port_receiver_passive++ <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> EPPS[sizeof(EPPS)-1].quantum_port++;
        EPPS[sizeof(EPPS)-1].quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> Repeater[lastRepeaterIndex].quantum_port_receiver_passive++;
}
