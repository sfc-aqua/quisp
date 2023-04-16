from quisp import QNodeAddr
from typing import List, Tuple, Optional


def find_network_boundary(
    paths: "List[List[QNodeAddr]]", src_addr: "QNodeAddr", dest_addr: "QNodeAddr"
):
    """
    RoutingDaemon::findNetworkBoundary's algorithm
    """
    layers: "List[List[QNodeAddr]]" = [[src_addr]]
    depth: "int" = 0

    def find_addr_pair(
        current_addr_list: "List[QNodeAddr]", next_addr_list: "List[QNodeAddr]"
    ) -> "Optional[List[QNodeAddr, QNodeAddr]]":
        for addr1 in current_addr_list:
            for addr2 in next_addr_list:
                if addr1.network_part == addr2.network_part:
                    return [addr1, addr2]

    def get_network_by_depth(cur_depth: int) -> int:
        assert len(layers) > cur_depth
        assert len(layers[cur_depth]) > 0
        return layers[cur_depth][-1].network_part

    def get_network(lst: "List[QNodeAddr]") -> int:
        """get the last addr's network."""
        assert len(lst) > 0
        return lst[-1].network_part

    for i in range(0, len(paths) - 1):
        current_hop = find_addr_pair(
            paths[i], paths[i + 1]
        )  # the first element is an external side address
        print(current_hop)
        if current_hop:
            # found subnetwork: ingress gateway or egress gateway or same layer addr
            cur_network = get_network_by_depth(depth)
            if get_network(current_hop) == cur_network:  # found same network layer
                layers[depth] += current_hop
            else:  # different network layer pair
                if depth > 0 and get_network(current_hop) == get_network_by_depth(
                    depth - 1
                ):
                    depth += -1
                    layers[depth] += current_hop
                else:
                    depth += 1
                    if len(layers) > depth:
                        layers[depth] += current_hop
                    else:
                        layers.append(current_hop)
        else:  # connecting different network
            current_hop = [
                paths[i][0],  # current node's external address
                paths[i + 1][0],  # next node's external address
            ]
            if len(layers) > depth:  # current layer exists
                if depth > 0:
                    depth += -1
                layers[depth] += current_hop
            else:  # this is the first node in this layer
                layers.append(current_hop)

    current_addr = QNodeAddr(-1, -1)
    neighbor_addr = QNodeAddr(-1, -1)
    lower_dest_addr = QNodeAddr(-1, -1)
    # find current_addr
    for addr in paths[0]:
        if len(layers) > 1 and addr == layers[1][0]:
            current_addr = addr
    if current_addr.network_part != -1 and len(layers) > 1:
        # find neighbor
        for addr in paths[1]:
            for addr2 in layers[1]:
                if addr2 == addr:
                    neighbor_addr = addr
        # find lower dest addr
        # the lower layer's first network
        cur_network = layers[1][0].network_part
        for addr in layers[1]:
            # if the lower layer's network part changed,
            # it goes the different network. so break it
            # to use the first layer's first subnet dest
            if cur_network != addr.network_part:
                break
            lower_dest_addr = addr

    # debug each layer addresses
    for addr_list in paths:
        print(f"-------{addr_list}-----")
        for addr in addr_list:
            found = False
            for layer, nodes_in_layer in enumerate(layers):
                if addr in nodes_in_layer:
                    print(f"addr: {addr} at {layer}")
                    found = True
            if not found:
                print(f"{addr} not found")

    for i, layer in enumerate(layers):
        print(f"layer{i}:", layer)
    return (lower_dest_addr.network_part, current_addr, neighbor_addr, lower_dest_addr)
