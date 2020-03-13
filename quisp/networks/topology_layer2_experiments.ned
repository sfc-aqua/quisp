package networks;
 

import ned.DatarateChannel;
import ned.IdealChannel;


network Layer2_Simple_MIM_MM_all_in_one
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=707,326");
    submodules:
        EndNode1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=device/pc;p=350,157");
        }
        EndNode2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=device/pc;p=407,231");
        }
        Repeater1[1]: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=220,137");
        }
        Repeater2[1]: QNode {
            address = 4;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=80,189");
        }
        Repeater3[1]: QNode {
            address = 5;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=66,124");
        }
        Repeater4[1]: QNode {
            address = 6;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=132,36");
        }
        Repeater5[1]: QNode {
            address = 7;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=171,76");
        }
        Repeater6[1]: QNode {
            address = 8;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=314,36");
        }
        Repeater7[1]: QNode {
            address = 9;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=314,36");
        }
        Repeater8[1]: QNode {
            address = 10;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=314,36");
        }
        Repeater9[1]: QNode {
            address = 11;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=386,36");
        }
        Repeater10[1]: QNode {
            address = 12;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=568,44");
        }
        Repeater11[1]: QNode {
            address = 13;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=568,44");
        }
        
        HoM1[1]: HoM {
            address = 14;
            @display("i=device/bsm;p=171,231");
        }
        HoM2[1]: HoM {
            address = 15;
            @display("i=device/bsm;p=66,51");
        }
        HoM3[1]: HoM {
            address = 16;
            @display("i=device/bsm;p=235,37");
        }
        HoM4[1]: HoM {
            address = 17;
            @display("i=device/bsm;p=235,37");
        }
        HoM5[1]: HoM {
            address = 18;
            @display("i=device/bsm;p=472,37");
        }
        HoM6[1]: HoM {
            address = 19;
            @display("i=device/bsm;p=557,125");
        }






    connections:
        //10km distance 
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater1[0].port++; //M<-10km->M

        Repeater1[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> HoM1[0].port++;
        HoM1[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> Repeater2[0].port++;//M<-5km->H<-5km->M

        //20km distance
        Repeater2[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Repeater3[0].port++;//M<-20km->M

        Repeater3[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM2[0].port++;
        HoM2[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater4[0].port++;//M<-10km->H<-10km->M

		//30km distance
        Repeater4[0].port++ <--> ClassicalChannel {  distance = 30km; } <--> Repeater5[0].port++;//M<-30km->M

        Repeater5[0].port++ <--> ClassicalChannel {  distance = 15km; } <--> HoM3[0].port++;
        HoM3[0].port++ <--> ClassicalChannel {  distance = 15km; } <--> Repeater6[0].port++;//M<-15km->H<-15km->M

		//40km distance
        Repeater6[0].port++ <--> ClassicalChannel {  distance = 40km; } <--> Repeater7[0].port++;//M<-40km->M

        Repeater7[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> HoM4[0].port++;
        HoM4[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Repeater8[0].port++;//M<-20km->H<-20km->M


		//50km distance
        Repeater8[0].port++ <--> ClassicalChannel {  distance = 50km; } <--> Repeater9[0].port++;//M<-40km->M

        Repeater9[0].port++ <--> ClassicalChannel {  distance = 25km; } <--> HoM5[0].port++;
        HoM5[0].port++ <--> ClassicalChannel {  distance = 25km; } <--> Repeater10[0].port++;//M<-20km->H<-20km->M

		//5km distance
        Repeater10[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> Repeater11[0].port++;//M<-50km->M

        Repeater11[0].port++ <--> ClassicalChannel {  distance = 2.5km; } <--> HoM6[0].port++;
        HoM6[0].port++ <--> ClassicalChannel {  distance = 2.5km; } <--> EndNode2[0].port++;//M<-2.5km->H<-2.5km->M




        //10km distance 
        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 10km; } <--> Repeater1[0].quantum_port++; //M<-10km->M

        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> HoM1[0].quantum_port++;
        HoM1[0].quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> Repeater2[0].quantum_port++;//M<-5km->H<-5km->M

        //20km distance
        Repeater2[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 20km; } <--> Repeater3[0].quantum_port++;//M<-20km->M

        Repeater3[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HoM2[0].quantum_port++;
        HoM2[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> Repeater4[0].quantum_port++;//M<-10km->H<-10km->M

		//30km distance
        Repeater4[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 30km; } <--> Repeater5[0].quantum_port++;//M<-30km->M

        Repeater5[0].quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> HoM3[0].quantum_port++;
        HoM3[0].quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> Repeater6[0].quantum_port++;//M<-15km->H<-15km->M

		//40km distance
        Repeater6[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 40km; } <--> Repeater7[0].quantum_port++;//M<-40km->M

        Repeater7[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> HoM4[0].quantum_port++;
        HoM4[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> Repeater8[0].quantum_port++;//M<-20km->H<-20km->M


		//50km distance
        Repeater8[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 50km; } <--> Repeater9[0].quantum_port++;//M<-40km->M

        Repeater9[0].quantum_port++ <--> QuantumChannel {  distance = 25km; } <--> HoM5[0].quantum_port++;
        HoM5[0].quantum_port++ <--> QuantumChannel {  distance = 25km; } <--> Repeater10[0].quantum_port++;//M<-20km->H<-20km->M

		//5km distance
        Repeater10[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 5km; } <--> Repeater11[0].quantum_port++;//M<-50km->M

        Repeater11[0].quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> HoM6[0].quantum_port++;
        HoM6[0].quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> EndNode2[0].quantum_port++;//M<-2.5km->H<-2.5km->M

}


network Layer2_Simple_MIM_MM_7km
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=707,326");
    submodules:
        EndNode1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=device/pc;p=350,157");
        }
        EndNode2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=device/pc;p=211,224");
        }
        Repeater1[1]: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=220,137");
        }
        HoM1[1]: HoM {
            address = 4;
            @display("i=device/bsm;p=164,176");
        }



    connections:
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 7km; } <--> Repeater1[0].port++;
        Repeater1[0].port++ <--> ClassicalChannel {  distance = 3.5km; } <--> HoM1[0].port++;
        EndNode2[0].port++ <--> ClassicalChannel {  distance = 3.5km; } <--> HoM1[0].port++;

        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 7km; } <--> Repeater1[0].quantum_port++;
        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 3.5km; } <--> HoM1[0].quantum_port++;
        EndNode2[0].quantum_port++ <--> QuantumChannel {  distance = 3.5km; } <--> HoM1[0].quantum_port++;

}

network Layer2_Simple_MIM_MM_10km
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=707,326");
    submodules:
        EndNode1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=device/pc;p=350,157");
        }
        EndNode2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=device/pc;p=211,224");
        }
        Repeater1[1]: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=220,137");
        }
        HoM1[1]: HoM {
            address = 4;
            @display("i=device/bsm;p=164,176");
        }



    connections:
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater1[0].port++;
        Repeater1[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> HoM1[0].port++;
        EndNode2[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> HoM1[0].port++;

        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 10km; } <--> Repeater1[0].quantum_port++;
        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> HoM1[0].quantum_port++;
        EndNode2[0].quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> HoM1[0].quantum_port++;

}



