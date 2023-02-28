package networks;

import ned.DatarateChannel;
import ned.IdealChannel;

import channels.*;
import modules.*;
import modules.Backend.Backend;
import modules.Logger.Logger;


network Linear_five_MM_network
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=707,326");
    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1[1]: QNode {
            address = "0.1";
            node_type = "EndNode";
            @display("i=COMP;p=72,170");
        }
        Repeater2[1]: QNode {
            address = "0.2";
            node_type = "Repeater";
            @display("i=REP1G;p=204,169");
        }
        Repeater3[1]: QNode {
            address = "0.3";
            node_type = "Repeater";
            @display("i=REP1G;p=324,169");
        }
        Repeater4[1]: QNode {
            address = "0.4";
            node_type = "Repeater";
            @display("i=REP1G;p=464,169");
        }
        EndNode5[1]: QNode {
            address = "0.5";
            node_type = "EndNode";
            @display("i=COMP;p=609,170");
        }




    connections:
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 7km; } <--> Repeater2[0].port++;
        Repeater2[0].port++ <--> ClassicalChannel {  distance = 7km; } <--> Repeater3[0].port++;
        Repeater3[0].port++ <--> ClassicalChannel {  distance = 7km; } <--> Repeater4[0].port++;
        Repeater4[0].port++ <--> ClassicalChannel {  distance = 7km; } <--> EndNode5[0].port++;


        EndNode1[0].quantum_port_receiver++ <--> ClassicalChannel {  distance = 7km; } <--> Repeater2[0].quantum_port++;
        Repeater2[0].quantum_port_receiver++ <--> ClassicalChannel {  distance = 7km; } <--> Repeater3[0].quantum_port++;
        Repeater3[0].quantum_port_receiver++ <--> ClassicalChannel {  distance = 7km; } <--> Repeater4[0].quantum_port++;
        Repeater4[0].quantum_port_receiver++ <--> ClassicalChannel {  distance = 7km; } <--> EndNode5[0].quantum_port++;
}
