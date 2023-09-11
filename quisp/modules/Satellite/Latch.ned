//Latch: When the CTRL signal is OPEN, this module is transparent. When it is CLOSED, the module stores all
// messages and relays them when CTRL is OPEN again. 

package modules.Satellite;
import ned.DelayChannel;
@namespace(quisp::modules::Satellite);

simple Latch {
    parameters:
        int address = default(0);
    gates:
        input in;
        input ctrl;
        output out;
}
