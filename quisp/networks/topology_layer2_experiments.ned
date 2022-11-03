package networks;

import ned.DatarateChannel;
import ned.IdealChannel;

import channels.*;
import modules.*;
import modules.Backend.Backend;
import modules.Logger.Logger;

network Layer2_Simple_MIM_MM_all_in_one
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=707,326");
    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=COMP;p=297,173");
        }
        EndNode2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=COMP;p=407,231");
        }
        Repeater1[1]: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=REP1G;p=270,238");
        }
        Repeater2[1]: QNode {
            address = 4;
            nodeType = "Repeater";
            @display("i=REP1G;p=66,259");
        }
        Repeater3[1]: QNode {
            address = 5;
            nodeType = "Repeater";
            @display("i=REP1G;p=47,189");
        }
        Repeater4[1]: QNode {
            address = 6;
            nodeType = "Repeater";
            @display("i=REP1G;p=47,51");
        }
        Repeater5[1]: QNode {
            address = 7;
            nodeType = "Repeater";
            @display("i=REP1G;p=121,36");
        }
        Repeater6[1]: QNode {
            address = 8;
            nodeType = "Repeater";
            @display("i=REP1G;p=262,45");
        }
        Repeater7[1]: QNode {
            address = 9;
            nodeType = "Repeater";
            @display("i=REP1G;p=343,37");
        }
        Repeater8[1]: QNode {
            address = 10;
            nodeType = "Repeater";
            @display("i=REP1G;p=474,37");
        }
        Repeater9[1]: QNode {
            address = 11;
            nodeType = "Repeater";
            @display("i=REP1G;p=577,29");
        }
        Repeater10[1]: QNode {
            address = 12;
            nodeType = "Repeater";
            @display("i=REP1G;p=666,189");
        }
        Repeater11[1]: QNode {
            address = 13;
            nodeType = "Repeater";
            @display("i=REP1G;p=623,252");
        }

        HOM1[1]: HOM {
            address = 14;
            @display("p=171,231");
        }
        HOM2[1]: HOM {
            address = 15;
            @display("p=47,121");
        }
        HOM3[1]: HOM {
            address = 16;
            @display("p=196,29");
        }
        HOM4[1]: HOM {
            address = 17;
            @display("p=408,86");
        }
        HOM5[1]: HOM {
            address = 18;
            @display("p=658,86");
        }
        HOM6[1]: HOM {
            address = 19;
            @display("p=509,245");
        }

    connections:
        //10km distance
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater1[0].port++; //M<-10km->M

        Repeater1[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> HOM1[0].port++;
        HOM1[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> Repeater2[0].port++;//M<-5km->H<-5km->M

        //20km distance
        Repeater2[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Repeater3[0].port++;//M<-20km->M

        Repeater3[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HOM2[0].port++;
        HOM2[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater4[0].port++;//M<-10km->H<-10km->M

		//30km distance
        Repeater4[0].port++ <--> ClassicalChannel {  distance = 30km; } <--> Repeater5[0].port++;//M<-30km->M

        Repeater5[0].port++ <--> ClassicalChannel {  distance = 15km; } <--> HOM3[0].port++;
        HOM3[0].port++ <--> ClassicalChannel {  distance = 15km; } <--> Repeater6[0].port++;//M<-15km->H<-15km->M

		//40km distance
        Repeater6[0].port++ <--> ClassicalChannel {  distance = 40km; } <--> Repeater7[0].port++;//M<-40km->M

        Repeater7[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> HOM4[0].port++;
        HOM4[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Repeater8[0].port++;//M<-20km->H<-20km->M


		//50km distance
        Repeater8[0].port++ <--> ClassicalChannel {  distance = 50km; } <--> Repeater9[0].port++;//M<-40km->M

        Repeater9[0].port++ <--> ClassicalChannel {  distance = 25km; } <--> HOM5[0].port++;
        HOM5[0].port++ <--> ClassicalChannel {  distance = 25km; } <--> Repeater10[0].port++;//M<-20km->H<-20km->M

		//5km distance
        Repeater10[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> Repeater11[0].port++;//M<-50km->M

        Repeater11[0].port++ <--> ClassicalChannel {  distance = 2.5km; } <--> HOM6[0].port++;
        HOM6[0].port++ <--> ClassicalChannel {  distance = 2.5km; } <--> EndNode2[0].port++;//M<-2.5km->H<-2.5km->M




        //10km distance
        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 10km; } <--> Repeater1[0].quantum_port++; //M<-10km->M

        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> HOM1[0].quantum_port++;
        HOM1[0].quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> Repeater2[0].quantum_port++;//M<-5km->H<-5km->M

        //20km distance
        Repeater2[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 20km; } <--> Repeater3[0].quantum_port++;//M<-20km->M

        Repeater3[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HOM2[0].quantum_port++;
        HOM2[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> Repeater4[0].quantum_port++;//M<-10km->H<-10km->M

		//30km distance
        Repeater4[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 30km; } <--> Repeater5[0].quantum_port++;//M<-30km->M

        Repeater5[0].quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> HOM3[0].quantum_port++;
        HOM3[0].quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> Repeater6[0].quantum_port++;//M<-15km->H<-15km->M

		//40km distance
        Repeater6[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 40km; } <--> Repeater7[0].quantum_port++;//M<-40km->M

        Repeater7[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> HOM4[0].quantum_port++;
        HOM4[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> Repeater8[0].quantum_port++;//M<-20km->H<-20km->M


		//50km distance
        Repeater8[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 50km; } <--> Repeater9[0].quantum_port++;//M<-40km->M

        Repeater9[0].quantum_port++ <--> QuantumChannel {  distance = 25km; } <--> HOM5[0].quantum_port++;
        HOM5[0].quantum_port++ <--> QuantumChannel {  distance = 25km; } <--> Repeater10[0].quantum_port++;//M<-20km->H<-20km->M

		//5km distance
        Repeater10[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 5km; } <--> Repeater11[0].quantum_port++;//M<-50km->M

        Repeater11[0].quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> HOM6[0].quantum_port++;
        HOM6[0].quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> EndNode2[0].quantum_port++;//M<-2.5km->H<-2.5km->M

}


network Layer2_Simple_MIM_MM_7km
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=707,326");
    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=COMP;p=350,157");
        }
        EndNode2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=COMP;p=211,224");
        }
        Repeater1[1]: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=REP1G;p=220,137");
        }
        HOM1[1]: HOM {
            address = 4;
            @display("p=164,176");
        }


    connections:
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 7km; } <--> Repeater1[0].port++;
        Repeater1[0].port++ <--> ClassicalChannel {  distance = 3.5km; } <--> HOM1[0].port++;
        EndNode2[0].port++ <--> ClassicalChannel {  distance = 3.5km; } <--> HOM1[0].port++;

        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 7km; } <--> Repeater1[0].quantum_port++;
        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 3.5km; } <--> HOM1[0].quantum_port++;
        EndNode2[0].quantum_port++ <--> QuantumChannel {  distance = 3.5km; } <--> HOM1[0].quantum_port++;

}

network Layer2_Simple_MIM_MM_10km
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=707,326");
    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=COMP;p=350,157");
        }
        EndNode2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=COMP;p=211,224");
        }
        Repeater1[1]: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=REP1G;p=220,137");
        }
        HOM1[1]: HOM {
            address = 4;
            @display("p=164,176");
        }



    connections:
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater1[0].port++;
        Repeater1[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> HOM1[0].port++;
        EndNode2[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> HOM1[0].port++;

        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 10km; } <--> Repeater1[0].quantum_port++;
        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> HOM1[0].quantum_port++;
        EndNode2[0].quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> HOM1[0].quantum_port++;

}



