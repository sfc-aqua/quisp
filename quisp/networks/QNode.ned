package networks;

module QNode
{
    parameters:
        int bufferSize = default(10);
        int address = default(0);
        int buffers = default(10); //default is defined as 10 in .ini file but can be changed independently in .ned file
        @display("bgl=4");
        //int numQNIC = 1;

        string includeInTopo = "yes";
        string nodeType = default("none");
        double emission_timing_std = default(0);//in seconds

    gates:
        inout port[];//size will be determined by the number of connections defined at the end of this file
        inout quantum_port[] @loose;
        inout quantum_port_receiver[] @loose;//HoM is active. Tells the neighboring nodes about the timings and so on.
        inout quantum_port_receiver_passive[] @loose;//HoM is passive. Doesnt do anything. SPDC is in charge here.
        //inout qp_test[2] @loose;

    //types:
    //    channel I extends IdealChannel{
    //
    //    }
    submodules:
        app: Application {
            parameters:
                address = address;//share the same address within all inner modules
                @display("p=30,43");
        }
        router: Router {
            parameters:
                address = address;
                @display("p=110,43");
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
                @display("p=206,49");
                number_of_qnics = sizeof(quantum_port);
                number_of_qnics_r = sizeof(quantum_port_receiver);
                number_of_qnics_rp = sizeof(quantum_port_receiver_passive);
        }
        qnic[sizeof(quantum_port)]: QNIC {//number of QNIC is the same as number of classical queue/NIC
            parameters:
                parent_node_address = address;
                self_qnic_address = index;
                self_qnic_index = index;
                numBuffer = default(int(buffers));//number of buffers for each qnic
                receiver = false;
                emission_std = emission_timing_std;
                self_qnic_type = 0;
                //@display("p=198,124");
                //@display("p=209,195;b=,,,white");
        }
        qnic_r[sizeof(quantum_port_receiver)]: QNIC {
        		parameters:
        		    	parent_node_address = address;
                self_qnic_address = index + sizeof(quantum_port);
                self_qnic_index = index;
                numBuffer = default(int(buffers));//number of buffers for each qnic
                receiver = true;
                passive = false;
                self_qnic_type = 1;
                emission_std = emission_timing_std;
        }
        qnic_rp[sizeof(quantum_port_receiver_passive)]: QNIC {
        		parameters:
        		    	parent_node_address = address;
                self_qnic_address = index + sizeof(quantum_port) + sizeof(quantum_port_receiver);
                self_qnic_index = index;
                numBuffer = default(int(buffers));//number of buffers for each qnic
                receiver = true;
                passive = true;
                self_qnic_type = 2;
                emission_std = emission_timing_std;
        }

    connections:
        if(nodeType=="EndNode"){
       	 	router.toApp --> app.fromRouter;
        		router.fromApp <-- app.toRouter;
        }
        for i=0..sizeof(port)-1 {
            router.toQueue[i] --> queue[i].in;//Each routing port is connected to its own queue
            router.fromQueue[i] <-- queue[i].out;
            queue[i].line <--> port[i];
        }
        for i=0..sizeof(quantum_port)-1{
        		qnic[i].qnic_quantum_port <--> quantum_port[i];
        		//qnic[i].dummyRoutingDaemonLink <--> qrsa.qnics++;
        }
        for i=0..sizeof(quantum_port_receiver)-1{
        		qnic_r[i].qnic_quantum_port <--> quantum_port_receiver[i];
        		qnic_r[i].toParentRouter --> router.fromQNIC++;//Directly connected to internal HoM
        		//qnic_r[i].dummyRoutingDaemonLink <--> qrsa.qnics++;
        }
        for i=0..sizeof(quantum_port_receiver_passive)-1{
        		qnic_rp[i].qnic_quantum_port <--> quantum_port_receiver_passive[i];
        		qnic_rp[i].toParentRouter --> router.fromQNIC++;//Directly connected to internal HoM
        		//qnic_rp[i].dummyRoutingDaemonLink <--> qrsa.qnics++;
        }

        router.rePort <--> qrsa.rePort;
        router.cmPort <--> qrsa.cmPort;
        router.hmPort <--> qrsa.hmPort;
}
