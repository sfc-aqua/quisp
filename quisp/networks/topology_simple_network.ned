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
        // **.speed_of_light_in_fiber = 208189.206944 km;

    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=60.333336,16.893333,m,5,60,60");
        }
        EndNode2: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP;p=60.333336,16.893333,m,5,60,60");
        }
        BSA: BSANode {
            address = 3;
            @display("p=67.57333,70.590004,m,5,60,60");
        }
    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 5km; } <--> BSA.port++;
        BSA.port++ <--> ClassicalChannel { distance = 5km; } <--> EndNode2.port++;
        EndNode1.quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> BSA.quantum_port++;
        BSA.quantum_port++ <--> QuantumChannel{ distance = 5km; } <--> EndNode2.quantum_port++;

}


// network Star_MSM
// {
//     parameters:
//         **.speed_of_light_in_fiber = 205336.986301 km;

//         @display("bgb=273,198");
//     submodules:
//         backend: Backend;
//         logger: Logger;
//         node[3]: QNode {
//             address = index;
//             node_type = "EndNode";
//             @display("i=COMP;p=182,120,m,5,60,60");
//             //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
//             //emission_timing_uncertainty = 10;
//         }
//         spdc[6]: SPDC {
//             address = index+1000;
//             @display("i=EPPS;p=110,77,m,5,60,60");
//         }
//         router[1]: QNode {
//             address = index+1000000;
//             @display("i=RTR;p=91,148,m,5,60,60");
//         }
//         repeater[3]: QNode {
//             address = index+1000;
//             @display("i=REP1G;p=175,40,m,5,60,60");
//         }


//     connections:
//         node[0].port++ <--> ClassicalChannel <--> spdc[0].port++;
//         spdc[0].port++ <--> ClassicalChannel <--> repeater[0].port++;
//         repeater[0].port++ <--> ClassicalChannel <--> spdc[1].port++;
//         spdc[1].port++ <--> ClassicalChannel <--> router[0].port++;

//         node[0].quantum_port_receiver++ <--> QuantumChannel <--> spdc[0].quantum_port++;
//         spdc[0].quantum_port++ <--> QuantumChannel <--> repeater[0].quantum_port_receiver++;
//         repeater[0].quantum_port_receiver++ <--> QuantumChannel <--> spdc[1].quantum_port++;
//         spdc[1].quantum_port++ <--> QuantumChannel <--> router[0].quantum_port_receiver++;

//         node[1].port++ <--> ClassicalChannel <--> spdc[2].port++;
//         spdc[2].port++ <--> ClassicalChannel <--> repeater[1].port++;
//         repeater[1].port++ <--> ClassicalChannel <--> spdc[3].port++;
//         spdc[3].port++ <--> ClassicalChannel <--> router[0].port++;

//         node[1].quantum_port_receiver++ <--> QuantumChannel <--> spdc[2].quantum_port++;
//         spdc[2].quantum_port++ <--> QuantumChannel <--> repeater[1].quantum_port_receiver++;
//         repeater[1].quantum_port_receiver++ <--> QuantumChannel <--> spdc[3].quantum_port++;
//         spdc[3].quantum_port++ <--> QuantumChannel <--> router[0].quantum_port_receiver++;

//         node[2].port++ <--> ClassicalChannel <--> spdc[4].port++;
//         spdc[4].port++ <--> ClassicalChannel <--> repeater[2].port++;
//         repeater[2].port++ <--> ClassicalChannel <--> spdc[5].port++;
//         spdc[5].port++ <--> ClassicalChannel <--> router[0].port++;

//         node[2].quantum_port_receiver++ <--> QuantumChannel <--> spdc[4].quantum_port++;
//         spdc[4].quantum_port++ <--> QuantumChannel <--> repeater[2].quantum_port_receiver++;
//         repeater[2].quantum_port_receiver++ <--> QuantumChannel <--> spdc[5].quantum_port++;
//         spdc[5].quantum_port++ <--> QuantumChannel <--> router[0].quantum_port_receiver++;
// }



// network Star_MM
// {
//     parameters:
//         **.speed_of_light_in_fiber = 205336.986301 km;

//     submodules:
//         backend: Backend;
//         logger: Logger;
//         node[3]: QNode {
//             address = index;
//             node_type = "EndNode";
//             @display("i=device/pc");
//             //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
//             //emission_timing_uncertainty = 10;
//         }
//         router[1]: QNode {
//             address = index+1000000;
//             @display("i=device/router");
//         }



//     connections:
//         node[0].port++ <--> ClassicalChannel <--> router[0].port++;
//         node[1].port++ <--> ClassicalChannel <--> router[0].port++;
//         node[2].port++ <--> ClassicalChannel <--> router[0].port++;

//         node[0].quantum_port_receiver++ <--> QuantumChannel <--> router[0].quantum_port++;
//         node[1].quantum_port_receiver++ <--> QuantumChannel <--> router[0].quantum_port++;
//         node[2].quantum_port_receiver++ <--> QuantumChannel <--> router[0].quantum_port++;
// }
