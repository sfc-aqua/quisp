package networks;

import ned.DatarateChannel;
import ned.IdealChannel;

import modules.*;
import modules.Backend.Backend;
import modules.Logger.Logger;
import modules.SharedResource.SharedResource;
import channels.*;


network CrossValidationTwoHop
{
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        EndNode[2]: QNode {
            address = index;
            node_type = "EndNode";
            @display("i=COMP;");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }

        repeater: QNode {
            address = 1234;
            node_type = "Repeater";
            //buffers = 25;
            @display("i=REP1G");
        }

        BSA: BSANode {
            address = 2;
            @display("i=BSA");
        }

    connections:
        EndNode[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> repeater.port++;
        repeater.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA.port++;
        BSA.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode[1].port++;

        EndNode[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 10km; } <--> repeater.quantum_port++;
        repeater.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA.quantum_port++;
        BSA.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode[1].quantum_port++;
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
        alice.port++ <--> ClassicalChannel {  distance = 20km; } <--> BSA.port++;
        BSA.port++ <--> ClassicalChannel {  distance = 20km; } <--> bob.port++;
        alice.quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> BSA.quantum_port++;
        BSA.quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> bob.quantum_port++;
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
