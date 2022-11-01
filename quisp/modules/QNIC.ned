package modules;
@namespace(quisp::modules);

import modules.QNIC.StationaryQubit.*;
import modules.QNIC.PhotonicSwitch.*;
import modules.HOM;
import modules.interHOM;

module QNIC
{
    parameters:

        int numBuffer = default(7);

        int self_qnic_address;//Buffer identifier/address
        int self_qnic_index;
        int parent_node_address;
        int neighbor_node_address @mutable = default(-1);
        //int neighbor_qnode_address = default(-1);
        int self_qnic_type;
        bool receiver = default(false);
        double emission_std = default(0);
        bool passive = default(false);
        @display("bgb=654.39,1687.06006");
        int burst_trial_counter @mutable = default(0);

        bool is_reserved @mutable = default(false);

    gates:
        inout qnic_quantum_port @loose;//One quantum port for every qnic in a node
        output toParentRouter @loose;//If not used, this still needs to be connected somewhere!!
        //inout dummyRoutingDaemonLink @loose;

    submodules:
        statQubit[numBuffer]: StationaryQubit {
            stationaryQubit_address = index;
            node_address = parent.parent_node_address;
            qnic_address = parent.self_qnic_address;
            qnic_index = parent.self_qnic_index;
            qnic_type = parent.self_qnic_type;
            xPosition_Graphics = 70 + 80*index;  // use submodule index to generate different IDs
            //@display("p=$xPosition_Graphics,40,,circle");
            @display("t=Id $stationaryQubit_address;i=block/circle,blue;p=150,100,m,5,60,60"); // modify display string
            std = parent.emission_std;
        }

        lens: PhotonicSwitch {
            address = parent.self_qnic_address;
            @display("i=block/dispatch;p=75.240005,117.810005");
        }

        internal_hom: interHOM if receiver {
            address = parent.parent_node_address;
            passive = parent.passive;
            @display("p=177.21,39.600002");
        }

        gate_closer: dummyModule if !receiver;
    connections:
        for i=0..numBuffer-1 {
            lens.toqubit_quantum_port++ <--> statQubit[i].tolens_quantum_port; //Put QuantumChannel_internal here if wanted
        }
        //If no HOM is inside the node
        qnic_quantum_port <--> lens.toQNIC_quantum_port if !receiver;
        toParentRouter <-- gate_closer.close_output if !receiver;//Seal the unused gate. Otherwise, this causes an error.
        //If an HOM is inside the node
        internal_hom.quantum_port++ <--> lens.toQNIC_quantum_port if receiver;//Also, put QuantumChannel_internal here if wanted
        internal_hom.quantum_port++ <--> qnic_quantum_port if receiver;
        internal_hom.toRouter --> toParentRouter if receiver;
        //dummyRoutingDaemonLink <--> lens.dummy_qnic_link;

}
