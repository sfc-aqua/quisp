
cplusplus {{
#include "base_messages_m.h"
#include <modules/QNIC.h>
#include <rules/RuleSet.h>
using quisp::rules::RuleSet;
}}

class QNIC_type {
  @existingClass;
  @opaque;
};

class QNIC_pair_info {
  @existingClass;
  @opaque;
};

class RuleSet {
  @existingClass;
  @opaque;
};

namespace quisp::messages;

packet Header
{
    int srcAddr;
    int destAddr;
    int hopCount;
}

packet Error extends Header
{
    string error_text;
}




