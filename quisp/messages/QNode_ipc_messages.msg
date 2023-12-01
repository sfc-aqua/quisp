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
    bool is_msm @getter(isMSM) @setter(setMSM);
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
