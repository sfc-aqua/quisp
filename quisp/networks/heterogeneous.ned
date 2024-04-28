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

network oneMIMinMSMs
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        @display("bgb=541,254");
        int numNodes = default(10);
        int numRepeaters = numNodes - 2; // 8
        int lastRepeaterIndex = numRepeaters - 1; // 7
        int numEPPSs = numRepeaters + 1; // 9
        double classicalDistance @unit(km) = default(1.0km);
        double quantumDistance @unit(km) = default(1.0km);
        int replacingLink = default(0);

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
            @display("i=EPPS");
    	}
        BSA: BSANode {
            address = 1000;
            node_type = "BSA";
            @display("i=BSA");
    	}
    connections:
        if replacingLink==0 {
            EndNode[0].port++ <--> ClassicalChannel{ distance = parent.classicalDistance / 2;} <--> BSA.port++;
            BSA.port++ <--> ClassicalChannel{ distance = parent.classicalDistance / 2;} <--> Repeater[0].port++;
            EndNode[0].quantum_port++ <--> QuantumChannel{ distance = parent.quantumDistance / 2;} <--> BSA.quantum_port++;
            BSA.quantum_port++ <--> QuantumChannel{ distance = parent.quantumDistance / 2;} <--> Repeater[0].quantum_port++;
        }
        if replacingLink!=0 {
            EndNode[0].port++ <--> ClassicalChannel{ distance = parent.classicalDistance / 2;} <--> EPPS[0].port++;
            EPPS[0].port++ <--> ClassicalChannel{ distance = parent.classicalDistance / 2;} <--> Repeater[0].port++;
            EndNode[0].quantum_port_receiver_passive++ <--> QuantumChannel{ distance = parent.quantumDistance / 2;} <--> EPPS[0].quantum_port++;
            EPPS[0].quantum_port++ <--> QuantumChannel{ distance = parent.quantumDistance / 2;} <--> Repeater[0].quantum_port_receiver_passive++;
        }
        for i = 0..numRepeaters-2 {
                Repeater[i].port++ <--> ClassicalChannel{ distance = parent.classicalDistance / 2;} <--> BSA.port++ if replacingLink==i+1;
                BSA.port++ <--> ClassicalChannel{ distance = parent.classicalDistance / 2;} <--> Repeater[i+1].port++ if replacingLink==i+1;
                Repeater[i].quantum_port++ <--> QuantumChannel{ distance = parent.quantumDistance / 2;} <--> BSA.quantum_port++ if replacingLink==i+1;
                BSA.quantum_port++ <--> QuantumChannel{ distance = parent.quantumDistance / 2;} <--> Repeater[i+1].quantum_port++ if replacingLink==i+1;
        
                Repeater[i].port++ <--> ClassicalChannel{ distance = parent.classicalDistance / 2;} <--> EPPS[i+1].port++ if replacingLink!=i+1;
                EPPS[i+1].port++ <--> ClassicalChannel{ distance = parent.classicalDistance / 2;} <--> Repeater[i+1].port++ if replacingLink!=i+1;
                Repeater[i].quantum_port_receiver_passive++ <--> QuantumChannel{ distance = parent.quantumDistance / 2;} <--> EPPS[i+1].quantum_port++ if replacingLink!=i+1;
                EPPS[i+1].quantum_port++ <--> QuantumChannel{ distance = parent.quantumDistance / 2;} <--> Repeater[i+1].quantum_port_receiver_passive++ if replacingLink!=i+1;
        }
        if replacingLink==lastRepeaterIndex+1{
            EndNode[1].port++ <--> ClassicalChannel{ distance = parent.classicalDistance / 2;} <--> BSA.port++;
            BSA.port++ <--> ClassicalChannel{ distance = parent.classicalDistance / 2;} <--> Repeater[lastRepeaterIndex].port++;
            EndNode[1].quantum_port++ <--> QuantumChannel{ distance = parent.quantumDistance / 2;} <--> BSA.quantum_port++;
            BSA.quantum_port++ <--> QuantumChannel{ distance = parent.quantumDistance / 2;} <--> Repeater[lastRepeaterIndex].quantum_port++;
        }
        if replacingLink!=lastRepeaterIndex+1{
            EndNode[1].port++ <--> ClassicalChannel{ distance = parent.classicalDistance / 2;} <--> EPPS[sizeof(EPPS)-1].port++;
            EPPS[sizeof(EPPS)-1].port++ <--> ClassicalChannel{ distance = parent.classicalDistance / 2;} <--> Repeater[lastRepeaterIndex].port++;
            EndNode[1].quantum_port_receiver_passive++ <--> QuantumChannel{ distance = parent.quantumDistance / 2;} <--> EPPS[sizeof(EPPS)-1].quantum_port++;
            EPPS[sizeof(EPPS)-1].quantum_port++ <--> QuantumChannel{ distance = parent.quantumDistance / 2;} <--> Repeater[lastRepeaterIndex].quantum_port_receiver_passive++;
        }

}

network MSMten
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        @display("bgb=541,254");
        int numNodes = default(10);
        int numRepeaters = numNodes - 2; // 8
        int lastRepeaterIndex = numRepeaters - 1; // 7
        int numEPPSs = numRepeaters + 1; // 9
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
            @display("i=EPPS");
    	}
    connections:
            EndNode[0].port++ <--> ClassicalChannel{ distance = parent.classicalDistance / 2;} <--> EPPS[0].port++;
            EPPS[0].port++ <--> ClassicalChannel{ distance = parent.classicalDistance / 2;} <--> Repeater[0].port++;
            EndNode[0].quantum_port_receiver_passive++ <--> QuantumChannel{ distance = parent.quantumDistance / 2;} <--> EPPS[0].quantum_port++;
            EPPS[0].quantum_port++ <--> QuantumChannel{ distance = parent.quantumDistance / 2;} <--> Repeater[0].quantum_port_receiver_passive++;
            for i = 0..numRepeaters-2 {
                    Repeater[i].port++ <--> ClassicalChannel{ distance = parent.classicalDistance / 2;} <--> EPPS[i+1].port++;
                    EPPS[i+1].port++ <--> ClassicalChannel{ distance = parent.classicalDistance / 2;} <--> Repeater[i+1].port++;
                    Repeater[i].quantum_port_receiver_passive++ <--> QuantumChannel{ distance = parent.quantumDistance / 2;} <--> EPPS[i+1].quantum_port++;
                    EPPS[i+1].quantum_port++ <--> QuantumChannel{ distance = parent.quantumDistance / 2;} <--> Repeater[i+1].quantum_port_receiver_passive++;
            }
            EndNode[1].port++ <--> ClassicalChannel{ distance = parent.classicalDistance / 2;} <--> EPPS[sizeof(EPPS)-1].port++;
            EPPS[sizeof(EPPS)-1].port++ <--> ClassicalChannel{ distance = parent.classicalDistance / 2;} <--> Repeater[lastRepeaterIndex].port++;
            EndNode[1].quantum_port_receiver_passive++ <--> QuantumChannel{ distance = parent.quantumDistance / 2;} <--> EPPS[sizeof(EPPS)-1].quantum_port++;
            EPPS[sizeof(EPPS)-1].quantum_port++ <--> QuantumChannel{ distance = parent.quantumDistance / 2;} <--> Repeater[lastRepeaterIndex].quantum_port_receiver_passive++;
}