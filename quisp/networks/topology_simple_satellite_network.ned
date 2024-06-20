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