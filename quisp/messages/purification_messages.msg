import base_messages;
namespace quisp::messages;

packet PurificationResult extends Header
{
    bool Output_is_plus;
    unsigned long ruleset_id;
    int rule_id;
    int shared_tag;
    int action_index;
    int PurType;
}

packet DoublePurificationResult extends PurificationResult
{
    bool ZOutput_is_plus;
    bool XOutput_is_plus;
}

packet DS_DoublePurificationResult extends PurificationResult
{
    bool ZOutput_is_plus;
    bool XOutput_is_plus;
    bool DS_ZOutput_is_plus;
    bool DS_XOutput_is_plus;
}

packet DS_DoublePurificationSecondResult extends PurificationResult
{
    bool ZOutput_is_plus;
    bool XOutput_is_plus;
    bool DS_Output_is_plus;
}
