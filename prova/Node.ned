import Transceiver;
import VisibilityChecker;
import GatedQueue;

module Node
{
    parameters:
        bool start = default(false);
        bool is_satellite = default(false);
        @statistic[received_photon](record=count,vector);
        @display("bgb=192,206");
    gates:
        inout port;
    submodules:
        tc: Transceiver {
            @display("p=25,153");
        }
        vc: VisibilityChecker {
            @display("p=26,52");
        }
        gq: GatedQueue {
            @display("p=143,152");
        }
        rt: Router {
            @display("p=145,51");
        }
    connections:
        gq.line <--> port;
        tc.p2 --> rt.from_tc;
        gq.out --> rt.from_gq;
        vc.ctrl --> rt.from_vc;
        rt.to_transceiver --> tc.p1;
        rt.to_latch_ctrl --> gq.ctrl_in;
        rt.to_outside --> gq.in;
}
