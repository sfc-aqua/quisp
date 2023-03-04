import base_messages;

namespace quisp::messages;

packet DeleteThisModule{}

packet GenerateTraffic{}

packet EmitPhotonRequest extends Header
{
    int qubit_index @setter(setQubitIndex) @getter(getQubitIndex);
    int qnic_index  @setter(setQnicIndex) @getter(getQnicIndex);
    QNIC_type qnic_type  @setter(setQnicType)   @getter(getQnicType);
    simtime_t interval_between_photons @setter(setIntervalBetweenPhotons) @getter(getIntervalBetweenPhotons);
    bool is_first @getter(isFirst) @setter(setFirst);
    bool is_last  @getter(isLast)  @setter(setLast);
}

packet SchedulePhotonTransmissionsOnebyOne extends Header
{
    int qnic_index = -1;
    int qnic_address;
    int num_sent = 0;
    int number_of_qubits_to_send;
    int trial;
    simtime_t interval;
    simtime_t timing;
    int internal_hom = 0;
}

packet StopEmitting extends Header{
    int qnic_address;
}

packet InternalRuleSetForwarding extends Header{
    unsigned long RuleSet_id;
    unsigned long Rule_id;

    json RuleSet;
}

packet InternalRuleSetForwarding_Application extends Header{
    unsigned long RuleSet_id;
    unsigned long Rule_id;
    int application_type;

    json RuleSet;
}
