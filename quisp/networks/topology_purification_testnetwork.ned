package networks;

import ned.DatarateChannel;
import ned.IdealChannel;

import channels.*;
import modules.*;

network Linear_five_MM_network
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=707,326");
    submodules:
        EndNode1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=device/pc;p=72,170");
        }
        Repeater2[1]: QNode {
            address = 2;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=204,169");
        }
        Repeater3[1]: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=324,169");
        }
        Repeater4[1]: QNode {
            address = 4;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=464,169");
        }
        EndNode5[1]: QNode {
            address = 5;
            nodeType = "EndNode";
            @display("i=device/pc;p=609,170");
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
