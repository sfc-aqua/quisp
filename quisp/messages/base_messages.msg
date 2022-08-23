cplusplus  {{
    #include "base_messages_m.h"
    #include <modules/QNIC.h>
    #include <rules/Active/ActiveRuleSet.h>
    #include <nlohmann/json.hpp>
    using quisp::rules::active::ActiveRuleSet;
    using quisp::modules::QNIC_pair_info;
    using quisp::modules::QNIC_type;
    using nlohmann::json;
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

class json {
    @existingClass;
    @opaque;
}

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
