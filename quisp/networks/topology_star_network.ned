package networks;

import ned.DatarateChannel;
import ned.IdealChannel;

import modules.*;
import modules.Backend.Backend;
import modules.Logger.Logger;
import modules.SharedResource.SharedResource;
import channels.*;

network Three_BSA_star
{
    parameters:
        **.speed_of_light_in_fiber = 208189.206944 km;

        @display("bgl=2;bgb=177,120");

    submodules:
        //configurator: IPv4NetworkConfigurator {
        //    @display("p=100,100");
        //}
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        EndNode[3]: QNode {
            //Initializerでaddress = node idにすればconflict無くなるかも。
            address = index+100000;
            node_type = "EndNode";
            @display("i=COMP;p=60.333336,16.893333,m,5,60,60");
        }
        BSA[3]: BSANode {
            address = index+1000;
            //@display("p=326,57");
            @display("p=67.57333,70.590004,m,5,60,60");
        }
        Router[1]: QNode {
            address = index;
            //@display("p=246,56");
            @display("i=RTR;p=126,87,m,5,60,60");
        }
    connections:
        EndNode[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> BSA[0].port++;
        BSA[0].port++ <--> ClassicalChannel <--> Router[0].port++;
        EndNode[0].quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> BSA[0].quantum_port++;
        BSA[0].quantum_port++ <--> QuantumChannel <--> Router[0].quantum_port++;

        EndNode[1].port++ <--> ClassicalChannel <--> BSA[1].port++;
        BSA[1].port++ <--> ClassicalChannel {  distance = 100km; } <--> Router[0].port++;
        EndNode[1].quantum_port++ <--> QuantumChannel <--> BSA[1].quantum_port++;
        BSA[1].quantum_port++ <--> QuantumChannel {  distance = 100km; } <--> Router[0].quantum_port++;

        EndNode[2].port++ <--> ClassicalChannel <--> BSA[2].port++;
        BSA[2].port++ <--> ClassicalChannel {  distance = 40km; } <--> Router[0].port++;
        EndNode[2].quantum_port++ <--> QuantumChannel <--> BSA[2].quantum_port++;
        BSA[2].quantum_port++ <--> QuantumChannel {  distance = 40km; } <--> Router[0].quantum_port++;
}


network Star_MSM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=273,198");
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        node[3]: QNode {
            address = index;
            node_type = "EndNode";
            @display("i=COMP;p=182,120,m,5,60,60");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        EPPS[6]: EPPSNode {
            address = index+1000;
            @display("i=EPPS;p=110,77,m,5,60,60");
        }
        router[1]: QNode {
            address = index+1000000;
            @display("i=RTR;p=91,148,m,5,60,60");
        }
        repeater[3]: QNode {
            address = index+1000;
            @display("i=REP1G;p=175,40,m,5,60,60");
        }


    connections:
        node[0].port++ <--> ClassicalChannel <--> EPPS[0].port++;
        EPPS[0].port++ <--> ClassicalChannel <--> repeater[0].port++;
        repeater[0].port++ <--> ClassicalChannel <--> EPPS[1].port++;
        EPPS[1].port++ <--> ClassicalChannel <--> router[0].port++;

        node[0].quantum_port_receiver++ <--> QuantumChannel <--> EPPS[0].quantum_port++;
        EPPS[0].quantum_port++ <--> QuantumChannel <--> repeater[0].quantum_port_receiver++;
        repeater[0].quantum_port_receiver++ <--> QuantumChannel <--> EPPS[1].quantum_port++;
        EPPS[1].quantum_port++ <--> QuantumChannel <--> router[0].quantum_port_receiver++;

        node[1].port++ <--> ClassicalChannel <--> EPPS[2].port++;
        EPPS[2].port++ <--> ClassicalChannel <--> repeater[1].port++;
        repeater[1].port++ <--> ClassicalChannel <--> EPPS[3].port++;
        EPPS[3].port++ <--> ClassicalChannel <--> router[0].port++;

        node[1].quantum_port_receiver++ <--> QuantumChannel <--> EPPS[2].quantum_port++;
        EPPS[2].quantum_port++ <--> QuantumChannel <--> repeater[1].quantum_port_receiver++;
        repeater[1].quantum_port_receiver++ <--> QuantumChannel <--> EPPS[3].quantum_port++;
        EPPS[3].quantum_port++ <--> QuantumChannel <--> router[0].quantum_port_receiver++;

        node[2].port++ <--> ClassicalChannel <--> EPPS[4].port++;
        EPPS[4].port++ <--> ClassicalChannel <--> repeater[2].port++;
        repeater[2].port++ <--> ClassicalChannel <--> EPPS[5].port++;
        EPPS[5].port++ <--> ClassicalChannel <--> router[0].port++;

        node[2].quantum_port_receiver++ <--> QuantumChannel <--> EPPS[4].quantum_port++;
        EPPS[4].quantum_port++ <--> QuantumChannel <--> repeater[2].quantum_port_receiver++;
        repeater[2].quantum_port_receiver++ <--> QuantumChannel <--> EPPS[5].quantum_port++;
        EPPS[5].quantum_port++ <--> QuantumChannel <--> router[0].quantum_port_receiver++;
}



network Star_MM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;

    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        node[3]: QNode {
            address = index;
            node_type = "EndNode";
            @display("i=device/pc");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        router[1]: QNode {
            address = index+1000000;
            @display("i=device/router");
        }



    connections:
        node[0].port++ <--> ClassicalChannel <--> router[0].port++;
        node[1].port++ <--> ClassicalChannel <--> router[0].port++;
        node[2].port++ <--> ClassicalChannel <--> router[0].port++;

        node[0].quantum_port_receiver++ <--> QuantumChannel <--> router[0].quantum_port++;
        node[1].quantum_port_receiver++ <--> QuantumChannel <--> router[0].quantum_port++;
        node[2].quantum_port_receiver++ <--> QuantumChannel <--> router[0].quantum_port++;
}






