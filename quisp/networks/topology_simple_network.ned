package networks;

import ned.DatarateChannel;
import ned.IdealChannel;

import modules.*;
import modules.Backend.Backend;
import modules.Logger.Logger;
import channels.*;

network Simple_MIM
{
    parameters:
        **.speed_of_light_in_fiber = 208189.206944 km;

    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1: QNode {
            address = "0.1";
            node_type = "EndNode";
            @display("i=COMP;p=98,62,m,5,60,60");
        }
        EndNode2: QNode {
            address = "0.2";
            node_type = "EndNode";
            @display("i=COMP;p=268,62,m,5,60,60");
        }
        BSA: BSANode {
            address = "0.3";
            @display("p=184,85,m,5,60,60");
        }

    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 1km; } <--> BSA.port++;
        BSA.port++ <--> ClassicalChannel {  distance = 1km; } <--> EndNode2.port++;
        EndNode1.quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> BSA.quantum_port++;
        BSA.quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> EndNode2.quantum_port++;

}

network Simple_MM
{
    parameters:
        **.speed_of_light_in_fiber = 208189.206944 km;

    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1: QNode {
            address = "0.1";
            node_type = "EndNode";
            @display("i=COMP;p=104,48,m,5,60,60");
        }
        EndNode2: QNode {
            address = "0.2";
            node_type = "EndNode";
            @display("i=COMP;p=248,39,m,5,60,60");
        }

    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 1km; } <--> EndNode2.port++;
        EndNode1.quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> EndNode2.quantum_port_receiver++;
}
