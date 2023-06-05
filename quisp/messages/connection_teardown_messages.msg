import base_messages;
namespace quisp::messages;



packet ConnectionTeardownMessage extends Header
{
    int destAddr;
    int srcAddr;
    unsigned long RuleSet_id;
}

packet InternalConnectionTeardownInfoForwarding extends Header
{
    int srcAddr;
    int destAddr;
    unsigned long RuleSet_id;
    int stack_of_QNodeIndexes[];
}
