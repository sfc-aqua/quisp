import base_messages;

namespace quisp::messages;


packet BSANotificationTimer extends Header{}

packet BSAresult extends Header
{
    bool entangled;
}

packet BSAfinish extends Header{
    bool entangled;
}
