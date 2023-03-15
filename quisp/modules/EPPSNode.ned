package modules;
@namespace(quisp::modules);

import ned.DatarateChannel;
import ned.DelayChannel;
import ned.IdealChannel;
import modules.PhysicalConnection.EPPS.*;
import modules.Common.Router;
import modules.Common.Queue;

module EPPSNode
{
    parameters:
        @display("i=EPPS");
        int address = default(0);
        string included_in_topology = default("yes");
        string node_type = default("EPPS");

    gates:
        inout quantum_port[];
        inout port[] @loose;

    submodules:
        epps: EntangledPhotonPairSource {
            parameters:
                @display("p=207.855,120.689995");
        }
        epps_controller: EPPSController {
            parameters:
                @display("p=103.55499,121.435");
        }
        router: Router {
            parameters:
                @display("p=157,40");
            gates:
                fromQueue[sizeof(parent.port)];
                toQueue[sizeof(parent.port)];
        }
        nic[sizeof(port)]: Queue {
            parameters:
                address = 0;
                @display("p=281.61,55.874996");
        }

    connections:
        for i=0..sizeof(port)-1 {
            router.toQueue[i] --> nic[i].in;//Each routing port is connected to its own queue
            router.fromQueue[i] <-- nic[i].out;
            nic[i].line <--> port[i];
        }

         for i=0..sizeof(quantum_port)-1 {
            quantum_port[i] <--> epps.quantum_port++;
        }

        epps_controller.to_router --> router.fromApp;
        router.toApp --> epps_controller.from_router;
}
