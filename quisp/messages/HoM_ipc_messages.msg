cplusplus {{
#include "base_messages_m.h"
}} 

namespace quisp::messages;

packet Header;

packet HoMNotificationTimer extends Header{}

packet BSAresult extends Header
{
    bool entangled;
}

packet BSAfinish extends Header{
    bool entangled;
}
