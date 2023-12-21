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
        @signal[clicks_in_batch](type=long);
        @statistic[clicks_in_batch](record=vector,sum);
        @signal[no_click](type=long);
        @statistic[no_click](record=vector,sum);
        @signal[dist](type=long);
        @statistic[dist](record=vector,sum);
        @signal[p_arrived](type=long);
        @statistic[p_arrived](record=vector,sum);
        @signal[q_arrived](type=long);
        @statistic[q_arrived](record=vector,sum);
    gates:
        inout quantum_port[];
        output to_bsa_controller;
}