network Layer2_Simple_MIM_MM_15km
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=707,326");
    submodules:
        EndNode1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=device/pc;p=350,157");
        }
        EndNode2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=device/pc;p=211,224");
        }
        Repeater1[1]: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=220,137");
        }
        HoM1[1]: HoM {
            address = 4;
            @display("i=device/bsm;p=164,176");
        }



    connections:
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 15km; } <--> Repeater1[0].port++;
        Repeater1[0].port++ <--> ClassicalChannel {  distance = 7.5km; } <--> HoM1[0].port++;
        EndNode2[0].port++ <--> ClassicalChannel {  distance = 7.5km; } <--> HoM1[0].port++;

        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 15km; } <--> Repeater1[0].quantum_port++;
        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 7.5km; } <--> HoM1[0].quantum_port++;
        EndNode2[0].quantum_port++ <--> QuantumChannel {  distance = 7.5km; } <--> HoM1[0].quantum_port++;

}

network Layer2_Simple_MIM_MM_50km
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=707,326");
    submodules:
        EndNode1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=device/pc;p=350,157");
        }
        EndNode2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=device/pc;p=211,224");
        }
        Repeater1[1]: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=220,137");
        }
        HoM1[1]: HoM {
            address = 4;
            @display("i=device/bsm;p=164,176");
        }



    connections:
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 50km; } <--> Repeater1[0].port++;
        Repeater1[0].port++ <--> ClassicalChannel {  distance = 25km; } <--> HoM1[0].port++;
        EndNode2[0].port++ <--> ClassicalChannel {  distance = 25km; } <--> HoM1[0].port++;

        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 50km; } <--> Repeater1[0].quantum_port++;
        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 25km; } <--> HoM1[0].quantum_port++;
        EndNode2[0].quantum_port++ <--> QuantumChannel {  distance = 25km; } <--> HoM1[0].quantum_port++;

}


