import base_messages;
namespace quisp::messages;

packet OspfHelloPacket extends Header
{
    int neighbors[];
}

enum OspfState
{
    DOWN = 0;
    INIT = 1;
    TWO_WAY = 2;
}
