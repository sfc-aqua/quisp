package modules;
@namespace(quisp::modules);

import ned.DatarateChannel;
import ned.DelayChannel;
import ned.IdealChannel;

import modules.PhysicalConnection.BSA.*;
import modules.QNIC.PhotonicSwitch.*;
import modules.Common.Router;
import modules.Common.Queue;

module BSANode
{
    parameters:
        @display("i=BSA");
        int address = default(0);
        string included_in_topology = default("yes");
        string node_type = default("BSA");

    gates:
        inout quantum_port[];
        inout port[] @loose;

    submodules:
        bsa: BellStateAnalyzer {
            parameters:
                @display("p=207.855,120.689995");
        }
        router: Router {
            parameters:
                address = parent.address;
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
        bsa_controller: BSAController {
            parameters:
                @display("p=103.55499,121.435");
        }

    connections:
        for i=0..sizeof(port)-1 {
            router.toQueue[i] --> nic[i].in; // Each routing port is connected to its own queue
            router.fromQueue[i] <-- nic[i].out;
            nic[i].line <--> port[i];
        }

        for i=0..sizeof(quantum_port)-1 {
            quantum_port[i] <--> bsa.quantum_port++;
        }

        bsa_controller.to_router --> router.fromApp;
        router.toApp --> bsa_controller.from_router;
        bsa.to_bsa_controller --> bsa_controller.from_bsa;
}
