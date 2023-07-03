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
    bool is_pure_bsa_result      @setter(setIsPureBSAResult) @getter(getIsPureBSAResult);

}

packet EPPSTimingNotification extends Header
{
    double first_photon_emit_time  @setter(setFirstPhotonEmitTime) @getter(getFirstPhotonEmitTime);
    double interval @setter(setInterval)  @getter(getInterval);
    QNIC_type qnic_type @setter(setQnicType)  @getter(getQnicType);
    int qnic_index      @setter(setQnicIndex) @getter(getQnicIndex);
    int epps_address     @setter(setEppsAddr) @getter(getEppsAddr);
    double travel_time @setter(setTravelTime) @getter(getTravelTime);
}

// Used for MIM and MM. BSA results are sent back to the neighboring nodes, together with the timing notifier
packet CombinedBSAresults extends BSMTimingNotification
{
    int neighbor_address @getter(getNeighborAddress) @setter(setNeighborAddress);
    int list_of_succesful_photon_indices[] @appender(appendSuccessIndex) @getter(getSuccessfulPhotonIndices) @sizeGetter(getSuccessCount);
    PauliOperator list_of_correction_operations[] @appender(appendCorrectionOperation) @getter(getCorrectionOperationList) ;
}
