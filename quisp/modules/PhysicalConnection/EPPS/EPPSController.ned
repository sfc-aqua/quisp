package modules.PhysicalConnection.EPPS;
@namespace(quisp::modules);

simple EPPSController
{
    parameters:
        double initial_notification_timing_buffer @unit(s) = default(0s);
        string mode = default("active");
    gates:
        input from_bsa;
        input from_router;
        output to_router;
}