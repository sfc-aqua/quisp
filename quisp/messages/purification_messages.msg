cplusplus {{
#include "base_messages_m.h"

using namespace omnetpp;
typedef cModule *GOD_statQubitPtr;
}} // C++ typedef
class noncobject GOD_statQubitPtr; // For tracking the truely entangled ones (Only God knows!). The system may think the qubit is entangled but it may not (darkcount)!

namespace quisp::messages;

packet Header;

packet PurificationResult extends Header
{
    bool Output_is_plus;
    unsigned long ruleset_id;
    int rule_id;
    int action_index;
    GOD_statQubitPtr entangled_with;//For Debugging purposes.
}

packet DoublePurificationResult extends Header
{
    bool ZOutput_is_plus;
    bool XOutput_is_plus;
    unsigned long ruleset_id;
    int rule_id;
    int action_index;
    GOD_statQubitPtr entangled_with;//For Debugging purposes.
}

packet DS_DoublePurificationResult extends Header
{
    bool ZOutput_is_plus;
    bool XOutput_is_plus;
    bool DS_ZOutput_is_plus;
    bool DS_XOutput_is_plus;
    unsigned long ruleset_id;
    int rule_id;
    int action_index;
    GOD_statQubitPtr entangled_with;//For Debugging purposes.
}

packet DS_DoublePurificationSecondResult extends Header
{
    bool ZOutput_is_plus;
    bool XOutput_is_plus;
    bool DS_Output_is_plus;
    unsigned long ruleset_id;
    int rule_id;
    int action_index;
    GOD_statQubitPtr entangled_with;//For Debugging purposes.
}
