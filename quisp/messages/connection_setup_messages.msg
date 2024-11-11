import base_messages;
namespace quisp::messages;



packet ConnectionSetupRequest extends Header
{
    int application_id @getter(getApplicationId) @setter(setApplicationId);
    int actual_destAddr;
    int actual_srcAddr;
    unsigned long connection_setup_request_id @setter(setConnectionSetupRequestId) @getter(getConnectionSetupRequestId);
    int num_measure;
    int number_of_required_Bellpairs;
    int stack_of_QNodeIndexes[];
    int stack_of_linkCosts[];
    QNicPairInfo stack_of_QNICs[];
}

packet RejectConnectionSetupRequest extends Header
{
    int application_id @getter(getApplicationId) @setter(setApplicationId);
    unsigned long connection_setup_request_id @setter(setConnectionSetupRequestId) @getter(getConnectionSetupRequestId);
    int actual_destAddr;
    int actual_srcAddr;
    int number_of_required_Bellpairs;
}

packet ConnectionSetupResponse extends Header
{
    int application_id @getter(getApplicationId) @setter(setApplicationId);
    int actual_srcAddr;
    int actual_destAddr;
    int initiator_addr @setter(setInitiatorAddr) @getter(getInitiatorAddr);
    int responder_addr @setter(setResponderAddr) @getter(getResponderAddr);
    unsigned long connection_setup_request_id @setter(setConnectionSetupRequestId) @getter(getConnectionSetupRequestId);
    unsigned long RuleSet_id;
    json ruleSet;
    int application_type;
    int stack_of_QNodeIndexes[];
}

packet InternalTerminatedRulesetIdsNotifier extends Header {
    unsigned long terminated_rulesets_ids[] @getter(getTerminatedRulesetId) @appender(appendTerminatedRulesetId) @sizeGetter(getNumberOfTerminatedRulesets);
}

packet ConnectionTeardown extends Header {
    unsigned long RuleSet_id;
}

packet RequestQnicReservation extends Header
{
    unsigned long RuleSet_id;
    int qnic_addr @getter(getQnicAddr) @setter(setQnicAddr);
    int partner_address @getter(getPartnerAddress) @setter(setPartnerAddress);
    bool prepare_teardown @setter(setPrepareTeardown) @getter(getPrepareTeardown);
}

packet RequestRulesetTermination extends Header
{
    unsigned long RuleSet_id;
}

packet ReleaseResources extends Header
{
    int qnic_addresses[] @getter(getQnicAddr) @appender(appendQnicAddr) @sizeGetter(getNumberOfQnicAddrs);
}