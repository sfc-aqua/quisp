package modules;
@namespace(quisp::modules);

import ned.DatarateChannel;
import ned.DelayChannel;
import ned.IdealChannel;
import modules.PhysicalConnection.EPPS.*;
import modules.Common.Router;
import modules.Common.GatedQueue;
import modules.Satellite.PointingSystem;

module EPPSNode_Sat extends EPPSNode
{
    parameters:
        @display("i=EPPS");
        bool is_satellite = default(true);


    gates:

    submodules:
        ps[sizeof(port)]: PointingSystem {
        }
        Gqueue[sizeof(port)]: GatedQueue {
            parameters:
                address = index;
                //buffer = 8;
                //@display("p=198,43");
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
