package modules;
@namespace(quisp::modules);

import modules.QNIC.StationaryQubit.*;
import modules.QNIC.PhotonicSwitch.*;
import modules.BSANode;
import modules.PhysicalConnection.BSA.*;

module QNIC
{
    parameters:
        int num_buffer = default(7);
        int self_qnic_address; // Buffer identifier/address
        int self_qnic_index;
        int parent_node_address;
        int neighbor_node_address @mutable = default(-1);
        int self_qnic_type;
        bool receiver = default(false);
        double emission_std = default(0);
        bool passive = default(false);
        @display("bgb=654.39,1687.06006");
        int burst_trial_counter @mutable = default(0);

    gates:
        output to_parent_router @loose; // Even if it is not used. Internally it's still need to be connected
        inout qnic_quantum_port @loose; // One quantum port for every qnic in a node;
                                        // input - if BSA is inside
                                        // output - if BSA is outside

    submodules:
        statQubit[num_buffer]: StationaryQubit {
            stationary_qubit_address = index;
            node_address = parent.parent_node_address;
            qnic_address = parent.self_qnic_address;
            qnic_index = parent.self_qnic_index;
            qnic_type = parent.self_qnic_type;
            x_position_graphics = 70 + 80*index;  // use submodule index to generate different IDs
            @display("t=Id $stationary_qubit_address;i=block/circle,blue;p=270.56,209.684,m,5,60,60"); // modify display string
            emission_jittering_standard_deviation = parent.emission_std;
        }

        lens: PhotonicSwitch {
            @display("i=block/dispatch;p=206.302,825.208");
        }

        bsa: BellStateAnalyzer if receiver {
            @display("p=436.278,487.008");
        }

        bsa_controller: BSAController if receiver && !passive {
            mode = "active";
            @display("p=466.716,798.152");
        }

        bsa_controller_passive: BSAController if receiver && passive {
            mode = "passive";
            @display("p=466.716,794.77");
        }

        gate_closer: dummyModule;

    connections:
        for i=0..num_buffer-1 {
            lens.from_emitters++ <-- statQubit[i].tolens_quantum_port;
        }
        // if qnic is qnic_emitter
        qnic_quantum_port <--> lens.to_bsa if !receiver;
        to_parent_router <-- gate_closer.close_output if !receiver;

        // if qnic is qnic_receiver
        bsa.quantum_port++ <--> lens.to_bsa if receiver;
        bsa.quantum_port++ <--> qnic_quantum_port if receiver;
        bsa.to_bsa_controller --> bsa_controller.from_bsa if receiver && !passive;
        bsa_controller.to_router --> to_parent_router if receiver && !passive;
        bsa_controller.from_router <-- gate_closer.close_output if receiver && !passive;

        // if qnic is qnic_receiver_passive
        bsa.to_bsa_controller --> bsa_controller_passive.from_bsa if receiver && passive;
        bsa_controller_passive.to_router --> to_parent_router if receiver && passive;
        bsa_controller_passive.from_router <-- gate_closer.close_output if receiver && passive;
}
