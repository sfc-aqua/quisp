import base_messages;

namespace quisp::messages;

packet LinkAllocationUpdateRequest extends Header {
  int srcAddr @setter(setSrcAddr) @getter(getSrcAddr);
  int destAddr @setter(setDestAddr) @getter(getDestAddr);
  unsigned long stack_of_CurrentRulesetIDs[];
  unsigned long stack_of_NextRulesetIDs[];
  int random_number; 
}

packet RejectLinkAllocationUpdateRequest extends Header {
  int srcAddr @setter(setSrcAddr) @getter(getSrcAddr);
  int destAddr @setter(setDestAddr) @getter(getDestAddr);
}

packet LinkAllocationUpdateResponse extends Header {
  int srcAddr @setter(setSrcAddr) @getter(getSrcAddr);
  int destAddr @setter(setDestAddr) @getter(getDestAddr);
  unsigned long stack_of_CurrentRulesetIDs[];
  unsigned long stack_of_NextRulesetIDs[];
  int random_number; 
}


