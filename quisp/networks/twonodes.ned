package networks;

import ned.DatarateChannel;
import modules.*;
import modules.Backend.Backend;
import channels.*;


network twonodes
{
    @display("bgb=418,183");
    types:
        channel C extends DatarateChannel
        {
            double cost = default(1);
            double distance @unit(km);
            distance = default(20km);
            //delay = uniform(0.01ms, 1s);
            delay = this.distance / 200000km * 1s;
            datarate = uniform(1kbps, 100kbps);
        }

    submodules:
        backend: Backend;
        source: QNode {
            address = 1;
            buffers = 7;
            @display("i=COMP");
        }
        target: QNode {
            address = 3;
            buffers = 7;
            @display("i=COMP;p=118.745,36.465");
        }

    connections:
        source.port++ <--> C <--> target.port++;
}


network threenodes
{
    types:
        channel C extends DatarateChannel
        {
            int index_temp;
            double cost = default(1);
            double distance @unit(km);
            distance = default(20km);
            //delay = uniform(0.01ms, 1s);
            delay = this.distance / 200000km * 1s;
            datarate = uniform(1kbps, 100kbps);
        }

    submodules:
        backend: Backend;
        source: QNode {
            address = 1;
            buffers = 7;
            @display("i=COMP;p=230,165");

        }
        target: QNode {
            address = 3;
            buffers = 3;
            @display("i=COMP;p=296,96");
        }
        anothertarget: QNode {
            address = 2;
            buffers = 3;
            @display("i=COMP;p=358,201");
        }

    connections:
        source.port++ <--> C { @display("ls=green,2"); index_temp = 1; cost = 100; } <--> target.port++;
        source.port++ <--> C { @display("ls=red,2"); index_temp = 2; } <--> anothertarget.port++;
        target.port++ <--> C { @display("ls=black,2"); index_temp = 3; } <--> anothertarget.port++;
}



network morenodes
{
    types:
        channel C extends DatarateChannel
        {
            //int index_temp;
            double cost = default(1);
            double distance @unit(km);
            distance = default(20km);
            //delay = uniform(0.01ms, 1s);
            delay = this.distance / 200000km * 1s;
            datarate = uniform(1kbps, 100kbps);
        }

    submodules:
        backend: Backend;
        source: QNode {
            address = 1;
            @display("i=COMP;p=278,81");
        }
        target: QNode {
            address = 2;
            @display("i=COMP;p=182,56");
        }
        anotherTarget: QNode {
            address = 3;
            @display("i=COMP;p=299,147");
        }
        andmoreTarget: QNode {
            address = 4;
            @display("i=COMP;p=57,79");
        }

    connections:
        source.port++ <--> C {  cost = 2; } <--> target.port++;
        source.port++ <--> C {  cost = 30;@display("ls=red"); } <--> anotherTarget.port++;
        anotherTarget.port++ <--> C {  cost = 2; } <--> andmoreTarget.port++;
        andmoreTarget.port++ <--> C {  cost = 2; } <--> anotherTarget.port++;
        andmoreTarget.port++ <--> C {  cost = 2; } <--> target.port++;
}



