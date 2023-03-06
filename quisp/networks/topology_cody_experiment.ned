
package networks;

import ned.DatarateChannel;
import ned.IdealChannel;

import modules.*;
import modules.Backend.Backend;
import modules.Logger.Logger;
import channels.*;

network Linear_Ten_MM_1km
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

network Linear_Ten_MM_5km
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
        EndNode1.port++                     <--> ClassicalChannel {  distance = 5km; } <--> Repeater[0].port++;
        Repeater[sizeof(Repeater)-1].port++ <--> ClassicalChannel {  distance = 5km; } <--> EndNode2.port++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].port++              <--> ClassicalChannel {  distance = 5km; } <--> Repeater[i+1].port++;
        }

        EndNode1.quantum_port++                     <--> QuantumChannel {  distance = 5km; } <--> Repeater[0].quantum_port_receiver++;
        Repeater[sizeof(Repeater)-1].quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> EndNode2.quantum_port_receiver++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].quantum_port++              <--> QuantumChannel {  distance = 5km; } <--> Repeater[i+1].quantum_port_receiver++;
        }
}

network Linear_Ten_MM_10km
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
        EndNode1.port++                     <--> ClassicalChannel {  distance = 10km; } <--> Repeater[0].port++;
        Repeater[sizeof(Repeater)-1].port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode2.port++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].port++              <--> ClassicalChannel {  distance = 10km; } <--> Repeater[i+1].port++;
        }

        EndNode1.quantum_port++                     <--> QuantumChannel {  distance = 10km; } <--> Repeater[0].quantum_port_receiver++;
        Repeater[sizeof(Repeater)-1].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode2.quantum_port_receiver++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].quantum_port++              <--> QuantumChannel {  distance = 10km; } <--> Repeater[i+1].quantum_port_receiver++;
        }
}

network Linear_Ten_MM_15km
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
        EndNode1.port++                     <--> ClassicalChannel {  distance = 15km; } <--> Repeater[0].port++;
        Repeater[sizeof(Repeater)-1].port++ <--> ClassicalChannel {  distance = 15km; } <--> EndNode2.port++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].port++              <--> ClassicalChannel {  distance = 15km; } <--> Repeater[i+1].port++;
        }

        EndNode1.quantum_port++                     <--> QuantumChannel {  distance = 15km; } <--> Repeater[0].quantum_port_receiver++;
        Repeater[sizeof(Repeater)-1].quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> EndNode2.quantum_port_receiver++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].quantum_port++              <--> QuantumChannel {  distance = 15km; } <--> Repeater[i+1].quantum_port_receiver++;
        }
}

network Linear_Ten_MM_20km
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
        EndNode1.port++                     <--> ClassicalChannel {  distance = 20km; } <--> Repeater[0].port++;
        Repeater[sizeof(Repeater)-1].port++ <--> ClassicalChannel {  distance = 20km; } <--> EndNode2.port++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].port++              <--> ClassicalChannel {  distance = 20km; } <--> Repeater[i+1].port++;
        }

        EndNode1.quantum_port++                     <--> QuantumChannel {  distance = 20km; } <--> Repeater[0].quantum_port_receiver++;
        Repeater[sizeof(Repeater)-1].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> EndNode2.quantum_port_receiver++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].quantum_port++              <--> QuantumChannel {  distance = 20km; } <--> Repeater[i+1].quantum_port_receiver++;
        }
}

network Linear_Ten_MM_25km
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
        EndNode1.port++                     <--> ClassicalChannel {  distance = 25km; } <--> Repeater[0].port++;
        Repeater[sizeof(Repeater)-1].port++ <--> ClassicalChannel {  distance = 25km; } <--> EndNode2.port++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].port++              <--> ClassicalChannel {  distance = 25km; } <--> Repeater[i+1].port++;
        }

        EndNode1.quantum_port++                     <--> QuantumChannel {  distance = 25km; } <--> Repeater[0].quantum_port_receiver++;
        Repeater[sizeof(Repeater)-1].quantum_port++ <--> QuantumChannel {  distance = 25km; } <--> EndNode2.quantum_port_receiver++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].quantum_port++              <--> QuantumChannel {  distance = 25km; } <--> Repeater[i+1].quantum_port_receiver++;
        }
}

network Linear_Ten_MM_30km
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
        EndNode1.port++                     <--> ClassicalChannel {  distance = 30km; } <--> Repeater[0].port++;
        Repeater[sizeof(Repeater)-1].port++ <--> ClassicalChannel {  distance = 30km; } <--> EndNode2.port++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].port++              <--> ClassicalChannel {  distance = 30km; } <--> Repeater[i+1].port++;
        }

        EndNode1.quantum_port++                     <--> QuantumChannel {  distance = 30km; } <--> Repeater[0].quantum_port_receiver++;
        Repeater[sizeof(Repeater)-1].quantum_port++ <--> QuantumChannel {  distance = 30km; } <--> EndNode2.quantum_port_receiver++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].quantum_port++              <--> QuantumChannel {  distance = 30km; } <--> Repeater[i+1].quantum_port_receiver++;
        }
}

network Linear_Ten_MM_35km
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
        EndNode1.port++                     <--> ClassicalChannel {  distance = 35km; } <--> Repeater[0].port++;
        Repeater[sizeof(Repeater)-1].port++ <--> ClassicalChannel {  distance = 35km; } <--> EndNode2.port++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].port++              <--> ClassicalChannel {  distance = 35km; } <--> Repeater[i+1].port++;
        }

        EndNode1.quantum_port++                     <--> QuantumChannel {  distance = 35km; } <--> Repeater[0].quantum_port_receiver++;
        Repeater[sizeof(Repeater)-1].quantum_port++ <--> QuantumChannel {  distance = 35km; } <--> EndNode2.quantum_port_receiver++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].quantum_port++              <--> QuantumChannel {  distance = 35km; } <--> Repeater[i+1].quantum_port_receiver++;
        }
}

