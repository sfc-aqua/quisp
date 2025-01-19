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
        double classicalDistance @unit(km) = default(1.0km);
        double quantumDistance @unit(km) = default(1.0km);

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
        EndNode1.port++ <--> ClassicalChannel {  distance = parent.classicalDistance/2; } <--> BSA.port++;
        BSA.port++ <--> ClassicalChannel {  distance = parent.classicalDistance/2; } <--> EndNode2.port++;
        EndNode1.quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance/2; } <--> BSA.quantum_port++;
        BSA.quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance/2; } <--> EndNode2.quantum_port++;
}

network Simple_MM
{
    parameters:
        **.speed_of_light_in_fiber = 208189.206944 km;
        double classicalDistance @unit(km) = default(1.0km);
        double quantumDistance @unit(km) = default(1.0km);
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
            node_type = "EndNode";
            @display("i=COMP;p=248,39,m,5,60,60");
        }

    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = parent.classicalDistance; } <--> EndNode2.port++;
        EndNode1.quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance; } <--> EndNode2.quantum_port_receiver++;
}

network Simple_MSM
{
    parameters:
        **.speed_of_light_in_fiber = 208189.206944 km;
        double classicalDistance @unit(km) = default(1.0km);
        double quantumDistance @unit(km) = default(1.0km);

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
        EndNode1.port++ <--> ClassicalChannel {  distance = parent.classicalDistance/2; } <--> EPPS.port++;
        EPPS.port++ <--> ClassicalChannel {  distance = parent.classicalDistance/2; } <--> EndNode2.port++;
        EndNode1.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = parent.quantumDistance/2; } <--> EPPS.quantum_port++;
        EPPS.quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance/2; } <--> EndNode2.quantum_port_receiver_passive++;
}

network three_node_MIM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        @display("bgb=541,254");
        double classicalDistance @unit(km) = default(1.0km);
        double quantumDistance @unit(km) = default(1.0km);

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
        EndNode1.port++ <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> BSA1.port++;
        BSA1.port++ <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> Repeater.port++;
        Repeater.port++ <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> BSA2.port++;
        BSA2.port++ <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> EndNode2.port++;

        EndNode1.quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> BSA1.quantum_port++;
        BSA1.quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> Repeater.quantum_port++;
        Repeater.quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> BSA2.quantum_port++;
        BSA2.quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> EndNode2.quantum_port++;
}

network three_node_MM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        @display("bgb=541,254");
        double classicalDistance @unit(km) = default(1.0km);
        double quantumDistance @unit(km) = default(1.0km);

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
        EndNode1.port++ <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> Repeater.port++;
        Repeater.port++ <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> EndNode2.port++;

        EndNode1.quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> Repeater.quantum_port_receiver++;
        Repeater.quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> EndNode2.quantum_port_receiver++;
}

network three_node_MSM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        @display("bgb=541,254");
        double classicalDistance @unit(km) = default(1.0km);
        double quantumDistance @unit(km) = default(1.0km);

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
        EndNode1.port++ <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> EPPS1.port++;
        EPPS1.port++ <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> Repeater.port++;
        Repeater.port++ <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> EPPS2.port++;
        EPPS2.port++ <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> EndNode2.port++;

        EndNode1.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> EPPS1.quantum_port++;
        EPPS1.quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> Repeater.quantum_port_receiver_passive++;
        Repeater.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> EPPS2.quantum_port++;
        EPPS2.quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> EndNode2.quantum_port_receiver_passive++;

}
network n_node_MIM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        @display("bgb=541,254");
        int numNodes = default(10);
        int numRepeaters = numNodes - 2;
        int lastRepeaterIndex = numRepeaters - 1;
        int numBSAs = numRepeaters + 1;
        double classicalDistance @unit(km) = default(1.0km);
        double quantumDistance @unit(km) = default(1.0km);

    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        Repeater[numNodes - 2]: QNode {
            address = index + 2;
            node_type = "Repeater";
            @display("i=REP1G;p=127,137");
        }
        EndNode[2]: QNode {
            address = index;
            node_type = "EndNode";
            @display("i=COMP;p=126,39");
        }
        BSANode[numBSAs]: BSANode {
            address = index + parent.numNodes;
            node_type = "BSA";
            @display("p=480,100");
        }
    connections:
        EndNode[0].port++ <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> BSANode[0].port++;
        BSANode[0].port++ <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> Repeater[0].port++;
        EndNode[0].quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> BSANode[0].quantum_port++;
        BSANode[0].quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> Repeater[0].quantum_port++;

        Repeater[i].port++ <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> BSANode[i+1].port++ for i=0..numRepeaters - 2;
        BSANode[i+1].port++ <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> Repeater[i+1].port++ for i=0..numRepeaters - 2;
        Repeater[i].quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> BSANode[i+1].quantum_port++ for i=0..numRepeaters - 2;
        BSANode[i+1].quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> Repeater[i+1].quantum_port++ for i=0..numRepeaters - 2;

        EndNode[1].port++ <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> BSANode[sizeof(BSANode)-1].port++;
        BSANode[sizeof(BSANode)-1].port++ <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> Repeater[lastRepeaterIndex].port++;

        EndNode[1].quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> BSANode[sizeof(BSANode)-1].quantum_port++;
        BSANode[sizeof(BSANode)-1].quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> Repeater[lastRepeaterIndex].quantum_port++;
}

network n_node_MM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        @display("bgb=541,254");
        int numNodes = default(10);
        int numRepeaters = numNodes - 2;
        int lastRepeaterIndex = numRepeaters - 1;
        double classicalDistance @unit(km) = default(1.0km);
        double quantumDistance @unit(km) = default(1.0km);

    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        Repeater[numNodes - 2]: QNode {
            address = index + 2;
            node_type = "Repeater";
            @display("i=REP1G;p=378,100");
        }
        EndNode[2]: QNode {
            address = index;
            node_type = "EndNode";
            @display("i=COMP;p=137,99");
        }
    connections:
        EndNode[0].port++ <--> ClassicalChannel {  distance = parent.classicalDistance; } <--> Repeater[0].port++;
        Repeater[0].port++ <--> ClassicalChannel {  distance = parent.classicalDistance; } <--> EndNode[1].port++;

        EndNode[0].quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance; } <--> Repeater[0].quantum_port_receiver++;
        Repeater[0].quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance; } <--> EndNode[1].quantum_port_receiver++;

        Repeater[i].port++ <--> ClassicalChannel {  distance = parent.classicalDistance; } <--> Repeater[i+1].port++ for i=0..numRepeaters - 2;
        Repeater[i].quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance; } <--> Repeater[i+1].quantum_port_receiver++ for i=0..numRepeaters - 2;

        Repeater[lastRepeaterIndex].port++ <--> ClassicalChannel {  distance = parent.classicalDistance; } <--> EndNode[1].port++;
        Repeater[lastRepeaterIndex].quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance; } <--> EndNode[1].quantum_port_receiver++;
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
            @display("i=REP1G;p=163,148");
        }
        EndNode[2]: QNode {
            address = index;
            node_type = "EndNode";
            @display("i=COMP;p=162,50");
        }
        EPPS[numEPPSs]: EPPSNode {
            address = index + parent.numNodes;
            node_type = "EPPS";
            @display("p=470,100");
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
