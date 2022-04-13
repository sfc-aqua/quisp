package modules.Backend;
@namespace(quisp::modules::backend);

simple Backend
{
    parameters:
        @class(BackendContainer);
        @display("p=30,40;");
        string backendType = default("ErrorTrackingBackend");

        // ErrorTracking Backend Configurations
        // characteristics of the hardware
        double memory_error_rate = default(0);
        double memory_z_error_rate = default(1);
        double memory_x_error_rate = default(1);
        double memory_y_error_rate = default(1);
        double memory_energy_excitation_rate = default(1);
        double memory_energy_relaxation_rate = default(1);
        double memory_completely_mixed_rate = default(1);

        double h_gate_error_rate = default(0);
        double h_gate_x_error_ratio = default(1);
        double h_gate_y_error_ratio = default(1);
        double h_gate_z_error_ratio = default(1);

        double x_gate_error_rate = default(0);
        double x_gate_x_error_ratio = default(1);
        double x_gate_y_error_ratio = default(1);
        double x_gate_z_error_ratio = default(1);

        double z_gate_error_rate = default(0);
        double z_gate_x_error_ratio = default(1);
        double z_gate_y_error_ratio = default(1);
        double z_gate_z_error_ratio = default(1);

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
}
