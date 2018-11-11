package networks;

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

import ned.DatarateChannel;
import ned.IdealChannel;


network Layer2_ChannelTest
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

    submodules:
        //EndNode[2]: QNode {
        EndNode[2]:QNode{
            address = 100+index;
            nodeType = "EndNode";
            @display("i=device/pc;");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }

        //repeater[4]: QNode {
        repeater[3]:QNode{
            address = 10000+sizeof(EndNode) + index;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=device/smallrouter");
        }

        //HoM[3]: HoM {
        HoM[2]: HoM {
            address = 100000+sizeof(EndNode)+ sizeof(repeater)+ index;
            @display("i=device/bsm");
        }

    connections:
        EndNode[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> repeater[0].port++;//MM    
        repeater[0].port++<--> ClassicalChannel {  distance = 5km; } <--> HoM[0].port++ ;//MIM
        repeater[1].port++ <--> ClassicalChannel {  distance = 15km; } <--> HoM[0].port++;
        	repeater[1].port++ <--> ClassicalChannel {  distance = 15km; } <--> HoM[1].port++;
        repeater[2].port++ <--> ClassicalChannel {  distance = 5km; } <--> HoM[1].port++;
        repeater[1].port++ <--> ClassicalChannel {  distance = 5km; } <--> EndNode[1].port++;
	
		EndNode[0].quantum_port++ <--> QuantumChannel {  distance = 20km; channel_error_rate = 0.5; photon_loss_ratio = 0; Z_error_ratio = 0; X_error_ratio = 1; Y_error_ratio = 0;} <--> repeater[0].quantum_port_receiver++;//MM	
        repeater[0].quantum_port++<--> QuantumChannel {  distance = 5km; channel_error_rate = 0.5; photon_loss_ratio = 0; Z_error_ratio = 1; X_error_ratio = 0; Y_error_ratio = 0; } <--> HoM[0].quantum_port++;//MIM
        repeater[1].quantum_port++ <--> QuantumChannel {  distance = 15km; channel_error_rate = 0.5; photon_loss_ratio = 0; Z_error_ratio = 1; X_error_ratio = 0; Y_error_ratio = 0; } <--> HoM[0].quantum_port++;
        repeater[1].quantum_port++ <--> QuantumChannel {  distance = 15km; channel_error_rate = 0.5; photon_loss_ratio = 0; Z_error_ratio = 1; X_error_ratio = 0; Y_error_ratio = 0; } <--> HoM[1].quantum_port++;
        repeater[2].quantum_port++ <--> QuantumChannel {  distance = 5km; channel_error_rate = 0.5; photon_loss_ratio = 0; Z_error_ratio = 1; X_error_ratio = 0; Y_error_ratio = 0; } <--> HoM[1].quantum_port++;
		repeater[1].quantum_port_receiver++ <--> QuantumChannel {  distance = 5km; channel_error_rate = 0.05; photon_loss_ratio = 1; Z_error_ratio = 0; X_error_ratio = 0; Y_error_ratio = 0; } <--> EndNode[1].quantum_port++;
}



