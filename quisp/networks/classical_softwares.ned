package networks;
//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003 Ahmet Sekercioglu
// Copyright (C) 2003-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

import ned.DatarateChannel;
import ned.IdealChannel;
//import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;


simple Application
{
    parameters:
        //@class(quisp::modules::Application);
        int address;
        volatile double sendIaTime @unit(s) = default(exponential(1s)); // time between generating packets
        string Other_endnodes_table = "";
        bool EndToEndConnection = default(false);
	// removing default here forces app to ask
	// int TrafficPattern = default(1);
	int TrafficPattern;
	int LoneInitiatorAddress;
        int NumberOfResources = default(1);

        int num_measure = default(7000); // temporary
    gates:
        input fromRouter @loose;
        output toRouter @loose;
}

simple Router
{
    parameters:
        //@class(quisp::modules::Router);
        int address;
        string classical_router_soft = "yes";
    gates:
        input fromQueue[];
        output toQueue[];
        input fromApp @loose;
        output toApp @loose;
		input fromQNIC[] @loose;
        inout rdPort @loose;
        inout cmPort @loose;
        inout rePort @loose;
        inout hmPort @loose;

        input fromRuleSet @directIn;//A little bit cheating but why not.
}

simple Queue
{
    parameters:
        //@class(quisp::modules::Queue);
        //int xPosition_Graphics;
        int address;
        //int buffer;//for qnic
        int frameCapacity = default(0); // max number of packets; 0 means no limit
        bool useCutThroughSwitching = default(false);  // use cut-through switching instead of store-and-forward
	    //@display("i=block/queue;q=queue");
        @signal[qlen](type="long");
        @signal[busy](type="bool");
        @signal[queueingTime](type="simtime_t");
        @signal[drop](type="long");
        @signal[txBytes](type="long");
        @signal[rxBytes](type="long");
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
