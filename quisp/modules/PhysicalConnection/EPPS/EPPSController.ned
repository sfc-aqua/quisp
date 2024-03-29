package modules.PhysicalConnection.EPPS;
@namespace(quisp::modules);

simple EPPSController
{
parameters:
    double max_photon_emission_per_second = default(1000000);
    double initial_notification_timing_buffer @unit(s) = default(0s);
    bool adaptive_epps = default(false);
    int replacing_address = default(0);
gates:
    input from_router;
    output to_router;
}
