import base_messages;
namespace quisp::messages;


packet ConnectionSetupRequest extends Header
{
    int application_id @getter(getApplicationId) @setter(setApplicationId);
    QNodeAddr actual_destAddr;
    QNodeAddr actual_srcAddr;
    int num_measure;
    int number_of_required_Bellpairs;
    QNodeAddr stack_of_QNodeIndexes[];
    int stack_of_linkCosts[];
    QNIC_pair_info stack_of_QNICs[];

    // for internetworking. this contains ConnectionSetupRequest
    Header *upperLayerRequest;
}

packet RejectConnectionSetupRequest extends Header
{
    int application_id @getter(getApplicationId) @setter(setApplicationId);
    QNodeAddr actual_destAddr;
    QNodeAddr actual_srcAddr;
    int number_of_required_Bellpairs;
}

packet ConnectionSetupResponse extends Header
{
    int application_id @getter(getApplicationId) @setter(setApplicationId);
    QNodeAddr actual_srcAddr;
    QNodeAddr actual_destAddr;
    unsigned long RuleSet_id;
    json ruleSet;
    int application_type;
    int stack_of_QNodeIndexes[];
}
