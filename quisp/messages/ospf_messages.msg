import base_messages;
namespace quisp::messages;

packet OspfHelloPacket extends Header
{
    int neighbors[];
}

packet OspfDbdPacket extends Header
{
    int dd_sequence;
    int state;
    bool is_master;
    Lsa lsas[];
}

packet Lsa extends Header
{
    int lsa_id;
    int lsa_origin_id;
    int lsa_age;
    int adjacent[];
}

packet Lsr extends Header
{
    int requested_router_info[];
}

packet LsuPacket extends Header
{
    Lsa lsas[];
}

packet LsAckPacket extends Header
{

}

enum OspfState
{
    DOWN = 0;
    INIT = 1;
    TWO_WAY = 2;
    EXSTART = 3;
    EXCHANGE = 4;
    LOADING = 5;
    FULL = 6;
}
