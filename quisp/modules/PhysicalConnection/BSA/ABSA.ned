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
        @signal[Num_Bell_state](type="int");
        @statistic[Num_Bell_state](title="actual number of resource"; record=vector, max; interpolationmode=sample-hold);

        @signal[num_trial](type="int");
        @statistic[num_trial](title="The average number of BSA trials to generate one Bell pair"; record=vector, mean; interpolationmode=sample-hold);

        int degree = 2;
        string bsa_parf_output_filename = default("bsa_default");
    gates:
        inout fromABSA_quantum_port[];
        output toABSAController_port;
}