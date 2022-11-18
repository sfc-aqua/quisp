package modules.QRSA.HardwareMonitor;
@namespace(quisp::modules);

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
	// int purification_type = default(-1);
        bool link_tomography;
        int num_measure = default(3000);
        string tomography_output_filename = default("default");
        string file_dir_name = default("results/");
	// purification control
        int initial_purification;
        int purification_type;
	// these two are obsolete controls for purification
        bool x_purification = default(false);
        bool z_purification = default(false);
    gates:
        inout RuleEnginePort;
        inout RouterPort;

}
