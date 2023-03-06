package networks;

import ned.DatarateChannel;
import ned.IdealChannel;

import modules.*;
import modules.Backend.Backend;
import modules.Logger.Logger;
import channels.*;

network TwoNetworks_MIM
{
    parameters:
        **.speed_of_light_in_fiber = 208189.206944 km;

    submodules:
        backend: Backend;
        logger: Logger;
        EndNode11: QNode {
            address = "1.1";
            available_addresses = ["3.1"];
            node_type = "EndNode";
            @display("i=COMP;p=29,273,m,5,60,60");
        }
        Repeater32: QNode {
            address = "3.2";
            node_type = "Repeater";
            @display("i=COMP;p=110,273,m,5,60,60");
        }
        Repeater33: QNode {
            address = "3.3";
            node_type = "EndNode";
            @display("i=COMP;p=198,273,m,5,60,60");
        }
        Router199: QNode {
            address = "1.99";
            available_addresses = ["3.99"];
            node_type = "Router";
            @display("i=COMP;p=274,273,m,5,60,60");

        }
        Router299: QNode {
            address = "2.99";
            available_addresses = ["4.99"];
            node_type = "Router";
            @display("i=COMP;p=438,273,m,5,60,60");
        }
        Repeater42: QNode {
            address = "4.2";
            node_type = "Router";
            @display("i=COMP;p=545,273,m,5,60,60");
        }
        EndNode21: QNode {
            address = "2.1";
            available_addresses = ["4.1"];
            node_type = "EndNode";
            @display("i=COMP;p=630,273,m,5,60,60");
        }
        BSA1132: BSANode {
            address = "3.10";
            @display("p=67,222,m,5,60,60");
        }
        BSA3233: BSANode {
            address = "3.11";
            @display("p=157,222,m,5,60,60");
        }
        BSA33199: BSANode {
            address = "3.12";
            @display("p=234,222,m,5,60,60");
        }
        BSA199299: BSANode {
            address = "1.10";
            @display("p=352,222,m,5,60,60");
        }
        BSA29942: BSANode {
            address = "4.10";
            @display("p=485,222,m,5,60,60");
        }
        BSA4221: BSANode {
            address = "4.11";
            @display("p=581,222,m,5,60,60");
        }

    connections:
        EndNode11.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA1132.port++;
        BSA1132.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> Repeater32.port++;
        EndNode11.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA1132.quantum_port++;
        BSA1132.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> Repeater32.quantum_port++;

        Repeater32.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA3233.port++;
        BSA3233.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> Repeater33.port++;
        Repeater32.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA3233.quantum_port++;
        BSA3233.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> Repeater33.quantum_port++;

        Repeater33.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA33199.port++;
        BSA33199.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> Router199.port++;
        Repeater33.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA33199.quantum_port++;
        BSA33199.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> Router199.quantum_port++;

        Router199.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA199299.port++;
        BSA199299.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> Router299.port++;
        Router199.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA199299.quantum_port++;
        BSA199299.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> Router299.quantum_port++;

        Router299.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA29942.port++;
        BSA29942.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> Repeater42.port++;
        Router299.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA29942.quantum_port++;
        BSA29942.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> Repeater42.quantum_port++;

        Repeater42.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA4221.port++;
        BSA4221.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> EndNode21.port++;
        Repeater42.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA4221.quantum_port++;
        BSA4221.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> EndNode21.quantum_port++;

}
