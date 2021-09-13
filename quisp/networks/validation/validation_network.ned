package networks.validation;

import ned.DatarateChannel;
import ned.IdealChannel;

import modules.*;
import channels.*;


network validation_network_mm
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;
	submodules:
		Repeater: QNode{
			address = 1000;
			nodeType="Repeater";
			@display("i=device/smallrouter");
		};

		EndNode1: QNode{
			address = 1;
			nodeType = "EndNode";
			@display("i=device/pc");
		};

		EndNode2: QNode{
			address = 10000;
			nodeType = "EndNode";
			@display("i=device/pc");
		};

	connections:
		// Classical channels
		EndNode1.port++ <--> ClassicalChannel { distance = 10km; } <--> Repeater.port++; 
		Repeater.port++ <--> ClassicalChannel { distance = 10km; } <--> EndNode2.port++;
		
		// Quantum Channels
		EndNode1.quantum_port_receiver++ <--> ClassicalChannel { distance = 10km; } <--> Repeater.quantum_port++; 
		Repeater.quantum_port++ <--> ClassicalChannel { distance = 10km; } <--> EndNode2.quantum_port_receiver++;
}