cplusplus  {{
    #include <modules/Common/LinkStateRoutingProtocol/Ospf.h>
    using quisp::modules::ospf::OspfNeighborInfo;
    using quisp::modules::ospf::OspfState;
    using quisp::modules::ospf::LinkStateAdvertisement;
    using quisp::modules::ospf::RouterIds;
    using quisp::modules::ospf::LinkStateUpdate;
    using quisp::modules::ospf::LinkStateDatabaseSummary;
    using quisp::modules::ospf::NeighborTable;
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

class RouterIds {
    @existingClass;
    @opaque;
};

class NeighborTable {
    @existingClass;
    @opaque;
};

class LinkStateDatabaseSummary {
    @existingClass;
    @opaque;
};

class LinkStateUpdate {
    @existingClass;
    @opaque;
};

import base_messages;
namespace quisp::messages;

packet OspfHelloPacket extends Header
{
    NeighborTable neighbor_table;
}

packet OspfDbdPacket extends Header
{
    OspfState state;
    bool is_master;
    LinkStateDatabaseSummary lsdb;
}

packet OspfLsrPacket extends Header
{
    RouterIds ids_of_requested_lsa;
}

packet OspfLsuPacket extends Header
{
    LinkStateUpdate lsas;
}

packet OspfLsAckPacket extends Header
{

}
