package networks;

 

import ned.DatarateChannel;
import ned.IdealChannel;



network RGS_linear
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

    submodules:
        MeasNode[2]: QNode {
            address = index;
            nodeType = "MeasNode";
            @display("i=device/pc;");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }

        RGSsource[2]: QNode {
            address = index+100;
            nodeType = "RGSsource";
            //buffers = 25;
            @display("i=device/smallrouter");
        }

        ABSA: ABSA {
            address = 2;
            @display("i=device/bsm");
        }

    connections:
        MeasNode[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> RGSsource[0].port++;
        RGSsource[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> ABSA.port++;
        ABSA.port++ <--> ClassicalChannel {  distance = 10km; } <--> RGSsource[1].port++;
        RGSsource[1].port++ <--> ClassicalChannel {  distance = 10km; } <--> MeasNode[1].port++;

        MeasNode[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 10km; } <--> RGSsource[0].quantum_port++;
        RGSsource[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> ABSA.quantum_port++;
        ABSA.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> RGSsource[1].quantum_port++;
        RGSsource[1].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> MeasNode[1].quantum_port_receiver++;
}