network Linear_Ten_MM_1km
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
        EndNode1.port++                     <--> ClassicalChannel {  distance = 40km; } <--> Repeater[0].port++;
        Repeater[sizeof(Repeater)-1].port++ <--> ClassicalChannel {  distance = 40km; } <--> EndNode2.port++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].port++              <--> ClassicalChannel {  distance = 40km; } <--> Repeater[i+1].port++;
        }

        EndNode1.quantum_port++                     <--> QuantumChannel {  distance = 40km; } <--> Repeater[0].quantum_port_receiver++;
        Repeater[sizeof(Repeater)-1].quantum_port++ <--> QuantumChannel {  distance = 40km; } <--> EndNode2.quantum_port_receiver++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].quantum_port++              <--> QuantumChannel {  distance = 40km; } <--> Repeater[i+1].quantum_port_receiver++;
        }
}

network Linear_Ten_MM_45km
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
        EndNode1.port++                     <--> ClassicalChannel {  distance = 45km; } <--> Repeater[0].port++;
        Repeater[sizeof(Repeater)-1].port++ <--> ClassicalChannel {  distance = 45km; } <--> EndNode2.port++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].port++              <--> ClassicalChannel {  distance = 45km; } <--> Repeater[i+1].port++;
        }

        EndNode1.quantum_port++                     <--> QuantumChannel {  distance = 45km; } <--> Repeater[0].quantum_port_receiver++;
        Repeater[sizeof(Repeater)-1].quantum_port++ <--> QuantumChannel {  distance = 45km; } <--> EndNode2.quantum_port_receiver++;
        for i=0..sizeof(Repeater)-2 {
            Repeater[i].quantum_port++              <--> QuantumChannel {  distance = 45km; } <--> Repeater[i+1].quantum_port_receiver++;
        }
}

