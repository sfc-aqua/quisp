cplusplus {{
#include "base_messages_m.h"
#include <rules/RuleSet.h>
}}

cplusplus {{
    typedef quisp::rules::RuleSet * RuleSetField;
}}
class noncobject RuleSetField;

namespace quisp::messages;

packet Header;

packet deleteThisModule{}

packet ConditionNotSatisfied{}

packet EmitPhotonRequest extends Header
{
    int qubit_index;
    int qnic_index;
    int qnic_address;
    int qnic_type;
    bool receiver;
    bool first;
    bool last;
    int trial;
}

packet SchedulePhotonTransmissionsOnebyOne extends Header
{
    int qnic_index = -1;
    int qnic_address;
    int num_sent = 0;
    int number_of_qubits_to_send;
    int trial;
    double interval;
    simtime_t timing;
    int internal_hom = 0;
}

packet StopEmitting extends Header{
    int qnic_address;
}

packet InternalRuleSetForwarding extends Header{
    unsigned long RuleSet_id;
    int Rule_id;

    RuleSetField RuleSet;
}

packet InternalRuleSetForwarding_Application extends Header{
    unsigned long RuleSet_id;
    int Rule_id;
    int application_type;

    RuleSetField RuleSet;
}
