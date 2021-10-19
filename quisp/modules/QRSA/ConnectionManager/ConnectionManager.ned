package modules.QRSA.ConnectionManager;
simple ConnectionManager
{
    parameters:
        int address;
        int number_of_qnics;
        int number_of_qnics_r;
        int number_of_qnics_rp;
        int total_number_of_qnics;
        int num_remote_purification = default(1);
        bool simultaneous_es_enabled = default(false);
        bool entanglement_swapping_with_purification = default(false);

    gates:
        inout RouterPort;
}