network Layer2_Star
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

    submodules:
        //EndNode[2]: QNode {
        EndNode[6]:QNode{
            address = 100+index;
            nodeType = "EndNode";
            @display("i=device/pc;");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }

        //repeater[4]: QNode {
        repeater[4]:QNode{
            address = 10000+sizeof(EndNode) + index;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=device/smallrouter");
        }

        //HoM[3]: HoM {
        HoM[4]: HoM {
            address = 100000+sizeof(EndNode)+ sizeof(repeater)+ index;
            @display("i=device/bsm");
        }

    connections:
        EndNode[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> repeater[0].port++;//MM    
        repeater[0].port++<--> ClassicalChannel {  distance = 5km; } <--> HoM[0].port++ ;//MIM
        repeater[1].port++ <--> ClassicalChannel {  distance = 15km; } <--> HoM[0].port++;
        	repeater[1].port++ <--> ClassicalChannel {  distance = 15km; } <--> HoM[1].port++;
        repeater[2].port++ <--> ClassicalChannel {  distance = 5km; } <--> HoM[1].port++;
        repeater[1].port++ <--> ClassicalChannel {  distance = 5km; } <--> EndNode[1].port++;
        
        EndNode[2].port++ <--> ClassicalChannel {  distance = 2km; } <--> repeater[0].port++;
        EndNode[3].port++ <--> ClassicalChannel {  distance = 20km; } <--> repeater[0].port++;
        
        repeater[3].port++ <--> ClassicalChannel {  distance = 20km; } <--> repeater[0].port++;
		repeater[3].port++ <--> ClassicalChannel {  distance = 15km; } <--> HoM[2].port++;
		repeater[3].port++ <--> ClassicalChannel {  distance = 15km; } <--> HoM[3].port++;
		EndNode[4].port++ <--> ClassicalChannel {  distance = 15km; } <--> HoM[2].port++;
		EndNode[5].port++ <--> ClassicalChannel {  distance = 15km; } <--> HoM[3].port++;
	
		EndNode[0].quantum_port++ <--> QuantumChannel {  distance = 20km; channel_error_rate = 0.5; photon_loss_ratio = 0; Z_error_ratio = 0; X_error_ratio = 1; Y_error_ratio = 0;} <--> repeater[0].quantum_port_receiver++;//MM	
        repeater[0].quantum_port++<--> QuantumChannel {  distance = 5km; channel_error_rate = 0.5; photon_loss_ratio = 0; Z_error_ratio = 1; X_error_ratio = 0; Y_error_ratio = 0; } <--> HoM[0].quantum_port++;//MIM
        repeater[1].quantum_port++ <--> QuantumChannel {  distance = 15km; channel_error_rate = 0.5; photon_loss_ratio = 0; Z_error_ratio = 1; X_error_ratio = 0; Y_error_ratio = 0; } <--> HoM[0].quantum_port++;
        repeater[1].quantum_port++ <--> QuantumChannel {  distance = 15km; channel_error_rate = 0.5; photon_loss_ratio = 0; Z_error_ratio = 1; X_error_ratio = 0; Y_error_ratio = 0; } <--> HoM[1].quantum_port++;
        repeater[2].quantum_port++ <--> QuantumChannel {  distance = 5km; channel_error_rate = 0.5; photon_loss_ratio = 0; Z_error_ratio = 1; X_error_ratio = 0; Y_error_ratio = 0; } <--> HoM[1].quantum_port++;
		repeater[1].quantum_port_receiver++ <--> QuantumChannel {  distance = 5km; channel_error_rate = 0.05; photon_loss_ratio = 1; Z_error_ratio = 0; X_error_ratio = 0; Y_error_ratio = 0; } <--> EndNode[1].quantum_port++;
		
		EndNode[2].quantum_port++ <--> QuantumChannel {  distance = 2km; } <--> repeater[0].quantum_port_receiver++;
        EndNode[3].quantum_port_receiver++ <--> QuantumChannel {  distance = 20km; } <--> repeater[0].quantum_port++;
		
		repeater[3].quantum_port_receiver++ <--> QuantumChannel {  distance = 20km; } <--> repeater[0].quantum_port++;
		repeater[3].quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> HoM[2].quantum_port++;
		repeater[3].quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> HoM[3].quantum_port++;
		EndNode[4].quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> HoM[2].quantum_port++;
		EndNode[5].quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> HoM[3].quantum_port++;

}



