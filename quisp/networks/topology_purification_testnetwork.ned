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
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=707,326");
    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=COMP;p=72,170");
        }
        Repeater2: QNode {
            address = 2;
            nodeType = "Repeater";
            @display("i=REP1G;p=204,200");
        }
        Repeater3: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=REP1G;p=324,230");
        }
        Repeater4: QNode {
            address = 4;
            nodeType = "Repeater";
            @display("i=REP1G;p=464,200");
        }
        EndNode5: QNode {
            address = 5;
            nodeType = "EndNode";
            @display("i=COMP;p=609,170");
        }




    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 7km; } <--> Repeater2.port++;
        Repeater2.port++ <--> ClassicalChannel {  distance = 7km; } <--> Repeater3.port++;
        Repeater3.port++ <--> ClassicalChannel {  distance = 7km; } <--> Repeater4.port++;
        Repeater4.port++ <--> ClassicalChannel {  distance = 7km; } <--> EndNode5.port++;


        EndNode1.quantum_port_receiver++ <--> ClassicalChannel {  distance = 7km; } <--> Repeater2.quantum_port++;
        Repeater2.quantum_port_receiver++ <--> ClassicalChannel {  distance = 7km; } <--> Repeater3.quantum_port++;
        Repeater3.quantum_port_receiver++ <--> ClassicalChannel {  distance = 7km; } <--> Repeater4.quantum_port++;
        Repeater4.quantum_port_receiver++ <--> ClassicalChannel {  distance = 7km; } <--> EndNode5.quantum_port++;
}
