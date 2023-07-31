import base_messages;

namespace quisp::messages;

packet LinkAllocationUpdateDecisionRequest extends Header {
    int srcAddr @setter(setSrcAddr) @getter(getSrcAddr);
    int destAddr @setter(setDestAddr) @getter(setDestAddr);
    unsigned long current_ruleset_id @setter(setCurrentRuleSet_id) @getter(getCurrentRuleSet_id);
    unsigned long offered_ruleset_ids[] @setter(setOfferedRuleSet_ids) @getter(getOfferedRuleSet_ids);    
}

packet LinkAllocationUpdateDecisionResponse extends Header {
  int srcAddr @setter(setSrcAddr) @getter(getSrcAddr);
  int destAddr @setter(setDestAddr) @getter(getDestAddr);
  unsigned long current_ruleset_id @setter(setCurrentRuleSet_id) @getter(getCurrentRuleSet_id);
  unsigned long negotiated_ruleset_id @setter(setNegotiatedRuleset_id) @getter(getNegotiatedRuleset_id); 
}

packet LinkAllocationUpdateRequest extends Header {
    int srcAddr @setter(setSrcAddr) @getter(getSrcAddr);
    int destAddr @setter(setDestAddr) @getter(setDestAddr);
    unsigned long current_ruleset_id @setter(setCurrentRuleSet_id) @getter(getCurrentRuleSet_id);
    unsigned long offered_ruleset_ids[] @setter(setOfferedRuleSet_ids) @getter(getOfferedRuleSet_ids);    
}

packet LinkAllocationUpdateResponse extends Header {
  int srcAddr @setter(setSrcAddr) @getter(getSrcAddr);
  int destAddr @setter(setDestAddr) @getter(getDestAddr);
  unsigned long current_ruleset_id @setter(setCurrentRuleSet_id) @getter(getCurrentRuleSet_id);
  unsigned long negotiated_ruleset_id @setter(setNegotiatedRuleset_id) @getter(getNegotiatedRuleset_id); 
}


