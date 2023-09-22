package modules;
@namespace(quisp::modules);

import modules.Application.Application;
import modules.QRSA.quantumRoutingSoft;
import modules.Common.*;
import modules.Satellite.*;

module QNode_Sat extends QNode
{
    parameters:
        bool is_satellite = default(true);

    gates:

    submodules:
        vc: VisibilityChecker {
            @display("p=343,202");
        }
        fo: Fanout {
            @display("p=343,303");
        }
        Gqueue[sizeof(port)]: GatedQueue {
            parameters:
                address = index;
                //buffer = 8;
                //@display("p=198,43");
                @display("p=278,203");
        }
    connections:
        vc.ctrl --> fo.in;
        for i=0..sizeof(port)-1 {
            router.toQueue[i] --> { @reconnect; } --> Gqueue[i].in; // Each routing port is connected to its own queue
            router.fromQueue[i] <-- { @reconnect; } <-- Gqueue[i].out;
            Gqueue[i].line <--> { @reconnect; } <--> port[i];
            Gqueue[i].ctrl_in <-- fo.out++;
        }

}
