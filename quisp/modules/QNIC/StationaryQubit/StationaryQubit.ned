package modules.QNIC.StationaryQubit;
@namespace(quisp::modules);

simple StationaryQubit
{
    parameters:
        // performance analysis
        // @signal[update_timing](type=double);
        // @statistic[update_timing](title="actual number of resource"; record=vector, max; interpolationmode=sample-hold);
        // these are configured at boot time
        int stationaryQubit_address;
        int node_address;
        int qnic_address;//Unique
        int qnic_type;
        int qnic_index;//Not unique

        // ZZZ -- these are volatile elements of the object (module) state
        // and should be private data members of the class object
        int GOD_entangled_stationaryQubit_address @mutable = default(-1);
        int GOD_entangled_node_address @mutable = default(-1);
        int GOD_entangled_qnic_address @mutable = default(-1);
        int GOD_entangled_qnic_type @mutable = default(-1);

        // ZZZ -- these are volatile elements of the object (module) state
        // and should be private data members of the class object
        int xPosition_Graphics;		// can this be usefully set in a .ned file?
        double photon_emitted_at @mutable = default(-1);
        double last_updated_at @mutable = default(-1);
        bool isBusy @mutable = default(false);
        double std @mutable = default(0);

        // ZZZ -- this is a volatile element of the object (module) state
        // and should be private data member of the class object
        // n.b.: this should be _software's_ idea of what the fidelity is?
        double fidelity @mutable = default(-1.0);

        // ZZZ -- these are volatile elements of the object (module) state
        // and should be private data members of the class object
        // n.b.: these represent the _hardware_ state, and aren't directly
        // accessible to repeater software (qrsa)
        bool GOD_Xerror @mutable = false;//Physical error on qubit
        bool GOD_Zerror @mutable = false;//Physical error on qubit
        bool GOD_EXerror @mutable = false;//Physical error on qubit
        bool GOD_REerror @mutable = false;//Physical error on qubit
        bool GOD_CMerror @mutable = false;//Physical error on qubit

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

        double X_measurement_error_rate = default(0);
        double Y_measurement_error_rate = default(0);
        double Z_measurement_error_rate = default(0);
        //int ruleset_id = default(-1);
        //int rule_id = default(-1);
        //int action_index = default(-1);
    gates:
        inout tolens_quantum_port;
}