network Layer2_MM_MIM_MIM_MIM_MM
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

    submodules:
        //EndNode[2]: QNode {
        EndNode[1]:QNode{
            address = 100+index;
            nodeType = "EndNode";
            @display("i=device/pc;");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }

        //repeater[4]: QNode {
        repeater[2]:QNode{
            address = 10000+sizeof(EndNode) + index;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=device/smallrouter");
        }

        //HoM[3]: HoM {
        HoM[1]: HoM {
            address = 100000+sizeof(EndNode)+ sizeof(repeater)+ index;
            @display("i=device/bsm");
        }

    connections:
        EndNode[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> repeater[0].port++;//MM    
        repeater[0].port++<--> ClassicalChannel {  distance = 5km; } <--> HoM[0].port++ ;//MIM
        repeater[1].port++ <--> ClassicalChannel {  distance = 15km; } <--> HoM[0].port++;
    	
		EndNode[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> repeater[0].quantum_port_receiver++;//MM	
        repeater[0].quantum_port++<--> QuantumChannel {  distance = 5km; } <--> HoM[0].quantum_port++ ;//MIM
        repeater[1].quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> HoM[0].quantum_port++;
}

network Layer2_MIM_MIM
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

    submodules:
        EndNode[2]: QNode {
            address = index;
            nodeType = "EndNode";
            @display("i=device/pc;");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }

        repeater[1]: QNode {
            address = sizeof(EndNode) + index;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=device/smallrouter");
        }

        HoM[2]: HoM {
            address = sizeof(EndNode)+ sizeof(repeater)+ index;
            @display("i=device/bsm");
        }

    connections:
        EndNode[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> HoM[0].port++;
        HoM[0].port++ <--> ClassicalChannel {  distance = 15km; } <--> repeater[0].port++;
        repeater[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM[1].port++;
        HoM[1].port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode[1].port++;

        EndNode[0].quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> HoM[0].quantum_port++;
        HoM[0].quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> repeater[0].quantum_port++;
        repeater[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HoM[1].quantum_port++;
        HoM[1].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode[1].quantum_port++;
}


network Layer2_MIM_tomography
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=305,240;bgl=3");
    submodules:
        EndNode[2]: QNode {
            address = index;
            nodeType = "EndNode";

            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }

        repeater[9]: QNode {
            address = sizeof(EndNode) + index;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=device/smallrouter");
        }

        HoM[10]: HoM {
            address = sizeof(EndNode)+ sizeof(repeater)+ index;
            @display("i=device/bsm");
        }

    connections:
        EndNode[0].port++ <--> ClassicalChannel {  distance = 1km; } <--> HoM[0].port++;
        HoM[0].port++ <--> ClassicalChannel {  distance = 19km; } <--> repeater[0].port++;

        repeater[0].port++ <--> ClassicalChannel {  distance = 2km; } <--> HoM[1].port++;
        HoM[1].port++ <--> ClassicalChannel {  distance = 18km; } <--> repeater[1].port++;

        repeater[1].port++ <--> ClassicalChannel {  distance = 3km; } <--> HoM[2].port++;
        HoM[2].port++ <--> ClassicalChannel {  distance = 17km; } <--> repeater[2].port++;

        repeater[2].port++ <--> ClassicalChannel {  distance = 4km; } <--> HoM[3].port++;
        HoM[3].port++ <--> ClassicalChannel {  distance = 16km; } <--> repeater[3].port++;

        repeater[3].port++ <--> ClassicalChannel {  distance = 5km; } <--> HoM[4].port++;
        HoM[4].port++ <--> ClassicalChannel {  distance = 15km; } <--> repeater[4].port++;

        repeater[4].port++ <--> ClassicalChannel {  distance = 6km; } <--> HoM[5].port++;
        HoM[5].port++ <--> ClassicalChannel {  distance = 14km; } <--> repeater[5].port++;

        repeater[5].port++ <--> ClassicalChannel {  distance = 7km; } <--> HoM[6].port++;
        HoM[6].port++ <--> ClassicalChannel {  distance = 13km; } <--> repeater[6].port++;

        repeater[6].port++ <--> ClassicalChannel {  distance = 8km; } <--> HoM[7].port++;
        HoM[7].port++ <--> ClassicalChannel {  distance = 12km; } <--> repeater[7].port++;

        repeater[7].port++ <--> ClassicalChannel {  distance = 9km; } <--> HoM[8].port++;
        HoM[8].port++ <--> ClassicalChannel {  distance = 11km; } <--> repeater[8].port++;

        repeater[8].port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM[9].port++;
        HoM[9].port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode[1].port++;



        EndNode[0].quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> HoM[0].quantum_port++;

        HoM[0].quantum_port++ <--> QuantumChannel {  distance = 19km; } <--> repeater[0].quantum_port++;


        repeater[0].quantum_port++ <--> QuantumChannel {  distance = 2km; } <--> HoM[1].quantum_port++;

        HoM[1].quantum_port++ <--> QuantumChannel {  distance = 18km; } <--> repeater[1].quantum_port++;


        repeater[1].quantum_port++ <--> QuantumChannel {  distance = 3km; } <--> HoM[2].quantum_port++;

        HoM[2].quantum_port++ <--> QuantumChannel {  distance = 17km; } <--> repeater[2].quantum_port++;


        repeater[2].quantum_port++ <--> QuantumChannel {  distance = 4km; } <--> HoM[3].quantum_port++;

        HoM[3].quantum_port++ <--> QuantumChannel {  distance = 16km; } <--> repeater[3].quantum_port++;


        repeater[3].quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> HoM[4].quantum_port++;

        HoM[4].quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> repeater[4].quantum_port++;


        repeater[4].quantum_port++ <--> QuantumChannel {  distance = 6km; } <--> HoM[5].quantum_port++;

        HoM[5].quantum_port++ <--> QuantumChannel {  distance = 14km; } <--> repeater[5].quantum_port++;


        repeater[5].quantum_port++ <--> QuantumChannel {  distance = 7km; } <--> HoM[6].quantum_port++;

        HoM[6].quantum_port++ <--> QuantumChannel {  distance = 13km; } <--> repeater[6].quantum_port++;


        repeater[6].quantum_port++ <--> QuantumChannel {  distance = 8km; } <--> HoM[7].quantum_port++;

        HoM[7].quantum_port++ <--> QuantumChannel {  distance = 12km; } <--> repeater[7].quantum_port++;


        repeater[7].quantum_port++ <--> QuantumChannel {  distance = 9km; } <--> HoM[8].quantum_port++;

        HoM[8].quantum_port++ <--> QuantumChannel {  distance = 11km; } <--> repeater[8].quantum_port++;


        repeater[8].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HoM[9].quantum_port++;

        HoM[9].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode[1].quantum_port++;


}
//
// TODO documentation
//
network Network
{
}

