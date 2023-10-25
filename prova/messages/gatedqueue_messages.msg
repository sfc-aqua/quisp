namespace messages;

packet GQ_ctrl {
    bool ctrl_signal;
    bool is_copy = false;
}

class NeighborTable {
    int neighbor;
    string st;
}



packet Header
{
    int srcAddr;
    int destAddr;
    int hopCount;
}

packet OspfPacket extends Header
{
    int sending_gate_index @getter(getSendingGateIndex) @setter(setSendingGateIndex);
}

packet OspfHelloPacket extends OspfPacket
{
    NeighborTable neighbor_table @getter(getNeighborTable) @setter(setNeighborTable);
}