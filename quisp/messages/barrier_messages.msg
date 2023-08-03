cplusplus  {{
    #include "base_messages_m.h"
    #include <modules/QRSA/RuleEngine/QubitRecord/QubitRecord.h>
    using quisp::modules::qubit_record::IQubitRecord;
}}

class IQubitRecord {
    @existingClass;
    @opaque;
};

import base_messages;
namespace quisp::messages;

packet BarrierMessage extends Header
{
    int srcAddr;
    int destAddr;
    unsigned long negotiated_ruleset_id @setter(setNegotiatedRuleset_id) @getter(getNegotiatedRuleset_id);
    IQubitRecord *qubit_record @setter(setQubitRecord) @getter(getQubitRecord);
    int sequence_number;
    string role;
}
