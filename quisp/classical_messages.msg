cplusplus {{ 
    #include <vector>
    #include <unsupported/Eigen/MatrixFunctions>

	using namespace omnetpp;
    typedef cModule *GOD_statQubitPtr; 
    
}} // C++ typedef
class noncobject GOD_statQubitPtr; // For tracking the truely entangled ones (Only God knows!). The system may think the qubit is entangled but it may not (darkcount)!


cplusplus {{
#include <rules/RuleSet.h>
#include <modules/QNIC.h>
typedef quisp::modules::QNIC_id_pair QNIC_pair_info;
}}
struct QNIC_pair_info;
struct QNIC_type;


namespace quisp::messages;

packet deleteThisModule{}

packet header
{
    int srcAddr;
    int destAddr;
    int hopCount;
}


packet ConnectionSetupRequest extends header
{
    int actual_destAddr;
    int actual_srcAddr;

    int number_of_required_Bellpairs;
    double required_fidelity;

    int stack_of_QNodeIndexes[];
    int stack_of_linkCosts[];

    QNIC_pair_info stack_of_QNICs[];
}

cplusplus {{
    typedef quisp::rules::RuleSet * RuleSetField;
   
}}
class noncobject RuleSetField;

packet LinkTomographyRuleSet extends header
{
    int process_id;
    int number_of_measuring_resources;
    RuleSetField RuleSet;
}

packet LinkTomographyRequest extends header
{
}

packet LinkTomographyAck extends header
{
	QNIC_type qnic_type;
	int qnic_index;
}

packet LinkTomographyResult extends header
{
	bool Output_is_plus;
	char Basis;
	int count_id;
	int partner_address;
	simtime_t finish = -1;
	int max_count;
}

packet PurificationResult extends header
{
	bool Output_is_plus;
	unsigned long ruleset_id;
	int rule_id;
	int action_index;
	GOD_statQubitPtr entangled_with;//For Debugging purposes.
}



packet DoublePurificationResult extends header
{
	bool ZOutput_is_plus;
	bool XOutput_is_plus;
	unsigned long ruleset_id;
	int rule_id;
	int action_index;
	GOD_statQubitPtr entangled_with;//For Debugging purposes.
}

packet ConditionNotSatisfied{
}

packet ConnectionSetupResponse extends header
{
    RuleSetField stack_of_RuleSets[];
}

packet BSMtimingNotifier extends header
{
    simtime_t timing_at;
    int accepted_photons_per_sec;
    double interval;
    int number_of_qubits;
    int internal_qnic_index = -1;
    int internal_qnic_address = -1;
}

packet BSAtimeoutChecker extends header
{
    double trial_id;
}

packet EPPStimingNotifier extends header
{
    simtime_t timing_at;
    double interval;
    int number_of_qubits;
    int internal_qnic = -1;
}

packet EmitPhotonRequest extends header
{
    int qubit_index;
    int qnic_index;
    int qnic_address;
    int qnic_type;
    bool receiver;
    bool first;
    bool last;
    int trial;
}

packet SchedulePhotonTransmissionsOnebyOne extends header
{
    int qnic_index = -1;
    int qnic_address;
    int num_sent = 0;
    int number_of_qubits_to_send;
    int trial;
    double interval;
    simtime_t timing;
    int internal_hom = 0;
}

packet BSAresult extends header
{
    bool entangled;

}

packet BSAfinish extends header{
    bool entangled;

}

//Used for MIM and MM. BSA results are sent back to the neighboring nodes, together with the timing notifier
packet CombinedBSAresults extends BSMtimingNotifier
{
    bool list_of_failed[];
}

//Used for MSM. BSA results are sent back to EPPS. EPPS will generate the next order based on that.
packet CombinedBSAresults_epps extends header
{
    bool list_of_failed[];
}

packet Error extends header
{
    string error_text;
}

