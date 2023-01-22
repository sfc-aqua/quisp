import base_messages;

cplusplus  {{
    #include <modules/PhysicalConnection/BSA/types.h>
    using quisp::physical::types::PauliOperator;
}}

class PauliOperator {
    @existingClass;
    @opaque;
};

namespace quisp::messages;

packet BSMTimingNotification extends Header
{
    simtime_t timing_at;
    int accepted_photons_per_sec;
    double interval;
    int number_of_qubits;
    int internal_qnic_index = -1;
    int internal_qnic_address = -1;
}

// Used for MIM and MM. BSA results are sent back to the neighboring nodes, together with the timing notifier
packet CombinedBSAresults extends BSMTimingNotification
{
    bool list_of_succesful_photon_indices[] @appender(appendSuccessIndex);
    PauliOperator list_of_correction_operations[] @appender(appendCorrectionOperation);
}
