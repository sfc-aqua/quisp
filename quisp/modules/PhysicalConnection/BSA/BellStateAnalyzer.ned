package modules.PhysicalConnection.BSA;
@namespace(quisp::modules);

simple BellStateAnalyzer
{
    parameters:
        double collection_efficiency = default(1);
        double darkcount_probability = default(0);
        double detection_efficiency = default(1);
        double indistinguishability_window = default(1.5e-9); // Precision of photon arrivial time ~1.5ns
        int photon_detection_per_second = default(10000);
        // TODO: do something this with detection per sec
    gates:
        input quantum_port[];
        output to_bsa_controller;
}
