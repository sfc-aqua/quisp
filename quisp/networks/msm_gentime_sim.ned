package networks;

import ned.DatarateChannel;
import ned.IdealChannel;

import modules.*;
import modules.Backend.Backend;
import modules.Logger.Logger;
import modules.SharedResource.SharedResource;
import channels.*;

network Testing_MSM
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
        EndNode1.port++ <--> ClassicalChannel {  distance = 10km; } <--> EPPS.port++;
        EPPS.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode2.port++;
        EndNode1.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 10km; } <--> EPPS.quantum_port++;
        EPPS.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode2.quantum_port_receiver_passive++;
}

network MSM_ES_Four
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
            @display("i=COMP;p=67,217,m,5,60,60");
        }
        EndNode2: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP;p=279,217,m,5,60,60");
        }
        EndNode3: QNode {
            address = 3;
            node_type = "EndNode";
            @display("i=COMP;p=505,110,m,5,60,60");
        }
        EndNode4: QNode {
            address = 4;
            node_type = "EndNode";
            @display("i=COMP;p=730,217,m,5,60,60");
        }
        EPPS1: EPPSNode {
            address = 5;
            @display("p=185,157,m,5,60,60");
        }
        EPPS2: EPPSNode {
            address = 6;
            @display("p=388,157,m,5,60,60");
        }
        EPPS3: EPPSNode {
            address = 7;
            @display("p=641,157,m,5,60,60");
        }

    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 10km; } <--> EPPS1.port++;
        EPPS1.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode2.port++;
        EndNode1.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 10km; } <--> EPPS1.quantum_port++;
        EPPS1.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode2.quantum_port_receiver_passive++;
        EndNode2.port++ <--> ClassicalChannel {  distance = 10km; } <--> EPPS2.port++;
        EPPS2.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode3.port++;
        EndNode2.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 10km; } <--> EPPS2.quantum_port++;
        EPPS2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode3.quantum_port_receiver_passive++;
        EndNode3.port++ <--> ClassicalChannel {  distance = 10km; } <--> EPPS3.port++;
        EPPS3.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode4.port++;
        EndNode3.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 10km; } <--> EPPS3.quantum_port++;
        EPPS3.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode4.quantum_port_receiver_passive++;
}
