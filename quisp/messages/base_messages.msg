cplusplus  {{
    #include "base_messages_m.h"
    #include <modules/QNIC.h>
    #include <rules/RuleSet.h>
    #include <nlohmann/json.hpp>
    #include <types/QNodeAddr.h>
    using quisp::rules::RuleSet;
    using quisp::modules::QNIC_pair_info;
    using nlohmann::json;
    using quisp::types::QNodeAddr;
}}

class QNIC_type {
    @existingClass;
    @opaque;
};

class QNodeAddr {
    @existingClass;
    @opaque;
    @toString(.str());
};

class QNIC_pair_info {
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
    QNodeAddr srcAddr;
    QNodeAddr destAddr;
    int hopCount;
}

packet Error extends Header
{
    string error_text;
}
