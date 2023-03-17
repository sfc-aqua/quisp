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
    double first_photon_emit_time  @setter(setFirstPhotonEmitTime) @getter(getFirstPhotonEmitTime);
    double interval @setter(setInterval)  @getter(getInterval);
    QNIC_type qnic_type @setter(setQnicType)  @getter(getQnicType);
    int qnic_index      @setter(setQnicIndex) @getter(getQnicIndex);
    int qnic_parent_addr     @setter(setQnicParentAddr) @getter(getQnicParentAddr);
    QNIC_type other_qnic_type @setter(setOtherQnicType)  @getter(getOtherQnicType);
    int other_qnic_index      @setter(setOtherQnicIndex) @getter(getOtherQnicIndex);
    int other_qnic_parent_addr     @setter(setOtherQnicParentAddr) @getter(getOtherQnicParentAddr);
    double travel_time @setter(setTravelTime) @getter(getTravelTime);
}

// Used for MIM and MM. BSA results are sent back to the neighboring nodes, together with the timing notifier
packet CombinedBSAresults extends BSMTimingNotification
{
    int neighbor_address @getter(getNeighborAddress) @setter(setNeighborAddress);
    int list_of_succesful_photon_indices[] @appender(appendSuccessIndex) @getter(getSuccessfulPhotonIndices) @sizeGetter(getSuccessCount);
    PauliOperator list_of_correction_operations[] @appender(appendCorrectionOperation) @getter(getCorrectionOperationList) ;
}
