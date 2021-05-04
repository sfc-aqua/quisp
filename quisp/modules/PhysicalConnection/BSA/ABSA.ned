package modules.PhysicalConnection.BSA;

simple ABSA
{
    parameters:
        double darkcount_probability = default(0);
        double loss_rate = default(0);
        double error_rate = default(0);
        double duration = default(0);
        double required_precision = default(1.5e-9);
        int photon_detection_per_sec = default(10000);
        int address;

        int degree = 2;
        string absa_parf_output_filename = default("absa_default");
    gates:
        inout fromABSA_quantum_port[];
        output toABSAController_port;
}