package modules.PhysicalConnection.EPPS;
@namespace(quisp::modules);

simple EPPSController
{
parameters:
    //TODO: rename frequency to something more understandable
    double frequency = default(1000000);
    double initial_notification_timing_buffer @unit(s) = default(0s);
gates:
    input from_router;
    output to_router;
}
