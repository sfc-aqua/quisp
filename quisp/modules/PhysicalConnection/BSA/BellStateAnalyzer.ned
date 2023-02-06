package modules.PhysicalConnection.BSA;
@namespace(quisp::modules);

simple BellStateAnalyzer
{
    parameters:
        double collection_efficiency = default(1);
        double darkcount_probability = default(0);
        double detection_efficiency = default(1);
        double indistinguishable_time_window @unit(ns) = default(1.5ns); // Precision of photon arrivial time ~1.5ns
        int photon_detection_per_second = default(1000000);
    gates:
        inout quantum_port[];
        output to_bsa_controller;
}
