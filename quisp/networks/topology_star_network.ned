package networks;

import ned.DatarateChannel;
import ned.IdealChannel;


network Three_HoM_star
{
    parameters:
        **.Speed_of_light_in_fiber = 208189.206944 km;
        //**.distance_of_light_in_fiber_per_sec = 205336.986301 km; // calculated as 299792/1.46
        int message_id_BSAtimingNoftifier = 4;
        int message_id_qubit = 100;
        int message_id_PathSelection = 1;
        int increment_address = 0;

        @display("bgl=2");
    types:
        channel C extends DatarateChannel
        {
            double cost = default(1);
            double distance @unit(km) = default(20km);
            //delay = uniform(0.01ms, 1s);
            double distance_of_light_in_fiber_per_sec @unit(km) = default(205336.986301km);
            delay = this.distance / distance_of_light_in_fiber_per_sec * 1s;
            datarate = uniform(1kbps, 100kbps);
            int test = default(0);
        }
        channel QuantumChannel extends DatarateChannel
        {
            double cost = default(1);
            double distance @unit(km) = default(20km);
            //delay = uniform(0.01ms, 1s);
            double distance_of_light_in_fiber_per_sec @unit(km) = default(205336.986301km);
            delay = this.distance / distance_of_light_in_fiber_per_sec * 1s;
            datarate = uniform(1kbps, 100kbps);
            double photon_loss_rate = default(0);//per km
            double channel_error_rate = default(0);//per km
            double Z_error_ratio = default(1);
            double X_error_ratio = default(1);
            double Y_error_ratio = default(1);
            int test = default(0);
        }
    submodules:
        //configurator: IPv4NetworkConfigurator {
        //    @display("p=100,100");
        //}
        EndNode[3]: QNode {
            //Initializerでaddress = node idにすればconflict無くなるかも。
            address = index+100000;
            nodeType = "EndNode";
            @display("i=device/pc");
        }
        HoM[3]: HoM {
            address = index+1000;
            //@display("p=326,57");
            @display("i=device/bsm");
        }
        Router[1]: QNode {
            address = index;
            //@display("p=246,56");
            @display("i=device/server");
        }
    connections:
        EndNode[0].port++ <--> C {  distance = 5km; } <--> HoM[0].port++;
        HoM[0].port++ <--> C <--> Router[0].port++;
        EndNode[0].quantum_port++ <--> QuantumChannel {  distance = 5km; } <--> HoM[0].quantum_port++;
        HoM[0].quantum_port++ <--> QuantumChannel <--> Router[0].quantum_port++;

        EndNode[1].port++ <--> C <--> HoM[1].port++;
        HoM[1].port++ <--> C {  distance = 100km; } <--> Router[0].port++;
        EndNode[1].quantum_port++ <--> QuantumChannel <--> HoM[1].quantum_port++;
        HoM[1].quantum_port++ <--> QuantumChannel {  distance = 100km; } <--> Router[0].quantum_port++;

        EndNode[2].port++ <--> C <--> HoM[2].port++;
        HoM[2].port++ <--> C {  distance = 40km; } <--> Router[0].port++;
        EndNode[2].quantum_port++ <--> QuantumChannel <--> HoM[2].quantum_port++;
        HoM[2].quantum_port++ <--> QuantumChannel {  distance = 40km; } <--> Router[0].quantum_port++;
}


