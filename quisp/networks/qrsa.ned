package networks;

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
	// XYZ --rdv defaults removed so that users will be asked; 200402
	// bool link_tomography = default(false);
	// int initial_purification = default(0);
	// int Purification_type = default(-1);
        bool link_tomography;
        int num_measure = default(3000);
        string tomography_output_filename = default("default");
        string file_dir_name = default("results/");
	// purification control
        int initial_purification;
        int Purification_type;
	// these two are obsolete controls for purification
        bool X_purification = default(false);
        bool Z_purification = default(false);
    gates:
        inout RuleEnginePort;
        inout RouterPort;
        
}

simple ConnectionManager
{
    parameters:
        int address;
        int number_of_qnics;
        int number_of_qnics_r;
        int number_of_qnics_rp;
        int total_number_of_qnics;

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
        // # of resources system hasbeen recognized
        // @signal[recog_res](type="int");
        // @statistic[recog_res](title="recognized number of resource"; record=vector, max; interpolationmode=sample-hold);
        // # of resources in the physically generated
        @signal[actual_res](type="int");
        @statistic[actual_res](title="actual number of resource"; record=vector, max; interpolationmode=sample-hold);

        // creation time
        @signal[creation_time](type="simtime_t");
        @statistic[creation_time](title="link established time"; record=vector; interpolationmode=sample-hold);


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
                number_of_qnics = number_of_qnics;
                number_of_qnics_r = number_of_qnics_r;
                number_of_qnics_rp = number_of_qnics_rp;
                total_number_of_qnics = number_of_qnics +  number_of_qnics_r + number_of_qnics_rp;
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
