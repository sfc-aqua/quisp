from .utils import Worker
import pytest


@pytest.mark.asyncio
async def test_NoErrorMIM():
    worker = Worker()
    await worker.run(
        config_name="XChannelErrorSimpleMIM",
        ned_file_path="simulations/simulation_test.ini",
    )
    print(worker.output)
    worker.print_results()
    assert worker.results["EndNode1<-->EndNode2"]["data"] == {
        "Fidelity": 0.495157,
        "Xerror": 0.504843,
        "Zerror": -0.0154454,
        "Yerror": 0.0154454,
    }
    assert worker.results["EndNode2<-->EndNode1"]["data"] == {
        "Fidelity": 0.495157,
        "Xerror": 0.504843,
        "Zerror": -0.0154454,
        "Yerror": 0.0154454,
    }


@pytest.mark.asyncio
async def test_NoErrorMM():
    worker = Worker()
    await worker.run(
        config_name="XChannelErrorSimpleMM",
        ned_file_path="simulations/simulation_test.ini",
    )
    print(worker.output)
    worker.print_results()
    assert worker.results["EndNode1<-->EndNode2"]["data"] == {
        "Fidelity": 0.503945,
        "Xerror": 0.496055,
        "Zerror": 0.00766231,
        "Yerror": -0.00766231,
    }
    assert worker.results["EndNode2<-->EndNode1"]["data"] == {
        "Fidelity": 0.503945,
        "Xerror": 0.496055,
        "Zerror": 0.00766231,
        "Yerror": -0.00766231,
    }
