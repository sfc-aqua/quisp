package networks;

import ned.DatarateChannel;
import ned.IdealChannel;

import modules.*;
import channels.*;

network Tomography_Linear_One_MM_MIM
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

        repeater: QNode {
            address = 1234;
            nodeType = "Repeater";
            //buffers = 25;
            @display("i=device/smallrouter");
        }

        HoM: HoM {
            address = 2;
            @display("i=device/bsm");
        }

    connections:
        EndNode[0].port++ <--> ClassicalChannel {  distance = 10km; } <--> repeater.port++;
        repeater.port++ <--> ClassicalChannel {  distance = 10km; } <--> HoM.port++;
        HoM.port++ <--> ClassicalChannel {  distance = 10km; } <--> EndNode[1].port++;

        EndNode[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 10km; } <--> repeater.quantum_port++;
        repeater.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> HoM.quantum_port++;
        HoM.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> EndNode[1].quantum_port++;
}

network Linear_One_MIM
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;
        //**.HoM_handshake = false;

    submodules:
        source: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=device/pc");
            //buffers = 15;
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        HoM: HoM {
            address = 2;
            @display("i=device/bsm");
        }
        target: QNode {
            address = 3;
            nodeType = "EndNode";
            //buffers = 20;
            @display("i=device/pc");
        }
    connections:
        source.port++ <--> ClassicalChannel {  distance = 1km; } <--> HoM.port++;
        HoM.port++ <--> ClassicalChannel {  distance = 1km; } <--> target.port++;
        source.quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> HoM.quantum_port++;
        HoM.quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> target.quantum_port++;

}

network Linear_One_MSM
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;
        double link_distance @unit(km);
        link_distance = default(1km);
        //**.HoM_handshake = false;

        @display("bgb=294,138");
    submodules:
        source: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=device/pc;p=235,69");
            //buffers = 15;
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        EPPS: SPDC {
            address = 2;
            @display("i=device/bsm;p=131,69");
        }
        target: QNode {
            address = 3;
            nodeType = "EndNode";
            //buffers = 20;
            @display("i=device/pc;p=32,69");
        }
    connections:
        source.port++ <--> ClassicalChannel {  distance = link_distance; } <--> EPPS.port++;
        EPPS.port++ <--> ClassicalChannel {  distance = link_distance; } <--> target.port++;

        source.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = link_distance; } <--> EPPS.quantum_port++;
        EPPS.quantum_port++ <--> QuantumChannel {  distance = link_distance; } <--> target.quantum_port_receiver_passive++;

}

network Linear_Two_MSM
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;
        //**.HoM_handshake = false;

        @display("bgb=500,138");
    submodules:
        EndNode1: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=device/pc;p=32,69");
        }
        EPPS1: SPDC {
            address = 2;
            @display("i=device/bsm;p=132,69");
        }
        Repeater: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=232,69");
        }
        EPPS2: SPDC {
            address = 4;
            @display("i=device/bsm;p=332,69");
        }
        EndNode2: QNode {
            address = 5;
            nodeType = "EndNode";
            @display("i=device/pc;p=432,69");
        }
    connections:
        //Classical Channel
        EndNode1.port++ <--> ClassicalChannel {  distance = 1km; } <--> EPPS1.port++;
        EPPS1.port++ <--> ClassicalChannel {  distance = 1km; } <--> Repeater.port++;
        Repeater.port++ <--> ClassicalChannel {  distance = 1km; } <--> EPPS2.port++;
        EPPS2.port++ <--> ClassicalChannel {  distance = 1km; } <--> EndNode2.port++;

        //Quantum Channel
        EndNode1.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 1km; } <--> EPPS1.quantum_port++;
        EPPS1.quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> Repeater.quantum_port_receiver_passive++;
        Repeater.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 1km; } <--> EPPS2.quantum_port++;
        EPPS2.quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> EndNode2.quantum_port_receiver_passive++;

}

