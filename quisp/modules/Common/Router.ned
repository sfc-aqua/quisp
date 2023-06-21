package modules.Common;
@namespace(quisp::modules);

simple Router
{
    parameters:
        @display("i=block/routing");
        bool run_ospf = default(true);
    gates:
        input fromQueue[];
        output toQueue[];
        input fromApp @loose;
        output toApp @loose;
        input fromQNIC[] @loose;
        inout rdPort @loose;
        inout cmPort @loose;
        inout rePort @loose;
        inout hmPort @loose;
}
