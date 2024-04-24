package modules.QRSA.ConnectionManager;
@namespace(quisp::modules);

simple ConnectionManager
{
    parameters:
        int number_of_qnics;
        int number_of_qnics_r;
        int number_of_qnics_rp;
        int total_number_of_qnics;
        int num_remote_purification = default(1);
        bool simultaneous_es_enabled = default(false);
        string purification_type_cm = default("SINGLE_SELECTION_X_PURIFICATION");
        double threshold_fidelity = default(0);
        int seed_cm = default(0);

    gates:
        inout RouterPort;
}


