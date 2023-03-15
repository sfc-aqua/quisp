package modules.PhysicalConnection.EPPS;
@namespace(quisp::modules);

simple EPPSController
{
parameters:
    int address;
    double frequency = default(1);
    double initial_notification_timing_buffer @unit(s) = default(0s);
gates:
    input from_router;
    output to_router;
}
