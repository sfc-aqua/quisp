plan = dict()

for num_nodes in [5,10, 15, 20, 25, 30, 35, 40, 45, 50]:
    for num_subnets in [0, 1,2,3,4,5]: #range(0, num_nodes // 3, 4):
        if num_subnets * 3 > num_nodes:
            continue
        network = generate_network(num_nodes=num_nodes, num_subnets=num_subnets)
        key = network.name
        plan[key] = {
            "network_name": key,
            "network": network,
            "num_nodes": num_nodes,
            "num_subnets": num_subnets,
            "error": None
        }

for k in plan:
    print(k)

print(len(plan), "networks")

# run simulations with generated plan dict. the dict contains each simulation setting.
async def run_all(plan: "Dict"):
    simulation_queue = [plan[key] for key in plan]




