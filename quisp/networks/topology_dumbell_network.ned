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
import modules.Backend.Backend;
import modules.Logger.Logger;

// Dumbell MM network
network topology_dumbell_MM
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;
    submodules:
        backend: Backend;
        logger: Logger;
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
        backend: Backend;
        logger: Logger;
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
        HOM1: HOM {
            address = 9;
            nodeType = "BSA";
            @dispaly("p=42,150");
            @display("p=105,238");
        }
        HOM2: HOM {
            address = 10;
            nodeType = "BSA";
            @dispaly("p=52,140");
            @display("p=186,238");
        }
        HOM3: HOM {
            address = 11;
            nodeType = "BSA";
            @dispaly("p=32,130");
        }
        HOM4: HOM {
            address = 12;
            nodeType = "BSA";
            @display("p=113,87");
        }
        HOM5: HOM {
            address = 13;
            nodeType = "BSA";
            @display("p=326,118");
        }
        HOM6: HOM {
            address = 14;
            nodeType = "BSA";
            @display("p=421,118");
        }
        HOM7: HOM {
            address = 15;
            nodeType = "BSA";
            @display("p=454,54");
        }


    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 10km; } <--> HOM1.port++;
        EndNode2.port++ <--> ClassicalChannel {  distance = 10km; } <--> HOM2.port++;
        EndNode3.port++ <--> ClassicalChannel {  distance = 10km; } <--> HOM3.port++;
        HOM1.port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater1.port++;
        HOM2.port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater1.port++;
        HOM3.port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater1.port++;
        Repeater1.port++ <--> ClassicalChannel {  distance = 10km; } <--> HOM4.port++;
        HOM4.port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater2.port++;
        Repeater2.port++ <--> ClassicalChannel {  distance = 10km; } <--> HOM5.port++;
        Repeater2.port++ <--> ClassicalChannel {  distance = 10km; } <--> HOM6.port++;
        Repeater2.port++ <--> ClassicalChannel {  distance = 10km; } <--> HOM7.port++;
        HOM5.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode4.port++;
        HOM6.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode5.port++;
        HOM7.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode6.port++;

        EndNode1.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HOM1.quantum_port++;
        EndNode2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HOM2.quantum_port++;
        EndNode3.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HOM3.quantum_port++;
        HOM1.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> Repeater1.quantum_port++;
        HOM2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> Repeater1.quantum_port++;
        HOM3.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> Repeater1.quantum_port++;
        Repeater1.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HOM4.quantum_port++;
        HOM4.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> Repeater2.quantum_port++;
        Repeater2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HOM5.quantum_port++;
        Repeater2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HOM6.quantum_port++;
        Repeater2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HOM7.quantum_port++;
        HOM5.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode4.quantum_port++;
        HOM6.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode5.quantum_port++;
        HOM7.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode6.quantum_port++;

}
