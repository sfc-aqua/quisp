package modules;

import ned.DatarateChannel;
import ned.DelayChannel;
import ned.IdealChannel;

import modules.Application.Application;
import modules.QRSA.quantumRoutingSoft;
import modules.PhysicalConnection.BSA.*;
import modules.QNIC.PhotonicSwitch.*;
import modules.Common.Router;
import modules.Common.Queue;

module ABSANode
{
    parameters:
        int bufferSize = default(10);
        int address = default(0);
        int buffers = default(10); //default is defined as 10 in .ini file but can be changed independently in .ned file
        @display("bgl=4;bgb=443,333");

        double absa_darkcount_probability = default(0);
        double absa_loss_rate = default(0);
        double absa_error_rate = default(0);
        double absa_required_precision = default(1.5e-9);
        double duration = default(0);
        int absa_photon_detection_per_sec = default(100000);
        string includeInTopo = default("yes");
        @display("bgl=2");
        string nodeType = default("ABSA");

    gates:
        inout quantum_absa_port[] @loose;
        inout port[] @loose;

    submodules:
        router: Router {
            parameters:
                address = address;
                @display("p=188,55");
            gates:
                fromQueue[sizeof(port)];
                toQueue[sizeof(port)];
        }
        queue[sizeof(port)]: Queue {
            parameters:
                address = index;
                //buffer = 8;
                //@display("p=198,43");
                @display("p=68,122");
        }
        qrsa: quantumRoutingSoft {
            parameters:
                address = address;
                @display("p=104,55");
                number_of_qnics = 0;
                number_of_qnics_r = 0;
                number_of_qnics_rp = 0;
        }
        Controller: ABSAController {
            parameters:
                address = address;
                photon_detection_per_sec = absa_photon_detection_per_sec;
                @display("p=188,190");
        }
        ABSA: ABSA {
            parameters:
                address = address;//share the same address within all inner modules
                darkcount_probability = absa_darkcount_probability;
                loss_rate = absa_loss_rate;
                error_rate = absa_error_rate;
                required_precision = absa_required_precision;
                photon_detection_per_sec = absa_photon_detection_per_sec;
                @display("p=335,190");
        }
    connections:
        for i=0..sizeof(port)-1 {
            router.toQueue[i] --> queue[i].in;//Each routing port is connected to its own queue
            router.fromQueue[i] <-- queue[i].out;
            queue[i].line <--> port[i];
        }

        for i=0..sizeof(quantum_absa_port)-1 {
            quantum_absa_port[i] <--> ABSA.fromABSA_quantum_port++;
        }
        Controller.toRouter_port --> router.fromApp;
        router.toApp --> Controller.fromRouter_port;
        ABSA.toABSAController_port --> Controller.fromABSA_port;

        router.rePort <--> qrsa.rePort;
        router.cmPort <--> qrsa.cmPort;
        router.hmPort <--> qrsa.hmPort;

}
