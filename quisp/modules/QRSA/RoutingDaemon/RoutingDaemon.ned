package modules.QRSA.RoutingDaemon;
@namespace(quisp::modules::routing_daemon);

simple RoutingDaemon
{
    parameters:
        bool run_ospf = default(false);
    gates:
        inout RouterPort @loose;
}

