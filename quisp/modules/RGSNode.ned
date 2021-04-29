package modules;

import modules.Application.Application;
import modules.QRSA.quantumRoutingSoft;
import modules.QNIC.*;
import modules.Common.*;


module RGS_source
{
    // overall structure is almost the same as the QNode
    parameters:
        int bufferSize = default(10);
        int address = default(0);
        int buffers = default(10); //default is defined as 10 in .ini file but can be changed independently in .ned file
        @display("bgl=4");

        string includeInTopo = "yes";
        string nodeType = default("RGS");
        double emission_timing_std = default(0);//in seconds

    gates:
        inout port[];//size will be determined by the number of connections defined at the end of this file
        inout quantum_rgs_source_port[] @loose; //rgs source node only send qubits

    submodules:
        app: Application {
            parameters:
                address = address;//share the same address within all inner modules
                @display("p=30,43");
        }
        router: Router {
            parameters:
                address = address;
                @display("p=140,94");
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
                //@display("p=110.05918,124.85208;is=vl");
                @display("p=171,33");
                number_of_qnics = sizeof(quantum_port);
                number_of_qnics_r = 0;
                number_of_qnics_rp = 0;
        }
        qnic[sizeof(quantum_rgs_source_port)]: QNIC {//number of QNIC is the same as number of classical queue/NIC
            parameters:
                parent_node_address = address;
                self_qnic_address = index;
                self_qnic_index = index;
                numBuffer = default(int(buffers));//number of buffers for each qnic
                receiver = false;
                emission_std = emission_timing_std;
                self_qnic_type = 0;
        }
    connections:
        for i=0..sizeof(port)-1 {
            router.toQueue[i] --> queue[i].in;//Each routing port is connected to its own queue
            router.fromQueue[i] <-- queue[i].out;
            queue[i].line <--> port[i];
        }
        for i=0..sizeof(quantum_rgs_source_port)-1 {
            qnic[i].qnic_quantum_port <--> quantum_rgs_source_port[i];
        		//qnic[i].dummyRoutingDaemonLink <--> qrsa.qnics++;
        }
        router.rePort <--> qrsa.rePort;
        router.cmPort <--> qrsa.cmPort;
        router.hmPort <--> qrsa.hmPort;
}