network Layer2_Simple_MIM_MM_40km
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=707,326");
    submodules:
        EndNode1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=device/pc;p=350,157");
        }
        EndNode2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=device/pc;p=211,224");
        }
        Repeater1[1]: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=220,137");
        }
        HoM1[1]: HoM {
            address = 4;
            @display("i=device/bsm;p=164,176");
        }



    connections:
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 40km; } <--> Repeater1[0].port++;
        Repeater1[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> HoM1[0].port++;
        EndNode2[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> HoM1[0].port++;

        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 40km; } <--> Repeater1[0].quantum_port++;
        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> HoM1[0].quantum_port++;
        EndNode2[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> HoM1[0].quantum_port++;

}

network Layer2_Simple_MIM_MM_30km
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=707,326");
    submodules:
        EndNode1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=device/pc;p=350,157");
        }
        EndNode2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=device/pc;p=211,224");
        }
        Repeater1[1]: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=220,137");
        }
        HoM1[1]: HoM {
            address = 4;
            @display("i=device/bsm;p=164,176");
        }



    connections:
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 30km; } <--> Repeater1[0].port++;
        Repeater1[0].port++ <--> ClassicalChannel {  distance = 15km; } <--> HoM1[0].port++;
        EndNode2[0].port++ <--> ClassicalChannel {  distance = 15km; } <--> HoM1[0].port++;

        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 30km; } <--> Repeater1[0].quantum_port++;
        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> HoM1[0].quantum_port++;
        EndNode2[0].quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> HoM1[0].quantum_port++;

}