network Linear_Ten_MSM
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;
        //**.HoM_handshake = false;

        @display("bgb=2095,138");
    submodules:
        EndNode1: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=device/pc;p=32,69");
        }
        EPPS1: SPDC {
            address = 2;
            @display("i=device/bsm;p=131,69");
        }
        Repeater1: QNode {
            address = 3;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=235,69");
        }
        EPPS2: SPDC {
            address = 4;
            @display("i=device/bsm;p=335,69");
        }
        Repeater2: QNode {
            address = 5;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=435,69");
        }
        EPPS3: SPDC {
            address = 6;
            @display("i=device/bsm;p=535,69");
        }
        Repeater3: QNode {
            address = 7;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=635,69");
        }
        EPPS4: SPDC {
            address = 8;
            @display("i=device/bsm;p=735,69");
        }
        Repeater4: QNode {
            address = 9;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=835,69");
        }
        EPPS5: SPDC {
            address = 10;
            @display("i=device/bsm;p=935,69");
        }
        Repeater5: QNode {
            address = 11;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=1035,69");
        }
        EPPS6: SPDC {
            address = 12;
            @display("i=device/bsm;p=1135,69");
        }
        Repeater6: QNode {
            address = 13;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=1235,69");
        }
        EPPS7: SPDC {
            address = 14;
            @display("i=device/bsm;p=1335,69");
        }
        Repeater7: QNode {
            address = 15;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=1435,69");
        }
        EPPS8: SPDC {
            address = 16;
            @display("i=device/bsm;p=1535,69");
        }
        Repeater8: QNode {
            address = 17;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=1635,69");
        }
        EPPS9: SPDC {
            address = 18;
            @display("i=device/bsm;p=1735,69");
        }
        Repeater9: QNode {
            address = 19;
            nodeType = "Repeater";
            @display("i=device/smallrouter;p=1835,69");
        }
        EPPS10: SPDC {
            address = 20;
            @display("i=device/bsm;p=1935,69");
        }
        EndNode2: QNode {
            address = 21;
            nodeType = "EndNode";
            @display("i=device/pc;p=2035,69");
        }
    connections:
        //Classical Channel
        EndNode1.port++ <--> ClassicalChannel {  distance = 1km; } <--> EPPS1.port++;

        EPPS1.port++ <--> ClassicalChannel {  distance = 1km; } <--> Repeater1.port++;
        Repeater1.port++ <--> ClassicalChannel {  distance = 1km; } <--> EPPS2.port++;
        EPPS2.port++ <--> ClassicalChannel {  distance = 1km; } <--> Repeater2.port++;
        Repeater2.port++ <--> ClassicalChannel {  distance = 1km; } <--> EPPS3.port++;
        EPPS3.port++ <--> ClassicalChannel {  distance = 1km; } <--> Repeater3.port++;
        Repeater3.port++ <--> ClassicalChannel {  distance = 1km; } <--> EPPS4.port++;
        EPPS4.port++ <--> ClassicalChannel {  distance = 1km; } <--> Repeater4.port++;
        Repeater4.port++ <--> ClassicalChannel {  distance = 1km; } <--> EPPS5.port++;
        EPPS5.port++ <--> ClassicalChannel {  distance = 1km; } <--> Repeater5.port++;
        Repeater5.port++ <--> ClassicalChannel {  distance = 1km; } <--> EPPS6.port++;
        EPPS6.port++ <--> ClassicalChannel {  distance = 1km; } <--> Repeater6.port++;
        Repeater6.port++ <--> ClassicalChannel {  distance = 1km; } <--> EPPS7.port++;
        EPPS7.port++ <--> ClassicalChannel {  distance = 1km; } <--> Repeater7.port++;
        Repeater7.port++ <--> ClassicalChannel {  distance = 1km; } <--> EPPS8.port++;
        EPPS8.port++ <--> ClassicalChannel {  distance = 1km; } <--> Repeater8.port++;
        Repeater8.port++ <--> ClassicalChannel {  distance = 1km; } <--> EPPS9.port++;
        EPPS9.port++ <--> ClassicalChannel {  distance = 1km; } <--> Repeater9.port++;
        Repeater9.port++ <--> ClassicalChannel {  distance = 1km; } <--> EPPS10.port++;

        EPPS10.port++ <--> ClassicalChannel {  distance = 1km; } <--> EndNode2.port++;

        //Quantum Channel
        EndNode1.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 1km; } <--> EPPS1.quantum_port++;

        EPPS1.quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> Repeater1.quantum_port_receiver_passive++;
        Repeater1.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 1km; } <--> EPPS2.quantum_port++;
        EPPS2.quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> Repeater2.quantum_port_receiver_passive++;
        Repeater2.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 1km; } <--> EPPS3.quantum_port++;
        EPPS3.quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> Repeater3.quantum_port_receiver_passive++;
        Repeater3.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 1km; } <--> EPPS4.quantum_port++;
        EPPS4.quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> Repeater4.quantum_port_receiver_passive++;
        Repeater4.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 1km; } <--> EPPS5.quantum_port++;
        EPPS5.quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> Repeater5.quantum_port_receiver_passive++;
        Repeater5.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 1km; } <--> EPPS6.quantum_port++;
        EPPS6.quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> Repeater6.quantum_port_receiver_passive++;
        Repeater6.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 1km; } <--> EPPS7.quantum_port++;
        EPPS7.quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> Repeater7.quantum_port_receiver_passive++;
        Repeater7.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 1km; } <--> EPPS8.quantum_port++;
        EPPS8.quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> Repeater8.quantum_port_receiver_passive++;
        Repeater8.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 1km; } <--> EPPS9.quantum_port++;
        EPPS9.quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> Repeater9.quantum_port_receiver_passive++;
        Repeater9.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 1km; } <--> EPPS10.quantum_port++;

        EPPS10.quantum_port++ <--> QuantumChannel {  distance = 1km; } <--> EndNode2.quantum_port_receiver_passive++;

}


