package networks;
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//



simple RoutingDaemon
{
    parameters:
        int address;
    gates:
        //output toRouter;
        //input fromRouter;
        //inout RouterPort;
        //output toConnectionManager;
        //input fromConnectionManager;
        //output toHardwareMonitor;
        //input fromHardwareMonitor;
}

simple HardwareMonitor
{
    parameters:
        int address;
        int number_of_qnics;
        int number_of_qnics_r;
        int number_of_qnics_rp;
        string ntable = "";

    gates:
        //output toRoutingDaemon;
        //input fromRoutingDaemon;
        //Either one of the sets
        //output toRealTimeController;
        //input fromRealTimeController;
        //output toRuleEngine;
        //input fromRuleEngine;
}

simple ConnectionManager
{
    parameters:
        int address;
        //int number_of_qnics;
        //int number_of_qnics_r;
        //int numner_of_qnics_rp;
        //int total_number_of_qnics;
    gates:
        //output toRouter;
        //input fromRouter;
        inout RouterPort;

        //output toRoutingDaemon;
        //input fromRoutingDaemon;
        //output toRuleEngine;
        //input fromRuleEngine;
}

simple RuleEngine
{
    parameters:
        int address;
        int number_of_qnics;
        int number_of_qnics_r;
        int number_of_qnics_rp;
        int total_number_of_qnics;

    gates:
        //output toRouter;
        //input fromRouter;
        inout RouterPort;

        //output toConnectionManager;
        //input fromConnectionManager;
        //output toRealTimeController;
        //input fromRealTimeController;
        //Maybe not needed
        //output toHardwareMonitor;
        //input fromHardwareMonitor;
}

simple RealTimeController
{
    parameters:
        int address;
    gates:
        inout QNIC[];
        //output toRuleEngine;
        //input fromRuleEngine;
        //Maybe not needed
        //output toHardwareMonitor;
        //input fromHardwareMonitor;
}


module quantumRoutingSoft
{
    parameters:
        int address;
        int number_of_qnics;
        int number_of_qnics_r;
        int number_of_qnics_rp;
    gates:
        //inout rdPort;//size will be determined by the number of connections defined at the end of this file
        inout cmPort;
        inout rePort;
        //inout QNICPort[1];//Maybe more than one if not ENDNODE

    submodules:
        rd: RoutingDaemon {
            parameters:
                address = address;//share the same address within all inner modules
                @display("p=115,63");
        }
        hm: HardwareMonitor {
            parameters:
                address = address;//share the same address within all inner modules
                @display("p=115,231");
                number_of_qnics = number_of_qnics;
                number_of_qnics_r = number_of_qnics_r;
                number_of_qnics_rp = number_of_qnics_rp;

        }
        cm: ConnectionManager {
            parameters:
                address = address;//share the same address within all inner modules
                @display("p=227,148");
        }
        rt: RealTimeController {
            parameters:
                address = address;//share the same address within all inner modules
                @display("p=227,231");
        }
        re: RuleEngine {
            parameters:
                address = address;//share the same address within all inner modules
                @display("p=227,63");
                number_of_qnics = number_of_qnics;
                number_of_qnics_r = number_of_qnics_r;
                number_of_qnics_rp = number_of_qnics_rp;
                total_number_of_qnics = number_of_qnics +  number_of_qnics_r + number_of_qnics_rp;


        }
    connections:
        //rd.toHardwareMonitor --> hm.fromRoutingDaemon;
        //rd.fromHardwareMonitor <-- hm.toRoutingDaemon;
        //rd.toConnectionManager --> cm.fromRoutingDaemon;
        //rd.fromConnectionManager <-- cm.toRoutingDaemon;
        //cm.toRuleEngine --> re.fromConnectionManager;
        //cm.fromRuleEngine <-- re.toConnectionManager;
        //re.toRealTimeController --> rt.fromRuleEngine;
        //re.fromRealTimeController <-- rt.toRuleEngine;

        //rt.toHardwareMonitor --> hm.fromRealTimeController;
        //rt.fromHardwareMonitor <-- hm.toRealTimeController;
        //hm.toRuleEngine --> re.fromHardwareMonitor;
        //hm.fromRuleEngine <-- re.toHardwareMonitor;

        //rd.RouterPort <--> rdPort;
        cm.RouterPort <--> cmPort;
        re.RouterPort <--> rePort;
        //rt.QNIC[0] <--> QNICPort[0];
}
