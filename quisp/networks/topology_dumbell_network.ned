//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package networks;

import modules.*;
import channels.*;
import ned.IdealChannel;
import ned.DatarateChannel;

// Dumbell MM network
network topology_dumbell_MM
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;
    submodules:
        EndNode1: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=COMP;p=152,238");
        }
        EndNode2: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=COMP;p=324,245");
        }
        EndNode3: QNode {
            address = 3;
            nodeType = "EndNode";
            @display("i=COMP;p=220,137");
        }
        EndNode4: QNode {
            address = 4;
            nodeType = "EndNode";
            @display("i=COMP;p=350,22");
        }
        EndNode5: QNode {
            address = 5;
            nodeType = "EndNode";
            @display("i=COMP;p=401,118");
        }
        EndNode6: QNode {
            address = 6;
            nodeType = "EndNode";
            @display("i=COMP;p=421,61");
        }
        Repeater1: QNode {
            address = 7;
            nodeType = "Repeater";
            @display("i=RTR;p=66,124");
        }
        Repeater2: QNode {
            address = 8;
            nodeType = "Repeater";
            @display("i=RTR;p=132,36");
        }

    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater1.port++;
        EndNode2.port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater1.port++;
        EndNode3.port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater1.port++;
        Repeater1.port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater2.port++;
        Repeater2.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode4.port++;
        Repeater2.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode5.port++;
        Repeater2.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode6.port++;

        EndNode1.quantum_port_receiver++ <--> QuantumChannel {  distance = 10km; } <--> Repeater1.quantum_port++;
        EndNode2.quantum_port_receiver++ <--> QuantumChannel {  distance = 10km; } <--> Repeater1.quantum_port++;
        EndNode3.quantum_port_receiver++ <--> QuantumChannel {  distance = 10km; } <--> Repeater1.quantum_port++;
        Repeater1.quantum_port_receiver++ <--> QuantumChannel {  distance = 10km; } <--> Repeater2.quantum_port++;
        Repeater2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode4.quantum_port_receiver++;
        Repeater2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode5.quantum_port_receiver++;
        Repeater2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode6.quantum_port_receiver++;
}


//Dumbell MIM network
network topology_dumbell_MIM
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;
    submodules:
        EndNode1: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=COMP;p=200,331");
        }
        EndNode2: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=COMP;p=329,322");
        }
        EndNode3: QNode {
            address = 3;
            nodeType = "EndNode";
            @display("i=COMP;p=454,285");
        }
        EndNode4: QNode {
            address = 4;
            nodeType = "EndNode";
            @display("i=COMP;p=454,199");
        }
        EndNode5: QNode {
            address = 5;
            nodeType = "EndNode";
            @display("i=COMP;p=554,168");
        }
        EndNode6: QNode {
            address = 6;
            nodeType = "EndNode";
            @display("i=COMP;p=602,73");
        }
        Repeater1: QNode {
            address = 7;
            nodeType = "Repeater";
            @display("i=RTR;p=45,161");
        }
        Repeater2: QNode {
            address = 8;
            nodeType = "Repeater";
            @display("i=RTR;p=197,21");
        }
        HoM1: HoM {
            address = 9;
            nodeType = "BSA";
            @dispaly("i=BSA;p=42,150");
            @display("p=105,238");
        }
        HoM2: HoM {
            address = 10;
            nodeType = "BSA";
            @dispaly("i=BSA;p=52,140");
            @display("p=186,238");
        }
        HoM3: HoM {
            address = 11;
            nodeType = "BSA";
            @dispaly("i=BSA;p=32,130");
            @display("p=293,238");
        }
        HoM4: HoM {
            address = 12;
            nodeType = "BSA";
            @dispaly("i=BSA;p=42,150");
            @display("p=113,87");
        }
        HoM5: HoM {
            address = 13;
            nodeType = "BSA";
            @dispaly("i=BSA;p=62,225");
            @display("p=326,118");
        }
        HoM6: HoM {
            address = 14;
            nodeType = "BSA";
            @dispaly("i=BSA;p=52,250");
            @display("p=421,118");
        }
        HoM7: HoM {
            address = 15;
            nodeType = "BSA";
            @dispaly("i=BSA;p=55,240");
            @display("p=454,54");
        }


    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM1.port++;
        EndNode2.port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM2.port++;
        EndNode3.port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM3.port++;
        HoM1.port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater1.port++;
        HoM2.port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater1.port++;
        HoM3.port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater1.port++;
        Repeater1.port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM4.port++;
        HoM4.port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater2.port++;
        Repeater2.port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM5.port++;
        Repeater2.port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM6.port++;
        Repeater2.port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM7.port++;
        HoM5.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode4.port++;
        HoM6.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode5.port++;
        HoM7.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode6.port++;

        EndNode1.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HoM1.quantum_port++;
        EndNode2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HoM2.quantum_port++;
        EndNode3.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HoM3.quantum_port++;
        HoM1.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> Repeater1.quantum_port++;
        HoM2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> Repeater1.quantum_port++;
        HoM3.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> Repeater1.quantum_port++;
        Repeater1.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HoM4.quantum_port++;
        HoM4.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> Repeater2.quantum_port++;
        Repeater2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HoM5.quantum_port++;
        Repeater2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HoM6.quantum_port++;
        Repeater2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HoM7.quantum_port++;
        HoM5.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode4.quantum_port++;
        HoM6.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode5.quantum_port++;
        HoM7.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode6.quantum_port++;

}
