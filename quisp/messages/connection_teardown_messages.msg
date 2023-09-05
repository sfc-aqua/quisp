import base_messages;
namespace quisp::messages;



packet ConnectionTeardownMessage extends Header
{
    int actual_srcAddr;
    int actual_destAddr;
    unsigned long RuleSet_id;
}

packet InternalConnectionTeardownMessage extends Header
{
    int actual_srcAddr;
    int actual_destAddr;
    string role;
    unsigned long RuleSet_id;
}

