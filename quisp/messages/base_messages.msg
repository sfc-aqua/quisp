cplusplus  {{
    #include "base_messages_m.h"
    #include <modules/QNIC.h>
    #include <rules/RuleSet.h>
    #include <nlohmann/json.hpp>
    using quisp::rules::RuleSet;
    using quisp::modules::QNicPairInfo;
    using quisp::modules::QNIC;
    using nlohmann::json;
}}

class QNIC_type {
    @existingClass;
    @opaque;
};

class QNicPairInfo {
    @existingClass;
    @opaque;
};

class QNIC {
    @existingClass;
    @opaque;
};

class RuleSet {
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
