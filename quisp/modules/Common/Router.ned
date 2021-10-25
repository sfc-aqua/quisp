package modules.Common;
@namespace(quisp::modules);

simple Router
{
    parameters:
        int address;
        string classical_router_soft = "yes";
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

        input fromRuleSet @directIn;//A little bit cheating but why not.
}
