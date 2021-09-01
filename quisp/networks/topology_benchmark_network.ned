package networks;

import ned.DatarateChannel;
import ned.IdealChannel;

import channels.*;
import modules.*;

network nodes100_qubits5000_network
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;
	submodules:
		Hom1[50]: HoM{
			address = index;
			@display("i=device/device");
		};

		Hom2[50]: HoM {
			address = 100+index;
			@display("i=device/device");
		}
		Repeater[10]: QNode{
			address = 1000+index;
			nodeType="Repeater";
			@display("i=device/smallrouter");
		};

		Repeater_mm[50]: QNode{
			address = 2000+index;
			nodeType="Repeater";
			@display("i=device/smallrouter");
		};
		Repeater_mim[50]: QNode{
			address = 3000+index;
			nodeType="Repeater";
			@display("i=device/smallrouter");
		};

		Endnode_mim[50]: QNode{
			address = 10000+index;
			nodeType = "EndNode";
			@display("i=device/pc");
		};

		Endnode_mm[50]: QNode{
			address = 20000+index;
			nodeType = "EndNode";
			@display("i=device/pc");
		};

		Router[10]: QNode{
			address = 100000+index;
			nodeType="Router";
			@display("p=400,400,ri,150,150;i=device/router");
		};

	connections:
		// Routers
		for i=0..sizeof(Router)-2{
			Router[i].port++ <--> ClassicalChannel { distance = 1km; } <--> Repeater[i].port++;
			Repeater[i].port++ <--> ClassicalChannel{ distance = 1km;} <--> Router[i+1].port++;
		}
		Router[9].port++ <--> ClassicalChannel { distance = 1km; } <--> Repeater[sizeof(Router)-1].port++;
		Repeater[sizeof(Router)-1].port++ <--> ClassicalChannel { distance = 1km; } <--> Router[0].port++;

		// Endnodes
		for i=0..sizeof(Endnode_mim)-1{
			Endnode_mim[i].port++ <--> ClassicalChannel { distance = 1.25km; } <--> Hom1[i].port++;	
			Hom1[i].port++ <--> ClassicalChannel { distance = 1.25km; } <--> Repeater_mim[i].port++;
			Repeater_mim[i].port++ <--> ClassicalChannel {distance = 1.25km; } <--> Hom2[i].port++;
			Hom2[i].port++ <--> ClassicalChannel { distance = 1.25km; } <--> Router[i%10].port++;	
		}
		for i=0..sizeof(Endnode_mm)-1{
			Endnode_mm[i].port++ <--> ClassicalChannel { distance = 2.5km; } <--> Repeater_mm[i].port++;
			Repeater_mm[i].port++<--> ClassicalChannel { distance = 2.5km; } <--> Router[i%10].port++;
		}

		// Quantum Channels
		// Routers
		for i=0..sizeof(Router)-2{
			Router[i].quantum_port++ <--> QuantumChannel { distance = 1km; } <--> Repeater[i].quantum_port_receiver++;
			Repeater[i].quantum_port_receiver++ <--> QuantumChannel{ distance = 1km;} <--> Router[i+1].quantum_port++;
		}
		Router[9].quantum_port++ <--> QuantumChannel { distance = 1km; } <--> Repeater[sizeof(Router)-1].quantum_port_receiver++;
		Repeater[sizeof(Router)-1].quantum_port_receiver++ <--> QuantumChannel { distance = 1km; } <--> Router[0].quantum_port++;

		// Endnodes
		for i=0..sizeof(Endnode_mim)-1{
			Endnode_mim[i].quantum_port++ <--> QuantumChannel { distance = 1.25km; } <--> Hom1[i].quantum_port++;	
			Hom1[i].quantum_port++ <--> QuantumChannel { distance = 1.25km; } <--> Repeater_mim[i].quantum_port++;
			Repeater_mim[i].quantum_port++ <--> QuantumChannel {distance = 1.25km; } <--> Hom2[i].quantum_port++;
			Hom2[i].quantum_port++ <--> QuantumChannel { distance = 1.25km; } <--> Router[i%10].quantum_port++;	
		}
		for i=0..sizeof(Endnode_mm)-1{
			Endnode_mm[i].quantum_port++ <--> QuantumChannel { distance = 2.5km; } <--> Repeater_mm[i].quantum_port_receiver++;
			Repeater_mm[i].quantum_port_receiver++<--> QuantumChannel { distance = 2.5km; } <--> Router[i%10].quantum_port++;
		}
}