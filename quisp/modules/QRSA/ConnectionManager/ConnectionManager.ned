package modules.QRSA.ConnectionManager;
simple ConnectionManager
{
    parameters:
        int address;
        int number_of_qnics;
        int number_of_qnics_r;
        int number_of_qnics_rp;
        int total_number_of_qnics;
        bool simultanious_ES;

    gates:
        inout RouterPort;
}


