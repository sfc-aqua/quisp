package modules;

import ned.DatarateChannel;
import ned.DelayChannel;
import ned.IdealChannel;

import modules.PhysicalConnection.BSA.*;
import modules.QNIC.PhotonicSwitch.*;
import modules.Common.Router;
import modules.Common.Queue;


module interHoM
{
    parameters:
        int address;
        double internal_hom_darkcount_probability = default(0);
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
        Controller: HoMController {
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
                darkcount_probability = internal_hom_darkcount_probability;
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


module HoM
{
    parameters:
        double hom_darkcount_probability = default(0);
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
                darkcount_probability = hom_darkcount_probability;
                loss_rate = hom_loss_rate;
                error_rate = hom_error_rate;
                required_precision = hom_required_precision;
                photon_detection_per_sec = hom_photon_detection_per_sec;
                @display("p=207.855,120.689995");
        }
        router: Router {
            parameters:
                address = address;
                @display("p=157,40");
            gates:
                fromQueue[sizeof(port)];
                toQueue[sizeof(port)];
        }
        nic[sizeof(port)]: Queue {
            parameters:
                address = 0;
                @display("p=281.61,55.874996");
        }
        Controller: HoMController {
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
