package modules.Application;
@namespace(quisp::modules);

import ned.DatarateChannel;
import ned.IdealChannel;

simple Application
{
    parameters:
        @display("i=block/app");
        volatile double request_generation_interval @unit(s) = default(exponential(5s)); // time between generating packets
        volatile int number_of_bellpair;

    gates:
        input fromRouter @loose;
        output toRouter @loose;
}
