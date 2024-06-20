package modules.Common;
@namespace(quisp::modules);

simple GatedQueue extends Queue
{
    @class(GatedQueue);
    gates:
        input from_ps;
        output to_ps;
}
