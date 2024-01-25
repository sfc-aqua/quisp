import channels.*;

network Network
{
    parameters:

    submodules:
        n1: Node {
            tc.start = true;
            is_satellite = true;
            @display("p=43,164");
            gq.address = 1;
        }
        n2: Node {
            is_satellite = false;
            @display("p=234,225;is=l");
            gq.address = 2;
        }
    connections:
        n1.port <--> ClassicalChannel_FS {  distance = 1km; } <--> n2.port;
}
