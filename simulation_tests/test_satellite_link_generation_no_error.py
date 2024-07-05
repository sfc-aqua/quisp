from .utils import Worker
import pytest

@pytest.mark.asyncio
async def test_NoErrorSatelliteMM_City1():
    worker = Worker()
    await worker.run(
        config_name="NoErrorSatelliteMM_City1", ned_file_path="simulations/satellite_simulation_test.ini"
    )
    print(worker.output)
    worker.print_results()
    assert worker.results["EndNode1<-->EndNode2"]["data"] == {
        "Fidelity": 1.0,
        "Xerror": 0.0,
        "Zerror": 0.0,
        "Yerror": 0.0,
    }
    assert worker.results["EndNode2<-->EndNode1"]["data"] == {
        "Fidelity": 1.0,
        "Xerror": 0.0,
        "Zerror": 0.0,
        "Yerror": 0.0,
    }

@pytest.mark.asyncio
async def test_NoErrorSatelliteMM_City2():
    worker = Worker()
    await worker.run(
        config_name="NoErrorSatelliteMM_City2", ned_file_path="simulations/satellite_simulation_test.ini"
    )
    print(worker.output)
    worker.print_results()
    assert worker.results["EndNode1<-->EndNode2"]["data"] == {
        "Fidelity": 1.0,
        "Xerror": 0.0,
        "Zerror": 0.0,
        "Yerror": 0.0,
    }
    assert worker.results["EndNode2<-->EndNode1"]["data"] == {
        "Fidelity": 1.0,
        "Xerror": 0.0,
        "Zerror": 0.0,
        "Yerror": 0.0,
    }
