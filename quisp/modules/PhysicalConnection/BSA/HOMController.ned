package modules.PhysicalConnection.BSA;
@namespace(quisp::modules);

simple HOMController
{
    parameters:
        int address;
        volatile double Speed_of_light_in_fiber @unit(km);//per sec
        int photon_detection_per_sec = default(10000);
        double Initial_notification_timing_buffer @unit(s) = default(0s);
        //rate can be up to 1 billion photons per second by default
        //interval will be 1photon/ns
        int neighbor_address @mutable = default(-1);
        int neighbor_address_two @mutable = default(-1);
        double distance_to_neighbor @mutable = default(-1);//in km
        double distance_to_neighbor_two @mutable = default(-1);//in km
        double max_neighbor_distance @mutable = default(-1);
        int max_buffer @mutable = default(-1);
        double emission_variance = default(0);//in seconds. Photons will be shot towards HOM with 100% accuracy
        bool receiver = default(false);
        bool passive = default(false);
        double bsa_notification_interval = default(1e-2);

        // performance
        @signal[creation_time](type=double);
        @statistic[creation_time](title="Bell pair creation time"; record=vector; interpolationmode=sample-hold);
    gates:
        input fromRouter_port @loose;
        output toRouter_port @loose;
        input fromBSA_port @loose;
}
