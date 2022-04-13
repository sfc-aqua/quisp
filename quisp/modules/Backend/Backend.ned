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
        double memory_Z_error_ratio = default(1);
        double memory_X_error_ratio = default(1);
        double memory_Y_error_ratio = default(1);
        double memory_energy_excitation_ratio = default(1);
        double memory_energy_relaxation_ratio = default(1);
        double memory_completely_mixed_ratio = default(1);

        double memory_Z_error_rate = default(0);
        double memory_X_error_rate = default(0);
        double memory_Y_error_rate = default(0);
        double memory_energy_excitation_rate = default(0);
        double memory_energy_relaxation_rate = default(0);
        double memory_completely_mixed_rate = default(0);

        double Hgate_error_rate = default(0);
        double Hgate_X_error_ratio = default(1);
        double Hgate_Y_error_ratio = default(1);
        double Hgate_Z_error_ratio = default(1);

        double Xgate_error_rate = default(0);
        double Xgate_X_error_ratio = default(1);
        double Xgate_Y_error_ratio = default(1);
        double Xgate_Z_error_ratio = default(1);

        double Zgate_error_rate = default(1);
        double Zgate_X_error_ratio = default(1);
        double Zgate_Y_error_ratio = default(1);
        double Zgate_Z_error_ratio = default(1);

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
}
