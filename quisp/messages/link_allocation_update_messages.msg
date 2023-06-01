import base_messages;

namespace quisp::messages;

packet LinkAllocationUpdateRequest extends Header {
    int srcAddr @setter(setSrcAddr) @getter(getSrcAddr);
    int destAddr @setter(setdestAddr) @getter(setdestAddr);
    unsigned long current_ruleset_id @setter(setCurrentRuleSet_id) @getter(setCurrentRuleSet_id);
    unsigned long offered_ruleset_ids[] @setter(setOfferedRuleSet_ids) @getter(setOfferedRuleSet_ids);    
}

packet LinkAllocationUpdateResponse extends Header {
  int srcAddr @setter(setSrcAddr) @getter(getSrcAddr);
  int destAddr @setter(setDestAddr) @getter(getDestAddr);
  unsigned long current_ruleset_id @setter(setCurrentRuleSet_id) @getter(getCurrentRuleSet_id);
  unsigned long negotiated_ruleset_id @setter(setNegotiatedRuleset_id) @getter(getNegotiatedRuleset_id); 
}