network Layer2_Simple_MIM_MM
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=707,326");
    submodules:
        EndNode1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=device/pc;p=350,157");
        }
        EndNode2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=device/pc;p=211,224");
        }
        Repeater1[1]: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=220,137");
        }
        HoM1[1]: HoM {
            address = 4;
            @display("i=device/bsm;p=164,176");
        }



    connections:
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Repeater1[0].port++;
        Repeater1[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM1[0].port++;
        EndNode2[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM1[0].port++;

        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 20km; } <--> Repeater1[0].quantum_port++;
        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HoM1[0].quantum_port++;
        EndNode2[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HoM1[0].quantum_port++;

}




network Layer2_Simple_MIM_MM_same
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=707,326");
    submodules:
        EndNode1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=device/pc;p=350,157");
        }
        EndNode2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=device/pc;p=211,224");
        }
        Repeater1[1]: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=220,137");
        }
        HoM1[1]: HoM {
            address = 4;
            @display("i=device/bsm;p=164,176");
        }



    connections:
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater1[0].port++;
        Repeater1[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM1[0].port++;
        EndNode2[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM1[0].port++;

        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 10km; } <--> Repeater1[0].quantum_port++;
        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HoM1[0].quantum_port++;
        EndNode2[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HoM1[0].quantum_port++;

}


network Layer2_RouterNet
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=707,326");
    submodules:
        Router1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=device/router;p=350,157");
        }
        Router2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=device/router;p=211,224");
        }
        Router3[1]: QNode {
            address = 3;
            nodeType = "EndNode";
            @display("i=device/router;p=220,137");
        }
        HoM1[1]: HoM {
            address = 4;
            @display("i=device/bsm;p=164,176");
        }
        Router5[1]: QNode {
            address = 5;
            @display("i=device/router;p=313,246");
        }
        Router4[1]: QNode {
            address = 6;
            nodeType = "EndNode";
            @display("i=device/router;p=432,246");
        }


    connections:
        Router1[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Router2[0].port++;
        Router3[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Router1[0].port++;

        Router3[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM1[0].port++;
        Router2[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM1[0].port++;

        Router2[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Router5[0].port++;
        Router4[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Router5[0].port++;
        Router4[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Router1[0].port++;
        Router5[0].port++ <--> ClassicalChannel {  distance = 25km; } <--> Router1[0].port++;
        Router4[0].port++ <--> ClassicalChannel {  distance = 40km; } <--> Router3[0].port++;






        Router1[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> Router2[0].quantum_port_receiver++;
        Router3[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> Router1[0].quantum_port_receiver++;
        Router3[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HoM1[0].quantum_port++;
        Router2[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HoM1[0].quantum_port++;

        Router2[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> Router5[0].quantum_port_receiver++;
        Router4[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> Router5[0].quantum_port_receiver++;
        Router4[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> Router1[0].quantum_port_receiver++;
        Router5[0].quantum_port++ <--> QuantumChannel {  distance = 25km; } <--> Router1[0].quantum_port_receiver++;
        Router4[0].quantum_port++ <--> QuantumChannel {  distance = 40km; } <--> Router3[0].quantum_port_receiver++;
}


network Layer2_Star_Sep
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=707,326");
    submodules:
        Router1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=device/router;p=350,157");
        }
        Router2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=device/router;p=211,224");
        }
        Router3[1]: QNode {
            address = 3;
            nodeType = "EndNode";
            @display("i=device/router;p=220,137");
        }
        HoM1[1]: HoM {
            address = 4;
            @display("i=device/bsm;p=164,176");
        }
        Router5[1]: QNode {
            address = 5;
            @display("i=device/router;p=313,246");
        }
        Router4[1]: QNode {
            address = 6;
            nodeType = "EndNode";
            @display("i=device/router;p=432,246");
        }
        Repeater1[1]: QNode {
            address = 7;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=device/smallrouter;p=406,109");
        }
        HoM2[1]: HoM {
            address = 8;
            @display("i=device/bsm;p=484,98");
        }
        EndNode1[1]: QNode {
            address = 9;
            nodeType = "EndNode";
            @display("i=device/pc;p=551,84");
        }
        HoM3[1]: HoM {
            address = 10;
            @display("i=device/bsm;p=445,157");
        }
        EndNode2[1]: QNode {
            address = 11;
            nodeType = "EndNode";
            @display("i=device/pc;p=518,157");
        }
        EndNode3[1]: QNode {
            address = 12;
            nodeType = "EndNode";
            @display("i=device/pc;p=220,297");
        }
        EndNode4[1]: QNode {
            address = 13;
            nodeType = "EndNode";
            @display("i=device/pc;p=128,285");
        }
        EndNode5[1]: QNode {
            address = 14;
            nodeType = "EndNode";
            @display("i=device/pc;p=109,246");
        }
        EndNode6[1]: QNode {
            address = 15;
            nodeType = "EndNode";
            @display("i=device/pc;p=503,263");
        }
        HoM4[1]: HoM {
            address = 16;
            @display("i=device/bsm;p=324,98");
        }
        HoM5[1]: HoM {
            address = 17;
            @display("i=device/bsm;p=270,70");
        }
        HoM6[1]: HoM {
            address = 18;
            @display("i=device/bsm;p=193,77");
        }
        HoM7[1]: HoM {
            address = 19;
            @display("i=device/bsm;p=128,137");
        }

        Repeater2[1]: QNode {
            address = 20;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=device/smallrouter;p=350,54");
        }
        Repeater3[1]: QNode {
            address = 21;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=device/smallrouter;p=285,22");
        }
        Repeater4[1]: QNode {
            address = 22;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=device/smallrouter;p=89,60");
        }
        Repeater5[1]: QNode {
            address = 23;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=device/smallrouter;p=58,143");
        }
        EndNode7[1]: QNode {
            address = 24;
            nodeType = "EndNode";
            @display("i=device/pc;p=419,16");
        }
        EndNode8[1]: QNode {
            address = 25;
            nodeType = "EndNode";
            @display("i=device/pc;p=211,16");
        }
        EndNode9[1]: QNode {
            address = 26;
            nodeType = "EndNode";
            @display("i=device/pc;p=34,77");
        }
        EndNode10[1]: QNode {
            address = 27;
            nodeType = "EndNode";
            @display("i=device/pc;p=13,208");
        }

    connections:
        Router1[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Router2[0].port++;
        Router3[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Router1[0].port++;

        Router3[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM1[0].port++;
        Router2[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM1[0].port++;

        Router2[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Router5[0].port++;
        Router4[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Router5[0].port++;
        Router4[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Router1[0].port++;
        Router5[0].port++ <--> ClassicalChannel {  distance = 25km; } <--> Router1[0].port++;
        Router4[0].port++ <--> ClassicalChannel {  distance = 40km; } <--> Router3[0].port++;

        Repeater1[0].port++ <--> ClassicalChannel {  distance = 25km; } <--> Router1[0].port++;
        Repeater1[0].port++ <--> ClassicalChannel {  distance = 25km; } <--> HoM2[0].port++;
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 25km; } <--> HoM2[0].port++;
        HoM3[0].port++ <--> ClassicalChannel {  distance = 25km; } <--> Router1[0].port++;
        HoM3[0].port++ <--> ClassicalChannel {  distance = 25km; } <--> EndNode2[0].port++;

        Router2[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> EndNode3[0].port++;
        Router2[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> EndNode4[0].port++;
        Router2[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> EndNode5[0].port++;

        Router4[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> EndNode6[0].port++;

        Router3[0].port++ <--> ClassicalChannel {  distance = 7km; } <--> HoM4[0].port++;
        Router3[0].port++ <--> ClassicalChannel {  distance = 8km; } <--> HoM5[0].port++;
        Router3[0].port++ <--> ClassicalChannel {  distance = 9km; } <--> HoM6[0].port++;
        Router3[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM7[0].port++;

        Repeater2[0].port++ <--> ClassicalChannel {  distance = 7km; } <--> HoM4[0].port++;
        Repeater3[0].port++ <--> ClassicalChannel {  distance = 8km; } <--> HoM5[0].port++;
        Repeater4[0].port++ <--> ClassicalChannel {  distance = 9km; } <--> HoM6[0].port++;
        Repeater5[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM7[0].port++;

        EndNode7[0].port++ <--> ClassicalChannel {  distance = 7km; } <--> Repeater2[0].port++;
        EndNode8[0].port++ <--> ClassicalChannel {  distance = 8km; } <--> Repeater3[0].port++;
        EndNode9[0].port++ <--> ClassicalChannel {  distance = 9km; } <--> Repeater4[0].port++;
        EndNode10[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater5[0].port++;






        Router1[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> Router2[0].quantum_port_receiver++;
        Router3[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> Router1[0].quantum_port_receiver++;
        Router3[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HoM1[0].quantum_port++;
        Router2[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HoM1[0].quantum_port++;

        Router2[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> Router5[0].quantum_port_receiver++;
        Router4[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> Router5[0].quantum_port_receiver++;
        Router4[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> Router1[0].quantum_port_receiver++;
        Router5[0].quantum_port++ <--> QuantumChannel {  distance = 25km; } <--> Router1[0].quantum_port_receiver++;
        Router4[0].quantum_port++ <--> QuantumChannel {  distance = 40km; } <--> Router3[0].quantum_port_receiver++;

        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 25km; } <--> Router1[0].quantum_port++;
        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 25km; } <--> HoM2[0].quantum_port++;
        EndNode1[0].quantum_port++ <--> QuantumChannel {  distance = 25km; } <--> HoM2[0].quantum_port++;
        HoM3[0].quantum_port++ <--> QuantumChannel {  distance = 25km; } <--> Router1[0].quantum_port++;
        HoM3[0].quantum_port++ <--> QuantumChannel {  distance = 25km; } <--> EndNode2[0].quantum_port++;

        Router2[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 5km; } <--> EndNode3[0].quantum_port++;
        Router2[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 5km; } <--> EndNode4[0].quantum_port++;
        Router2[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 5km; } <--> EndNode5[0].quantum_port++;
        Router4[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 20km; } <--> EndNode6[0].quantum_port++;

        Router3[0].quantum_port++ <--> QuantumChannel {  distance = 7km; } <--> HoM4[0].quantum_port++;
        Router3[0].quantum_port++ <--> QuantumChannel {  distance = 8km; } <--> HoM5[0].quantum_port++;
        Router3[0].quantum_port++ <--> QuantumChannel {  distance = 9km; } <--> HoM6[0].quantum_port++;
        Router3[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HoM7[0].quantum_port++;

        Repeater2[0].quantum_port++ <--> QuantumChannel {  distance = 7km; } <--> HoM4[0].quantum_port++;
        Repeater3[0].quantum_port++ <--> QuantumChannel {  distance = 8km; } <--> HoM5[0].quantum_port++;
        Repeater4[0].quantum_port++ <--> QuantumChannel {  distance = 9km; } <--> HoM6[0].quantum_port++;
        Repeater5[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HoM7[0].quantum_port++;

        EndNode7[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 7km; } <--> Repeater2[0].quantum_port++;
        EndNode8[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 8km; } <--> Repeater3[0].quantum_port++;
        EndNode9[0].quantum_port++ <--> QuantumChannel {  distance = 9km; } <--> Repeater4[0].quantum_port_receiver++;
        EndNode10[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> Repeater5[0].quantum_port_receiver++;
}





network Layer2_MM_MIM_MIM_MIM_MM
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

    submodules:
        //EndNode[2]: QNode {
        EndNode[1]: QNode {
            address = 100+index;
            nodeType = "EndNode";
            @display("i=device/pc;");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }

        //repeater[4]: QNode {
        repeater[2]: QNode {
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
        repeater[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> HoM[0].port++;//MIM
        repeater[1].port++ <--> ClassicalChannel {  distance = 15km; } <--> HoM[0].port++;

        EndNode[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> repeater[0].quantum_port_receiver++;//MM	
        repeater[0].quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> HoM[0].quantum_port++;//MIM
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

