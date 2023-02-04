package modules.QNIC.PhotonicSwitch;
@namespace(quisp::modules);

simple PhotonicSwitch
{
    parameters:
        int address;
    gates:
        inout to_bsa;
        input from_emitters[];
}
