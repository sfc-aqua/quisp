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
import modules.SharedResource.SharedResource;

// Dumbell MM network with four end nodes
network topology_dumbell_MM_four_end_nodes
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        EndNode1: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=152,238");
        }
        EndNode2: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP;p=324,245");
        }
        EndNode3: QNode {
            address = 3;
            node_type = "EndNode";
            @display("i=COMP;p=220,137");
        }
        EndNode4: QNode {
            address = 4;
            node_type = "EndNode";
            @display("i=COMP;p=350,22");
        }
        Repeater1: QNode {
            address = 7;
            node_type = "Repeater";
            @display("i=RTR;p=66,124");
        }
        Repeater2: QNode {
            address = 8;
            node_type = "Repeater";
            @display("i=RTR;p=132,36");
        }

    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater1.port++;
        EndNode2.port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater1.port++;
        Repeater1.port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater2.port++;
        Repeater2.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode3.port++;
        Repeater2.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode4.port++;

        EndNode1.quantum_port_receiver++ <--> QuantumChannel {  distance = 10km; } <--> Repeater1.quantum_port++;
        EndNode2.quantum_port_receiver++ <--> QuantumChannel {  distance = 10km; } <--> Repeater1.quantum_port++;
        Repeater1.quantum_port_receiver++ <--> QuantumChannel {  distance = 10km; } <--> Repeater2.quantum_port++;
        Repeater2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode3.quantum_port_receiver++;
        Repeater2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode4.quantum_port_receiver++;
}


// Dumbell MM network with six end nodes
network topology_dumbell_MM_six_end_nodes
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        EndNode1: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=152,238");
        }
        EndNode2: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP;p=324,245");
        }
        EndNode3: QNode {
            address = 3;
            node_type = "EndNode";
            @display("i=COMP;p=220,137");
        }
        EndNode4: QNode {
            address = 4;
            node_type = "EndNode";
            @display("i=COMP;p=350,22");
        }
        EndNode5: QNode {
            address = 5;
            node_type = "EndNode";
            @display("i=COMP;p=401,118");
        }
        EndNode6: QNode {
            address = 6;
            node_type = "EndNode";
            @display("i=COMP;p=421,61");
        }
        Repeater1: QNode {
            address = 7;
            node_type = "Repeater";
            @display("i=RTR;p=66,124");
        }
        Repeater2: QNode {
            address = 8;
            node_type = "Repeater";
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

//Dumbell MIM network with four end nodes
network topology_dumbell_MIM_four_end_nodes
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        EndNode1: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=200,331");
        }
        EndNode2: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP;p=329,322");
        }
        EndNode3: QNode {
            address = 3;
            node_type = "EndNode";
            @display("i=COMP;p=454,285");
        }
        EndNode4: QNode {
            address = 4;
            node_type = "EndNode";
            @display("i=COMP;p=454,199");
        }
        Repeater1: QNode {
            address = 7;
            node_type = "Repeater";
            @display("i=RTR;p=45,161");
        }
        Repeater2: QNode {
            address = 8;
            node_type = "Repeater";
            @display("i=RTR;p=197,21");
        }
        BSA1: BSANode {
            address = 9;
            node_type = "BSA";
            @display("p=42,150");
            @display("p=105,238");
        }
        BSA2: BSANode {
            address = 10;
            node_type = "BSA";
            @display("p=52,140");
            @display("p=186,238");
        }
        BSA3: BSANode {
            address = 11;
            node_type = "BSA";
            @display("p=32,130");
        }
        BSA4: BSANode {
            address = 12;
            node_type = "BSA";
            @display("p=113,87");
        }
        BSA5: BSANode {
            address = 13;
            node_type = "BSA";
            @display("p=326,118");
        }
        BSA6: BSANode {
            address = 14;
            node_type = "BSA";
            @display("p=421,118");
        }
        BSA7: BSANode {
            address = 15;
            node_type = "BSA";
            @display("p=454,54");
        }


    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA1.port++;
        EndNode2.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA2.port++;
        BSA1.port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater1.port++;
        BSA2.port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater1.port++;
        Repeater1.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA3.port++;
        BSA3.port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater2.port++;
        Repeater2.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA4.port++;
        Repeater2.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA5.port++;
        BSA4.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode3.port++;
        BSA5.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode4.port++;

        EndNode1.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA1.quantum_port++;
        EndNode2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA2.quantum_port++;
        EndNode3.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA3.quantum_port++;
        BSA1.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> Repeater1.quantum_port++;
        BSA2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> Repeater1.quantum_port++;
        BSA3.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> Repeater1.quantum_port++;
        Repeater1.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA4.quantum_port++;
        BSA4.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> Repeater2.quantum_port++;
        Repeater2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA5.quantum_port++;
        Repeater2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA6.quantum_port++;
        Repeater2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA7.quantum_port++;
        BSA5.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode4.quantum_port++;
        BSA6.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode5.quantum_port++;
        BSA7.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode6.quantum_port++;

}