network Linear_Ten_MIM_1km
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;

    submodules:
        backend: Backend;
        logger: Logger;
        source: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP");
        }
        BSA1: BSANode {
            address = 11;
            @display("i=BSA");
        }
        BSA2: BSANode {
            address = 12;
            @display("i=BSA");
        }
        BSA3: BSANode {
            address = 13;
            @display("i=BSA");
        }
        BSA4: BSANode {
            address = 14;
            @display("i=BSA");
        }
        BSA5: BSANode {
            address = 15;
            @display("i=BSA");
        }
        BSA6: BSANode {
            address = 16;
            @display("i=BSA");
        }
        BSA7: BSANode {
            address = 17;
            @display("i=BSA");
        }
        BSA8: BSANode {
            address = 18;
            @display("i=BSA");
        }
        BSA9: BSANode {
            address = 19;
            @display("i=BSA");
        }
        BSA10: BSANode {
            address = 20;
            @display("i=BSA");
        }
        repeater1: QNode {
            address = 101;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater2: QNode {
            address = 102;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater3: QNode {
            address = 103;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater4: QNode {
            address = 104;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater5: QNode {
            address = 105;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater6: QNode {
            address = 106;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater7: QNode {
            address = 107;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater8: QNode {
            address = 108;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater9: QNode {
            address = 109;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        target: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP");
        }
    connections:
        source.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA1.port++;
        BSA1.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> repeater1.port++;
        repeater1.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA2.port++;
        BSA2.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> repeater2.port++;
        repeater2.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA3.port++;
        BSA3.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> repeater3.port++;
        repeater3.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA4.port++;
        BSA4.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> repeater4.port++;
        repeater4.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA5.port++;
        BSA5.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> repeater5.port++;
        repeater5.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA6.port++;
        BSA6.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> repeater6.port++;
        repeater6.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA7.port++;
        BSA7.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> repeater7.port++;
        repeater7.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA8.port++;
        BSA8.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> repeater8.port++;
        repeater8.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA9.port++;
        BSA9.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> repeater9.port++;
        repeater9.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA10.port++;
        BSA10.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> target.port++;

        source.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA1.quantum_port++;
        BSA1.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> repeater1.quantum_port++;
        repeater1.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA2.quantum_port++;
        BSA2.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> repeater2.quantum_port++;
        repeater2.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA3.quantum_port++;
        BSA3.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> repeater3.quantum_port++;
        repeater3.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA4.quantum_port++;
        BSA4.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> repeater4.quantum_port++;
        repeater4.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA5.quantum_port++;
        BSA5.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> repeater5.quantum_port++;
        repeater5.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA6.quantum_port++;
        BSA6.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> repeater6.quantum_port++;
        repeater6.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA7.quantum_port++;
        BSA7.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> repeater7.quantum_port++;
        repeater7.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA8.quantum_port++;
        BSA8.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> repeater8.quantum_port++;
        repeater8.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA9.quantum_port++;
        BSA9.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> repeater9.quantum_port++;
        repeater9.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA10.quantum_port++;
        BSA10.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> target.quantum_port++;

}

network Linear_Ten_MIM_5km
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;

    submodules:
        backend: Backend;
        logger: Logger;
        source: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP");
        }
        BSA1: BSANode {
            address = 11;
            @display("i=BSA");
        }
        BSA2: BSANode {
            address = 12;
            @display("i=BSA");
        }
        BSA3: BSANode {
            address = 13;
            @display("i=BSA");
        }
        BSA4: BSANode {
            address = 14;
            @display("i=BSA");
        }
        BSA5: BSANode {
            address = 15;
            @display("i=BSA");
        }
        BSA6: BSANode {
            address = 16;
            @display("i=BSA");
        }
        BSA7: BSANode {
            address = 17;
            @display("i=BSA");
        }
        BSA8: BSANode {
            address = 18;
            @display("i=BSA");
        }
        BSA9: BSANode {
            address = 19;
            @display("i=BSA");
        }
        BSA10: BSANode {
            address = 20;
            @display("i=BSA");
        }
        repeater1: QNode {
            address = 101;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater2: QNode {
            address = 102;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater3: QNode {
            address = 103;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater4: QNode {
            address = 104;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater5: QNode {
            address = 105;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater6: QNode {
            address = 106;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater7: QNode {
            address = 107;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater8: QNode {
            address = 108;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater9: QNode {
            address = 109;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        target: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP");
        }
    connections:
        source.port++ <--> ClassicalChannel {  distance = 2.5km; } <--> BSA1.port++;
        BSA1.port++ <--> ClassicalChannel {  distance = 2.5km; } <--> repeater1.port++;
        repeater1.port++ <--> ClassicalChannel {  distance = 2.5km; } <--> BSA2.port++;
        BSA2.port++ <--> ClassicalChannel {  distance = 2.5km; } <--> repeater2.port++;
        repeater2.port++ <--> ClassicalChannel {  distance = 2.5km; } <--> BSA3.port++;
        BSA3.port++ <--> ClassicalChannel {  distance = 2.5km; } <--> repeater3.port++;
        repeater3.port++ <--> ClassicalChannel {  distance = 2.5km; } <--> BSA4.port++;
        BSA4.port++ <--> ClassicalChannel {  distance = 2.5km; } <--> repeater4.port++;
        repeater4.port++ <--> ClassicalChannel {  distance = 2.5km; } <--> BSA5.port++;
        BSA5.port++ <--> ClassicalChannel {  distance = 2.5km; } <--> repeater5.port++;
        repeater5.port++ <--> ClassicalChannel {  distance = 2.5km; } <--> BSA6.port++;
        BSA6.port++ <--> ClassicalChannel {  distance = 2.5km; } <--> repeater6.port++;
        repeater6.port++ <--> ClassicalChannel {  distance = 2.5km; } <--> BSA7.port++;
        BSA7.port++ <--> ClassicalChannel {  distance = 2.5km; } <--> repeater7.port++;
        repeater7.port++ <--> ClassicalChannel {  distance = 2.5km; } <--> BSA8.port++;
        BSA8.port++ <--> ClassicalChannel {  distance = 2.5km; } <--> repeater8.port++;
        repeater8.port++ <--> ClassicalChannel {  distance = 2.5km; } <--> BSA9.port++;
        BSA9.port++ <--> ClassicalChannel {  distance = 2.5km; } <--> repeater9.port++;
        repeater9.port++ <--> ClassicalChannel {  distance = 2.5km; } <--> BSA10.port++;
        BSA10.port++ <--> ClassicalChannel {  distance = 2.5km; } <--> target.port++;

        source.quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> BSA1.quantum_port++;
        BSA1.quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> repeater1.quantum_port++;
        repeater1.quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> BSA2.quantum_port++;
        BSA2.quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> repeater2.quantum_port++;
        repeater2.quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> BSA3.quantum_port++;
        BSA3.quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> repeater3.quantum_port++;
        repeater3.quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> BSA4.quantum_port++;
        BSA4.quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> repeater4.quantum_port++;
        repeater4.quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> BSA5.quantum_port++;
        BSA5.quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> repeater5.quantum_port++;
        repeater5.quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> BSA6.quantum_port++;
        BSA6.quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> repeater6.quantum_port++;
        repeater6.quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> BSA7.quantum_port++;
        BSA7.quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> repeater7.quantum_port++;
        repeater7.quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> BSA8.quantum_port++;
        BSA8.quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> repeater8.quantum_port++;
        repeater8.quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> BSA9.quantum_port++;
        BSA9.quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> repeater9.quantum_port++;
        repeater9.quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> BSA10.quantum_port++;
        BSA10.quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> target.quantum_port++;
}

network Linear_Ten_MIM_10km
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        //**.BSA_handshake = false;

    submodules:
        backend: Backend;
        logger: Logger;
        source: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP");
        }
        BSA1: BSANode {
            address = 11;
            @display("i=BSA");
        }
        BSA2: BSANode {
            address = 12;
            @display("i=BSA");
        }
        BSA3: BSANode {
            address = 13;
            @display("i=BSA");
        }
        BSA4: BSANode {
            address = 14;
            @display("i=BSA");
        }
        BSA5: BSANode {
            address = 15;
            @display("i=BSA");
        }
        BSA6: BSANode {
            address = 16;
            @display("i=BSA");
        }
        BSA7: BSANode {
            address = 17;
            @display("i=BSA");
        }
        BSA8: BSANode {
            address = 18;
            @display("i=BSA");
        }
        BSA9: BSANode {
            address = 19;
            @display("i=BSA");
        }
        BSA10: BSANode {
            address = 20;
            @display("i=BSA");
        }
        repeater1: QNode {
            address = 101;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater2: QNode {
            address = 102;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater3: QNode {
            address = 103;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater4: QNode {
            address = 104;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater5: QNode {
            address = 105;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater6: QNode {
            address = 106;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater7: QNode {
            address = 107;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater8: QNode {
            address = 108;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater9: QNode {
            address = 109;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        target: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP");
        }
    connections:
        source.port++ <--> ClassicalChannel {  distance = 5km; } <--> BSA1.port++;
        BSA1.port++ <--> ClassicalChannel {  distance = 5km; } <--> repeater1.port++;
        repeater1.port++ <--> ClassicalChannel {  distance = 5km; } <--> BSA2.port++;
        BSA2.port++ <--> ClassicalChannel {  distance = 5km; } <--> repeater2.port++;
        repeater2.port++ <--> ClassicalChannel {  distance = 5km; } <--> BSA3.port++;
        BSA3.port++ <--> ClassicalChannel {  distance = 5km; } <--> repeater3.port++;
        repeater3.port++ <--> ClassicalChannel {  distance = 5km; } <--> BSA4.port++;
        BSA4.port++ <--> ClassicalChannel {  distance = 5km; } <--> repeater4.port++;
        repeater4.port++ <--> ClassicalChannel {  distance = 5km; } <--> BSA5.port++;
        BSA5.port++ <--> ClassicalChannel {  distance = 5km; } <--> repeater5.port++;
        repeater5.port++ <--> ClassicalChannel {  distance = 5km; } <--> BSA6.port++;
        BSA6.port++ <--> ClassicalChannel {  distance = 5km; } <--> repeater6.port++;
        repeater6.port++ <--> ClassicalChannel {  distance = 5km; } <--> BSA7.port++;
        BSA7.port++ <--> ClassicalChannel {  distance = 5km; } <--> repeater7.port++;
        repeater7.port++ <--> ClassicalChannel {  distance = 5km; } <--> BSA8.port++;
        BSA8.port++ <--> ClassicalChannel {  distance = 5km; } <--> repeater8.port++;
        repeater8.port++ <--> ClassicalChannel {  distance = 5km; } <--> BSA9.port++;
        BSA9.port++ <--> ClassicalChannel {  distance = 5km; } <--> repeater9.port++;
        repeater9.port++ <--> ClassicalChannel {  distance = 5km; } <--> BSA10.port++;
        BSA10.port++ <--> ClassicalChannel {  distance = 5km; } <--> target.port++;

        source.quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> BSA1.quantum_port++;
        BSA1.quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> repeater1.quantum_port++;
        repeater1.quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> BSA2.quantum_port++;
        BSA2.quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> repeater2.quantum_port++;
        repeater2.quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> BSA3.quantum_port++;
        BSA3.quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> repeater3.quantum_port++;
        repeater3.quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> BSA4.quantum_port++;
        BSA4.quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> repeater4.quantum_port++;
        repeater4.quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> BSA5.quantum_port++;
        BSA5.quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> repeater5.quantum_port++;
        repeater5.quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> BSA6.quantum_port++;
        BSA6.quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> repeater6.quantum_port++;
        repeater6.quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> BSA7.quantum_port++;
        BSA7.quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> repeater7.quantum_port++;
        repeater7.quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> BSA8.quantum_port++;
        BSA8.quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> repeater8.quantum_port++;
        repeater8.quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> BSA9.quantum_port++;
        BSA9.quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> repeater9.quantum_port++;
        repeater9.quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> BSA10.quantum_port++;
        BSA10.quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> target.quantum_port++;
}

network Linear_Ten_MIM_15km
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        //**.BSA_handshake = false;

    submodules:
        backend: Backend;
        logger: Logger;
        source: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP");
        }
        BSA1: BSANode {
            address = 11;
            @display("i=BSA");
        }
        BSA2: BSANode {
            address = 12;
            @display("i=BSA");
        }
        BSA3: BSANode {
            address = 13;
            @display("i=BSA");
        }
        BSA4: BSANode {
            address = 14;
            @display("i=BSA");
        }
        BSA5: BSANode {
            address = 15;
            @display("i=BSA");
        }
        BSA6: BSANode {
            address = 16;
            @display("i=BSA");
        }
        BSA7: BSANode {
            address = 17;
            @display("i=BSA");
        }
        BSA8: BSANode {
            address = 18;
            @display("i=BSA");
        }
        BSA9: BSANode {
            address = 19;
            @display("i=BSA");
        }
        BSA10: BSANode {
            address = 20;
            @display("i=BSA");
        }
        repeater1: QNode {
            address = 101;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater2: QNode {
            address = 102;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater3: QNode {
            address = 103;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater4: QNode {
            address = 104;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater5: QNode {
            address = 105;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater6: QNode {
            address = 106;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater7: QNode {
            address = 107;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater8: QNode {
            address = 108;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater9: QNode {
            address = 109;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        target: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP");
        }
    connections:
        source.port++ <--> ClassicalChannel {  distance = 7.5km; } <--> BSA1.port++;
        BSA1.port++ <--> ClassicalChannel {  distance = 7.5km; } <--> repeater1.port++;
        repeater1.port++ <--> ClassicalChannel {  distance = 7.5km; } <--> BSA2.port++;
        BSA2.port++ <--> ClassicalChannel {  distance = 7.5km; } <--> repeater2.port++;
        repeater2.port++ <--> ClassicalChannel {  distance = 7.5km; } <--> BSA3.port++;
        BSA3.port++ <--> ClassicalChannel {  distance = 7.5km; } <--> repeater3.port++;
        repeater3.port++ <--> ClassicalChannel {  distance = 7.5km; } <--> BSA4.port++;
        BSA4.port++ <--> ClassicalChannel {  distance = 7.5km; } <--> repeater4.port++;
        repeater4.port++ <--> ClassicalChannel {  distance = 7.5km; } <--> BSA5.port++;
        BSA5.port++ <--> ClassicalChannel {  distance = 7.5km; } <--> repeater5.port++;
        repeater5.port++ <--> ClassicalChannel {  distance = 7.5km; } <--> BSA6.port++;
        BSA6.port++ <--> ClassicalChannel {  distance = 7.5km; } <--> repeater6.port++;
        repeater6.port++ <--> ClassicalChannel {  distance = 7.5km; } <--> BSA7.port++;
        BSA7.port++ <--> ClassicalChannel {  distance = 7.5km; } <--> repeater7.port++;
        repeater7.port++ <--> ClassicalChannel {  distance = 7.5km; } <--> BSA8.port++;
        BSA8.port++ <--> ClassicalChannel {  distance = 7.5km; } <--> repeater8.port++;
        repeater8.port++ <--> ClassicalChannel {  distance = 7.5km; } <--> BSA9.port++;
        BSA9.port++ <--> ClassicalChannel {  distance = 7.5km; } <--> repeater9.port++;
        repeater9.port++ <--> ClassicalChannel {  distance = 7.5km; } <--> BSA10.port++;
        BSA10.port++ <--> ClassicalChannel {  distance = 7.5km; } <--> target.port++;

        source.quantum_port++ <--> QuantumChannel {  distance = 7.5km; } <--> BSA1.quantum_port++;
        BSA1.quantum_port++ <--> QuantumChannel {  distance = 7.5km; } <--> repeater1.quantum_port++;
        repeater1.quantum_port++ <--> QuantumChannel {  distance = 7.5km; } <--> BSA2.quantum_port++;
        BSA2.quantum_port++ <--> QuantumChannel {  distance = 7.5km; } <--> repeater2.quantum_port++;
        repeater2.quantum_port++ <--> QuantumChannel {  distance = 7.5km; } <--> BSA3.quantum_port++;
        BSA3.quantum_port++ <--> QuantumChannel {  distance = 7.5km; } <--> repeater3.quantum_port++;
        repeater3.quantum_port++ <--> QuantumChannel {  distance = 7.5km; } <--> BSA4.quantum_port++;
        BSA4.quantum_port++ <--> QuantumChannel {  distance = 7.5km; } <--> repeater4.quantum_port++;
        repeater4.quantum_port++ <--> QuantumChannel {  distance = 7.5km; } <--> BSA5.quantum_port++;
        BSA5.quantum_port++ <--> QuantumChannel {  distance = 7.5km; } <--> repeater5.quantum_port++;
        repeater5.quantum_port++ <--> QuantumChannel {  distance = 7.5km; } <--> BSA6.quantum_port++;
        BSA6.quantum_port++ <--> QuantumChannel {  distance = 7.5km; } <--> repeater6.quantum_port++;
        repeater6.quantum_port++ <--> QuantumChannel {  distance = 7.5km; } <--> BSA7.quantum_port++;
        BSA7.quantum_port++ <--> QuantumChannel {  distance = 7.5km; } <--> repeater7.quantum_port++;
        repeater7.quantum_port++ <--> QuantumChannel {  distance = 7.5km; } <--> BSA8.quantum_port++;
        BSA8.quantum_port++ <--> QuantumChannel {  distance = 7.5km; } <--> repeater8.quantum_port++;
        repeater8.quantum_port++ <--> QuantumChannel {  distance = 7.5km; } <--> BSA9.quantum_port++;
        BSA9.quantum_port++ <--> QuantumChannel {  distance = 7.5km; } <--> repeater9.quantum_port++;
        repeater9.quantum_port++ <--> QuantumChannel {  distance = 7.5km; } <--> BSA10.quantum_port++;
        BSA10.quantum_port++ <--> QuantumChannel {  distance = 7.5km; } <--> target.quantum_port++;

}

network Linear_Ten_MIM_20km
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        //**.BSA_handshake = false;

    submodules:
        backend: Backend;
        logger: Logger;
        source: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP");
        }
        BSA1: BSANode {
            address = 11;
            @display("i=BSA");
        }
        BSA2: BSANode {
            address = 12;
            @display("i=BSA");
        }
        BSA3: BSANode {
            address = 13;
            @display("i=BSA");
        }
        BSA4: BSANode {
            address = 14;
            @display("i=BSA");
        }
        BSA5: BSANode {
            address = 15;
            @display("i=BSA");
        }
        BSA6: BSANode {
            address = 16;
            @display("i=BSA");
        }
        BSA7: BSANode {
            address = 17;
            @display("i=BSA");
        }
        BSA8: BSANode {
            address = 18;
            @display("i=BSA");
        }
        BSA9: BSANode {
            address = 19;
            @display("i=BSA");
        }
        BSA10: BSANode {
            address = 20;
            @display("i=BSA");
        }
        repeater1: QNode {
            address = 101;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater2: QNode {
            address = 102;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater3: QNode {
            address = 103;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater4: QNode {
            address = 104;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater5: QNode {
            address = 105;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater6: QNode {
            address = 106;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater7: QNode {
            address = 107;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater8: QNode {
            address = 108;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater9: QNode {
            address = 109;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        target: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP");
        }
    connections:
        source.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA1.port++;
        BSA1.port++ <--> ClassicalChannel {  distance = 10km; } <--> repeater1.port++;
        repeater1.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA2.port++;
        BSA2.port++ <--> ClassicalChannel {  distance = 10km; } <--> repeater2.port++;
        repeater2.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA3.port++;
        BSA3.port++ <--> ClassicalChannel {  distance = 10km; } <--> repeater3.port++;
        repeater3.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA4.port++;
        BSA4.port++ <--> ClassicalChannel {  distance = 10km; } <--> repeater4.port++;
        repeater4.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA5.port++;
        BSA5.port++ <--> ClassicalChannel {  distance = 10km; } <--> repeater5.port++;
        repeater5.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA6.port++;
        BSA6.port++ <--> ClassicalChannel {  distance = 10km; } <--> repeater6.port++;
        repeater6.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA7.port++;
        BSA7.port++ <--> ClassicalChannel {  distance = 10km; } <--> repeater7.port++;
        repeater7.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA8.port++;
        BSA8.port++ <--> ClassicalChannel {  distance = 10km; } <--> repeater8.port++;
        repeater8.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA9.port++;
        BSA9.port++ <--> ClassicalChannel {  distance = 10km; } <--> repeater9.port++;
        repeater9.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA10.port++;
        BSA10.port++ <--> ClassicalChannel {  distance = 10km; } <--> target.port++;

        source.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA1.quantum_port++;
        BSA1.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> repeater1.quantum_port++;
        repeater1.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA2.quantum_port++;
        BSA2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> repeater2.quantum_port++;
        repeater2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA3.quantum_port++;
        BSA3.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> repeater3.quantum_port++;
        repeater3.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA4.quantum_port++;
        BSA4.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> repeater4.quantum_port++;
        repeater4.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA5.quantum_port++;
        BSA5.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> repeater5.quantum_port++;
        repeater5.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA6.quantum_port++;
        BSA6.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> repeater6.quantum_port++;
        repeater6.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA7.quantum_port++;
        BSA7.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> repeater7.quantum_port++;
        repeater7.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA8.quantum_port++;
        BSA8.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> repeater8.quantum_port++;
        repeater8.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA9.quantum_port++;
        BSA9.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> repeater9.quantum_port++;
        repeater9.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA10.quantum_port++;
        BSA10.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> target.quantum_port++;
}

network Linear_Ten_MIM_25km
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        //**.BSA_handshake = false;

    submodules:
        backend: Backend;
        logger: Logger;
        source: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP");
        }
        BSA1: BSANode {
            address = 11;
            @display("i=BSA");
        }
        BSA2: BSANode {
            address = 12;
            @display("i=BSA");
        }
        BSA3: BSANode {
            address = 13;
            @display("i=BSA");
        }
        BSA4: BSANode {
            address = 14;
            @display("i=BSA");
        }
        BSA5: BSANode {
            address = 15;
            @display("i=BSA");
        }
        BSA6: BSANode {
            address = 16;
            @display("i=BSA");
        }
        BSA7: BSANode {
            address = 17;
            @display("i=BSA");
        }
        BSA8: BSANode {
            address = 18;
            @display("i=BSA");
        }
        BSA9: BSANode {
            address = 19;
            @display("i=BSA");
        }
        BSA10: BSANode {
            address = 20;
            @display("i=BSA");
        }
        repeater1: QNode {
            address = 101;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater2: QNode {
            address = 102;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater3: QNode {
            address = 103;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater4: QNode {
            address = 104;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater5: QNode {
            address = 105;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater6: QNode {
            address = 106;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater7: QNode {
            address = 107;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater8: QNode {
            address = 108;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater9: QNode {
            address = 109;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        target: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP");
        }
    connections:
        source.port++ <--> ClassicalChannel {  distance = 12.5km; } <--> BSA1.port++;
        BSA1.port++ <--> ClassicalChannel {  distance = 12.5km; } <--> repeater1.port++;
        repeater1.port++ <--> ClassicalChannel {  distance = 12.5km; } <--> BSA2.port++;
        BSA2.port++ <--> ClassicalChannel {  distance = 12.5km; } <--> repeater2.port++;
        repeater2.port++ <--> ClassicalChannel {  distance = 12.5km; } <--> BSA3.port++;
        BSA3.port++ <--> ClassicalChannel {  distance = 12.5km; } <--> repeater3.port++;
        repeater3.port++ <--> ClassicalChannel {  distance = 12.5km; } <--> BSA4.port++;
        BSA4.port++ <--> ClassicalChannel {  distance = 12.5km; } <--> repeater4.port++;
        repeater4.port++ <--> ClassicalChannel {  distance = 12.5km; } <--> BSA5.port++;
        BSA5.port++ <--> ClassicalChannel {  distance = 12.5km; } <--> repeater5.port++;
        repeater5.port++ <--> ClassicalChannel {  distance = 12.5km; } <--> BSA6.port++;
        BSA6.port++ <--> ClassicalChannel {  distance = 12.5km; } <--> repeater6.port++;
        repeater6.port++ <--> ClassicalChannel {  distance = 12.5km; } <--> BSA7.port++;
        BSA7.port++ <--> ClassicalChannel {  distance = 12.5km; } <--> repeater7.port++;
        repeater7.port++ <--> ClassicalChannel {  distance = 12.5km; } <--> BSA8.port++;
        BSA8.port++ <--> ClassicalChannel {  distance = 12.5km; } <--> repeater8.port++;
        repeater8.port++ <--> ClassicalChannel {  distance = 12.5km; } <--> BSA9.port++;
        BSA9.port++ <--> ClassicalChannel {  distance = 12.5km; } <--> repeater9.port++;
        repeater9.port++ <--> ClassicalChannel {  distance = 12.5km; } <--> BSA10.port++;
        BSA10.port++ <--> ClassicalChannel {  distance = 12.5km; } <--> target.port++;

        source.quantum_port++ <--> QuantumChannel {  distance = 12.5km; } <--> BSA1.quantum_port++;
        BSA1.quantum_port++ <--> QuantumChannel {  distance = 12.5km; } <--> repeater1.quantum_port++;
        repeater1.quantum_port++ <--> QuantumChannel {  distance = 12.5km; } <--> BSA2.quantum_port++;
        BSA2.quantum_port++ <--> QuantumChannel {  distance = 12.5km; } <--> repeater2.quantum_port++;
        repeater2.quantum_port++ <--> QuantumChannel {  distance = 12.5km; } <--> BSA3.quantum_port++;
        BSA3.quantum_port++ <--> QuantumChannel {  distance = 12.5km; } <--> repeater3.quantum_port++;
        repeater3.quantum_port++ <--> QuantumChannel {  distance = 12.5km; } <--> BSA4.quantum_port++;
        BSA4.quantum_port++ <--> QuantumChannel {  distance = 12.5km; } <--> repeater4.quantum_port++;
        repeater4.quantum_port++ <--> QuantumChannel {  distance = 12.5km; } <--> BSA5.quantum_port++;
        BSA5.quantum_port++ <--> QuantumChannel {  distance = 12.5km; } <--> repeater5.quantum_port++;
        repeater5.quantum_port++ <--> QuantumChannel {  distance = 12.5km; } <--> BSA6.quantum_port++;
        BSA6.quantum_port++ <--> QuantumChannel {  distance = 12.5km; } <--> repeater6.quantum_port++;
        repeater6.quantum_port++ <--> QuantumChannel {  distance = 12.5km; } <--> BSA7.quantum_port++;
        BSA7.quantum_port++ <--> QuantumChannel {  distance = 12.5km; } <--> repeater7.quantum_port++;
        repeater7.quantum_port++ <--> QuantumChannel {  distance = 12.5km; } <--> BSA8.quantum_port++;
        BSA8.quantum_port++ <--> QuantumChannel {  distance = 12.5km; } <--> repeater8.quantum_port++;
        repeater8.quantum_port++ <--> QuantumChannel {  distance = 12.5km; } <--> BSA9.quantum_port++;
        BSA9.quantum_port++ <--> QuantumChannel {  distance = 12.5km; } <--> repeater9.quantum_port++;
        repeater9.quantum_port++ <--> QuantumChannel {  distance = 12.5km; } <--> BSA10.quantum_port++;
        BSA10.quantum_port++ <--> QuantumChannel {  distance = 12.5km; } <--> target.quantum_port++;
}

network Linear_Ten_MIM_30km
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        //**.BSA_handshake = false;

    submodules:
        backend: Backend;
        logger: Logger;
        source: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP");
        }
        BSA1: BSANode {
            address = 11;
            @display("i=BSA");
        }
        BSA2: BSANode {
            address = 12;
            @display("i=BSA");
        }
        BSA3: BSANode {
            address = 13;
            @display("i=BSA");
        }
        BSA4: BSANode {
            address = 14;
            @display("i=BSA");
        }
        BSA5: BSANode {
            address = 15;
            @display("i=BSA");
        }
        BSA6: BSANode {
            address = 16;
            @display("i=BSA");
        }
        BSA7: BSANode {
            address = 17;
            @display("i=BSA");
        }
        BSA8: BSANode {
            address = 18;
            @display("i=BSA");
        }
        BSA9: BSANode {
            address = 19;
            @display("i=BSA");
        }
        BSA10: BSANode {
            address = 20;
            @display("i=BSA");
        }
        repeater1: QNode {
            address = 101;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater2: QNode {
            address = 102;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater3: QNode {
            address = 103;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater4: QNode {
            address = 104;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater5: QNode {
            address = 105;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater6: QNode {
            address = 106;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater7: QNode {
            address = 107;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater8: QNode {
            address = 108;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater9: QNode {
            address = 109;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        target: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP");
        }
    connections:
        source.port++ <--> ClassicalChannel {  distance = 15km; } <--> BSA1.port++;
        BSA1.port++ <--> ClassicalChannel {  distance = 15km; } <--> repeater1.port++;
        repeater1.port++ <--> ClassicalChannel {  distance = 15km; } <--> BSA2.port++;
        BSA2.port++ <--> ClassicalChannel {  distance = 15km; } <--> repeater2.port++;
        repeater2.port++ <--> ClassicalChannel {  distance = 15km; } <--> BSA3.port++;
        BSA3.port++ <--> ClassicalChannel {  distance = 15km; } <--> repeater3.port++;
        repeater3.port++ <--> ClassicalChannel {  distance = 15km; } <--> BSA4.port++;
        BSA4.port++ <--> ClassicalChannel {  distance = 15km; } <--> repeater4.port++;
        repeater4.port++ <--> ClassicalChannel {  distance = 15km; } <--> BSA5.port++;
        BSA5.port++ <--> ClassicalChannel {  distance = 15km; } <--> repeater5.port++;
        repeater5.port++ <--> ClassicalChannel {  distance = 15km; } <--> BSA6.port++;
        BSA6.port++ <--> ClassicalChannel {  distance = 15km; } <--> repeater6.port++;
        repeater6.port++ <--> ClassicalChannel {  distance = 15km; } <--> BSA7.port++;
        BSA7.port++ <--> ClassicalChannel {  distance = 15km; } <--> repeater7.port++;
        repeater7.port++ <--> ClassicalChannel {  distance = 15km; } <--> BSA8.port++;
        BSA8.port++ <--> ClassicalChannel {  distance = 15km; } <--> repeater8.port++;
        repeater8.port++ <--> ClassicalChannel {  distance = 15km; } <--> BSA9.port++;
        BSA9.port++ <--> ClassicalChannel {  distance = 15km; } <--> repeater9.port++;
        repeater9.port++ <--> ClassicalChannel {  distance = 15km; } <--> BSA10.port++;
        BSA10.port++ <--> ClassicalChannel {  distance = 15km; } <--> target.port++;

        source.quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> BSA1.quantum_port++;
        BSA1.quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> repeater1.quantum_port++;
        repeater1.quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> BSA2.quantum_port++;
        BSA2.quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> repeater2.quantum_port++;
        repeater2.quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> BSA3.quantum_port++;
        BSA3.quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> repeater3.quantum_port++;
        repeater3.quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> BSA4.quantum_port++;
        BSA4.quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> repeater4.quantum_port++;
        repeater4.quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> BSA5.quantum_port++;
        BSA5.quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> repeater5.quantum_port++;
        repeater5.quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> BSA6.quantum_port++;
        BSA6.quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> repeater6.quantum_port++;
        repeater6.quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> BSA7.quantum_port++;
        BSA7.quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> repeater7.quantum_port++;
        repeater7.quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> BSA8.quantum_port++;
        BSA8.quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> repeater8.quantum_port++;
        repeater8.quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> BSA9.quantum_port++;
        BSA9.quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> repeater9.quantum_port++;
        repeater9.quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> BSA10.quantum_port++;
        BSA10.quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> target.quantum_port++;

}

network Linear_Ten_MIM_35km
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
        //**.BSA_handshake = false;

    submodules:
        backend: Backend;
        logger: Logger;
        source: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP");
        }
        BSA1: BSANode {
            address = 11;
            @display("i=BSA");
        }
        BSA2: BSANode {
            address = 12;
            @display("i=BSA");
        }
        BSA3: BSANode {
            address = 13;
            @display("i=BSA");
        }
        BSA4: BSANode {
            address = 14;
            @display("i=BSA");
        }
        BSA5: BSANode {
            address = 15;
            @display("i=BSA");
        }
        BSA6: BSANode {
            address = 16;
            @display("i=BSA");
        }
        BSA7: BSANode {
            address = 17;
            @display("i=BSA");
        }
        BSA8: BSANode {
            address = 18;
            @display("i=BSA");
        }
        BSA9: BSANode {
            address = 19;
            @display("i=BSA");
        }
        BSA10: BSANode {
            address = 20;
            @display("i=BSA");
        }
        repeater1: QNode {
            address = 101;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater2: QNode {
            address = 102;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater3: QNode {
            address = 103;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater4: QNode {
            address = 104;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater5: QNode {
            address = 105;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater6: QNode {
            address = 106;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater7: QNode {
            address = 107;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater8: QNode {
            address = 108;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        repeater9: QNode {
            address = 109;
            node_type = "Repeater";
            @display("i=Repeater");
        }

        target: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP");
        }
    connections:
        source.port++ <--> ClassicalChannel {  distance = 17.5km; } <--> BSA1.port++;
        BSA1.port++ <--> ClassicalChannel {  distance = 17.5km; } <--> repeater1.port++;
        repeater1.port++ <--> ClassicalChannel {  distance = 17.5km; } <--> BSA2.port++;
        BSA2.port++ <--> ClassicalChannel {  distance = 17.5km; } <--> repeater2.port++;
        repeater2.port++ <--> ClassicalChannel {  distance = 17.5km; } <--> BSA3.port++;
        BSA3.port++ <--> ClassicalChannel {  distance = 17.5km; } <--> repeater3.port++;
        repeater3.port++ <--> ClassicalChannel {  distance = 17.5km; } <--> BSA4.port++;
        BSA4.port++ <--> ClassicalChannel {  distance = 17.5km; } <--> repeater4.port++;
        repeater4.port++ <--> ClassicalChannel {  distance = 17.5km; } <--> BSA5.port++;
        BSA5.port++ <--> ClassicalChannel {  distance = 17.5km; } <--> repeater5.port++;
        repeater5.port++ <--> ClassicalChannel {  distance = 17.5km; } <--> BSA6.port++;
        BSA6.port++ <--> ClassicalChannel {  distance = 17.5km; } <--> repeater6.port++;
        repeater6.port++ <--> ClassicalChannel {  distance = 17.5km; } <--> BSA7.port++;
        BSA7.port++ <--> ClassicalChannel {  distance = 17.5km; } <--> repeater7.port++;
        repeater7.port++ <--> ClassicalChannel {  distance = 17.5km; } <--> BSA8.port++;
        BSA8.port++ <--> ClassicalChannel {  distance = 17.5km; } <--> repeater8.port++;
        repeater8.port++ <--> ClassicalChannel {  distance = 17.5km; } <--> BSA9.port++;
        BSA9.port++ <--> ClassicalChannel {  distance = 17.5km; } <--> repeater9.port++;
        repeater9.port++ <--> ClassicalChannel {  distance = 17.5km; } <--> BSA10.port++;
        BSA10.port++ <--> ClassicalChannel {  distance = 17.5km; } <--> target.port++;

        source.quantum_port++ <--> QuantumChannel {  distance = 17.5km; } <--> BSA1.quantum_port++;
        BSA1.quantum_port++ <--> QuantumChannel {  distance = 17.5km; } <--> repeater1.quantum_port++;
        repeater1.quantum_port++ <--> QuantumChannel {  distance = 17.5km; } <--> BSA2.quantum_port++;
        BSA2.quantum_port++ <--> QuantumChannel {  distance = 17.5km; } <--> repeater2.quantum_port++;
        repeater2.quantum_port++ <--> QuantumChannel {  distance = 17.5km; } <--> BSA3.quantum_port++;
        BSA3.quantum_port++ <--> QuantumChannel {  distance = 17.5km; } <--> repeater3.quantum_port++;
        repeater3.quantum_port++ <--> QuantumChannel {  distance = 17.5km; } <--> BSA4.quantum_port++;
        BSA4.quantum_port++ <--> QuantumChannel {  distance = 17.5km; } <--> repeater4.quantum_port++;
        repeater4.quantum_port++ <--> QuantumChannel {  distance = 17.5km; } <--> BSA5.quantum_port++;
        BSA5.quantum_port++ <--> QuantumChannel {  distance = 17.5km; } <--> repeater5.quantum_port++;
        repeater5.quantum_port++ <--> QuantumChannel {  distance = 17.5km; } <--> BSA6.quantum_port++;
        BSA6.quantum_port++ <--> QuantumChannel {  distance = 17.5km; } <--> repeater6.quantum_port++;
        repeater6.quantum_port++ <--> QuantumChannel {  distance = 17.5km; } <--> BSA7.quantum_port++;
        BSA7.quantum_port++ <--> QuantumChannel {  distance = 17.5km; } <--> repeater7.quantum_port++;
        repeater7.quantum_port++ <--> QuantumChannel {  distance = 17.5km; } <--> BSA8.quantum_port++;
        BSA8.quantum_port++ <--> QuantumChannel {  distance = 17.5km; } <--> repeater8.quantum_port++;
        repeater8.quantum_port++ <--> QuantumChannel {  distance = 17.5km; } <--> BSA9.quantum_port++;
        BSA9.quantum_port++ <--> QuantumChannel {  distance = 17.5km; } <--> repeater9.quantum_port++;
        repeater9.quantum_port++ <--> QuantumChannel {  distance = 17.5km; } <--> BSA10.quantum_port++;
        BSA10.quantum_port++ <--> QuantumChannel {  distance = 17.5km; } <--> target.quantum_port++;

}
