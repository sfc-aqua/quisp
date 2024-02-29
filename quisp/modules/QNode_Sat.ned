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
        ps[sizeof(port)]: PointingSystem {
            @display("p=530,273");
        }
        Gqueue[sizeof(port)]: GatedQueue {
            parameters:
                address = index;
                //buffer = 8;
                //@display("p=198,43");
                @display("p=341,185");
        }
    connections:
        for i=0..sizeof(port)-1 {
            router.toQueue[i] --> { @reconnect; } --> Gqueue[i].in; // Each routing port is connected to its own queue
            router.fromQueue[i] <-- { @reconnect; } <-- Gqueue[i].out;
            Gqueue[i].line <--> { @reconnect; } <--> port[i];
            Gqueue[i].to_ps --> ps[i].req;
            Gqueue[i].from_ps <-- ps[i].ans;
        }

}
