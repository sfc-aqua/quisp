import base_messages;
namespace quisp::messages;

packet ConnectionSetupHeader extends Header {
    int application_id @getter(getApplicationId) @setter(setApplicationId);
    QNodeAddr actual_srcAddr;
    QNodeAddr actual_destAddr;
    unsigned long RuleSet_id;
    bool fromExternalNetwork;
}

packet ConnectionSetupRequest extends ConnectionSetupHeader
{
    int num_measure;
    int number_of_required_Bellpairs;
    QNodeAddr stack_of_QNodeIndexes[];
    int stack_of_linkCosts[];

    // for internetworking. this contains ConnectionSetupRequest
    Header *upperLayerRequest;
}

packet RejectConnectionSetupRequest extends ConnectionSetupHeader
{
    int number_of_required_Bellpairs;
}

packet ConnectionSetupResponse extends ConnectionSetupHeader
{
    json ruleSet;
    int application_type;
    int stack_of_QNodeIndexes[];
    QNodeAddr initiatorAddr;
    QNodeAddr responderAddr;
}
