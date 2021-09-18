

import base_messages;


namespace quisp::messages;

packet PurificationResult extends Header
{
    bool Output_is_plus;
    unsigned long ruleset_id;
    unsigned long rule_id;
    int action_index;
    cModule* entangled_with;//For Debugging purposes.
}

packet DoublePurificationResult extends Header
{
    bool ZOutput_is_plus;
    bool XOutput_is_plus;
    unsigned long ruleset_id;
    unsigned long rule_id;
    int action_index;
    cModule* entangled_with;//For Debugging purposes.
}

packet DS_DoublePurificationResult extends Header
{
    bool ZOutput_is_plus;
    bool XOutput_is_plus;
    bool DS_ZOutput_is_plus;
    bool DS_XOutput_is_plus;
    unsigned long ruleset_id;
    unsigned long rule_id;
    int action_index;
    cModule* entangled_with;//For Debugging purposes.
}

packet DS_DoublePurificationSecondResult extends Header
{
    bool ZOutput_is_plus;
    bool XOutput_is_plus;
    bool DS_Output_is_plus;
    unsigned long ruleset_id;
    unsigned long rule_id;
    int action_index;
    cModule* entangled_with;//For Debugging purposes.
}
