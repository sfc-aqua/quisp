import base_messages;

namespace quisp::messages;

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
    unsigned long Rule_id;

    RuleSet* ruleSet;
}

packet InternalRuleSetForwarding_Application extends Header{
    unsigned long RuleSet_id;
    unsigned long Rule_id;
    int application_type;

    RuleSet* ruleSet;
}
