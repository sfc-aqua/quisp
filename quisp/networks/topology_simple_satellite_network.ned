package networks;

import ned.DatarateChannel;
import ned.IdealChannel;

import modules.*;
import modules.Backend.Backend;
import modules.Logger.Logger;
import modules.SharedResource.SharedResource;
import channels.*;



network Simple_Satellite_MM
{
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        EndNode1: SatelliteQNode {
            address = 1;
            is_satellite=true;
            node_type = "EndNode";
            @display("i=COMP;p=104,48,m,5,60,60");
        }
        EndNode2: SatelliteQNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP;p=253,248,m,5,60,60");
        }

    connections:
        EndNode1.port++ <--> FreeSpaceChannel {  distance = 1000km; } <--> EndNode2.port++;
        EndNode1.quantum_port++ <--> FreeSpaceQuantumChannel {  distance = 1000km; } <--> EndNode2.quantum_port_receiver++;
}

network three_node_Satellite_MM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        **.speed_of_light_in_FS = 299792.458 km;
        @display("bgb=541,254");
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource {
            @display("p=266,203");
        }
        EndNode1: SatelliteQNode {
            address = 10;
            node_type = "EndNode";
            @display("i=COMP;p=56,202");
        }
        EndNode2: SatelliteQNode {
            address = 5;
            node_type = "EndNode";
            @display("i=COMP;p=473,202");
        }
        Repeater: SatelliteQNode {
            address = 3;
            node_type = "Repeater";
            is_satellite = true;
            @display("i=REP1G;p=266,40");
        }
    connections:
        EndNode1.port++ <--> FreeSpaceChannel {  distance = 500km; } <--> Repeater.port++;
        Repeater.port++ <--> FreeSpaceChannel {  distance = 500km; } <--> EndNode2.port++;

        EndNode1.quantum_port_receiver++ <--> FreeSpaceQuantumChannel {  distance = 500km; } <--> Repeater.quantum_port++;
        Repeater.quantum_port++ <--> FreeSpaceQuantumChannel {  distance = 500km; } <--> EndNode2.quantum_port_receiver++;
}
