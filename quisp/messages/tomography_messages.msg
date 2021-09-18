cplusplus {{
#include "base_messages_m.h"
#include <rules/RuleSet.h>
#include <modules/QNIC.h>
}}

import base_messages;

namespace quisp::messages;

packet LinkTomographyRuleSet extends Header
{
    int process_id;
    int number_of_measuring_resources;
    RuleSet* ruleSet;
}

packet LinkTomographyRequest extends Header {}

packet LinkTomographyAck extends Header
{
    QNIC_type qnic_type;
    int qnic_index;
}

packet LinkTomographyResult extends Header
{
    bool Output_is_plus;
    char Basis;
    int count_id;
    int partner_address;
    simtime_t finish = -1;
    int max_count;
    char GOD_clean;
}
