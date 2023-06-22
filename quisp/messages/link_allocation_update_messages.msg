import base_messages;

namespace quisp::messages;

packet LinkAllocationUpdateRequest extends Header {
    int srcAddr @setter(setSrcAddr) @getter(getSrcAddr);
    int destAddr @setter(setDestAddr) @getter(setDestAddr);
    unsigned long current_ruleset_ids[] @setter(setCurrentRuleSet_ids) @getter(setCurrentRuleSet_ids);
    unsigned long offered_ruleset_ids[] @setter(setOfferedRuleSet_ids) @getter(setOfferedRuleSet_ids);    
}

packet LinkAllocationUpdateResponse extends Header {
  int srcAddr @setter(setSrcAddr) @getter(getSrcAddr);
  int destAddr @setter(setDestAddr) @getter(getDestAddr);
  unsigned long current_ruleset_ids[] @setter(setCurrentRuleSet_ids) @getter(getCurrentRuleSet_ids);
  unsigned long negotiated_ruleset_ids[] @setter(setNegotiatedRuleset_ids) @getter(getNegotiatedRuleset_ids); 
}


