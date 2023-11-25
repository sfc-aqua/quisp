package modules;
@namespace(quisp::modules);

import ned.DatarateChannel;
import ned.DelayChannel;
import ned.IdealChannel;

import modules.Common.*;
import modules.Satellite.PointingSystem;

module SPDC_Sat extends SPDC
{
    parameters:
    bool is_satellite = default(false);
    submodules:
        ps[sizeof(port)]: PointingSystem {
            @display("p=530,273");
        }
        Gqueue[sizeof(port)]: GatedQueue {
            parameters:
                address = index;
                @display("p=281.61,55.874996");
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






