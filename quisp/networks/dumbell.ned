//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package networks;

import ned.DatarateChannel;
import ned.IdealChannel;



network topology_dumbell_MM
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;
    submodules:
        EndNode1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=device/pc;p=350,157");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        EndNode2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=device/pc;p=407,231");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        EndNode3[1]: QNode {
            address = 3;
            nodeType = "EndNode";
            @display("i=device/pc;p=220,137");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        EndNode4[1]: QNode {
            address = 4;
            nodeType = "EndNode";
            @display("i=device/pc;p=80,189");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        repeater1[1]: QNode {
            address = 5;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=device/smallrouter;p=66,124");
        }
        repeater2[1]: QNode {
            address = 6;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=device/smallrouter;p=132,36");
        }

    connections:
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> repeater1[0].port++;
        EndNode3[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> repeater1[0].port++;
        repeater1[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> repeater2[0].port++;
        repeater2[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode2[0].port++;
        repeater2[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode4[0].port++;
        
        
        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 10km; } <--> repeater1[0].quantum_port++;
        EndNode3[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 10km; } <--> repeater1[0].quantum_port++;
        repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> repeater2[0].quantum_port++;
        repeater2[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode2[0].quantum_port_receiver++;
        repeater2[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode4[0].quantum_port_receiver++;
}


network topology_dumbell_MIM
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;
    submodules:
        EndNode1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=device/pc;p=350,157");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        EndNode2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=device/pc;p=407,231");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        EndNode3[1]: QNode {
            address = 3;
            nodeType = "EndNode";
            @display("i=device/pc;p=220,137");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        EndNode4[1]: QNode {
            address = 4;
            nodeType = "EndNode";
            @display("i=device/pc;p=80,189");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        HoM1[1]: HoM {
            address = 5;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=device/smallrouter;p=66,124");
        }
        HoM2[1]: HoM {
            address = 6;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=device/smallrouter;p=132,36");
        }

    connections:
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM1[0].port++;
        EndNode3[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM1[0].port++;
        HoM1[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM2[0].port++;
        HoM2[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode2[0].port++;
        HoM2[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode4[0].port++;
        
        
        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 10km; } <--> HoM1[0].quantum_port++;
        EndNode3[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 10km; } <--> HoM1[0].quantum_port++;
        HoM1[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HoM2[0].quantum_port++;
        HoM2[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode2[0].quantum_port_receiver++;
        HoM2[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode4[0].quantum_port_receiver++;
}


network topology_dumbell_MM_MIM
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;
    submodules:
        EndNode1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=device/pc;p=350,157");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        EndNode2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=device/pc;p=407,231");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        EndNode3[1]: QNode {
            address = 3;
            nodeType = "EndNode";
            @display("i=device/pc;p=220,137");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        EndNode4[1]: QNode {
            address = 4;
            nodeType = "EndNode";
            @display("i=device/pc;p=80,189");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        repeater1[1]: QNode {
            address = 5;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=device/smallrouter;p=66,124");
        }
        repeater2[1]: QNode {
            address = 6;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=device/smallrouter;p=132,36");
        }
        repeater3[1]: QNode {
            address = 7;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=device/smallrouter;p=66,124");
        }
        repeater4[1]: QNode {
            address = 8;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=device/smallrouter;p=132,36");
        }
        HoM1[1]: HoM {
            address = 9;
            //buffers = 25;
            @display("i=device/bsm;p=171,231");
        }
        HoM2[1]: HoM {
            address = 10;
            //buffers = 25;
            @display("i=device/bsm;p=66,51");
        }
       

    connections:
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> repeater1[0].port++;
        repeater1[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM1[0].port++;
        HoM1[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM2[0].port++;
        HoM2[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> repeater2[0].port++;
        repeater2[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode2[0].port++;
        
        EndNode3[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> repeater3[0].port++;
        repeater3[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM1[0].port++;
        HoM1[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM2[0].port++;
        HoM2[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> repeater4[0].port++;
        repeater4[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode4[0].port++;
        
        
        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 10km; } <--> repeater1[0].quantum_port++;
        repeater1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 10km; } <--> HoM1[0].quantum_port++;
        HoM1[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HoM2[0].quantum_port++;
        HoM2[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> repeater2[0].quantum_port_receiver++;
        repeater2[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode2[0].quantum_port_receiver++;
        
        EndNode3[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 10km; } <--> repeater3[0].quantum_port++;
        repeater3[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 10km; } <--> HoM1[0].quantum_port++;
        HoM1[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HoM2[0].quantum_port++;
        HoM2[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> repeater4[0].quantum_port_receiver++;
        repeater4[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode4[0].quantum_port_receiver++;
        
}
