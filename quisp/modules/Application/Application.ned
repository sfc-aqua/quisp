package modules.Application;
@namespace(quisp::modules);

import ned.DatarateChannel;
import ned.IdealChannel;

simple Application
{
    parameters:
        @display("i=block/app");
        int address;
        volatile double sendIaTime @unit(s) = default(exponential(5s)); // time between generating packets
        volatile int numberOfBellpair;

    gates:
        input fromRouter @loose;
        output toRouter @loose;
}
