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
        //inout dummyQNICLink[];
}

simple HardwareMonitor
{
    parameters:
        int address;
        int number_of_qnics;
        int number_of_qnics_r;
        int number_of_qnics_rp;
        string ntable = "";
        bool link_tomography = default(false);
        int initial_purification = default(0);
        bool X_purification = default(false);
        bool Z_purification = default(false);
        int Purification_type = default(-1);
        int num_measure = default(3000);
        string tomography_output_filename = default("default");
        string file_dir_name = default("results/");
    gates:
        inout RuleEnginePort;
        inout RouterPort;
        
}

simple ConnectionManager
{
    parameters:
        int address;
    gates:
        inout RouterPort;
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
        inout RouterPort;
        inout HardwareMonitorPort;
}

simple RealTimeController
{
    parameters:
        int address;
    //gates:
        //inout QNIC[];
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
        inout hmPort;
        inout qnics[] @loose;
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
        cm.RouterPort <--> cmPort;
        re.RouterPort <--> rePort;
        re.HardwareMonitorPort <--> hm.RuleEnginePort;
        hm.RouterPort <--> hmPort;
        
        //for i=0..sizeof(qnics)-1{
        //    rd.dummyQNICLink++ <--> qnics[i];
        //}

}
