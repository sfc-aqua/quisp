package networks;

import modules.*;
import channels.*;
import ned.IdealChannel;
import ned.DatarateChannel;
import modules.Backend.Backend;
import modules.Logger.Logger;

// this network topology is taken from Figure 7.4 from Aparicio's Master thesis (https://aqua.sfc.wide.ad.jp/publications/Aparicio-master-thesis.pdf)
// For the MIM link, the distance between one hop is the same as mentioned in the thesis but the probability of getting a Bell pair
// is higher due to BSA at the middle.

// this is exactly as mentioned in the thesis
network aparicio_MM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
    submodules:
        backend: Backend;
        logger: Logger;
        EndNodeA: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=107,159");
        }
        EndNodeB: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP;p=107,234");
        }
        EndNodeC: QNode {
            address = 3;
            node_type = "EndNode";
            @display("i=COMP;p=107,318");
        }
        EndNodeD: QNode {
            address = 4;
            node_type = "EndNode";
            @display("i=COMP;p=107,400");
        }
        RouterE: QNode {
            address = 5;
            node_type = "Router";
            @display("i=RTR;p=287,279");
        }
        RouterF: QNode {
            address = 6;
            node_type = "Router";
            @display("i=RTR;p=496,279");
        }
        EndNodeG: QNode {
            address = 7;
            node_type = "EndNode";
            @display("i=COMP;p=387,364");
        }
        EndNodeH: QNode {
            address = 8;
            node_type = "EndNode";
            @display("i=COMP;p=558,377");
        }
        EndNodeI: QNode {
            address = 9;
            node_type = "EndNode";
            @display("i=COMP;p=655,325");
        }
        RouterJ: QNode {
            address = 10;
            node_type = "Router";
            @display("i=RTR;p=605,186");
        }
        EndNodeK: QNode {
            address = 11;
            node_type = "EndNode";
            @display("i=COMP;p=686,61");
        }
        EndNodeL: QNode {
            address = 12;
            node_type = "EndNode";
            @display("i=COMP;p=760,110");
        }
        EndNodeM: QNode {
            address = 13;
            node_type = "EndNode";
            @display("i=COMP;p=760,186");
        }

    connections:
        // classical channels
        EndNodeA.port++ <--> ClassicalChannel {  distance = 20km; } <--> RouterE.port++;
        EndNodeB.port++ <--> ClassicalChannel {  distance = 20km; } <--> RouterE.port++;
        EndNodeC.port++ <--> ClassicalChannel {  distance = 20km; } <--> RouterE.port++;
        EndNodeD.port++ <--> ClassicalChannel {  distance = 20km; } <--> RouterE.port++;

        RouterE.port++ <--> ClassicalChannel {  distance = 20km; } <--> RouterF.port++;

        RouterF.port++ <--> ClassicalChannel {  distance = 20km; } <--> EndNodeG.port++;
        RouterF.port++ <--> ClassicalChannel {  distance = 20km; } <--> EndNodeH.port++;
        RouterF.port++ <--> ClassicalChannel {  distance = 20km; } <--> EndNodeI.port++;
        RouterF.port++ <--> ClassicalChannel {  distance = 20km; } <--> RouterJ.port++;

        RouterJ.port++ <--> ClassicalChannel {  distance = 20km; } <--> EndNodeK.port++;
        RouterJ.port++ <--> ClassicalChannel {  distance = 20km; } <--> EndNodeL.port++;
        RouterJ.port++ <--> ClassicalChannel {  distance = 20km; } <--> EndNodeM.port++;

        // quantum channels
        EndNodeA.quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> RouterE.quantum_port_receiver++;
        EndNodeB.quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> RouterE.quantum_port_receiver++;
        EndNodeC.quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> RouterE.quantum_port_receiver++;
        EndNodeD.quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> RouterE.quantum_port_receiver++;

        RouterF.quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> RouterE.quantum_port_receiver++;
        RouterF.quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> EndNodeG.quantum_port_receiver++;
        RouterF.quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> EndNodeH.quantum_port_receiver++;
        RouterF.quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> EndNodeI.quantum_port_receiver++;
        RouterF.quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> RouterJ.quantum_port_receiver++;

        RouterJ.quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> EndNodeK.quantum_port_receiver++;
        RouterJ.quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> EndNodeL.quantum_port_receiver++;
        RouterJ.quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> EndNodeM.quantum_port_receiver++;
}

