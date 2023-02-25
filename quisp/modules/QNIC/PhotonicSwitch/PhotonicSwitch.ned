package modules.QNIC.PhotonicSwitch;
@namespace(quisp::modules);

simple PhotonicSwitch
{
    parameters:
    gates:
        inout to_bsa;
        input from_emitters[];
}
