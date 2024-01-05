package modules;
@namespace(quisp::modules);

import modules.Application.Application;
import modules.QRSA.quantumRoutingSoft;
import modules.QNIC.*;
import modules.Common.*;

module QNode
{
    parameters:
        int address = default(0);
        int buffers = default(10); // default is defined as 10 in .ini file but can be changed independently in .ned file
        int mass = default(100);
        bool is_initiator = default(false);
        @display("bgl=4");

        string included_in_topology = "yes";
        string node_type = default("none");
        double emission_timing_std = default(0); // in seconds
        bool simultaneous_es_enabled = default(false);

    gates:
        inout port[]; // size will be determined by the number of connections defined at the end of this file
        inout quantum_port[] @loose;
        inout quantum_port_receiver[] @loose; // BSA is active. Tells the neighboring nodes about the timings and so on.
        inout quantum_port_receiver_passive[] @loose; // BSA is passive. Doesnt do anything. EPPS is in charge here.

    submodules:
        app: Application {
            parameters:
                @display("p=30,43");
        }
        router: Router {
            parameters:
                @display("p=140,94");
            gates:
                fromQueue[sizeof(parent.port)];
                toQueue[sizeof(parent.port)];
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
                @display("p=179,35;is=l");
                number_of_qnics = sizeof(parent.quantum_port);
                number_of_qnics_r = sizeof(parent.quantum_port_receiver);
                number_of_qnics_rp = sizeof(parent.quantum_port_receiver_passive);
                simultaneous_es_enabled = parent.simultaneous_es_enabled;
        }
        qnic[sizeof(quantum_port)]: QNIC { // number of QNIC is the same as number of classical queue/NIC
            parameters:
                parent_node_address = parent.address;
                self_qnic_address = index;
                self_qnic_index = index;
                num_buffer = default(int(parent.buffers)); // number of buffers for each qnic
                receiver = false;
                emission_std = parent.emission_timing_std;
                self_qnic_type = 0;
                @display("p=311,161,m,5,100,50");
        }
        qnic_r[sizeof(quantum_port_receiver)]: QNIC {
            parameters:
                parent_node_address = parent.address;
                self_qnic_address = index + sizeof(parent.quantum_port);
                self_qnic_index = index;
                num_buffer = default(int(parent.buffers)); // number of buffers for each qnic
                receiver = true;
                passive = false;
                self_qnic_type = 1;
                emission_std = parent.emission_timing_std;
                @display("p=179,200,m,5,50,60");
        }
        qnic_rp[sizeof(quantum_port_receiver_passive)]: QNIC {
            parameters:
                parent_node_address = parent.address;
                self_qnic_address = index + sizeof(parent.quantum_port) + sizeof(parent.quantum_port_receiver);
                self_qnic_index = index;
                num_buffer = default(int(parent.buffers)); // number of buffers for each qnic
                receiver = true;
                passive = true;
                self_qnic_type = 2;
                emission_std = parent.emission_timing_std;
                @display("p=338,82,m,5,50,60");
        }

    connections:
        if (node_type=="EndNode") {
            router.toApp --> app.fromRouter;
            router.fromApp <-- app.toRouter;
        }
        for i=0..sizeof(port)-1 {
            router.toQueue[i] --> queue[i].in; // Each routing port is connected to its own queue
            router.fromQueue[i] <-- queue[i].out;
            queue[i].line <--> port[i];
        }
        for i=0..sizeof(quantum_port)-1 {
            qnic[i].qnic_quantum_port <--> quantum_port[i];
        }
        for i=0..sizeof(quantum_port_receiver)-1 {
            qnic_r[i].qnic_quantum_port <--> quantum_port_receiver[i];
            qnic_r[i].to_parent_router --> router.fromQNIC++; // Directly connected to internal BSA
        }
        for i=0..sizeof(quantum_port_receiver_passive)-1 {
            qnic_rp[i].qnic_quantum_port <--> quantum_port_receiver_passive[i];
            qnic_rp[i].to_parent_router --> router.fromQNIC++; // Directly connected to internal BSA
        }

        router.rdPort <--> qrsa.rdPort;
        router.rePort <--> qrsa.rePort;
        router.cmPort <--> qrsa.cmPort;
        router.hmPort <--> qrsa.hmPort;
}