network Layer2_Simple_MIM_MM_15km
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=707,326");
    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=COMP;p=350,157");
        }
        EndNode2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=COMP;p=211,224");
        }
        Repeater1[1]: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=REP1G;p=220,137");
        }
        HOM1[1]: HOM {
            address = 4;
            @display("p=164,176");
        }



    connections:
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 15km; } <--> Repeater1[0].port++;
        Repeater1[0].port++ <--> ClassicalChannel {  distance = 7.5km; } <--> HOM1[0].port++;
        EndNode2[0].port++ <--> ClassicalChannel {  distance = 7.5km; } <--> HOM1[0].port++;

        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 15km; } <--> Repeater1[0].quantum_port++;
        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 7.5km; } <--> HOM1[0].quantum_port++;
        EndNode2[0].quantum_port++ <--> QuantumChannel {  distance = 7.5km; } <--> HOM1[0].quantum_port++;

}

network Layer2_Simple_MIM_MM_50km
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=707,326");
    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=COMP;p=350,157");
        }
        EndNode2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=COMP;p=211,224");
        }
        Repeater1[1]: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=REP1G;p=220,137");
        }
        HOM1[1]: HOM {
            address = 4;
            @display("p=164,176");
        }



    connections:
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 50km; } <--> Repeater1[0].port++;
        Repeater1[0].port++ <--> ClassicalChannel {  distance = 25km; } <--> HOM1[0].port++;
        EndNode2[0].port++ <--> ClassicalChannel {  distance = 25km; } <--> HOM1[0].port++;

        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 50km; } <--> Repeater1[0].quantum_port++;
        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 25km; } <--> HOM1[0].quantum_port++;
        EndNode2[0].quantum_port++ <--> QuantumChannel {  distance = 25km; } <--> HOM1[0].quantum_port++;

}


