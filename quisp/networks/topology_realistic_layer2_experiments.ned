package networks;

import ned.DatarateChannel;
import ned.IdealChannel;

import modules.*;
import modules.Backend.Backend;
import modules.Logger.Logger;
import channels.*;

network Realistic_Layer2_Simple_MIM_MM_all_in_one
{
    parameters:
        **.Speed_of_light_in_fiber = 208189.206944 km;

        @display("bgb=707,326");
    submodules:
        backend: Backend{}
        logger: Logger;
        EndNode1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=COMP;p=314,124");
        }
        EndNode2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=COMP;p=42,190");
        }
        Repeater1[1]: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=REP1G;p=378,137");
        }
        Repeater2[1]: QNode {
            address = 4;
            nodeType = "Repeater";
            @display("i=REP1G;p=275,209");
        }
        Repeater3[1]: QNode {
            address = 5;
            nodeType = "Repeater";
            @display("i=REP1G;p=187,201");
        }
        Repeater4[1]: QNode {
            address = 6;
            nodeType = "Repeater";
            @display("i=REP1G;p=105,68");
        }
        Repeater5[1]: QNode {
            address = 7;
            nodeType = "Repeater";
            @display("i=REP1G;p=179,36");
        }
        Repeater6[1]: QNode {
            address = 8;
            nodeType = "Repeater";
            @display("i=REP1G;p=350,36");
        }
        Repeater7[1]: QNode {
            address = 9;
            nodeType = "Repeater";
            @display("i=REP1G;p=424,42");
        }
        Repeater8[1]: QNode {
            address = 10;
            nodeType = "Repeater";
            @display("i=REP1G;p=563,143");
        }
        Repeater9[1]: QNode {
            address = 11;
            nodeType = "Repeater";
            @display("i=REP1G;p=505,241");
        }
        Repeater10[1]: QNode {
            address = 12;
            nodeType = "Repeater";
            @display("i=REP1G;p=232,273");
        }
        Repeater11[1]: QNode {
            address = 13;
            nodeType = "Repeater";
            @display("i=REP1G;p=140,273");
        }

        HOM1[1]: HOM {
            address = 14;
            @display("p=389,195");
        }
        HOM2[1]: HOM {
            address = 15;
            @display("p=105,137");
        }
        HOM3[1]: HOM {
            address = 16;
            @display("p=275,30");
        }
        HOM4[1]: HOM {
            address = 17;
            @display("p=523,68");
        }
        HOM5[1]: HOM {
            address = 18;
            @display("p=350,273");
        }
        HOM6[1]: HOM {
            address = 19;
            @display("p=66,241");
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


network Realistic_Layer2_Simple_MIM_MM_5km
{
    parameters:
        **.Speed_of_light_in_fiber = 208189.206944 km;

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
            @display("i=COMP;p=98,233");
        }
        Repeater1[1]: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=REP1G;p=220,137");
        }
        HOM1[1]: HOM {
            address = 4;
            @display("p=163,182");
        }



    connections:
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> Repeater1[0].port++;
        Repeater1[0].port++ <--> ClassicalChannel {  distance = 2.5km; } <--> HOM1[0].port++;
        EndNode2[0].port++ <--> ClassicalChannel {  distance = 2.5km; } <--> HOM1[0].port++;

        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 5km; } <--> Repeater1[0].quantum_port++;
        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> HOM1[0].quantum_port++;
        EndNode2[0].quantum_port++ <--> QuantumChannel {  distance = 2.5km; } <--> HOM1[0].quantum_port++;

}

network Realistic_Layer3_Simple_MM_MM_5km
{
    parameters:
        **.Speed_of_light_in_fiber = 208189.206944 km;

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
            @display("i=COMP;p=98,233");
        }
        Repeater1[1]: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=REP1G;p=220,137");
        }
        Repeater2[1]: QNode {
            address = 4;
            nodeType = "Repeater";
            @display("i=REP1G;p=163,182");
        }




    connections:
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> Repeater1[0].port++;
        Repeater1[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> Repeater2[0].port++;
        Repeater2[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> EndNode2[0].port++;

        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 5km; } <--> Repeater1[0].quantum_port++;
        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> Repeater2[0].quantum_port_receiver++;
        Repeater2[0].quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> EndNode2[0].quantum_port_receiver++;

}



network Realistic_Layer2_Simple_MIM_MM_7_5km
{
    parameters:
        **.Speed_of_light_in_fiber = 208189.206944 km;

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
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 7.5km; } <--> Repeater1[0].port++;
        Repeater1[0].port++ <--> ClassicalChannel {  distance = 3.75km; } <--> HOM1[0].port++;
        EndNode2[0].port++ <--> ClassicalChannel {  distance = 3.75km; } <--> HOM1[0].port++;

        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 7.5km; } <--> Repeater1[0].quantum_port++;
        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 3.75km; } <--> HOM1[0].quantum_port++;
        EndNode2[0].quantum_port++ <--> QuantumChannel {  distance = 3.75km; } <--> HOM1[0].quantum_port++;

}


