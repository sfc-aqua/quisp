package networks;

import ned.DatarateChannel;
import ned.IdealChannel;

import modules.*;
import modules.Backend.Backend;
import modules.Logger.Logger;
import modules.SharedResource.SharedResource;
import channels.*;


network cross_validation_swapping
{
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
        EndNode1.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA1.port++;
        Repeater.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA1.port++;
        Repeater.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA2.port++;
        EndNode2.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA2.port++;

        EndNode1.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA1.quantum_port++;
        Repeater.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA1.quantum_port++;
        Repeater.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA2.quantum_port++;
        EndNode2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA2.quantum_port++;
}

network cross_validation_mim_link_middle
{
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        alice: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP");
        }
        BSA: BSANode {
            address = 2;
            @display("i=BSA");
        }
        bob: QNode {
            address = 3;
            node_type = "EndNode";
            @display("i=COMP");
        }
    connections:
        alice.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA.port++;
        BSA.port++ <--> ClassicalChannel {  distance = 10km; } <--> bob.port++;
        alice.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA.quantum_port++;
        BSA.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> bob.quantum_port++;
}

network cross_validation_mim_link_imbalanced_10_10
{
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        alice: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP");
        }
        BSA: BSANode {
            address = 2;
            @display("i=BSA");
        }
        bob: QNode {
            address = 3;
            node_type = "EndNode";
            @display("i=COMP");
        }
    connections:
        alice.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA.port++;
        BSA.port++ <--> ClassicalChannel {  distance = 10km; } <--> bob.port++;
        alice.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA.quantum_port++;
        BSA.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> bob.quantum_port++;
}

network cross_validation_mim_link_imbalanced_11_9
{
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        alice: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP");
        }
        BSA: BSANode {
            address = 2;
            @display("i=BSA");
        }
        bob: QNode {
            address = 3;
            node_type = "EndNode";
            @display("i=COMP");
        }
    connections:
        alice.port++ <--> ClassicalChannel {  distance = 11km; } <--> BSA.port++;
        BSA.port++ <--> ClassicalChannel {  distance = 9km; } <--> bob.port++;
        alice.quantum_port++ <--> QuantumChannel {  distance = 11km; } <--> BSA.quantum_port++;
        BSA.quantum_port++ <--> QuantumChannel {  distance = 9km; } <--> bob.quantum_port++;
}

network cross_validation_mim_link_imbalanced_12_8
{
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        alice: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP");
        }
        BSA: BSANode {
            address = 2;
            @display("i=BSA");
        }
        bob: QNode {
            address = 3;
            node_type = "EndNode";
            @display("i=COMP");
        }
    connections:
        alice.port++ <--> ClassicalChannel {  distance = 12km; } <--> BSA.port++;
        BSA.port++ <--> ClassicalChannel {  distance = 8km; } <--> bob.port++;
        alice.quantum_port++ <--> QuantumChannel {  distance = 12km; } <--> BSA.quantum_port++;
        BSA.quantum_port++ <--> QuantumChannel {  distance = 8km; } <--> bob.quantum_port++;
}

network cross_validation_mim_link_imbalanced_13_7
{
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        alice: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP");
        }
        BSA: BSANode {
            address = 2;
            @display("i=BSA");
        }
        bob: QNode {
            address = 3;
            node_type = "EndNode";
            @display("i=COMP");
        }
    connections:
        alice.port++ <--> ClassicalChannel {  distance = 13km; } <--> BSA.port++;
        BSA.port++ <--> ClassicalChannel {  distance = 7km; } <--> bob.port++;
        alice.quantum_port++ <--> QuantumChannel {  distance = 13km; } <--> BSA.quantum_port++;
        BSA.quantum_port++ <--> QuantumChannel {  distance = 7km; } <--> bob.quantum_port++;
}

network cross_validation_mim_link_imbalanced_14_6
{
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        alice: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP");
        }
        BSA: BSANode {
            address = 2;
            @display("i=BSA");
        }
        bob: QNode {
            address = 3;
            node_type = "EndNode";
            @display("i=COMP");
        }
    connections:
        alice.port++ <--> ClassicalChannel {  distance = 14km; } <--> BSA.port++;
        BSA.port++ <--> ClassicalChannel {  distance = 6km; } <--> bob.port++;
        alice.quantum_port++ <--> QuantumChannel {  distance = 14km; } <--> BSA.quantum_port++;
        BSA.quantum_port++ <--> QuantumChannel {  distance = 6km; } <--> bob.quantum_port++;
}

