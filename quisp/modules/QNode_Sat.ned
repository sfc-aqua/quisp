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
        vc: VisibilityChecker;
        lt[sizeof(port)]: Latch {
        parameters:
            address = index;
        }
        fo: Fanout;
    connections:
        vc.ctrl --> fo.in;
        for idx=0..sizeof(port)-1 {
            queue[idx].line$o --> { @reconnect; } --> lt[idx].in;
            port$o[idx] <-- {@reconnect;} <-- lt[idx].out;
            port$i[idx] --> { @reconnect; } --> queue[idx].line$i;
            lt[idx].ctrl <-- fo.out++;
        }

}
