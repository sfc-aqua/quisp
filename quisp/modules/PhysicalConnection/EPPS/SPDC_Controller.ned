simple SPDC_Controller
{
    parameters:
        int address;
        int neighbor_address = default(-1);
        int neighbor_address_two = default(-1);
        int neighbor_buffer = default(-1);
        int neighbor_buffer_two = default(-1);
        int max_buffer = default(-1);
        double distance_to_neighbor = default(-1);//in km
        double distance_to_neighbor_two = default(-1);//in km
        double max_neighbor_distance = default(-1);//in km
        double accepted_burst_interval = default(-1);//in s
        double Speed_of_light_in_fiber @unit(km);
        double timing_buffer = default(1e-9);
        double frequency = default(-1);
    gates:
        input fromRouter_port;
        output toRouter_port;
        inout toPairSource_port;
}