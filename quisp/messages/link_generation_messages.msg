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
    simtime_t first_photon_emit_time @setter(setFirstPhotonEmitTime) @getter(getFirstPhotonEmitTime);
    simtime_t interval  @setter(setInterval)  @getter(getInterval);
    QNIC_type qnic_type @setter(setQnicType)  @getter(getQnicType);
    int qnic_index      @setter(setQnicIndex) @getter(getQnicIndex);
}

packet EPPSTimingNotification extends Header
{
    simtime_t firstPhotonEmitTime;
    simtime_t interval;
    QNIC_type qnicType;
    int qnicIndex;
    int qnicParentAddr;
    QNIC_type otherQnicType;
    int otherQnicIndex;
    int otherQnicParentAddr;
    simtime_t totalTravelTime;
    int EPPSAddr;
}

// Used for MIM and MM. BSA results are sent back to the neighboring nodes, together with the timing notifier
packet CombinedBSAresults extends BSMTimingNotification
{
    int neighbor_address @getter(getNeighborAddress) @setter(setNeighborAddress);
    int list_of_succesful_photon_indices[] @appender(appendSuccessIndex) @getter(getSuccessfulPhotonIndices) @sizeGetter(getSuccessCount);
    PauliOperator list_of_correction_operations[] @appender(appendCorrectionOperation) @getter(getCorrectionOperationList) ;
}

// Used for MSM. Sends the BSA success/failure, correction message to the partner node
packet MSMResult extends Header
{
    QNIC_type qnicType;
    int qnicIndex;
    uint64_t photonIndex;
    bool success;
    PauliOperator correctionOperation;
}

packet MSMResultArrivalCheck extends Header
{
    int qnicIndex;
    int qubitIndex;
}

packet StopEPPSEmission extends Header
{
}
