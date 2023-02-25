import base_messages;

namespace quisp::messages;

packet SwappingResult extends Header{

    unsigned long ruleset_id @setter(setRulesetId)         @getter(getRulesetId);
    int shared_rule_tag      @setter(setSharedRuleTag)     @getter(getSharedRuleTag);
    int sequence_number      @setter(setSequenceNumber)    @getter(getSequenceNumber);
    int correction_frame     @setter(setCorrectionFrame)   @getter(getCorrectionFrame);
    int new_partner          @setter(setNewPartner)        @getter(getNewPartner);

    unsigned long RuleSet_id;
    int Rule_id;
    int shared_tag;
    int action_index;

    int left_Dest;
    int right_Dest;

    int new_partner_left;
    int new_partner_qnic_index_left;
    int new_partner_qnic_address_left;
    int measured_qubit_index_left;
    QNIC_type new_partner_qnic_type_left;

    int new_partner_right;
    int new_partner_qnic_index_right;
    int new_partner_qnic_address_right;
    int measured_qubit_index_right;
    QNIC_type new_partner_qnic_type_right;

    int operation_type_left;
    int operation_type_right;

    int operation_type; // when this would reach the destination
    int new_partner_qnic_index;
    int new_partner_qnic_address;
    int measured_qubit_index;
    QNIC_type new_partner_qnic_type;
}

packet SimultaneousSwappingResult extends Header{
    unsigned long RuleSet_id;
    unsigned long Rule_id;
    int action_index;

    int initiator_Dest;
    int responder_Dest;

    int new_partner_left;
    int new_partner_qnic_index_left;
    int new_partner_qnic_address_left;
    int measured_qubit_index_left;
    QNIC_type new_partner_qnic_type_left;

    int new_partner_right;
    int new_partner_qnic_index_right;
    int new_partner_qnic_address_right;
    int measured_qubit_index_right;
    QNIC_type new_partner_qnic_type_right;

    int operation_type_left;
    int operation_type_right;

    int operation_type; // when this would reach the destination
    int new_partner;
    int new_partner_qnic_index;
    int new_partner_qnic_address;
    int measured_qubit_index;
    QNIC_type new_partner_qnic_type;

    // Simultaneous EP
    int index_in_path;
    int path_length_exclude_IR;
}

packet WaitResult extends Header {
    unsigned long RuleSet_id;
    unsigned long Rule_id;
}