network Realistic_Layer2_Simple_MIM_MM_10km
{
    parameters:
        **.Speed_of_light_in_fiber = 208189.206944 km;

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



network Realistic_Layer2_Simple_MIM_MM_15km
{
    parameters:
        **.Speed_of_light_in_fiber = 208189.206944 km;

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

network Realistic_Layer2_Simple_MIM_MM_50km
{
    parameters:
        **.Speed_of_light_in_fiber = 208189.206944 km;

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


network Realistic_Layer2_Simple_MIM_MM_40km
{
    parameters:
        **.Speed_of_light_in_fiber = 208189.206944 km;

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



network Realistic_Layer2_Simple_MIM_MM_25km
{
    parameters:
        **.Speed_of_light_in_fiber = 208189.206944 km;

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
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 25km; } <--> Repeater1[0].port++;
        Repeater1[0].port++ <--> ClassicalChannel {  distance = 12.5km; } <--> HOM1[0].port++;
        EndNode2[0].port++ <--> ClassicalChannel {  distance = 12.5km; } <--> HOM1[0].port++;

        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 25km; } <--> Repeater1[0].quantum_port++;
        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 12.5km; } <--> HOM1[0].quantum_port++;
        EndNode2[0].quantum_port++ <--> QuantumChannel {  distance = 12.5km; } <--> HOM1[0].quantum_port++;

}

network Realistic_Layer2_Simple_MIM_MM_30km
{
    parameters:
        **.Speed_of_light_in_fiber = 208189.206944 km;

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



network Realistic_Layer2_Simple_MIM_MM
{
    parameters:
        **.Speed_of_light_in_fiber = 208189.206944 km;

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
            @display("i=COMP;p=350,78");
        }
        Repeater1[1]: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=REP1G;p=220,137");
        }
        BSA[1]: HOM {
            address = 4;
            @display("p=269,85");
        }



    connections:
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> Repeater1[0].port++;
        Repeater1[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA[0].port++;
        EndNode2[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> BSA[0].port++;

        EndNode1[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 20km; } <--> Repeater1[0].quantum_port++;
        Repeater1[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA[0].quantum_port++;
        EndNode2[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> BSA[0].quantum_port++;

}




network Realistic_Layer2_Simple_MIM_MM_same
{
    parameters:
        **.Speed_of_light_in_fiber = 208189.206944 km;

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


network Realistic_Layer2_RouterNet
{
    parameters:
        **.Speed_of_light_in_fiber = 208189.206944 km;

        @display("bgb=707,326");
    submodules:
        backend: Backend;
        logger: Logger;
        Router1[1]: QNode {
            address = 1;
            nodeType = "Router";
            @display("i=RTR;p=350,157");
        }
        Router2[1]: QNode {
            address = 2;
            nodeType = "Router";
            @display("i=RTR;p=211,224");
        }
        Router3[1]: QNode {
            address = 3;
            nodeType = "Router";
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
            nodeType = "Router";
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


network Realistic_Layer2_Star_Sep
{
    parameters:
        **.Speed_of_light_in_fiber = 208189.206944 km;

        @display("bgb=707,326");
    submodules:
        backend: Backend;
        logger: Logger;
        EndNode1[1]: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=COMP;p=551,84");
        }
        EndNode2[1]: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=COMP;p=518,157");
        }
        EndNode3[1]: QNode {
            address = 3;
            nodeType = "EndNode";
            @display("i=COMP;p=220,297");
        }
        EndNode4[1]: QNode {
            address = 4;
            nodeType = "EndNode";
            @display("i=COMP;p=128,285");
        }
        EndNode5[1]: QNode {
            address = 5;
            nodeType = "EndNode";
            @display("i=COMP;p=109,246");
        }
        EndNode6[1]: QNode {
            address = 6;
            nodeType = "EndNode";
            @display("i=COMP;p=503,263");
        }
        EndNode7[1]: QNode {
            address = 7;
            nodeType = "EndNode";
            @display("i=COMP;p=419,16");
        }
        EndNode8[1]: QNode {
            address = 8;
            nodeType = "EndNode";
            @display("i=COMP;p=211,16");
        }
        EndNode9[1]: QNode {
            address = 9;
            nodeType = "EndNode";
            @display("i=COMP;p=34,77");
        }
        EndNode10[1]: QNode {
            address = 10;
            nodeType = "EndNode";
            @display("i=COMP;p=13,208");
        }
        Router11[1]: QNode {
            address = 11;
            nodeType = "Router";
            @display("i=RTR;p=350,157");
        }
        Router12[1]: QNode {
            address = 12;
            nodeType = "Router";
            @display("i=RTR;p=211,224");
        }
        Router13[1]: QNode {
            address = 13;
            nodeType = "Router";
            @display("i=RTR;p=220,137");
        }
        Router14[1]: QNode {
            address = 14;
            @display("i=RTR;p=313,246");
        }
        Router15[1]: QNode {
            address = 15;
            nodeType = "Router";
            @display("i=RTR;p=432,246");
        }
        Repeater16[1]: QNode {
            address = 16;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=REP1G;p=406,109");
        }
        Repeater17[1]: QNode {
            address = 17;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=REP1G;p=350,54");
        }
        Repeater18[1]: QNode {
            address = 18;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=REP1G;p=285,22");
        }
        Repeater19[1]: QNode {
            address = 19;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=REP1G;p=89,60");
        }
        Repeater20[1]: QNode {
            address = 20;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=REP1G;p=58,143");
        }
        HOM21[1]: HOM {
            address = 21;
            @display("p=164,176");
        }
        HOM22[1]: HOM {
            address = 22;
            @display("p=484,98");
        }
        HOM23[1]: HOM {
            address = 23;
            @display("p=445,157");
        }
        HOM24[1]: HOM {
            address = 24;
            @display("p=324,98");
        }
        HOM25[1]: HOM {
            address = 25;
            @display("p=270,70");
        }
        HOM26[1]: HOM {
            address = 26;
            @display("p=193,77");
        }
        HOM27[1]: HOM {
            address = 27;
            @display("p=128,137");
        }

    connections:
        Router11[0].port++ <--> ClassicalChannel {  distance = 19km; } <--> Router12[0].port++;
        Router13[0].port++ <--> ClassicalChannel {  distance = 21km; } <--> Router11[0].port++;

        Router13[0].port++ <--> ClassicalChannel {  distance = 11km; } <--> HOM21[0].port++;
        Router12[0].port++ <--> ClassicalChannel {  distance = 12km; } <--> HOM21[0].port++;

        Router12[0].port++ <--> ClassicalChannel {  distance = 18km; } <--> Router14[0].port++;
        Router15[0].port++ <--> ClassicalChannel {  distance = 22km; } <--> Router14[0].port++;
        Router15[0].port++ <--> ClassicalChannel {  distance = 23km; } <--> Router11[0].port++;
        Router14[0].port++ <--> ClassicalChannel {  distance = 25km; } <--> Router11[0].port++;
        Router15[0].port++ <--> ClassicalChannel {  distance = 40km; } <--> Router13[0].port++;

        Repeater16[0].port++ <--> ClassicalChannel {  distance = 26km; } <--> Router11[0].port++;
        Repeater16[0].port++ <--> ClassicalChannel {  distance = 27km; } <--> HOM22[0].port++;
        EndNode1[0].port++ <--> ClassicalChannel {  distance = 28km; } <--> HOM22[0].port++;
        HOM23[0].port++ <--> ClassicalChannel {  distance = 29km; } <--> Router11[0].port++;
        HOM23[0].port++ <--> ClassicalChannel {  distance = 30km; } <--> EndNode2[0].port++;

        Router12[0].port++ <--> ClassicalChannel {  distance = 3km; } <--> EndNode3[0].port++;
        Router12[0].port++ <--> ClassicalChannel {  distance = 4km; } <--> EndNode4[0].port++;
        Router12[0].port++ <--> ClassicalChannel {  distance = 5km; } <--> EndNode5[0].port++;

        Router15[0].port++ <--> ClassicalChannel {  distance = 20km; } <--> EndNode6[0].port++;

        Router13[0].port++ <--> ClassicalChannel {  distance = 7km; } <--> HOM24[0].port++;
        Router13[0].port++ <--> ClassicalChannel {  distance = 8km; } <--> HOM25[0].port++;
        Router13[0].port++ <--> ClassicalChannel {  distance = 9km; } <--> HOM26[0].port++;
        Router13[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> HOM27[0].port++;

        Repeater17[0].port++ <--> ClassicalChannel {  distance = 11km; } <--> HOM24[0].port++;
        Repeater18[0].port++ <--> ClassicalChannel {  distance = 12km; } <--> HOM25[0].port++;
        Repeater19[0].port++ <--> ClassicalChannel {  distance = 13km; } <--> HOM26[0].port++;
        Repeater20[0].port++ <--> ClassicalChannel {  distance = 14km; } <--> HOM27[0].port++;

        EndNode7[0].port++ <--> ClassicalChannel {  distance = 7.5km; } <--> Repeater17[0].port++;
        EndNode8[0].port++ <--> ClassicalChannel {  distance = 8.5km; } <--> Repeater18[0].port++;
        EndNode9[0].port++ <--> ClassicalChannel {  distance = 9.5km; } <--> Repeater19[0].port++;
        EndNode10[0].port++ <--> ClassicalChannel {  distance = 10.5km; } <--> Repeater20[0].port++;




        Router11[0].quantum_port++ <--> QuantumChannel {  distance = 19km; } <--> Router12[0].quantum_port_receiver++;
        Router13[0].quantum_port++ <--> QuantumChannel {  distance = 21km; } <--> Router11[0].quantum_port_receiver++;

        Router13[0].quantum_port++ <--> QuantumChannel {  distance = 11km; } <--> HOM21[0].quantum_port++;
        Router12[0].quantum_port++ <--> QuantumChannel {  distance = 12km; } <--> HOM21[0].quantum_port++;

        Router12[0].quantum_port++ <--> QuantumChannel {  distance = 18km; } <--> Router14[0].quantum_port_receiver++;
        Router15[0].quantum_port++ <--> QuantumChannel {  distance = 22km; } <--> Router14[0].quantum_port_receiver++;
        Router15[0].quantum_port++ <--> QuantumChannel {  distance = 23km; } <--> Router11[0].quantum_port_receiver++;
        Router14[0].quantum_port++ <--> QuantumChannel {  distance = 25km; } <--> Router11[0].quantum_port_receiver++;
        Router15[0].quantum_port++ <--> QuantumChannel {  distance = 40km; } <--> Router13[0].quantum_port_receiver++;

        Repeater16[0].quantum_port++ <--> QuantumChannel {  distance = 26km; } <--> Router11[0].quantum_port_receiver++;
        Repeater16[0].quantum_port++ <--> QuantumChannel {  distance = 27km; } <--> HOM22[0].quantum_port++;
        EndNode1[0].quantum_port++ <--> QuantumChannel {  distance = 28km; } <--> HOM22[0].quantum_port++;
        HOM23[0].quantum_port++ <--> QuantumChannel {  distance = 29km; } <--> Router11[0].quantum_port++;
        HOM23[0].quantum_port++ <--> QuantumChannel {  distance = 30km; } <--> EndNode2[0].quantum_port++;

        Router12[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 3km; } <--> EndNode3[0].quantum_port++;
        Router12[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 4km; } <--> EndNode4[0].quantum_port++;
        Router12[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 5km; } <--> EndNode5[0].quantum_port++;

        Router15[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 20km; } <--> EndNode6[0].quantum_port++;

        Router13[0].quantum_port++ <--> QuantumChannel {  distance = 7km; } <--> HOM24[0].quantum_port++;
        Router13[0].quantum_port++ <--> QuantumChannel {  distance = 8km; } <--> HOM25[0].quantum_port++;
        Router13[0].quantum_port++ <--> QuantumChannel {  distance = 9km; } <--> HOM26[0].quantum_port++;
        Router13[0].quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HOM27[0].quantum_port++;

        Repeater17[0].quantum_port++ <--> QuantumChannel {  distance = 11km; } <--> HOM24[0].quantum_port++;
        Repeater18[0].quantum_port++ <--> QuantumChannel {  distance = 12km; } <--> HOM25[0].quantum_port++;
        Repeater19[0].quantum_port++ <--> QuantumChannel {  distance = 13km; } <--> HOM26[0].quantum_port++;
        Repeater20[0].quantum_port++ <--> QuantumChannel {  distance = 14km; } <--> HOM27[0].quantum_port++;

        EndNode7[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 7.5km; } <--> Repeater17[0].quantum_port++;
        EndNode8[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 8.5km; } <--> Repeater18[0].quantum_port++;
        EndNode9[0].quantum_port++ <--> QuantumChannel {  distance = 9.5km; } <--> Repeater19[0].quantum_port_receiver++;
        EndNode10[0].quantum_port++ <--> QuantumChannel {  distance = 10.5km; } <--> Repeater20[0].quantum_port_receiver++;
}





network Realistic_Layer2_MM_MIM_MIM_MIM_MM
{
    parameters:
        **.Speed_of_light_in_fiber = 208189.206944 km;

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

network Realistic_Layer2_MIM_MIM
{
    parameters:
        **.Speed_of_light_in_fiber = 208189.206944 km;

    submodules:
        backend: Backend;
        logger: Logger;
        EndNode[2]: QNode {
            address = index;
            nodeType = "EndNode";
            @display("i=COMP;p=174,138");
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


network Realistic_Layer2_MIM_tomography
{
    parameters:
        **.Speed_of_light_in_fiber = 208189.206944 km;

        @display("bgb=305,240;bgl=3");
    submodules:
        backend: Backend;
        logger: Logger;
        EndNode[2]: QNode {
            address = index;
            nodeType = "EndNode";
            @display("i=COMP");
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


