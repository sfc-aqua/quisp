//Simple module for one-to-many fanout, i.e. input a message in one port, output N copies.

package modules.Satellite;

simple Fanout
{
    parameters:
    gates:
        input in @loose;
        output out[];
}
