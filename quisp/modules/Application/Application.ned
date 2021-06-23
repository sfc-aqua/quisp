package modules.Application;

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
        int NumberOfResources = default(1);
        int ConnectionGen = default(1);

        int num_measure = default(7000); // temporary
    gates:
        input fromRouter @loose;
        output toRouter @loose;
}
