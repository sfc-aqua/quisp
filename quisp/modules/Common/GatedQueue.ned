
package modules.Common;

simple GatedQueue extends Queue
{
    @class(GatedQueue);
    gates:
        input ctrl_in @loose;
}