network Layer2_Simple_MIM_MM_40km
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=707,326");
    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=COMP;p=350,157");
        }
        EndNode2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=COMP;p=211,224");
        }
        Repeater1[1]: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=REP1G;p=220,137");
        }
        HOM1[1]: HOM {
            address = 4;
            @display("p=164,176");
        }



    connections:
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 40km; } <--> Repeater1[0].port++;
        Repeater1[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> HOM1[0].port++;
        EndNode2[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> HOM1[0].port++;

        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 40km; } <--> Repeater1[0].quantum_port++;
        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> HOM1[0].quantum_port++;
        EndNode2[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> HOM1[0].quantum_port++;

}

network Layer2_Simple_MIM_MM_30km
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=707,326");
    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=COMP;p=350,157");
        }
        EndNode2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=COMP;p=211,224");
        }
        Repeater1[1]: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=REP1G;p=220,137");
        }
        HOM1[1]: HOM {
            address = 4;
            @display("p=164,176");
        }



    connections:
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 30km; } <--> Repeater1[0].port++;
        Repeater1[0].port++ <--> ClassicalChannel {  distance = 15km; } <--> HOM1[0].port++;
        EndNode2[0].port++ <--> ClassicalChannel {  distance = 15km; } <--> HOM1[0].port++;

        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 30km; } <--> Repeater1[0].quantum_port++;
        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> HOM1[0].quantum_port++;
        EndNode2[0].quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> HOM1[0].quantum_port++;

}



