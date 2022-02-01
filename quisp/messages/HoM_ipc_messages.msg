import base_messages;

namespace quisp::messages;


packet HoMNotificationTimer extends Header{}

packet BSAresult extends Header
{
    bool entangled;
    int qnic_index = -1;
    int qubit_index = -1;
}

packet BSAfinish extends Header{
    bool entangled;
    int qnic_index = -1;
    int qnic_address = -1;
}
