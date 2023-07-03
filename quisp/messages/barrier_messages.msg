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
    unsigned long negotiated_ruleset_id;
    IQubitRecord *photon_record;
    int sequence_number;
}