//Dumbell MIM network with six end nodes
network topology_dumbell_MIM_six_end_nodes
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
    submodules:
        backend: Backend;
        logger: Logger;
        sharedResource: SharedResource;
        EndNode1: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=200,331");
        }
        EndNode2: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP;p=329,322");
        }
        EndNode3: QNode {
            address = 3;
            node_type = "EndNode";
            @display("i=COMP;p=454,285");
        }
        EndNode4: QNode {
            address = 4;
            node_type = "EndNode";
            @display("i=COMP;p=454,199");
        }
        EndNode5: QNode {
            address = 5;
            node_type = "EndNode";
            @display("i=COMP;p=554,168");
        }
        EndNode6: QNode {
            address = 6;
            node_type = "EndNode";
            @display("i=COMP;p=602,73");
        }
        Repeater1: QNode {
            address = 7;
            node_type = "Repeater";
            @display("i=RTR;p=45,161");
        }
        Repeater2: QNode {
            address = 8;
            node_type = "Repeater";
            @display("i=RTR;p=197,21");
        }
        BSA1: BSANode {
            address = 9;
            node_type = "BSA";
            @display("p=42,150");
            @display("p=105,238");
        }
        BSA2: BSANode {
            address = 10;
            node_type = "BSA";
            @display("p=52,140");
            @display("p=186,238");
        }
        BSA3: BSANode {
            address = 11;
            node_type = "BSA";
            @display("p=32,130");
        }
        BSA4: BSANode {
            address = 12;
            node_type = "BSA";
            @display("p=113,87");
        }
        BSA5: BSANode {
            address = 13;
            node_type = "BSA";
            @display("p=326,118");
        }
        BSA6: BSANode {
            address = 14;
            node_type = "BSA";
            @display("p=421,118");
        }
        BSA7: BSANode {
            address = 15;
            node_type = "BSA";
            @display("p=454,54");
        }


    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA1.port++;
        EndNode2.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA2.port++;
        EndNode3.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA3.port++;
        BSA1.port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater1.port++;
        BSA2.port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater1.port++;
        BSA3.port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater1.port++;
        Repeater1.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA4.port++;
        BSA4.port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater2.port++;
        Repeater2.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA5.port++;
        Repeater2.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA6.port++;
        Repeater2.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA7.port++;
        BSA5.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode4.port++;
        BSA6.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode5.port++;
        BSA7.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode6.port++;

        EndNode1.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA1.quantum_port++;
        EndNode2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA2.quantum_port++;
        EndNode3.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA3.quantum_port++;
        BSA1.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> Repeater1.quantum_port++;
        BSA2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> Repeater1.quantum_port++;
        BSA3.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> Repeater1.quantum_port++;
        Repeater1.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA4.quantum_port++;
        BSA4.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> Repeater2.quantum_port++;
        Repeater2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA5.quantum_port++;
        Repeater2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA6.quantum_port++;
        Repeater2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA7.quantum_port++;
        BSA5.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode4.quantum_port++;
        BSA6.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode5.quantum_port++;
        BSA7.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode6.quantum_port++;

}