network Layer2_Simple_MIM_MM
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=707,326");
    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=COMP;p=350,157");
        }
        EndNode2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=COMP;p=211,224");
        }
        Repeater1[1]: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=REP1G;p=220,137");
        }
        HOM1[1]: HOM {
            address = 4;
            @display("p=164,176");
        }



    connections:
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Repeater1[0].port++;
        Repeater1[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HOM1[0].port++;
        EndNode2[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HOM1[0].port++;

        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 20km; } <--> Repeater1[0].quantum_port++;
        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HOM1[0].quantum_port++;
        EndNode2[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HOM1[0].quantum_port++;

}




network Layer2_Simple_MIM_MM_same
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=707,326");
    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=COMP;p=350,157");
        }
        EndNode2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=COMP;p=211,224");
        }
        Repeater1[1]: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=REP1G;p=220,137");
        }
        HOM1[1]: HOM {
            address = 4;
            @display("p=164,176");
        }



    connections:
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater1[0].port++;
        Repeater1[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HOM1[0].port++;
        EndNode2[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HOM1[0].port++;

        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 10km; } <--> Repeater1[0].quantum_port++;
        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HOM1[0].quantum_port++;
        EndNode2[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HOM1[0].quantum_port++;

}


network Layer2_RouterNet
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=707,326");
    submodules:
        backend: Backend;
        logger: Logger;
        Router1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=COMP;p=350,157");
        }
        Router2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=COMP;p=211,224");
        }
        Router3[1]: QNode {
            address = 3;
            nodeType = "EndNode";
            @display("i=COMP;p=220,137");
        }
        HOM1[1]: HOM {
            address = 4;
            @display("p=164,176");
        }
        Router5[1]: QNode {
            address = 5;
            @display("i=RTR;p=313,246");
        }
        Router4[1]: QNode {
            address = 6;
            nodeType = "EndNode";
            @display("i=RTR;p=432,246");
        }


    connections:
        Router1[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Router2[0].port++;
        Router3[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Router1[0].port++;

        Router3[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HOM1[0].port++;
        Router2[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HOM1[0].port++;

        Router2[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Router5[0].port++;
        Router4[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Router5[0].port++;
        Router4[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Router1[0].port++;
        Router5[0].port++ <--> ClassicalChannel {  distance = 25km; } <--> Router1[0].port++;
        Router4[0].port++ <--> ClassicalChannel {  distance = 40km; } <--> Router3[0].port++;






        Router1[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> Router2[0].quantum_port_receiver++;
        Router3[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> Router1[0].quantum_port_receiver++;
        Router3[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HOM1[0].quantum_port++;
        Router2[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HOM1[0].quantum_port++;

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
        backend: Backend;
        logger: Logger;
        Router1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=RTR;p=350,157");
        }
        Router2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=RTR;p=211,224");
        }
        Router3[1]: QNode {
            address = 3;
            nodeType = "EndNode";
            @display("i=RTR;p=220,137");
        }
        HOM1[1]: HOM {
            address = 4;
            @display("p=164,176");
        }
        Router5[1]: QNode {
            address = 5;
            @display("i=RTR;p=313,246");
        }
        Router4[1]: QNode {
            address = 6;
            nodeType = "EndNode";
            @display("i=RTR;p=432,246");
        }
        Repeater1[1]: QNode {
            address = 7;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=REP1G;p=406,109");
        }
        HOM2[1]: HOM {
            address = 8;
            @display("p=484,98");
        }
        EndNode1[1]: QNode {
            address = 9;
            nodeType = "EndNode";
            @display("i=COMP;p=551,84");
        }
        HOM3[1]: HOM {
            address = 10;
            @display("p=445,157");
        }
        EndNode2[1]: QNode {
            address = 11;
            nodeType = "EndNode";
            @display("i=COMP;p=518,157");
        }
        EndNode3[1]: QNode {
            address = 12;
            nodeType = "EndNode";
            @display("i=COMP;p=220,297");
        }
        EndNode4[1]: QNode {
            address = 13;
            nodeType = "EndNode";
            @display("i=COMP;p=128,285");
        }
        EndNode5[1]: QNode {
            address = 14;
            nodeType = "EndNode";
            @display("i=COMP;p=109,246");
        }
        EndNode6[1]: QNode {
            address = 15;
            nodeType = "EndNode";
            @display("i=COMP;p=503,263");
        }
        HOM4[1]: HOM {
            address = 16;
            @display("p=324,98");
        }
        HOM5[1]: HOM {
            address = 17;
            @display("p=270,70");
        }
        HOM6[1]: HOM {
            address = 18;
            @display("p=193,77");
        }
        HOM7[1]: HOM {
            address = 19;
            @display("p=128,137");
        }

        Repeater2[1]: QNode {
            address = 20;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=REP1G;p=350,54");
        }
        Repeater3[1]: QNode {
            address = 21;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=REP1G;p=285,22");
        }
        Repeater4[1]: QNode {
            address = 22;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=REP1G;p=89,60");
        }
        Repeater5[1]: QNode {
            address = 23;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=REP1G;p=58,143");
        }
        EndNode7[1]: QNode {
            address = 24;
            nodeType = "EndNode";
            @display("i=COMP;p=419,16");
        }
        EndNode8[1]: QNode {
            address = 25;
            nodeType = "EndNode";
            @display("i=COMP;p=211,16");
        }
        EndNode9[1]: QNode {
            address = 26;
            nodeType = "EndNode";
            @display("i=COMP;p=34,77");
        }
        EndNode10[1]: QNode {
            address = 27;
            nodeType = "EndNode";
            @display("i=COMP;p=13,208");
        }

    connections:
        Router1[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Router2[0].port++;
        Router3[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Router1[0].port++;

        Router3[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HOM1[0].port++;
        Router2[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HOM1[0].port++;

        Router2[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Router5[0].port++;
        Router4[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Router5[0].port++;
        Router4[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Router1[0].port++;
        Router5[0].port++ <--> ClassicalChannel {  distance = 25km; } <--> Router1[0].port++;
        Router4[0].port++ <--> ClassicalChannel {  distance = 40km; } <--> Router3[0].port++;

        Repeater1[0].port++ <--> ClassicalChannel {  distance = 25km; } <--> Router1[0].port++;
        Repeater1[0].port++ <--> ClassicalChannel {  distance = 25km; } <--> HOM2[0].port++;
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 25km; } <--> HOM2[0].port++;
        HOM3[0].port++ <--> ClassicalChannel {  distance = 25km; } <--> Router1[0].port++;
        HOM3[0].port++ <--> ClassicalChannel {  distance = 25km; } <--> EndNode2[0].port++;

        Router2[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> EndNode3[0].port++;
        Router2[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> EndNode4[0].port++;
        Router2[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> EndNode5[0].port++;

        Router4[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> EndNode6[0].port++;

        Router3[0].port++ <--> ClassicalChannel {  distance = 7km; } <--> HOM4[0].port++;
        Router3[0].port++ <--> ClassicalChannel {  distance = 8km; } <--> HOM5[0].port++;
        Router3[0].port++ <--> ClassicalChannel {  distance = 9km; } <--> HOM6[0].port++;
        Router3[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HOM7[0].port++;

        Repeater2[0].port++ <--> ClassicalChannel {  distance = 7km; } <--> HOM4[0].port++;
        Repeater3[0].port++ <--> ClassicalChannel {  distance = 8km; } <--> HOM5[0].port++;
        Repeater4[0].port++ <--> ClassicalChannel {  distance = 9km; } <--> HOM6[0].port++;
        Repeater5[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HOM7[0].port++;

        EndNode7[0].port++ <--> ClassicalChannel {  distance = 7km; } <--> Repeater2[0].port++;
        EndNode8[0].port++ <--> ClassicalChannel {  distance = 8km; } <--> Repeater3[0].port++;
        EndNode9[0].port++ <--> ClassicalChannel {  distance = 9km; } <--> Repeater4[0].port++;
        EndNode10[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> Repeater5[0].port++;






        Router1[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> Router2[0].quantum_port_receiver++;
        Router3[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> Router1[0].quantum_port_receiver++;
        Router3[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HOM1[0].quantum_port++;
        Router2[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HOM1[0].quantum_port++;

        Router2[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> Router5[0].quantum_port_receiver++;
        Router4[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> Router5[0].quantum_port_receiver++;
        Router4[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> Router1[0].quantum_port_receiver++;
        Router5[0].quantum_port++ <--> QuantumChannel {  distance = 25km; } <--> Router1[0].quantum_port_receiver++;
        Router4[0].quantum_port++ <--> QuantumChannel {  distance = 40km; } <--> Router3[0].quantum_port_receiver++;

        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 25km; } <--> Router1[0].quantum_port++;
        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 25km; } <--> HOM2[0].quantum_port++;
        EndNode1[0].quantum_port++ <--> QuantumChannel {  distance = 25km; } <--> HOM2[0].quantum_port++;
        HOM3[0].quantum_port++ <--> QuantumChannel {  distance = 25km; } <--> Router1[0].quantum_port++;
        HOM3[0].quantum_port++ <--> QuantumChannel {  distance = 25km; } <--> EndNode2[0].quantum_port++;

        Router2[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 5km; } <--> EndNode3[0].quantum_port++;
        Router2[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 5km; } <--> EndNode4[0].quantum_port++;
        Router2[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 5km; } <--> EndNode5[0].quantum_port++;
        Router4[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 20km; } <--> EndNode6[0].quantum_port++;

        Router3[0].quantum_port++ <--> QuantumChannel {  distance = 7km; } <--> HOM4[0].quantum_port++;
        Router3[0].quantum_port++ <--> QuantumChannel {  distance = 8km; } <--> HOM5[0].quantum_port++;
        Router3[0].quantum_port++ <--> QuantumChannel {  distance = 9km; } <--> HOM6[0].quantum_port++;
        Router3[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HOM7[0].quantum_port++;

        Repeater2[0].quantum_port++ <--> QuantumChannel {  distance = 7km; } <--> HOM4[0].quantum_port++;
        Repeater3[0].quantum_port++ <--> QuantumChannel {  distance = 8km; } <--> HOM5[0].quantum_port++;
        Repeater4[0].quantum_port++ <--> QuantumChannel {  distance = 9km; } <--> HOM6[0].quantum_port++;
        Repeater5[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HOM7[0].quantum_port++;

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
        backend: Backend;
        logger: Logger;
        //EndNode[2]: QNode {
        EndNode[1]: QNode {
            address = 100+index;
            nodeType = "EndNode";
            @display("i=COMP;");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }

        //repeater[4]: QNode {
        repeater[2]: QNode {
            address = 10000+sizeof(EndNode) + index;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=REP1G");
        }

        //HOM[3]: HOM {
        HOM[1]: HOM {
            address = 100000+sizeof(EndNode)+ sizeof(repeater)+ index;
        }

    connections:
        EndNode[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> repeater[0].port++;//MM
        repeater[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> HOM[0].port++;//MIM
        repeater[1].port++ <--> ClassicalChannel {  distance = 15km; } <--> HOM[0].port++;

        EndNode[0].quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> repeater[0].quantum_port_receiver++;//MM
        repeater[0].quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> HOM[0].quantum_port++;//MIM
        repeater[1].quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> HOM[0].quantum_port++;
}

network Layer2_MIM_MIM
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

    submodules:
        backend: Backend;
        logger: Logger;
        EndNode[2]: QNode {
            address = index;
            nodeType = "EndNode";
            @display("i=COMP;");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }

        repeater[1]: QNode {
            address = sizeof(EndNode) + index;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=REP1G");
        }

        HOM[2]: HOM {
            address = sizeof(EndNode)+ sizeof(repeater)+ index;
        }

    connections:
        EndNode[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> HOM[0].port++;
        HOM[0].port++ <--> ClassicalChannel {  distance = 15km; } <--> repeater[0].port++;
        repeater[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HOM[1].port++;
        HOM[1].port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode[1].port++;

        EndNode[0].quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> HOM[0].quantum_port++;
        HOM[0].quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> repeater[0].quantum_port++;
        repeater[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HOM[1].quantum_port++;
        HOM[1].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode[1].quantum_port++;
}


network Layer2_MIM_tomography
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=305,240;bgl=3");
    submodules:
        backend: Backend;
        logger: Logger;
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
            @display("i=REP1G");
        }

        HOM[10]: HOM {
            address = sizeof(EndNode)+ sizeof(repeater)+ index;
        }

    connections:
        EndNode[0].port++ <--> ClassicalChannel {  distance = 1km; } <--> HOM[0].port++;
        HOM[0].port++ <--> ClassicalChannel {  distance = 19km; } <--> repeater[0].port++;

        repeater[0].port++ <--> ClassicalChannel {  distance = 2km; } <--> HOM[1].port++;
        HOM[1].port++ <--> ClassicalChannel {  distance = 18km; } <--> repeater[1].port++;

        repeater[1].port++ <--> ClassicalChannel {  distance = 3km; } <--> HOM[2].port++;
        HOM[2].port++ <--> ClassicalChannel {  distance = 17km; } <--> repeater[2].port++;

        repeater[2].port++ <--> ClassicalChannel {  distance = 4km; } <--> HOM[3].port++;
        HOM[3].port++ <--> ClassicalChannel {  distance = 16km; } <--> repeater[3].port++;

        repeater[3].port++ <--> ClassicalChannel {  distance = 5km; } <--> HOM[4].port++;
        HOM[4].port++ <--> ClassicalChannel {  distance = 15km; } <--> repeater[4].port++;

        repeater[4].port++ <--> ClassicalChannel {  distance = 6km; } <--> HOM[5].port++;
        HOM[5].port++ <--> ClassicalChannel {  distance = 14km; } <--> repeater[5].port++;

        repeater[5].port++ <--> ClassicalChannel {  distance = 7km; } <--> HOM[6].port++;
        HOM[6].port++ <--> ClassicalChannel {  distance = 13km; } <--> repeater[6].port++;

        repeater[6].port++ <--> ClassicalChannel {  distance = 8km; } <--> HOM[7].port++;
        HOM[7].port++ <--> ClassicalChannel {  distance = 12km; } <--> repeater[7].port++;

        repeater[7].port++ <--> ClassicalChannel {  distance = 9km; } <--> HOM[8].port++;
        HOM[8].port++ <--> ClassicalChannel {  distance = 11km; } <--> repeater[8].port++;

        repeater[8].port++ <--> ClassicalChannel {  distance = 10km; } <--> HOM[9].port++;
        HOM[9].port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode[1].port++;



        EndNode[0].quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> HOM[0].quantum_port++;

        HOM[0].quantum_port++ <--> QuantumChannel {  distance = 19km; } <--> repeater[0].quantum_port++;


        repeater[0].quantum_port++ <--> QuantumChannel {  distance = 2km; } <--> HOM[1].quantum_port++;

        HOM[1].quantum_port++ <--> QuantumChannel {  distance = 18km; } <--> repeater[1].quantum_port++;


        repeater[1].quantum_port++ <--> QuantumChannel {  distance = 3km; } <--> HOM[2].quantum_port++;

        HOM[2].quantum_port++ <--> QuantumChannel {  distance = 17km; } <--> repeater[2].quantum_port++;


        repeater[2].quantum_port++ <--> QuantumChannel {  distance = 4km; } <--> HOM[3].quantum_port++;

        HOM[3].quantum_port++ <--> QuantumChannel {  distance = 16km; } <--> repeater[3].quantum_port++;


        repeater[3].quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> HOM[4].quantum_port++;

        HOM[4].quantum_port++ <--> QuantumChannel {  distance = 15km; } <--> repeater[4].quantum_port++;


        repeater[4].quantum_port++ <--> QuantumChannel {  distance = 6km; } <--> HOM[5].quantum_port++;

        HOM[5].quantum_port++ <--> QuantumChannel {  distance = 14km; } <--> repeater[5].quantum_port++;


        repeater[5].quantum_port++ <--> QuantumChannel {  distance = 7km; } <--> HOM[6].quantum_port++;

        HOM[6].quantum_port++ <--> QuantumChannel {  distance = 13km; } <--> repeater[6].quantum_port++;


        repeater[6].quantum_port++ <--> QuantumChannel {  distance = 8km; } <--> HOM[7].quantum_port++;

        HOM[7].quantum_port++ <--> QuantumChannel {  distance = 12km; } <--> repeater[7].quantum_port++;


        repeater[7].quantum_port++ <--> QuantumChannel {  distance = 9km; } <--> HOM[8].quantum_port++;

        HOM[8].quantum_port++ <--> QuantumChannel {  distance = 11km; } <--> repeater[8].quantum_port++;


        repeater[8].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HOM[9].quantum_port++;

        HOM[9].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode[1].quantum_port++;


}

