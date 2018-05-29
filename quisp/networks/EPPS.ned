package networks;
import ned.DatarateChannel;
import ned.DelayChannel;
import ned.IdealChannel;


//Maybe as a stand alone simple module is enough?
//simple SPDC_simple
//{
//    parameters:
//        int address;
//        double frequency = default(100);// 100 shots per sec as a default
//        double error_rate;
//    gates:
//        inout quantum_port[2];
//        inout port[2];
//}





simple SPDC_Controller
{
    parameters:
        //@class(quisp::modules::SPDC_Controller);
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

simple EntangledPhotonPairSource{
	parameters:
      //@class(quisp::modules::EntangledPhotonPairSource);
	    int address;
	    double frequency;
	    double error_rate;
	    double Y_error_ratio;
	    double X_error_ratio;
	    double Z_error_ratio;
	    double emission_std;
	 gates:
	      inout fromController;
	     inout to_quantum_port[2];
}

//Rather than simulating the entire pair generation success in the simulation,
//I have decided to assume that the SPDC node is capable of emitting a pair per some rate.
//simple Pump_Source
//{
//    parameters:
//        int address;
//        double frequency;
//    gates:
//        inout toBBO;
//        inout fromController;
//}

//simple BBO_Crystal
//{
//    parameters:
//        int address;
//       double success_rate;
//       double error_rate;
//    gates:
//        inout fromPumpSource;
//        inout to_quantum_port[2];
//}

module SPDC
{
    parameters:
        int address;
        double epps_frequency = default(5.9*10^6);// 5.9*10^6 = 5.9million pairs per sec as a default https://arxiv.org/pdf/1707.01339.pdf
        double epps_error_rate = default(0.093);//From 0~1. Fidelity = 0.907. This is the fidelity of the entangled qubit before entering the channel.
        string includeInTopo = "yes";
        double epps_Y_error_ratio = default(1);
        double epps_Z_error_ratio = default(1);
        double epps_X_error_ratio = default(1);
        double epps_timing_buffer = default(1e-9);//1ns buffer (gap between classical notifier and the actual photon emission)
        string nodeType = default("SPDC");
        double epps_emission_std = default(0);
    gates:
        inout quantum_port[] @loose;
        inout port[] @loose;
    submodules:
        Controller: SPDC_Controller {
            parameters:
                address = address;//share the same address within all inner modules
                timing_buffer = epps_timing_buffer;
                frequency = epps_frequency;//It is probably better to get it from PairSource
                @display("p=105,138");
        }
        router: Router {
            parameters:
                address = address;
                @display("p=105.045,57.364998");
            gates:
                fromQueue[sizeof(port)];
                toQueue[sizeof(port)];
        }
        queue[sizeof(port)]: Queue {
            parameters:
                address = 0;
                @display("p=281.61,55.874996");
        }

        PairSource: EntangledPhotonPairSource {
            parameters:
                address = address;
                frequency = epps_frequency;
                error_rate = epps_error_rate;
                	Y_error_ratio = epps_Y_error_ratio;
        			Z_error_ratio = epps_Z_error_ratio;
      			X_error_ratio = epps_X_error_ratio;
      			emission_std = epps_emission_std;
                @display("p=281,138");
        }
    connections:

        for i=0..sizeof(port)-1 {
            router.toQueue[i] --> queue[i].in;//Each routing port is connected to its own queue
            router.fromQueue[i] <-- queue[i].out;
            queue[i].line <--> port[i];
        }

         for i=0..sizeof(quantum_port)-1 {
            quantum_port[i] <--> PairSource.to_quantum_port++;
        }

        Controller.toRouter_port --> router.fromApp;
        router.toApp --> Controller.fromRouter_port;
		Controller.toPairSource_port <--> PairSource.fromController;
}











