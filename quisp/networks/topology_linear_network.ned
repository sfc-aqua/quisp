package networks;

import ned.DatarateChannel;
import ned.IdealChannel;

import modules.*;
import modules.Backend.Backend;
import modules.Logger.Logger;
import modules.SharedResource.SharedResource;
import channels.*;


network Tomography_Linear_One_MM_MIM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;

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

network Linear_One_MIM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        //**.BSA_handshake = false;

    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        source: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP");
        }
        BSA: BSANode {
            address = 2;
            @display("i=BSA");
        }
        target: QNode {
            address = 3;
            node_type = "EndNode";
            @display("i=COMP");
        }
    connections:
        source.port++ <--> ClassicalChannel {  distance = 1km; } <--> BSA.port++;
        BSA.port++ <--> ClassicalChannel {  distance = 1km; } <--> target.port++;
        source.quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> BSA.quantum_port++;
        BSA.quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> target.quantum_port++;

}


network Linear_One_MIM_biasedDistance
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        //**.BSA_handshake = false;

    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        source: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP");
            //buffers = 15;
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        BSA: BSANode {
            address = 2;
            @display("i=BSA");
        }
        target: QNode {
            address = 3;
            node_type = "EndNode";
            //buffers = 20;
            @display("i=COMP");
        }
    connections:
        source.port++ <--> ClassicalChannel {  distance = 7km; } <--> BSA.port++;
        BSA.port++ <--> ClassicalChannel {  distance = 10km; } <--> target.port++;
        source.quantum_port++ <--> QuantumChannel {  distance = 7km; } <--> BSA.quantum_port++;
        BSA.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> target.quantum_port++;

}



network Linear_One_MM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;

    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        EndNode[2]: QNode {
            address = index;
            node_type = "EndNode";
            @display("i=COMP");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }

    connections:
        EndNode[0].port++ <--> ClassicalChannel {  distance = 1km; } <--> EndNode[1].port++;
        EndNode[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 1km; } <--> EndNode[1].quantum_port++;
}

network Linear_One_MM_bufferGap
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;

    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        Small: QNode {
            address = 112302;
            node_type = "EndNode";
            buffers = 1;
            @display("i=COMP");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }

        Big: QNode {
            address = 300;
            buffers = 1;
            node_type = "EndNode";
            @display("i=COMP");
        }
    connections:
        Small.port++ <--> ClassicalChannel {  distance = 12.3km; } <--> Big.port++;
        Small.quantum_port_receiver++ <--> QuantumChannel {  distance = 12.3km; } <--> Big.quantum_port++;
}


network Linear_One_MSM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=281,95");
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        source: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=240,48");

            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        epps: EPPSNode {//needs to check the buffersize, and tell each node how many photon arrivals to expect.
            address = 2;
            @display("i=EPPS;p=132,48");
        }
        target: QNode {
            address = 3;
            node_type = "EndNode";
            @display("i=COMP");
        }
    connections:
        source.port++ <--> ClassicalChannel {  distance = 40km; } <--> epps.port++;
        epps.port++ <--> ClassicalChannel {  distance = 20km; } <--> target.port++;
        source.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 40km; } <--> epps.quantum_port++;
        epps.quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> target.quantum_port_receiver_passive++;
}













































network Linear_One_MIM_MM_MSM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;//per second

        @display("bgb=526,236");

    submodules:
        source: QNode {
            address = 10000000;
            node_type = "EndNode";
            @display("i=COMP;p=502,132");
            //buffers = 15;
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        BSA: BSANode {
            address = 2;
            @display("i=BSA;p=304,132");
        }
        repeater: QNode {
            address = 1234;
            node_type = "Repeater";
        		//buffers = 25;

            @display("i=REP1G;p=408,131");
        }
        router: QNode {
            address = 3;
            node_type = "Router";
            //buffers = 30;
            @display("i=RTR;p=207,131");
        }
        mm[2]: QNode {
            address = index + 100;
            //buffers = 20;
            node_type = "EndNode";
            @display("i=COMP;p=207,31");
        }
        epps: EPPSNode {
            address = 5;
            @display("i=EPPS;p=110,132");
        }

        pas: QNode {
            address = 6;
            //buffers = 5;
            node_type = "EndNode";
            @display("i=COMP;p=21,132");
        }
    connections:
        source.port++ <--> ClassicalChannel <--> repeater.port++;
        repeater.port++ <--> ClassicalChannel <--> BSA.port++;
        BSA.port++ <--> ClassicalChannel {  distance = 90km; } <--> router.port++;
        mm[0].port++ <--> ClassicalChannel {  distance = 40km; } <--> router.port++;
        mm[1].port++ <--> ClassicalChannel {  distance = 40km; } <--> router.port++;
        epps.port++ <--> ClassicalChannel <--> router.port++;
        epps.port++ <--> ClassicalChannel <--> pas.port++;
        source.quantum_port++ <--> QuantumChannel <--> repeater.quantum_port_receiver++;
        repeater.quantum_port++ <--> QuantumChannel <--> BSA.quantum_port++;
        BSA.quantum_port++ <--> QuantumChannel {  distance = 90km; } <--> router.quantum_port++;
        mm[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 40km; } <--> router.quantum_port++;
        mm[1].quantum_port++ <--> QuantumChannel {  distance = 40km; } <--> router.quantum_port_receiver++;
        router.quantum_port_receiver_passive++ <--> QuantumChannel <--> epps.quantum_port++;
        epps.quantum_port++ <--> QuantumChannel <--> pas.quantum_port_receiver_passive++;
}


