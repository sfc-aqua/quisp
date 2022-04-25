package networks;

import modules.*;
import channels.*;
import modules.Backend.Backend;

network linear_network
{
    parameters:
        string connectionType; // MM / MIM / MSM
        int numNodes = default(5);
        int numRepeaters = numNodes - 2;
        int lastRepeaterIndex = numRepeaters - 1;
        int numHoMs = connectionType == "MIM" ? numRepeaters + 1: 0;
        double classicalDistance @unit(km) = default(1.0km);
        double quantumDistance @unit(km) = default(1.0km);

    submodules:
        backend: Backend {

        }
        Repeater[numNodes - 2]: QNode {
            address = index + 2;
            @display("i=device/smallrouter");
        }
        EndNode[2]: QNode {
            address = index;
            nodeType = "EndNode";
            @display("i=device/pc");
        }
    	HoM[numHoMs]: HoM {
    	    address = index + numNodes;
    	    @display("i=device/device");
    	}

    connections:

        if connectionType == "MIM" {
            EndNode[0].port++ <--> ClassicalChannel{distance = classicalDistance / 2;} <--> HoM[0].port++;
            HoM[0].port++ <--> ClassicalChannel{distance = classicalDistance / 2;} <--> Repeater[0].port++;
            EndNode[0].quantum_port++ <--> QuantumChannel{ distance = quantumDistance / 2;} <--> HoM[0].quantum_port++;
            HoM[0].quantum_port++ <--> QuantumChannel{ distance = quantumDistance / 2;} <--> Repeater[0].quantum_port++;

            Repeater[i].port++ <--> ClassicalChannel{distance = classicalDistance / 2;} <--> HoM[i+1].port++ for i=0..numRepeaters - 2;
            HoM[i+1].port++ <--> ClassicalChannel{distance = classicalDistance / 2;} <--> Repeater[i+1].port++ for i=0..numRepeaters - 2;
            Repeater[i].quantum_port++ <--> QuantumChannel{ distance = quantumDistance / 2;} <--> HoM[i+1].quantum_port++ for i=0..numRepeaters - 2;
            HoM[i+1].quantum_port++ <--> QuantumChannel{ distance = quantumDistance / 2;} <--> Repeater[i+1].quantum_port++ for i=0..numRepeaters - 2;

            EndNode[1].port++ <--> ClassicalChannel{distance = classicalDistance / 2;} <--> HoM[sizeof(HoM)-1].port++;
            HoM[sizeof(HoM)-1].port++ <--> ClassicalChannel{distance = classicalDistance / 2;} <--> Repeater[lastRepeaterIndex].port++;

            EndNode[1].quantum_port++ <--> QuantumChannel{ distance = quantumDistance / 2;} <--> HoM[sizeof(HoM)-1].quantum_port++;
            HoM[sizeof(HoM)-1].quantum_port++ <--> QuantumChannel{ distance = quantumDistance / 2;} <--> Repeater[lastRepeaterIndex].quantum_port++;

        }

        if connectionType == "MM" {
            EndNode[0].port++ <--> ClassicalChannel{distance = classicalDistance;} <--> Repeater[0].port++;
            EndNode[0].quantum_port++ <--> QuantumChannel{ distance = quantumDistance;} <--> Repeater[0].quantum_port_receiver++;

            Repeater[i].port++ <--> ClassicalChannel{distance = classicalDistance;} <--> Repeater[i+1].port++ for i=0..numRepeaters - 2;
            Repeater[i].quantum_port++ <--> QuantumChannel{ distance = quantumDistance;} <--> Repeater[i+1].quantum_port_receiver++ for i=0..numRepeaters - 2;

            EndNode[1].port++ <--> ClassicalChannel{distance = classicalDistance;} <--> Repeater[lastRepeaterIndex].port++;
            EndNode[1].quantum_port++ <--> QuantumChannel{ distance = quantumDistance;} <--> Repeater[lastRepeaterIndex].quantum_port_receiver++;
        }
}
