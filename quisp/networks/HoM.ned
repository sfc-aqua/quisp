package networks;
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//
import ned.DatarateChannel;
import ned.DelayChannel;
import ned.IdealChannel;

simple BellStateAnalyzer
{
    parameters:
        double darkcount_rate = default(0);
        double loss_rate = default(0);
        double error_rate = default(0);
        double duration = default(0);
        double required_precision = default(1.5e-9);
        int photon_detection_per_sec = default(10000);
        int address;

        int degree = 2;
    gates:
        inout fromHoM_quantum_port[];
        output toHoMController_port;
}

simple HoM_Controller
{
    parameters:
        @class(quisp::modules::HoM_Controller);
        int address;
        volatile double Speed_of_light_in_fiber @unit(km);//per sec
        int photon_detection_per_sec = default(10000);
        //rate can be up to 1 billion photons per second by default
        //interval will be 1photon/ns
        int neighbor_address = default(-1);
        int neighbor_address_two = default(-1);
        double distance_to_neighbor = default(-1);//in km
        double distance_to_neighbor_two = default(-1);//in km
        double max_neighbor_distance = default(-1);
        double max_buffer = default(-1);
        double emission_variance = default(0);//in seconds. Photons will be shot towards HoM with 100% accuracy
        bool receiver = default(false);
        bool passive = default(false);
    gates:
        input fromRouter_port @loose;
        output toRouter_port @loose;
        input fromBSA_port @loose;
}



module interHoM{
     parameters:
        int address;
        double internal_hom_darkcount_rate = default(0);
        double internal_hom_loss_rate = default(0);
        double internal_hom_error_rate = default(0);
        double internal_hom_required_precision = default(1.5e-9);
        int internal_hom_photon_detection_per_sec = default(10000);
        int qnic_index = default(-1);
        double internal_distance = default(0);
        bool passive = default(false);

	 gates:
        //inout quantum_port_one @loose;
        //inout quantum_port_two @loose;
        inout quantum_port[] @loose;
        output toRouter @loose;
     submodules:
        Controller: HoM_Controller {
            parameters:
                address = address;
                @display("p=103.55499,121.435");
                receiver = true;
                passive = passive;
                photon_detection_per_sec = internal_hom_photon_detection_per_sec;
        }
        BSA: BellStateAnalyzer {
            parameters:
                address = address;//share the same address within all inner modules
                darkcount_rate = internal_hom_darkcount_rate;
                loss_rate = internal_hom_loss_rate;
        		    error_rate = internal_hom_error_rate;
        		    required_precision = internal_hom_required_precision;
        		    photon_detection_per_sec = internal_hom_photon_detection_per_sec;
                @display("p=207.855,120.689995");
        }
     connections:
         Controller.toRouter_port --> toRouter;
         BSA.toHoMController_port --> Controller.fromBSA_port;
         
         quantum_port++ <--> BSA.fromHoM_quantum_port++;
         quantum_port++ <--> BSA.fromHoM_quantum_port++;        
}

simple dummyModule{
	gates:
	   inout close @loose;
	   input close_input @loose;
	   output close_output @loose;
}


module HoM
{
    parameters:
        double hom_darkcount_rate = default(0);
        double hom_loss_rate = default(0);
        double hom_error_rate = default(0);
        double hom_required_precision = default(1.5e-9);
        double duration = default(0);
        int hom_photon_detection_per_sec = default(100000);
        int address = default(0);
        string includeInTopo = default("yes");
        @display("bgl=2");
        string nodeType = default("HoM");
        bool interHoM = default(false);
    gates:
        inout quantum_port[] @loose;
        inout port[] @loose;

    submodules:
        BSA: BellStateAnalyzer {
            parameters:
                address = address;//share the same address within all inner modules
                darkcount_rate = hom_darkcount_rate;
                loss_rate = hom_loss_rate;
        		    error_rate = hom_error_rate;
        		    required_precision = hom_required_precision;
        		    photon_detection_per_sec = hom_photon_detection_per_sec;
                @display("p=207.855,120.689995");
        }
        router: Router {
            parameters:
                address = address;
                @display("p=105.045,57.364998");
            gates:
                fromQueue[sizeof(port)];
                toQueue[sizeof(port)];
        }
        nic[sizeof(port)]: Queue {
            parameters:
                address = 0;
                @display("p=281.61,55.874996");
        }
        Controller: HoM_Controller {
            parameters:
                address = address;
                photon_detection_per_sec = hom_photon_detection_per_sec;
                @display("p=103.55499,121.435");
        }
    connections:

        for i=0..sizeof(port)-1 {
            router.toQueue[i] --> nic[i].in;//Each routing port is connected to its own queue
            router.fromQueue[i] <-- nic[i].out;
            nic[i].line <--> port[i];
        }

        for i=0..sizeof(quantum_port)-1 {
            quantum_port[i] <--> BSA.fromHoM_quantum_port++;
        }

        Controller.toRouter_port --> router.fromApp;
        router.toApp --> Controller.fromRouter_port;
        BSA.toHoMController_port --> Controller.fromBSA_port;
}





