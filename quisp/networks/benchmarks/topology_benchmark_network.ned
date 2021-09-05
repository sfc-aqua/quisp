package networks.benchmarks;

import ned.DatarateChannel;
import ned.IdealChannel;

import channels.*;
import modules.*;


network linear10_mm
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;
	submodules:
		Repeater[10]: QNode{
			address = 1000+index;
			nodeType="Repeater";
			@display("i=device/smallrouter");
		};

		EndNode[2]: QNode{
			address = 10000+index;
			nodeType = "EndNode";
			@display("i=device/pc");
		};

	connections:
		// Classical channels
		EndNode[0].port++ <--> ClassicalChannel { distance = 1km; } <--> Repeater[0].port++; 
		// Repeaters
		for i=0..sizeof(Repeater)-2{
			Repeater[i].port++ <--> ClassicalChannel{ distance = 1km;} <--> Repeater[i+1].port++;
		}
		Repeater[sizeof(Repeater)-1].port++ <--> ClassicalChannel { distance = 1km; } <--> EndNode[1].port++;
		
		// Quantum Channels
		EndNode[0].quantum_port_receiver++ <--> ClassicalChannel { distance = 1km; } <--> Repeater[0].quantum_port++; 
		// Repeaters
		for i=0..sizeof(Repeater)-2{
			Repeater[i].quantum_port_receiver++ <--> ClassicalChannel{ distance = 1km;} <--> Repeater[i+1].quantum_port++;
		}
		Repeater[sizeof(Repeater)-1].quantum_port++ <--> ClassicalChannel { distance = 1km; } <--> EndNode[1].quantum_port_receiver++;
}


network linear50_mm
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;
	submodules:
		Repeater[50]: QNode{
			address = 1000+index;
			nodeType="Repeater";
			@display("i=device/smallrouter");
		};

		EndNode1: QNode{
			address = 1;
			nodeType = "EndNode";
			@display("i=device/pc");
		};

		EndNode2: QNode{
			address = 100;
			nodeType = "EndNode";
			@display("i=device/pc");
		};

	connections:
		// Classical channels
		EndNode1.port++ <--> ClassicalChannel { distance = 1km; } <--> Repeater[0].port++; 
		// Repeaters
		for i=0..sizeof(Repeater)-2{
			Repeater[i].port++ <--> ClassicalChannel{ distance = 1km;} <--> Repeater[i+1].port++;
		}
		Repeater[sizeof(Repeater)-1].port++ <--> ClassicalChannel { distance = 1km; } <--> EndNode2.port++;
		
		// Quantum Channels
		EndNode1.quantum_port_receiver++ <--> ClassicalChannel { distance = 1km; } <--> Repeater[0].quantum_port++; 
		// Repeaters
		for i=0..sizeof(Repeater)-2{
			Repeater[i].quantum_port_receiver++ <--> ClassicalChannel{ distance = 1km;} <--> Repeater[i+1].quantum_port++;
		}
		Repeater[sizeof(Repeater)-1].quantum_port++ <--> ClassicalChannel { distance = 1km; } <--> EndNode2.quantum_port_receiver++;
}

network linear100_mm
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;
	submodules:
		Repeater[100]: QNode{
			address = 1000+index;
			nodeType="Repeater";
			@display("i=device/smallrouter");
		};

		EndNode1: QNode{
			address = 1;
			nodeType = "EndNode";
			@display("i=device/pc");
		};


		EndNode2: QNode{
			address = 100;
			nodeType = "EndNode";
			@display("i=device/pc");
		};

	connections:
		// Classical channels
		EndNode1.port++ <--> ClassicalChannel { distance = 1km; } <--> Repeater[0].port++; 
		// Repeaters
		for i=0..sizeof(Repeater)-2{
			Repeater[i].port++ <--> ClassicalChannel{ distance = 1km;} <--> Repeater[i+1].port++;
		}
		Repeater[sizeof(Repeater)-1].port++ <--> ClassicalChannel { distance = 1km; } <--> EndNode2.port++;
		
		// Quantum Channels
		EndNode1.quantum_port_receiver++ <--> ClassicalChannel { distance = 1km; } <--> Repeater[0].quantum_port++; 
		// Repeaters
		for i=0..sizeof(Repeater)-2{
			Repeater[i].quantum_port_receiver++ <--> ClassicalChannel{ distance = 1km;} <--> Repeater[i+1].quantum_port++;
		}
		Repeater[sizeof(Repeater)-1].quantum_port++ <--> ClassicalChannel { distance = 1km; } <--> EndNode2.quantum_port_receiver++;
}

network nodes10_network_small
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;
	submodules:
		Hom1[10]: HoM{
			address = index;
			@display("i=device/device");
		};

		Hom2[10]: HoM {
			address = 100+index;
			@display("i=device/device");
		}
		Repeater[10]: QNode{
			address = 1000+index;
			nodeType="Repeater";
			@display("i=device/smallrouter");
		};

		Repeater_mm[10]: QNode{
			address = 2000+index;
			nodeType="Repeater";
			@display("i=device/smallrouter");
		};
		Repeater_mim[10]: QNode{
			address = 3000+index;
			nodeType="Repeater";
			@display("i=device/smallrouter");
		};

		Endnode_mim[10]: QNode{
			address = 10000+index;
			nodeType = "EndNode";
			@display("i=device/pc");
		};

		Endnode_mm[10]: QNode{
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

network nodes50_network_medium
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;
	submodules:
		Hom1[25]: HoM{
			address = index;
			@display("i=device/device");
		};

		Hom2[25]: HoM {
			address = 100+index;
			@display("i=device/device");
		}
		Repeater[10]: QNode{
			address = 1000+index;
			nodeType="Repeater";
			@display("i=device/smallrouter");
		};

		Repeater_mm[25]: QNode{
			address = 2000+index;
			nodeType="Repeater";
			@display("i=device/smallrouter");
		};
		Repeater_mim[25]: QNode{
			address = 3000+index;
			nodeType="Repeater";
			@display("i=device/smallrouter");
		};

		Endnode_mim[25]: QNode{
			address = 10000+index;
			nodeType = "EndNode";
			@display("i=device/pc");
		};

		Endnode_mm[25]: QNode{
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

network nodes100_network_large
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