network Linear_One_MIM_biasedDistance
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;
        //**.HoM_handshake = false;

    submodules:
        source: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=device/pc");
            //buffers = 15;
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        HoM: HoM {
            address = 2;
            @display("i=device/bsm");
        }
        target: QNode {
            address = 3;
            nodeType = "EndNode";
            //buffers = 20;
            @display("i=device/pc");
        }
    connections:
        source.port++ <--> ClassicalChannel {  distance = 7km; } <--> HoM.port++;
        HoM.port++ <--> ClassicalChannel {  distance = 10km; } <--> target.port++;
        source.quantum_port++ <--> QuantumChannel {  distance = 7km; } <--> HoM.quantum_port++;
        HoM.quantum_port++ <--> QuantumChannel {  distance = 10km; } <--> target.quantum_port++;

}



network Linear_One_MM
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

    submodules:
        EndNode[2]: QNode {
            address = index;
            nodeType = "EndNode";
            @display("i=device/pc");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }

    connections:
        EndNode[0].port++ <--> ClassicalChannel {  distance = 1km; } <--> EndNode[1].port++;
        EndNode[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 1km; } <--> EndNode[1].quantum_port++;
}

network Linear_One_MM_bufferGap
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

    submodules:
        Small: QNode {
            address = 112302;
            nodeType = "EndNode";
            buffers = 1;
            @display("i=device/pc");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }

        Big: QNode {
            address = 300;
            buffers = 1;
            nodeType = "EndNode";
            @display("i=device/pc");
        }
    connections:
        Small.port++ <--> ClassicalChannel {  distance = 12.3km; } <--> Big.port++;
        Small.quantum_port_receiver++ <--> QuantumChannel {  distance = 12.3km; } <--> Big.quantum_port++;
}











































network Linear_One_MIM_MM_MSM
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;//per second

        @display("bgb=526,236");

    types:
        channel ClassicalChannel extends DatarateChannel
        {
            double cost = default(100);
            double distance @unit(km) = default(20km);
            //delay = uniform(0.01ms, 1s);
            double distance_of_light_in_fiber_per_sec @unit(km) = default(205336.986301km);
            delay = this.distance / distance_of_light_in_fiber_per_sec * 1s;
            datarate = uniform(1kbps, 100kbps);
            int test = default(0);
            @defaultname(ClassicalChannel);
        }

        //channel QuantumChannel extends DatarateChannel
        //{
        //    double cost = default(1);
        //    double distance @unit(km) = default(20km);
            //delay = uniform(0.01ms, 1s);
        //    double distance_of_light_in_fiber_per_sec @unit(km) = default(205336.986301km);
        //    delay = this.distance / distance_of_light_in_fiber_per_sec * 1s;
        //    datarate = uniform(1kbps, 100kbps);
        //    double photon_loss_rate = default(0);//per km
        //    double channel_error_rate = default(0);//per km
        //    double Z_error_ratio = default(1);
         //   double X_error_ratio = default(1);
         //   double Y_error_ratio = default(1);
         //   int test = default(0);
         //   @defaultname(QuantumChannel);
       // }
    submodules:
        source: QNode {
            address = 10000000;
            nodeType = "EndNode";
            @display("i=device/pc;p=502,132");
            //buffers = 15;
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        HoM: HoM {
            address = 2;
            @display("i=device/bsm;p=304,132");
        }
        repeater: QNode {
            address = 1234;
            nodeType = "Repeater";
        		//buffers = 25;

            @display("i=device/smallrouter;p=408,131");
        }
        router: QNode {
            address = 3;
            nodeType = "Router";
            //buffers = 30;
            @display("i=device/smallrouter;p=207,131");
        }
        mm[2]: QNode {
            address = index + 100;
            //buffers = 20;
            nodeType = "EndNode";
            @display("i=device/pc_s;p=207,31");
        }
        epps: SPDC {
            address = 5;
            @display("i=device/epps;p=110,132");
        }

        pas: QNode {
            address = 6;
            //buffers = 5;
            nodeType = "EndNode";
            @display("i=device/pc_s;p=21,132");
        }
    connections:
        source.port++ <--> ClassicalChannel <--> repeater.port++;
        repeater.port++ <--> ClassicalChannel <--> HoM.port++;
        HoM.port++ <--> ClassicalChannel {  distance = 90km; } <--> router.port++;
        mm[0].port++ <--> ClassicalChannel {  distance = 40km; } <--> router.port++;
        mm[1].port++ <--> ClassicalChannel {  distance = 40km; } <--> router.port++;
        epps.port++ <--> ClassicalChannel <--> router.port++;
        epps.port++ <--> ClassicalChannel <--> pas.port++;
        source.quantum_port++ <--> QuantumChannel <--> repeater.quantum_port_receiver++;
        repeater.quantum_port++ <--> QuantumChannel <--> HoM.quantum_port++;
        HoM.quantum_port++ <--> QuantumChannel {  distance = 90km; } <--> router.quantum_port++;
        mm[0].quantum_port_receiver++ <--> QuantumChannel {  distance = 40km; } <--> router.quantum_port++;
        mm[1].quantum_port++ <--> QuantumChannel {  distance = 40km; } <--> router.quantum_port_receiver++;
        router.quantum_port_receiver_passive++ <--> QuantumChannel <--> epps.quantum_port++;
        epps.quantum_port++ <--> QuantumChannel <--> pas.quantum_port_receiver_passive++;
}


