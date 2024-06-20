package modules;
@namespace(quisp::modules);

import modules.Satellite.*;
import modules.Common.GatedQueue;

module SatelliteQNode extends QNode
{
    parameters:
        bool is_satellite = default(false);

    gates:

    submodules:
        ps[sizeof(port)]: PointingSystem;
        Gqueue[sizeof(port)]: GatedQueue {
            parameters:
                address = index;
                @display("p=338,234");
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
