package networks;

import ned.DatarateChannel;
import ned.IdealChannel;

import modules.*;
import modules.Backend.Backend;
import modules.Logger.Logger;
import channels.*;

network four_node_MM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        @display("bgb=541,254");
    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=56,202");
        }
        EndNode2: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP;p=473,202");
        }
        Repeater[2]: QNode {
            address = 3 + index;
            node_type = "Repeater";
            @display("i=REP1G;p=264,203");
        }
    connections:
        EndNode1.port++                     <--> ClassicalChannel {  distance = 1km; } <--> Repeater[0].port++;
        Repeater[sizeof(Repeater)-1].port++ <--> ClassicalChannel {  distance = 1km; } <--> EndNode2.port++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].port++              <--> ClassicalChannel {  distance = 1km; } <--> Repeater[i+1].port++;
        }

        EndNode1.quantum_port++                     <--> QuantumChannel {  distance = 1km; } <--> Repeater[0].quantum_port_receiver++;
        Repeater[sizeof(Repeater)-1].quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> EndNode2.quantum_port_receiver++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].quantum_port++              <--> QuantumChannel {  distance = 1km; } <--> Repeater[i+1].quantum_port_receiver++;
        }
}

network five_node_MM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        @display("bgb=541,254");
    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=56,202");
        }
        EndNode2: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP;p=473,202");
        }
        Repeater[3]: QNode {
            address = 3 + index;
            node_type = "Repeater";
            @display("i=REP1G;p=264,203");
        }
    connections:
        EndNode1.port++                     <--> ClassicalChannel {  distance = 1km; } <--> Repeater[0].port++;
        Repeater[sizeof(Repeater)-1].port++ <--> ClassicalChannel {  distance = 1km; } <--> EndNode2.port++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].port++              <--> ClassicalChannel {  distance = 1km; } <--> Repeater[i+1].port++;
        }

        EndNode1.quantum_port++                     <--> QuantumChannel {  distance = 1km; } <--> Repeater[0].quantum_port_receiver++;
        Repeater[sizeof(Repeater)-1].quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> EndNode2.quantum_port_receiver++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].quantum_port++              <--> QuantumChannel {  distance = 1km; } <--> Repeater[i+1].quantum_port_receiver++;
        }
}

network six_node_MM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        @display("bgb=541,254");
    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=56,202");
        }
        EndNode2: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP;p=473,202");
        }
        Repeater[4]: QNode {
            address = 3 + index;
            node_type = "Repeater";
            @display("i=REP1G;p=264,203");
        }
    connections:
        EndNode1.port++                     <--> ClassicalChannel {  distance = 1km; } <--> Repeater[0].port++;
        Repeater[sizeof(Repeater)-1].port++ <--> ClassicalChannel {  distance = 1km; } <--> EndNode2.port++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].port++              <--> ClassicalChannel {  distance = 1km; } <--> Repeater[i+1].port++;
        }

        EndNode1.quantum_port++                     <--> QuantumChannel {  distance = 1km; } <--> Repeater[0].quantum_port_receiver++;
        Repeater[sizeof(Repeater)-1].quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> EndNode2.quantum_port_receiver++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].quantum_port++              <--> QuantumChannel {  distance = 1km; } <--> Repeater[i+1].quantum_port_receiver++;
        }
}

network seven_node_MM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        @display("bgb=541,254");
    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=56,202");
        }
        EndNode2: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP;p=473,202");
        }
        Repeater[5]: QNode {
            address = 3 + index;
            node_type = "Repeater";
            @display("i=REP1G;p=264,203");
        }
    connections:
        EndNode1.port++                     <--> ClassicalChannel {  distance = 1km; } <--> Repeater[0].port++;
        Repeater[sizeof(Repeater)-1].port++ <--> ClassicalChannel {  distance = 1km; } <--> EndNode2.port++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].port++              <--> ClassicalChannel {  distance = 1km; } <--> Repeater[i+1].port++;
        }

        EndNode1.quantum_port++                     <--> QuantumChannel {  distance = 1km; } <--> Repeater[0].quantum_port_receiver++;
        Repeater[sizeof(Repeater)-1].quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> EndNode2.quantum_port_receiver++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].quantum_port++              <--> QuantumChannel {  distance = 1km; } <--> Repeater[i+1].quantum_port_receiver++;
        }
}

network eight_node_MM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        @display("bgb=541,254");
    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=56,202");
        }
        EndNode2: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP;p=473,202");
        }
        Repeater[6]: QNode {
            address = 3 + index;
            node_type = "Repeater";
            @display("i=REP1G;p=264,203");
        }
    connections:
        EndNode1.port++                     <--> ClassicalChannel {  distance = 1km; } <--> Repeater[0].port++;
        Repeater[sizeof(Repeater)-1].port++ <--> ClassicalChannel {  distance = 1km; } <--> EndNode2.port++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].port++              <--> ClassicalChannel {  distance = 1km; } <--> Repeater[i+1].port++;
        }

        EndNode1.quantum_port++                     <--> QuantumChannel {  distance = 1km; } <--> Repeater[0].quantum_port_receiver++;
        Repeater[sizeof(Repeater)-1].quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> EndNode2.quantum_port_receiver++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].quantum_port++              <--> QuantumChannel {  distance = 1km; } <--> Repeater[i+1].quantum_port_receiver++;
        }
}

network nine_node_MM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        @display("bgb=541,254");
    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=56,202");
        }
        EndNode2: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP;p=473,202");
        }
        Repeater[7]: QNode {
            address = 3 + index;
            node_type = "Repeater";
            @display("i=REP1G;p=264,203");
        }
    connections:
        EndNode1.port++                     <--> ClassicalChannel {  distance = 1km; } <--> Repeater[0].port++;
        Repeater[sizeof(Repeater)-1].port++ <--> ClassicalChannel {  distance = 1km; } <--> EndNode2.port++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].port++              <--> ClassicalChannel {  distance = 1km; } <--> Repeater[i+1].port++;
        }

        EndNode1.quantum_port++                     <--> QuantumChannel {  distance = 1km; } <--> Repeater[0].quantum_port_receiver++;
        Repeater[sizeof(Repeater)-1].quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> EndNode2.quantum_port_receiver++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].quantum_port++              <--> QuantumChannel {  distance = 1km; } <--> Repeater[i+1].quantum_port_receiver++;
        }
}

network ten_node_MM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        @display("bgb=541,254");
    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=56,202");
        }
        EndNode2: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP;p=473,202");
        }
        Repeater[8]: QNode {
            address = 3 + index;
            node_type = "Repeater";
            @display("i=REP1G;p=264,203");
        }
    connections:
        EndNode1.port++                     <--> ClassicalChannel {  distance = 1km; } <--> Repeater[0].port++;
        Repeater[sizeof(Repeater)-1].port++ <--> ClassicalChannel {  distance = 1km; } <--> EndNode2.port++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].port++              <--> ClassicalChannel {  distance = 1km; } <--> Repeater[i+1].port++;
        }

        EndNode1.quantum_port++                     <--> QuantumChannel {  distance = 1km; } <--> Repeater[0].quantum_port_receiver++;
        Repeater[sizeof(Repeater)-1].quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> EndNode2.quantum_port_receiver++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].quantum_port++              <--> QuantumChannel {  distance = 1km; } <--> Repeater[i+1].quantum_port_receiver++;
        }
}
