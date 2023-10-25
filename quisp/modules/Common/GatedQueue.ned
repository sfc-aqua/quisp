
package modules.Common;

simple GatedQueue extends Queue
{
    @class(GatedQueue);
    gates:
        input from_vc;
        output to_vc;
}
