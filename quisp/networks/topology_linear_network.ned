package networks;

 

import ned.DatarateChannel;
import ned.IdealChannel;



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


network Linear_One_MSM
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;

        @display("bgb=281,95");
    submodules:
        source: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=device/pc;p=240,48");

            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        epps: SPDC {//needs to check the buffersize, and tell each node how many photon arrivals to expect.
            address = 2;
            @display("i=device/epps;p=132,48");
        }
        target: QNode {
            address = 3;
            nodeType = "EndNode";
            @display("i=device/pc");
        }
    connections:
        source.port++ <--> ClassicalChannel {  distance = 40km; } <--> epps.port++;
        epps.port++ <--> ClassicalChannel {  distance = 20km; } <--> target.port++;
        source.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 40km; } <--> epps.quantum_port++;
        epps.quantum_port++ <--> QuantumChannel {  distance = 20km; } <--> target.quantum_port_receiver_passive++;
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


