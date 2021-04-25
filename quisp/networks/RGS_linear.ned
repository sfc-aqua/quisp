package networks;

import ned.DatarateChannel;
import ned.IdealChannel;

import modules.PhysicalConnection.BSA.*;
import modules.*;
import channels.*;

network RGS_linear_simple
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=549,261");
    submodules:
        EndNode1: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=device/pc;p=502,47");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        EndNode2: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=device/pc;");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }

        RGSsource1: RGS_source {
            address = 3;
            nodeType = "RGS";
            //buffers = 25;
            @display("i=device/smallrouter;p=420,201");
        }

        RGSsource2: RGS_source {
            address = 4;
            nodeType = "RGS";
            //buffers = 25;
            @display("i=device/smallrouter;p=169,201");
        }

        ABSANode: ABSANode {
            address = 5;
            nodeType = "ABSA";
            @display("i=device/smallrouter;p=311,201");
        }

    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 1km; } <--> RGSsource1.port++;
        RGSsource1.port++ <--> ClassicalChannel {  distance = 1km; } <--> ABSANode.port++;
        ABSANode.port++ <--> ClassicalChannel {  distance = 1km; } <--> RGSsource2.port++;
        RGSsource2.port++ <--> ClassicalChannel {  distance = 1km; } <--> EndNode2.port++;

        EndNode1.quantum_port_receiver++ <--> QuantumChannel {  distance = 1km; } <--> RGSsource1.quantum_rgs_source_port++;
        RGSsource1.quantum_rgs_source_port++ <--> QuantumChannel {  distance = 1km; } <--> ABSANode.quantum_absa_port++;
        ABSANode.quantum_absa_port++ <--> QuantumChannel {  distance = 1km; } <--> RGSsource2.quantum_rgs_source_port++;
        RGSsource2.quantum_rgs_source_port++ <--> QuantumChannel {  distance = 1km; } <--> EndNode2.quantum_port_receiver++;
}
