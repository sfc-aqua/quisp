import base_messages;

namespace quisp::messages;

packet SwappingResult extends Header {
    unsigned long ruleset_id @setter(setRulesetId)         @getter(getRulesetId);
    int shared_rule_tag      @setter(setSharedRuleTag)     @getter(getSharedRuleTag);
    int sequence_number      @setter(setSequenceNumber)    @getter(getSequenceNumber);
    int correction_frame     @setter(setCorrectionFrame)   @getter(getCorrectionFrame);
    int new_partner          @setter(setNewPartner)        @getter(getNewPartner);
}
