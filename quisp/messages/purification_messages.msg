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

packet SteanePurificationResult extends PurificationResult
{
    bool Output_is_plus_1;
    bool Output_is_plus_2;
    bool Output_is_plus_3;
    bool Output_is_plus_4;
    bool Output_is_plus_5;
    bool Output_is_plus_6;
}