from .utils import Worker
import pytest

@pytest.mark.asyncio
async def test_Entanglement_Swapping_Satellite_MM_3_Nodes():
    worker = Worker()
    await worker.run(
        config_name="Entanglement_Swapping_Satellite_MM_3_Nodes",
        ned_file_path="simulations/satellite_simulation_test.ini",
    )
    print(worker.output)
    worker.print_results()
    assert worker.results["EndNode1<-->Repeater"]["data"] == {
        "Fidelity": 1.0,
        "Xerror": 0.0,
        "Zerror": 0.0,
        "Yerror": 0.0,
    }
    assert worker.results["EndNode2<-->Repeater"]["data"] == {
        "Fidelity": 1.0,
        "Xerror": 0.0,
        "Zerror": 0.0,
        "Yerror": 0.0,
    }
    assert worker.results["Repeater<-->EndNode1"]["data"] == {
        "Fidelity": 1.0,
        "Xerror": 0.0,
        "Zerror": 0.0,
        "Yerror": 0.0,
    }
    assert worker.results["Repeater<-->EndNode2"]["data"] == {
        "Fidelity": 1.0,
        "Xerror": 0.0,
        "Zerror": 0.0,
        "Yerror": 0.0,
    }
