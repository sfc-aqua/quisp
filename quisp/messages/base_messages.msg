cplusplus  {{
    #include "base_messages_m.h"
    #include <modules/QNIC.h>
    #include <rules/Active/ActiveRuleSet.h>
    using quisp::rules::active::ActiveRuleSet;
    using quisp::modules::QNIC_pair_info;
}}

class QNIC_type {
    @existingClass;
    @opaque;
};

class QNIC_pair_info {
    @existingClass;
    @opaque;
};

class ActiveRuleSet {
    @existingClass;
    @opaque;
};

namespace quisp::messages;

packet Header
{
    int srcAddr;
    int destAddr;
    int hopCount;
}

packet Error extends Header
{
    string error_text;
}
