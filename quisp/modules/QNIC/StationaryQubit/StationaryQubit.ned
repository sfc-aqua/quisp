package modules.QNIC.StationaryQubit;
@namespace(quisp::modules);

simple StationaryQubit
{
    parameters:
        // performance analysis
        // @signal[update_timing](type=double);
        // @statistic[update_timing](title="actual number of resource"; record=vector, max; interpolationmode=sample-hold);
        // these are configured at boot time
        int stationary_qubit_address;
        int node_address;
        int qnic_address;//Unique
        int qnic_type;
        int qnic_index;//Not unique

        // ZZZ -- these are volatile elements of the object (module) state
        // and should be private data members of the class object
        int x_position_graphics;		// can this be usefully set in a .ned file?
        double emission_jittering_standard_deviation = default(0);

        // ZZZ -- these are configured at boot time
        // characteristics of the hardware
        // could eventually change over time if we model dynamic
        // changes to the device
        double emission_success_probability = default(1);
        double emission_z_error_rate = default(0);// 1% per shot by default
        double emission_x_error_rate = default(0);
        double emission_y_error_rate = default(0);

        // ZZZ -- these are configured at boot time
        // characteristics of the hardware
        // could eventually change over time if we model dynamic
        // changes to the device
        double memory_z_error_rate = default(0);
        double memory_x_error_rate = default(0);
        double memory_y_error_rate = default(0);
        double memory_energy_excitation_rate = default(0);
        double memory_energy_relaxation_rate = default(0);
        double memory_completely_mixed_rate = default(0);

        // ZZZ -- these are configured at boot time
        // characteristics of the hardware
        // could eventually change over time if we model dynamic
        // changes to the device
        double h_gate_error_rate = default(0);
        double h_gate_x_error_ratio = default(1);
        double h_gate_y_error_ratio = default(1);
        double h_gate_z_error_ratio = default(1);

        // ZZZ -- these are configured at boot time
        // characteristics of the hardware
        // could eventually change over time if we model dynamic
        // changes to the device
        double x_gate_error_rate = default(0);
        double x_gate_x_error_ratio = default(1);
        double x_gate_y_error_ratio = default(1);
        double x_gate_z_error_ratio = default(1);

        // ZZZ -- these are configured at boot time
        // characteristics of the hardware
        // could eventually change over time if we model dynamic
        // changes to the device
        double z_gate_error_rate = default(0);
        double z_gate_x_error_ratio = default(1);
        double z_gate_y_error_ratio = default(1);
        double z_gate_z_error_ratio = default(1);

        // ZZZ -- these are configured at boot time
        // characteristics of the hardware
        // could eventually change over time if we model dynamic
        // changes to the device
        double cnot_gate_error_rate = default(0);
        double cnot_gate_iz_error_ratio = default(1);
        double cnot_gate_zi_error_ratio = default(1);
        double cnot_gate_zz_error_ratio = default(1);
        double cnot_gate_ix_error_ratio = default(1);
        double cnot_gate_xi_error_ratio = default(1);
        double cnot_gate_xx_error_ratio = default(1);
        double cnot_gate_iy_error_ratio = default(1);
        double cnot_gate_yi_error_ratio = default(1);
        double cnot_gate_yy_error_ratio = default(1);

        double x_measurement_error_rate = default(0);
        double y_measurement_error_rate = default(0);
        double z_measurement_error_rate = default(0);
        //int ruleset_id = default(-1);
        //int rule_id = default(-1);
        //int action_index = default(-1);
    gates:
        inout tolens_quantum_port;
}
