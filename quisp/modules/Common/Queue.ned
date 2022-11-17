package modules.Common;
@namespace(quisp::modules);

import ned.DatarateChannel;
import ned.IdealChannel;

simple Queue
{
    parameters:
        //int xPosition_Graphics;
        int address;
        //int buffer;//for qnic
        int frame_capacity = default(0); // max number of packets; 0 means no limit
        bool useCutThroughSwitching = default(false);  // use cut-through switching instead of store-and-forward
	    @display("i=block/queue");
        @signal[qlen](type=long);
        @signal[busy](type=bool);
        @signal[queueingTime](type=simtime_t);
        @signal[drop](type=long);
        @signal[txBytes](type=long);
        @signal[rxBytes](type=long);
        // @statistic[qlen](title="queue length"; record=vector?,timeavg,max; interpolationmode=sample-hold);
        // @statistic[busy](title="server busy state"; record=vector?,timeavg; interpolationmode=sample-hold);
        // @statistic[queueingTime](title="queueing time at dequeue"; unit=s; interpolationmode=none);
        // @statistic[drop](title="dropped packet byte length"; unit=bytes; record=vector?,count,sum; interpolationmode=none);
        // @statistic[txBytes](title="transmitting packet byte length"; unit=bytes; record=vector?,count,sum,histogram; interpolationmode=none);
        // @statistic[rxBytes](title="received packet byte length"; unit=bytes; record=vector?,count,sum,histogram; interpolationmode=none);
    gates:
        input in;
        output out;
        inout line;
}
