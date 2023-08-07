cplusplus  {{
    #include <modules/QRSA/RoutingDaemon/RoutingProtocol/Ospf/Ospf.h>
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

packet OspfPacket extends Header
{
    int sending_gate_index @getter(getSendingGateIndex) @setter(setSendingGateIndex);
}

packet OspfHelloPacket extends OspfPacket
{
    NeighborTable neighbor_table @getter(getNeighborTable) @setter(setNeighborTable);
}

packet OspfDbdPacket extends OspfPacket
{
    OspfState state;
    bool is_master @getter(isMaster) @setter(setIsMaster);
    LinkStateDatabaseSummary lsdb;
}

packet OspfLsrPacket extends OspfPacket
{
    RouterIds ids_of_requested_lsa @getter(getIDsOfRequestedLsa) @setter(setIDsOfRequestedLsa);
}

packet OspfLsuPacket extends OspfPacket
{
    LinkStateUpdate lsas;
}

packet OspfLsAckPacket extends OspfPacket
{

}
