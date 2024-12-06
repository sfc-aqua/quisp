package networks;

import ned.DatarateChannel;
import ned.IdealChannel;

import modules.*;
import modules.Backend.Backend;
import modules.Logger.Logger;
import modules.SharedResource.SharedResource;
import channels.*;

network Var_MIM
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
        EndNode1.port++ <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> BSA.port++;
        BSA.port++      <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> EndNode2.port++;
        EndNode1.quantum_port++ <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> BSA.quantum_port++;
        BSA.quantum_port++      <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> EndNode2.quantum_port++;
}

network Var_MSM
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
        EndNode1.port++ <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> EPPS.port++;
        EPPS.port++      <--> ClassicalChannel {  distance = parent.classicalDistance / 2; } <--> EndNode2.port++;
        EndNode1.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> EPPS.quantum_port++;
        EPPS.quantum_port++      <--> QuantumChannel {  distance = parent.quantumDistance / 2; } <--> EndNode2.quantum_port_receiver_passive++;
}