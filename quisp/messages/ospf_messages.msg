import base_messages;
namespace quisp::messages;

packet OSPFHelloPacket extends Header
{
    int neighbors[];
}
