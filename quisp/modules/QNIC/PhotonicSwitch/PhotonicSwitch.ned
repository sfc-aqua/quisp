package modules.QNIC.PhotonicSwitch;

simple PhotonicSwitch
{
    parameters:
        int address;
    gates:
        inout toQNIC_quantum_port;
        //input toQNIC_quantum_port_i;
        //output toQNIC_quantum_port_o;
        inout toqubit_quantum_port[] @loose;
        //inout dummy_qnic_link;
        //input toqubit_quantum_port_i[];
        //output toqubit_quantum_port_o[];

}