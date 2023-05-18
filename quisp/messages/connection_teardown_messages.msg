import base_messages;
namespace quisp::messages;



packet ConnectionTeardownMessage extends Header
{
    int destAddr;
    int srcAddr;
    unsigned long RuleSet_id;
}
