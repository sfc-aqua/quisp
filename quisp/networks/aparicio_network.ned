//Date: 2020/6/6
//Authors: lucho, coscos. lingraj, giuseppe, paul.
//
//Description: This to represent the network used in the paper Multiplexing schemes for quantum repeater networks
//            presented in Proceedings Volume 8163, Quantum Communications and Quantum Imaging IX; 816308 (2011)
//             https://doi.org/10.1117/12.893272
//             
//This file needs "aparicio_network.ini" to run


network aparicio_network
{
    parameters:
        **.distance_of_light_in_fiber_per_sec = 205336.986301 km;

        @display("bgb=714,412");
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
     


        A: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=device/pc;p=135,137");
        }
        B: QNode {
            address = 2;
            nodeType = "EndNode";
            @display("i=device/pc;p=135,198");
        }
        CC: QNode {
            address = 3;
            nodeType = "EndNode";
            @display("i=device/pc;p=135,268");
        }
        D: QNode {
            address = 4;
            nodeType = "EndNode";
            @display("i=device/pc;p=135,329");
        }
        G: QNode {
            address = 5;
            nodeType = "EndNode";
            @display("i=device/pc;p=313,319");
        }
        H: QNode {
            address = 6;
            nodeType = "EndNode";
            @display("i=device/pc;p=387,319");
        }
        I: QNode {
            address = 7;
            nodeType = "EndNode";
            @display("i=device/pc;p=464,319");
        }
        K: QNode {
            address = 8;
            nodeType = "EndNode";
            @display("i=device/pc;p=571,40");
        }
        L: QNode {
            address = 10;
            nodeType = "EndNode";
            @display("i=device/pc;p=571,110");
        }
        M: QNode {
            address = 11;
            nodeType = "EndNode";
            @display("i=device/pc;p=571,183");
        }
        E: QNode {
            address = 12;
            nodeType = "Router";
            @display("i=device/router;p=261,208");
        }
        F: QNode {
            address = 13;
            nodeType = "Router";
            @display("i=device/router;p=352,208");
        }
        J: QNode {
            address = 14;
            nodeType = "Router";
            @display("i=device/router;p=464,149");
        }
    connections:

        A.port++ <--> C <--> E.port++;
        B.port++ <--> C <--> E.port++;
        CC.port++ <--> C <--> E.port++;
        D.port++ <--> C <--> E.port++;
        E.port++ <--> C <--> F.port++;
        F.port++ <--> C <--> G.port++;
        F.port++ <--> C <--> H.port++;
        F.port++ <--> C <--> I.port++;
        F.port++ <--> C <--> J.port++;
        J.port++ <--> C <--> K.port++;
        J.port++ <--> C <--> L.port++;
        J.port++ <--> C <--> M.port++;
        A.quantum_port++ <--> QuantumChannel <--> E.quantum_port++;
        B.quantum_port++ <--> QuantumChannel <--> E.quantum_port++;
        CC.quantum_port++ <--> QuantumChannel <--> E.quantum_port++;
        D.quantum_port++ <--> QuantumChannel <--> E.quantum_port++;
        E.quantum_port++ <--> QuantumChannel <--> F.quantum_port++;
        F.quantum_port++ <--> QuantumChannel <--> G.quantum_port++;
        F.quantum_port++ <--> QuantumChannel <--> H.quantum_port++;
        F.quantum_port++ <--> QuantumChannel <--> I.quantum_port++;
        F.quantum_port++ <--> QuantumChannel <--> J.quantum_port++;
        J.quantum_port++ <--> QuantumChannel <--> K.quantum_port++;
        J.quantum_port++ <--> QuantumChannel <--> L.quantum_port++;
        J.quantum_port++ <--> QuantumChannel <--> M.quantum_port++;
}

