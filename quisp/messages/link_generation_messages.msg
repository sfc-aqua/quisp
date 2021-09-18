cplusplus {{
#include "base_messages_m.h"
}}

import base_messages;
namespace quisp::messages;


packet BSMtimingNotifier extends Header
{
    simtime_t timing_at;
    int accepted_photons_per_sec;
    double interval;
    int number_of_qubits;
    int internal_qnic_index = -1;
    int internal_qnic_address = -1;
}

packet EPPStimingNotifier extends Header
{
    simtime_t timing_at;
    double interval;
    int number_of_qubits;
    int internal_qnic = -1;
}

//Used for MIM and MM. BSA results are sent back to the neighboring nodes, together with the timing notifier
packet CombinedBSAresults extends BSMtimingNotifier
{
    bool list_of_failed[];
}

//Used for MSM. BSA results are sent back to EPPS. EPPS will generate the next order based on that.
packet CombinedBSAresults_epps extends Header
{
    bool list_of_failed[];
}
