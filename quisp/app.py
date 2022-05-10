import opp
import application

def init_app_module(app):
    num_resources = app.par("distant_measure_count").int()
    pattern = app.par("TrafficPattern").int()
    initiator_addr = app.par("LoneInitiatorAddress").int()

    if pattern == 1 and app.my_address == initiator_addr:
        dest_addr = app.get_one_random_endnode_addr()
        pk = app.create_conn_setup_req(dest_addr,num_resources)
        app.schedule_at(opp.sim_time(), pk)
    if pattern == 2:
        dest_addr = app.get_one_random_endnode_addr()
        pk = app.create_conn_setup_req(dest_addr,num_resources)
        app.schedule_at(opp.sim_time() + 0.00001 * app.my_address, pk)
