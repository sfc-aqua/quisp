package modules.Common;
@namespace(quisp::modules);

simple Router
{
    parameters:
        @display("i=block/routing");
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
