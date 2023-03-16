package modules.PhysicalConnection.EPPS;
@namespace(quisp::modules);

simple EntangledPhotonPairSource
{
    parameters:
        double emission_jittering_standard_deviation = default(0);
        double emission_success_probability = default(1);
        double emission_x_error_rate = default(0);
        double emission_y_error_rate = default(0);
        double emission_z_error_rate = default(0);
    gates:
        inout quantum_port[];
}
