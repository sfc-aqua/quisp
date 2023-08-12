package modules.QRSA;
@namespace(quisp::modules);

import modules.QRSA.ConnectionManager.*;
import modules.QRSA.HardwareMonitor.*;
import modules.QRSA.RealTimeController.*;
import modules.QRSA.RoutingDaemon.*;
import modules.QRSA.RuleEngine.*;

module quantumRoutingSoft
{
    parameters:
        int number_of_qnics;
        int number_of_qnics_r;
        int number_of_qnics_rp;
        bool simultaneous_es_enabled;
    gates:
        inout rdPort; //size will be determined by the number of connections defined at the end of this file
        inout cmPort;
        inout rePort;
        inout hmPort;
        inout qnics[] @loose;
        //inout QNICPort[1];//Maybe more than one if not ENDNODE

    submodules:
        rd: RoutingDaemon {
            parameters:
                @display("p=115,63");
                number_of_qnics = parent.number_of_qnics;
                number_of_qnics_r = parent.number_of_qnics_r;
                number_of_qnics_rp = parent.number_of_qnics_rp;
        }
        hm: HardwareMonitor {
            parameters:
                @display("p=115,231");
                number_of_qnics = parent.number_of_qnics;
                number_of_qnics_r = parent.number_of_qnics_r;
                number_of_qnics_rp = parent.number_of_qnics_rp;

        }
        cm: ConnectionManager {
            parameters:
                number_of_qnics = parent.number_of_qnics;
                number_of_qnics_r = parent.number_of_qnics_r;
                number_of_qnics_rp = parent.number_of_qnics_rp;
                total_number_of_qnics = parent.number_of_qnics +  parent.number_of_qnics_r + parent.number_of_qnics_rp;
                simultaneous_es_enabled = parent.simultaneous_es_enabled;
                @display("p=227,148");
        }
        rt: RealTimeController {
            parameters:
                @display("p=227,231");
        }
        re: RuleEngine {
            parameters:
                @display("p=227,63");
                number_of_qnics = parent.number_of_qnics;
                number_of_qnics_r = parent.number_of_qnics_r;
                number_of_qnics_rp = parent.number_of_qnics_rp;
                total_number_of_qnics = parent.number_of_qnics +  parent.number_of_qnics_r + parent.number_of_qnics_rp;


        }
    connections:
        rd.RouterPort <--> rdPort;
        cm.RouterPort <--> cmPort;
        re.RouterPort <--> rePort;
        re.HardwareMonitorPort <--> hm.RuleEnginePort;
        hm.RouterPort <--> hmPort;

}
