cplusplus {{
#include "base_messages_m.h"
}}
import base_messages;

namespace quisp::messages;


packet HoMNotificationTimer extends Header{}

packet BSAresult extends Header
{
    bool entangled;
}

packet BSAfinish extends Header{
    bool entangled;
}
