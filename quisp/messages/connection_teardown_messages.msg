import base_messages;
namespace quisp::messages;



packet ConnectionTeardownMessage extends Header
{
    int actual_destAddr;
    int actual_srcAddr;
    int LAU_req_srcAddr;
    int LAU_req_destAddr;
    bool is_sender;
    unsigned long RuleSet_id;
}

packet InternalConnectionTeardownMessage extends Header
{
    int actual_destAddr;
    int actual_srcAddr;
    int LAU_req_srcAddr;
    int LAU_req_destAddr;
    bool is_sender;
    unsigned long RuleSet_id;
}

