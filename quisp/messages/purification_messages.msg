import base_messages;
namespace quisp::messages;

packet PurificationResult extends Header
{
    unsigned long ruleset_id @setter(setRulesetId)         @getter(getRulesetId);
    int shared_rule_tag      @setter(setSharedRuleTag)     @getter(getSharedRuleTag);
    int sequence_number      @setter(setSequenceNumber)    @getter(getSequenceNumber);
    int measurement_result   @setter(setMeasurementResult) @getter(getMeasurementResult); // can handle up to 32 qubits protocol
    int protocol             @setter(setProtocol)          @getter(getProtocol);
}