network cross_validation_mim_link_imbalanced_15_5
{
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        alice: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP");
        }
        BSA: BSANode {
            address = 2;
            @display("i=BSA");
        }
        bob: QNode {
            address = 3;
            node_type = "EndNode";
            @display("i=COMP");
        }
    connections:
        alice.port++ <--> ClassicalChannel {  distance = 15km; } <--> BSA.port++;
        BSA.port++ <--> ClassicalChannel {  distance = 5km; } <--> bob.port++;
        alice.quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> BSA.quantum_port++;
        BSA.quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> bob.quantum_port++;
}

network cross_validation_mim_link_imbalanced_16_4
{
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        alice: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP");
        }
        BSA: BSANode {
            address = 2;
            @display("i=BSA");
        }
        bob: QNode {
            address = 3;
            node_type = "EndNode";
            @display("i=COMP");
        }
    connections:
        alice.port++ <--> ClassicalChannel {  distance = 16km; } <--> BSA.port++;
        BSA.port++ <--> ClassicalChannel {  distance = 4km; } <--> bob.port++;
        alice.quantum_port++ <--> QuantumChannel {  distance = 16km; } <--> BSA.quantum_port++;
        BSA.quantum_port++ <--> QuantumChannel {  distance = 4km; } <--> bob.quantum_port++;
}

network cross_validation_mim_link_imbalanced_17_3
{
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        alice: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP");
        }
        BSA: BSANode {
            address = 2;
            @display("i=BSA");
        }
        bob: QNode {
            address = 3;
            node_type = "EndNode";
            @display("i=COMP");
        }
    connections:
        alice.port++ <--> ClassicalChannel {  distance = 17km; } <--> BSA.port++;
        BSA.port++ <--> ClassicalChannel {  distance = 3km; } <--> bob.port++;
        alice.quantum_port++ <--> QuantumChannel {  distance = 17km; } <--> BSA.quantum_port++;
        BSA.quantum_port++ <--> QuantumChannel {  distance = 3km; } <--> bob.quantum_port++;
}

network cross_validation_mim_link_imbalanced_18_2
{
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        alice: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP");
        }
        BSA: BSANode {
            address = 2;
            @display("i=BSA");
        }
        bob: QNode {
            address = 3;
            node_type = "EndNode";
            @display("i=COMP");
        }
    connections:
        alice.port++ <--> ClassicalChannel {  distance = 18km; } <--> BSA.port++;
        BSA.port++ <--> ClassicalChannel {  distance = 2km; } <--> bob.port++;
        alice.quantum_port++ <--> QuantumChannel {  distance = 18km; } <--> BSA.quantum_port++;
        BSA.quantum_port++ <--> QuantumChannel {  distance = 2km; } <--> bob.quantum_port++;
}

network cross_validation_mim_link_imbalanced_19_1
{
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        alice: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP");
        }
        BSA: BSANode {
            address = 2;
            @display("i=BSA");
        }
        bob: QNode {
            address = 3;
            node_type = "EndNode";
            @display("i=COMP");
        }
    connections:
        alice.port++ <--> ClassicalChannel {  distance = 19km; } <--> BSA.port++;
        BSA.port++ <--> ClassicalChannel {  distance = 1km; } <--> bob.port++;
        alice.quantum_port++ <--> QuantumChannel {  distance = 19km; } <--> BSA.quantum_port++;
        BSA.quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> bob.quantum_port++;
}

network cross_validation_mim_link_imbalanced_20_0
{
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        alice: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP");
        }
        BSA: BSANode {
            address = 2;
            @display("i=BSA");
        }
        bob: QNode {
            address = 3;
            node_type = "EndNode";
            @display("i=COMP");
        }
    connections:
        alice.port++ <--> ClassicalChannel {  distance = 20km; } <--> BSA.port++;
        BSA.port++ <--> ClassicalChannel {  distance = 0km; } <--> bob.port++;
        alice.quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> BSA.quantum_port++;
        BSA.quantum_port++ <--> QuantumChannel {  distance = 0km; } <--> bob.quantum_port++;
}
