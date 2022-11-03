package modules;
@namespace(quisp::modules);

import ned.DatarateChannel;
import ned.DelayChannel;
import ned.IdealChannel;

import modules.PhysicalConnection.BSA.*;
import modules.QNIC.PhotonicSwitch.*;
import modules.Common.Router;
import modules.Common.Queue;


module interHOM
{
    parameters:
        int address;
        double internal_hom_darkcount_probability = default(0);
        double internal_hom_loss_rate = default(0);
        double internal_hom_error_rate = default(0);
        double internal_hom_required_precision = default(1.5e-9);
        int internal_hom_photon_detection_per_sec = default(10000);
        int qnic_index @mutable = default(-1);
        double internal_distance = default(0);
        bool passive = default(false);
        @display("i=BSA");

    gates:
        //inout quantum_port_one @loose;
        //inout quantum_port_two @loose;
        inout quantum_port[] @loose;
        output toRouter @loose;
    submodules:
        Controller: HOMController {
            parameters:
                address = parent.address;
                @display("p=103.55499,121.435");
                receiver = true;
                passive = parent.passive;
                photon_detection_per_sec = parent.internal_hom_photon_detection_per_sec;
        }
        BSA: BellStateAnalyzer {
            parameters:
                address = parent.address;//share the same address within all inner modules
                darkcount_probability = parent.internal_hom_darkcount_probability;
                loss_rate = parent.internal_hom_loss_rate;
                error_rate = parent.internal_hom_error_rate;
                required_precision = parent.internal_hom_required_precision;
                photon_detection_per_sec = parent.internal_hom_photon_detection_per_sec;
                @display("p=207.855,120.689995");
        }
    connections:
        Controller.toRouter_port --> toRouter;
        BSA.toHOMController_port --> Controller.fromBSA_port;

        quantum_port++ <--> BSA.fromHOM_quantum_port++;
        quantum_port++ <--> BSA.fromHOM_quantum_port++;
}


module HOM
{
    parameters:
        @display("i=BSA");
        double hom_darkcount_probability = default(0);
        double hom_loss_rate = default(0);
        double hom_error_rate = default(0);
        double hom_required_precision = default(1.5e-9);
        double duration = default(0);
        int hom_photon_detection_per_sec = default(100000);
        int address = default(0);
        string includeInTopo = default("yes");
        @display("bgl=2");
        string nodeType = default("HOM");
        bool interHOM = default(false);

    gates:
        inout quantum_port[] @loose;
        inout port[] @loose;

    submodules:
        BSA: BellStateAnalyzer {
            parameters:
                address = parent.address;//share the same address within all inner modules
                darkcount_probability = parent.hom_darkcount_probability;
                loss_rate = parent.hom_loss_rate;
                error_rate = parent.hom_error_rate;
                required_precision = parent.hom_required_precision;
                photon_detection_per_sec = parent.hom_photon_detection_per_sec;
                @display("p=207.855,120.689995");
        }
        router: Router {
            parameters:
                address = parent.address;
                @display("p=157,40");
            gates:
                fromQueue[sizeof(parent.port)];
                toQueue[sizeof(parent.port)];
        }
        nic[sizeof(port)]: Queue {
            parameters:
                address = 0;
                @display("p=281.61,55.874996");
        }
        Controller: HOMController {
            parameters:
                address = parent.address;
                photon_detection_per_sec = parent.hom_photon_detection_per_sec;
                @display("p=103.55499,121.435");
        }
    connections:

        for i=0..sizeof(port)-1 {
            router.toQueue[i] --> nic[i].in;//Each routing port is connected to its own queue
            router.fromQueue[i] <-- nic[i].out;
            nic[i].line <--> port[i];
        }

        for i=0..sizeof(quantum_port)-1 {
            quantum_port[i] <--> BSA.fromHOM_quantum_port++;
        }

        Controller.toRouter_port --> router.fromApp;
        router.toApp --> Controller.fromRouter_port;
        BSA.toHOMController_port --> Controller.fromBSA_port;
}
