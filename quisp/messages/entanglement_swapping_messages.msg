cplusplus {{
#include "base_messages_m.h"
#include <modules/QNIC.h>

using namespace quisp::modules;
}}

struct QNIC_type;

namespace quisp::messages;

packet Header;

packet SwappingResult extends Header{
    unsigned long RuleSet_id;
    int Rule_id;
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
    int new_partner;
    int new_partner_qnic_index;
    int new_partner_qnic_address;
    int measured_qubit_index;
    QNIC_type new_partner_qnic_type;
}

packet SimultaneousSwappingResult extends Header{
    unsigned long RuleSet_id;
    int Rule_id;
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