// MIM version while preserving one hop distance (BSA in the middle changes link-probability)
network aparicio_MIM
{
    parameters:
        **.speed_of_light_in_fiber = 205336.986301 km;
    submodules:
        backend: Backend;
        logger: Logger;
        EndNodeA: QNode {
            address = 1;
            node_type = "EndNode";
            @display("i=COMP;p=107,159");
        }
        EndNodeB: QNode {
            address = 2;
            node_type = "EndNode";
            @display("i=COMP;p=107,234");
        }
        EndNodeC: QNode {
            address = 3;
            node_type = "EndNode";
            @display("i=COMP;p=107,318");
        }
        EndNodeD: QNode {
            address = 4;
            node_type = "EndNode";
            @display("i=COMP;p=107,400");
        }
        RouterE: QNode {
            address = 5;
            node_type = "Router";
            @display("i=RTR;p=287,279");
        }
        RouterF: QNode {
            address = 6;
            node_type = "Router";
            @display("i=RTR;p=496,279");
        }
        EndNodeG: QNode {
            address = 7;
            node_type = "EndNode";
            @display("i=COMP;p=387,364");
        }
        EndNodeH: QNode {
            address = 8;
            node_type = "EndNode";
            @display("i=COMP;p=558,377");
        }
        EndNodeI: QNode {
            address = 9;
            node_type = "EndNode";
            @display("i=COMP;p=655,325");
        }
        RouterJ: QNode {
            address = 10;
            node_type = "Router";
            @display("i=RTR;p=605,186");
        }
        EndNodeK: QNode {
            address = 11;
            node_type = "EndNode";
            @display("i=COMP;p=686,61");
        }
        EndNodeL: QNode {
            address = 12;
            node_type = "EndNode";
            @display("i=COMP;p=760,110");
        }
        EndNodeM: QNode {
            address = 13;
            node_type = "EndNode";
            @display("i=COMP;p=760,186");
        }
        BSANode0: BSA {
            address = 100;
            node_type = "BSA";
            @display("i=BSA");
        }
        BSANode1: BSA {
            address = 101;
            node_type = "BSA";
            @display("i=BSA");
        }
        BSANode2: BSA {
            address = 102;
            node_type = "BSA";
            @display("i=BSA");
        }
        BSANode3: BSA {
            address = 103;
            node_type = "BSA";
            @display("i=BSA");
        }
        BSANode4: BSA {
            address = 104;
            node_type = "BSA";
            @display("i=BSA");
        }
        BSANode5: BSA {
            address = 105;
            node_type = "BSA";
            @display("i=BSA");
        }
        BSANode6: BSA {
            address = 106;
            node_type = "BSA";
            @display("i=BSA");
        }
        BSANode7: BSA {
            address = 107;
            node_type = "BSA";
            @display("i=BSA");
        }
        BSANode8: BSA {
            address = 108;
            node_type = "BSA";
            @display("i=BSA");
        }
        BSANode9: BSA {
            address = 109;
            node_type = "BSA";
            @display("i=BSA");
        }
        BSANode10: BSA {
            address = 110;
            node_type = "BSA";
            @display("i=BSA");
        }
        BSANode11: BSA {
            address = 111;
            node_type = "BSA";
            @display("i=BSA");
        }
    connections:
        // classical channels
        // QNode to BSA
        EndNodeA.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSANode0.port++;
        EndNodeB.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSANode1.port++;
        EndNodeC.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSANode2.port++;
        EndNodeD.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSANode3.port++;

        RouterE.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSANode4.port++;

        RouterF.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSANode5.port++;
        RouterF.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSANode6.port++;
        RouterF.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSANode7.port++;
        RouterF.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSANode8.port++;

        RouterJ.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSANode9.port++;
        RouterJ.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSANode10.port++;
        RouterJ.port++ <--> ClassicalChannel {  distance = 10km; } <--> BSANode11.port++;

        // BSA to QNode channels
        BSANode0.port++ <--> ClassicalChannel {  distance = 10km; } <--> RouterE.port++;
        BSANode1.port++ <--> ClassicalChannel {  distance = 10km; } <--> RouterE.port++;
        BSANode2.port++ <--> ClassicalChannel {  distance = 10km; } <--> RouterE.port++;
        BSANode3.port++ <--> ClassicalChannel {  distance = 10km; } <--> RouterE.port++;

        BSANode4.port++ <--> ClassicalChannel {  distance = 10km; } <--> RouterF.port++;

        BSANode5.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNodeG.port++;
        BSANode6.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNodeH.port++;
        BSANode7.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNodeI.port++;
        BSANode8.port++ <--> ClassicalChannel {  distance = 10km; } <--> RouterJ.port++;

        BSANode9.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNodeK.port++;
        BSANode10.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNodeL.port++;
        BSANode11.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNodeM.port++;

        // quantum channels
        EndNodeA.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSANode0.quantum_port++;
        EndNodeB.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSANode1.quantum_port++;
        EndNodeC.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSANode2.quantum_port++;
        EndNodeD.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSANode3.quantum_port++;

        RouterE.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSANode4.quantum_port++;

        RouterF.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSANode5.quantum_port++;
        RouterF.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSANode6.quantum_port++;
        RouterF.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSANode7.quantum_port++;
        RouterF.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSANode8.quantum_port++;

        RouterJ.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSANode9.quantum_port++;
        RouterJ.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSANode10.quantum_port++;
        RouterJ.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSANode11.quantum_port++;

        // BSA to QNode channels
        BSANode0.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> RouterE.quantum_port++;
        BSANode1.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> RouterE.quantum_port++;
        BSANode2.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> RouterE.quantum_port++;
        BSANode3.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> RouterE.quantum_port++;

        BSANode4.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> RouterF.quantum_port++;

        BSANode5.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNodeG.quantum_port++;
        BSANode6.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNodeH.quantum_port++;
        BSANode7.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNodeI.quantum_port++;
        BSANode8.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> RouterJ.quantum_port++;

        BSANode9.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNodeK.quantum_port++;
        BSANode10.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNodeL.quantum_port++;
        BSANode11.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNodeM.quantum_port++;
}
