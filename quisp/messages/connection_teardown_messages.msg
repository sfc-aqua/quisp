import base_messages;
namespace quisp::messages;



packet ConnectionTeardownMessage extends Header
{
    int actual_destAddr;
    int actual_srcAddr;
    int LAU_destAddr_left;
    int LAU_destAddr_right;
    unsigned long RuleSet_id;
}

packet InternalConnectionTeardownMessage extends Header
{
    int actual_destAddr;
    int actual_srcAddr;
    int LAU_destAddr_left;
    int LAU_destAddr_right;
    unsigned long RuleSet_id;
    int stack_of_QNICAddresses[];
}

