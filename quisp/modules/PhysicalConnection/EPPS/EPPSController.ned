package modules.PhysicalConnection.EPPS;
@namespace(quisp::modules);

simple EPPSController
{
parameters:
    int address;
    double frequency = default(1);
    double timing_buffer = default(0);
gates:
    input from_router;
    output to_router;
    output to_epps;
}
