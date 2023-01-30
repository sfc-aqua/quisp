package modules.QNIC.PhotonicSwitch;
@namespace(quisp::modules);

simple PhotonicSwitch
{
    parameters:
        int address;
    gates:
        output to_bsa;
        input from_emitters[] @loose;
}
