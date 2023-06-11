cplusplus  {{
    #include <modules/Common/Ospf.h>
    using quisp::modules::OspfNeighborInfo;
    using quisp::modules::OspfState;
    using quisp::modules::LinkStateAdvertisement;
}}

class OspfNeighborInfo {
    @existingClass;
    @opaque;
};

class OspfState {
    @existingClass;
    @opaque;
};

class LinkStateAdvertisement {
    @existingClass;
    @opaque;
};

import base_messages;
namespace quisp::messages;

packet OspfHelloPacket extends Header
{
    int neighbors[];
}

packet OspfDbdPacket extends Header
{
    int dd_sequence;
    OspfState state;
    bool is_master;
    LinkStateAdvertisement lsdb[];
}

packet OspfLsrPacket extends Header
{
    int requested_router_info[];
}

packet OspfLsuPacket extends Header
{
    LinkStateAdvertisement lsas[];
}

packet OspfLsAckPacket extends Header
{

}
