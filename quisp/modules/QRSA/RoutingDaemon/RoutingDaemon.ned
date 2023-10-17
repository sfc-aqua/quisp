package modules.QRSA.RoutingDaemon;
@namespace(quisp::modules::routing_daemon);

simple RoutingDaemon
{
    parameters:
        bool run_ospf = default(true);
        int number_of_qnics;
        int number_of_qnics_r;
        int number_of_qnics_rp;
    gates:
        inout RouterPort @loose;
}

