import base_messages;

namespace quisp::messages;

packet LinkAllocationUpdateRequest extends Header {
    int srcAddr @setter(setSrcAddr) @getter(getSrcAddr);
    int destAddr @setter(setDestAddr) @getter(getDestAddr);
    unsigned long current_ruleset_id @setter(setCurrentRuleSet_id) @getter(getCurrentRuleSet_id);
    unsigned long negotiated_ruleset_id @setter(setNegotiatedRuleSet_id) @getter(getNegotiatedRuleSet_id); 
}

packet RejectLinkAllocationUpdateRequest extends Header {
    int srcAddr @setter(setSrcAddr) @getter(getSrcAddr);
    int destAddr @setter(setDestAddr) @getter(getDestAddr);
    unsigned long current_ruleset_id @setter(setCurrentRuleSet_id) @getter(getCurrentRuleSet_id);
    unsigned long negotiated_ruleset_id @setter(setNegotiatedRuleSet_id) @getter(getNegotiatedRuleSet_id); 
}

packet LinkAllocationUpdateResponse extends Header {
  int srcAddr @setter(setSrcAddr) @getter(getSrcAddr);
  int destAddr @setter(setDestAddr) @getter(getDestAddr);
  unsigned long current_ruleset_id @setter(setCurrentRuleSet_id) @getter(getCurrentRuleSet_id);
  unsigned long negotiated_ruleset_id @setter(setNegotiatedRuleSet_id) @getter(getNegotiatedRuleSet_id);
}


