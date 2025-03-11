import base_messages;
namespace quisp::messages;



packet ConnectionSetupRequest extends Header
{
    int application_id @getter(getApplicationId) @setter(setApplicationId);
    int actual_destAddr;
    int actual_srcAddr;
    int num_measure;
    int number_of_required_Bellpairs;
    int stack_of_QNodeIndexes[];
    int stack_of_linkCosts[];
    QNicPairInfo stack_of_QNICs[];
}

packet RejectConnectionSetupRequest extends Header
{
    int application_id @getter(getApplicationId) @setter(setApplicationId);
    int actual_destAddr;
    int actual_srcAddr;
    int number_of_required_Bellpairs;
}

packet ConnectionSetupResponse extends Header
{
    int application_id @getter(getApplicationId) @setter(setApplicationId);
    int actual_srcAddr;
    int actual_destAddr;
    unsigned long RuleSet_id;
    json ruleSet;
    int application_type;
    int stack_of_QNodeIndexes[];
    simtime_t execution_start_time @setter(setStartTime) @getter(getStartTime);
}

packet TerminatedIdNotification extends Header {
    unsigned long RuleSet_id @setter(setRuleSetId) @getter(getRuleSetId);
}

packet InternalTerminatedIdNotification extends Header {
    unsigned long RuleSet_id @setter(setRuleSetId) @getter(getRuleSetId);
}

packet DeallocateResources extends Header {
    unsigned long RuleSet_id @setter(setRuleSetId) @getter(getRuleSetId);
}



