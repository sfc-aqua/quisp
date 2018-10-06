package networks;

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


simple stationaryQubit
{
    parameters:
        int stationaryQubit_address;
        int node_address;
        int qnic_address;
        int qnic_type;
        
        int GOD_entangled_stationaryQubit_address = default(-1);
        int GOD_entangled_node_address = default(-1);
        int GOD_entangled_qnic_address = default(-1);
        int GOD_entangled_qnic_type = default(-1);
        
        int xPosition_Graphics;
        double photon_emitted_at = default(-1);
        double last_updated_at = default(-1);
        bool isBusy = default(false);
        double std = default(0);

        double fidelity = default(-1.0);
        
        bool GOD_Xerror = false;//Physical error on qubit
        bool GOD_Zerror = false;//Physical error on qubit
        bool GOD_EXerror = false;//Physical error on qubit
        bool GOD_REerror = false;//Physical error on qubit
        bool GOD_CMerror = false;//Physical error on qubit
        
        double emission_error_rate = default(0.01);// 1% per shot by default
        double emission_Z_error_ratio = default(1);
        double emission_X_error_ratio = default(1);
        double emission_Y_error_ratio = default(1);
        
        double memory_error_rate = default(0.1);// 10% per μs by default
        double memory_Z_error_ratio = default(1);
        double memory_X_error_ratio = default(1);
        double memory_Y_error_ratio = default(1);
        double memory_energy_excitation_ratio = default(1);
        double memory_energy_relaxation_ratio = default(1);
       
        
    gates:
        inout tolens_quantum_port;
}

simple QNIC_photonic_switch
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
        int self_qnic_address;//Buffer identifier/address
        int parent_node_address;
        int neighbor_node_address = default(-1);
        //int neighbor_qnode_address = default(-1);
        int numBuffer = default(7);
        int self_qnic_type;
        bool receiver = default(false);
        double emission_std = default(0);
        bool passive = default(false);
        @display("bgb=612,194");
        int burst_trial_counter = default(0);
        
    gates:
        inout qnic_quantum_port @loose;//One quantum port for every qnic in a node
        output toParentRouter @loose;//If not used, this still needs to be connected somewhere!!
        //inout dummyRoutingDaemonLink @loose;

    submodules:
        statQubit[numBuffer]: stationaryQubit {
            stationaryQubit_address = index;
            node_address = parent_node_address;
            qnic_address = self_qnic_address;
            qnic_type = self_qnic_type;
            xPosition_Graphics = 70 + 65*index;  // use submodule index to generate different IDs
            //@display("p=$xPosition_Graphics,40,,circle");
            @display("t=Id $stationaryQubit_address;i=block/circle,blue;"); // modify display string
            std = emission_std;
        }
        lens: QNIC_photonic_switch {
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
