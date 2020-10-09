package networks;

simple StationaryQubit
{
    parameters:
        // performance analysis
        // @signal[update_timing](type="float");
        // @statistic[update_timing](title="actual number of resource"; record=vector, max; interpolationmode=sample-hold);
	// these are configured at boot time
        int stationaryQubit_address;
        int node_address;
        int qnic_address;//Unique
        int qnic_type;
        int qnic_index;//Not unique

	// ZZZ -- these are volatile elements of the object (module) state
	// and should be private data members of the class object
        int GOD_entangled_stationaryQubit_address = default(-1);
        int GOD_entangled_node_address = default(-1);
        int GOD_entangled_qnic_address = default(-1);
        int GOD_entangled_qnic_type = default(-1);

	// ZZZ -- these are volatile elements of the object (module) state
	// and should be private data members of the class object
        int xPosition_Graphics;		// can this be usefully set in a .ned file?
        double photon_emitted_at = default(-1);
        double last_updated_at = default(-1);
        bool isBusy = default(false);
        double std = default(0);

	// ZZZ -- this is a volatile element of the object (module) state
	// and should be private data member of the class object
	// n.b.: this should be _software's_ idea of what the fidelity is?
        double fidelity = default(-1.0);

	// ZZZ -- these are volatile elements of the object (module) state
	// and should be private data members of the class object
	// n.b.: these represent the _hardware_ state, and aren't directly
	// accessible to repeater software (qrsa)
        bool GOD_Xerror = false;//Physical error on qubit
        bool GOD_Zerror = false;//Physical error on qubit
        bool GOD_EXerror = false;//Physical error on qubit
        bool GOD_REerror = false;//Physical error on qubit
        bool GOD_CMerror = false;//Physical error on qubit

	// ZZZ -- these are configured at boot time
	// characteristics of the hardware
	// could eventually change over time if we model dynamic
	// changes to the device
        double emission_success_probability = default(1);
        double emission_Z_error_rate = default(0);// 1% per shot by default
        double emission_X_error_rate = default(0);
        double emission_Y_error_rate = default(0);

	// ZZZ -- these are configured at boot time
	// characteristics of the hardware
	// could eventually change over time if we model dynamic
	// changes to the device
        double memory_error_rate = default(0);// 10% per μs by default
        double memory_Z_error_ratio = default(1);
        double memory_X_error_ratio = default(1);
        double memory_Y_error_ratio = default(1);
        double memory_energy_excitation_ratio = default(1);
        double memory_energy_relaxation_ratio = default(1);
        double memory_completely_mixed_ratio = default(1);

	// ZZZ -- these are configured at boot time
	// characteristics of the hardware
	// could eventually change over time if we model dynamic
	// changes to the device
	double memory_Z_error_rate = default(0);
        double memory_X_error_rate = default(0);
        double memory_Y_error_rate = default(0);
        double memory_energy_excitation_rate = default(0);
        double memory_energy_relaxation_rate = default(0);
        double memory_completely_mixed_rate = default(0);

	// ZZZ -- these are configured at boot time
	// characteristics of the hardware
	// could eventually change over time if we model dynamic
	// changes to the device
        double Hgate_error_rate = default(0);
        double Hgate_X_error_ratio = default(1);
        double Hgate_Y_error_ratio = default(1);
        double Hgate_Z_error_ratio = default(1);

	// ZZZ -- these are configured at boot time
	// characteristics of the hardware
	// could eventually change over time if we model dynamic
	// changes to the device
        double Measurement_error_rate = default(0);
        double Measurement_X_error_ratio = default(1);
        double Measurement_Y_error_ratio = default(1);
        double Measurement_Z_error_ratio = default(1);

	// ZZZ -- these are configured at boot time
	// characteristics of the hardware
	// could eventually change over time if we model dynamic
	// changes to the device
        double Xgate_error_rate = default(0);
        double Xgate_X_error_ratio = default(1);
        double Xgate_Y_error_ratio = default(1);
        double Xgate_Z_error_ratio = default(1);

	// ZZZ -- these are configured at boot time
	// characteristics of the hardware
	// could eventually change over time if we model dynamic
	// changes to the device
        double Zgate_error_rate = default(0);
        double Zgate_X_error_ratio = default(1);
        double Zgate_Y_error_ratio = default(1);
        double Zgate_Z_error_ratio = default(1);

	// ZZZ -- these are configured at boot time
	// characteristics of the hardware
	// could eventually change over time if we model dynamic
	// changes to the device
        double CNOTgate_error_rate = default(0);
        double CNOTgate_IZ_error_ratio = default(1);
        double CNOTgate_ZI_error_ratio = default(1);
        double CNOTgate_ZZ_error_ratio = default(1);
        double CNOTgate_IX_error_ratio = default(1);
        double CNOTgate_XI_error_ratio = default(1);
        double CNOTgate_XX_error_ratio = default(1);
        double CNOTgate_IY_error_ratio = default(1);
        double CNOTgate_YI_error_ratio = default(1);
        double CNOTgate_YY_error_ratio = default(1);

        //int ruleset_id = default(-1);
        //int rule_id = default(-1);
        //int action_index = default(-1);


    gates:
        inout tolens_quantum_port;
}

simple PhotonicSwitch
{
    parameters:
        int address;
    gates:
        inout toQNIC_quantum_port;
        //input toQNIC_quantum_port_i;
        //output toQNIC_quantum_port_o;
        inout toqubit_quantum_port[] @loose;
        //inout dummy_qnic_link;
        //input toqubit_quantum_port_i[];
        //output toqubit_quantum_port_o[];

}


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
            @display("t=Id $stationaryQubit_address;i=block/circle,blue;"); // modify display string
            std = emission_std;
        }
        lens: PhotonicSwitch {
            address = self_qnic_address;
            @display("i=block/dispatch;");
        }

        internal_hom: interHoM if receiver {
            address = parent_node_address;
            passive = passive;
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
