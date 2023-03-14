package modules.PhysicalConnection.EPPS;
@namespace(quisp::modules);

simple EPPSController
{
parameters:
    int address;
    double frequency = default(1);
    double timing_buffer = default(1);
gates:
    input from_router_port;
    output to_router_port;
    inout to_epps_port;
}
