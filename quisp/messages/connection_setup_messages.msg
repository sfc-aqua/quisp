cplusplus {{
#include "base_messages_m.h"
#include <modules/QNIC.h>
#include <rules/RuleSet.h>
}} 

cplusplus {{
    typedef quisp::rules::RuleSet * RuleSetField;
}}
class noncobject RuleSetField;

struct QNIC_pair_info;

namespace quisp::messages;

packet Header;

packet ConnectionSetupRequest extends Header
{
    int actual_destAddr;
    int actual_srcAddr;
    int num_measure;
    int number_of_required_Bellpairs;
    int stack_of_QNodeIndexes[];
    int stack_of_linkCosts[];
    QNIC_pair_info stack_of_QNICs[];
}

packet RejectConnectionSetupRequest extends Header
{
    int actual_destAddr;
    int actual_srcAddr;
    int number_of_required_Bellpairs;
}

packet ConnectionSetupResponse extends Header
{
    int actual_srcAddr;
    int actual_destAddr;
    unsigned long RuleSet_id;
    RuleSetField RuleSet;
    int application_type;
    int stack_of_QNodeIndexes[];
}
