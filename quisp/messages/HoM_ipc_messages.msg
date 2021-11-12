cplusplus {{
#include "base_messages_m.h"
}}

namespace quisp::messages;

packet Header;

packet HoMNotificationTimer extends Header{}

packet BSAresult extends Header
{
    bool entangled;
    int QNIC_index = -1;
    int qubit_index = -1;
}

packet BSAfinish extends Header{
    bool entangled;
    int QNIC_index = -1;
}
