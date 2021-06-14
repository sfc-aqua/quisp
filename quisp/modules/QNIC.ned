package modules;

import modules.QNIC.StationaryQubit.*;
import modules.QNIC.PhotonicSwitch.*;
import modules.HoM;
import modules.interHoM;

module QNIC
{
    parameters:
        int numBuffer = default(7);
        int self_qnic_address;//Buffer identifier/address
        int self_qnic_index;
        int parent_node_address;
        int neighbor_node_address = default(-1);
        //int neighbor_qnode_address = default(-1);
        int self_qnic_type;
        bool receiver = default(false);
        double emission_std = default(0);
        bool passive = default(false);
        @display("bgb=612,194");
        int burst_trial_counter = default(0);

        bool is_reserved = default(false);

    gates:
        inout qnic_quantum_port @loose;//One quantum port for every qnic in a node
        output toParentRouter @loose;//If not used, this still needs to be connected somewhere!!
        //inout dummyRoutingDaemonLink @loose;

    submodules:
        statQubit[numBuffer]: StationaryQubit {
            stationaryQubit_address = index;
            node_address = parent_node_address;
            qnic_address = self_qnic_address;
            qnic_index = self_qnic_index;
            qnic_type = self_qnic_type;
            xPosition_Graphics = 70 + 65*index;  // use submodule index to generate different IDs
            //@display("p=$xPosition_Graphics,40,,circle");
            @display("t=Id $stationaryQubit_address;i=block/circle,blue;p=150,100,m,5,60,60"); // modify display string
            std = emission_std;
        }
        lens: PhotonicSwitch {
            address = self_qnic_address;
            @display("i=block/dispatch;p=75.240005,117.810005");
        }

        internal_hom: interHoM if receiver {
            address = parent_node_address;
            passive = passive;
            @display("p=177.21,39.600002");
        }

        gate_closer: dummyModule if !receiver;
    connections:
        for i=0..numBuffer-1 {
            lens.toqubit_quantum_port++ <--> statQubit[i].tolens_quantum_port; //Put QuantumChannel_internal here if wanted
        }
        //If no HoM is inside the node
        qnic_quantum_port <--> lens.toQNIC_quantum_port if !receiver;
        toParentRouter <-- gate_closer.close_output if !receiver;//Seal the unused gate. Otherwise, this causes an error.
        //If an HoM is inside the node
        internal_hom.quantum_port++ <--> lens.toQNIC_quantum_port if receiver;//Also, put QuantumChannel_internal here if wanted
        internal_hom.quantum_port++ <--> qnic_quantum_port if receiver;
        internal_hom.toRouter --> toParentRouter if receiver;
        //dummyRoutingDaemonLink <--> lens.dummy_qnic_link;

}
