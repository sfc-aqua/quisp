package modules.PhysicalConnection.EPPS;
@namespace(quisp::modules);

simple EPPSController
{
parameters:
    int address;
    double frequency = default(1);
    double first_notification_timer = default(0);
gates:
    input from_router;
    output to_router;
}