network Star_MSM
{
    parameters:
        **.distance_of_light_in_fiber_per_sec = 205336.986301 km;

    types:
        channel C extends DatarateChannel
        {
            double cost = default(1);
            double distance @unit(km);
            distance = default(20km);
            //delay = uniform(0.01ms, 1s);
            double distance_of_light_in_fiber_per_sec @unit(km) = default(205336.986301km);
            delay = this.distance / distance_of_light_in_fiber_per_sec * 1s;
            datarate = uniform(1kbps, 100kbps);

        }
        channel QuantumChannel extends DatarateChannel
        {
            double cost = default(1.0);
            double fidelity = default(1.0);
            double bellpair_per_sec = default(1.0);
            double distance @unit(km) = default(20km);
            //delay = uniform(0.01ms, 1s);
            double distance_of_light_in_fiber_per_sec @unit(km) = default(205336.986301km);
            delay = this.distance / distance_of_light_in_fiber_per_sec * 1s;
            datarate = uniform(1kbps, 100kbps);
            double photon_loss_rate = default(0);//per km
            double channel_error_rate = default(0);//per km
            double Z_error_ratio = default(1);
            double X_error_ratio = default(1);
            double Y_error_ratio = default(1);
            int test = default(0);
        }
    submodules:
        node[3]: QNode {
            address = index;
            nodeType = "EndNode";
            @display("i=device/pc");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        spdc[6]: SPDC {
            address = index+1000;
            @display("i=device/epps");
        }
        router[1]: QNode {
            address = index+1000000;
            @display("i=device/router");
        }
        repeater[3]: QNode {
            address = index+1000;
            @display("i=device/device");
        }


    connections:
        node[0].port++ <--> C <--> spdc[0].port++;
        spdc[0].port++ <--> C <--> repeater[0].port++;
        repeater[0].port++ <--> C <--> spdc[1].port++;
        spdc[1].port++ <--> C <--> router[0].port++;

        node[0].quantum_port_receiver++ <--> QuantumChannel <--> spdc[0].quantum_port++;
        spdc[0].quantum_port++ <--> QuantumChannel <--> repeater[0].quantum_port_receiver++;
        repeater[0].quantum_port_receiver++ <--> QuantumChannel <--> spdc[1].quantum_port++;
        spdc[1].quantum_port++ <--> QuantumChannel <--> router[0].quantum_port_receiver++;

        node[1].port++ <--> C <--> spdc[2].port++;
        spdc[2].port++ <--> C <--> repeater[1].port++;
        repeater[1].port++ <--> C <--> spdc[3].port++;
        spdc[3].port++ <--> C <--> router[0].port++;

        node[1].quantum_port_receiver++ <--> QuantumChannel <--> spdc[2].quantum_port++;
        spdc[2].quantum_port++ <--> QuantumChannel <--> repeater[1].quantum_port_receiver++;
        repeater[1].quantum_port_receiver++ <--> QuantumChannel <--> spdc[3].quantum_port++;
        spdc[3].quantum_port++ <--> QuantumChannel <--> router[0].quantum_port_receiver++;

        node[2].port++ <--> C <--> spdc[4].port++;
        spdc[4].port++ <--> C <--> repeater[2].port++;
        repeater[2].port++ <--> C <--> spdc[5].port++;
        spdc[5].port++ <--> C <--> router[0].port++;

        node[2].quantum_port_receiver++ <--> QuantumChannel <--> spdc[4].quantum_port++;
        spdc[4].quantum_port++ <--> QuantumChannel <--> repeater[2].quantum_port_receiver++;
        repeater[2].quantum_port_receiver++ <--> QuantumChannel <--> spdc[5].quantum_port++;
        spdc[5].quantum_port++ <--> QuantumChannel <--> router[0].quantum_port_receiver++;
}



network Star_MM
{
    parameters:
        **.distance_of_light_in_fiber_per_sec = 205336.986301 km;

    types:
        channel C extends DatarateChannel
        {
            double cost = default(1);
            double distance @unit(km);
            distance = default(20km);
            //delay = uniform(0.01ms, 1s);
            double distance_of_light_in_fiber_per_sec @unit(km) = default(205336.986301km);
            delay = this.distance / distance_of_light_in_fiber_per_sec * 1s;
            datarate = uniform(1kbps, 100kbps);

        }
        channel QuantumChannel extends DatarateChannel
        {
            double cost = default(1);
            double distance @unit(km) = default(20km);
            //delay = uniform(0.01ms, 1s);
            double distance_of_light_in_fiber_per_sec @unit(km) = default(205336.986301km);
            delay = this.distance / distance_of_light_in_fiber_per_sec * 1s;
            datarate = uniform(1kbps, 100kbps);
            double photon_loss_rate = default(0);//per km
            double channel_error_rate = default(0);//per km
            double Z_error_ratio = default(1);
            double X_error_ratio = default(1);
            double Y_error_ratio = default(1);
            int test = default(0);
        }
    submodules:
        node[3]: QNode {
            address = index;
            nodeType = "EndNode";
            @display("i=device/pc");
            //emission_timing_std = 1e-5;//standard deviation. normal(0, 1e-9)
            //emission_timing_uncertainty = 10;
        }
        router[1]: QNode {
            address = index+1000000;
            @display("i=device/router");
        }



    connections:
        node[0].port++ <--> C <--> router[0].port++;
        node[1].port++ <--> C <--> router[0].port++;
        node[2].port++ <--> C <--> router[0].port++;

        node[0].quantum_port_receiver++ <--> QuantumChannel <--> router[0].quantum_port++;
        node[1].quantum_port_receiver++ <--> QuantumChannel <--> router[0].quantum_port++;
        node[2].quantum_port_receiver++ <--> QuantumChannel <--> router[0].quantum_port++;
}






