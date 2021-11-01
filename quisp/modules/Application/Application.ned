package modules.Application;
@namespace(quisp::modules);

import ned.DatarateChannel;
import ned.IdealChannel;

simple Application
{
    parameters:
        int address;
        volatile double sendIaTime @unit(s) = default(exponential(1s)); // time between generating packets
        string Other_endnodes_table = "";
        bool EndToEndConnection = default(false);
        // removing default here forces app to ask
        // int TrafficPattern = default(1);
        int TrafficPattern;
        int LoneInitiatorAddress;
        int distant_measure_count = default(7000);
        // Maybe don't have to set the default here.

    gates:
        input fromRouter @loose;
        output toRouter @loose;
}
