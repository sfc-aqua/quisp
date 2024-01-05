from .utils import Worker
import pytest


@pytest.mark.asyncio
async def test_NoErrorMIM():
    worker = Worker()
    await worker.run(
        config_name="NoErrorMIM", ned_file_path="simulations/simulation_test.ini"
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
async def test_NoErrorMM():
    worker = Worker()
    await worker.run(
        config_name="NoErrorMM", ned_file_path="simulations/simulation_test.ini"
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
async def test_NoErrorMSM():
    worker = Worker()
    await worker.run(
        config_name="NoErrorMSM", ned_file_path="simulations/simulation_test.ini"
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
