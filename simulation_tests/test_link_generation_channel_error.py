from .utils import Worker
import pytest


@pytest.mark.asyncio
async def test_ChannelXErrorSimpleMIM():
    worker = Worker()
    await worker.run(
        config_name="ChannelXErrorSimpleMIM",
        ned_file_path="simulations/simulation_test.ini",
    )
    print(worker.output)
    worker.print_results()
    assert worker.results["EndNode1<-->EndNode2"]["data"] == {
        "Fidelity": 0.815958,
        "Xerror": 0.184042,
        "Zerror": -0.0205033,
        "Yerror": 0.0205033,
    }
    assert worker.results["EndNode2<-->EndNode1"]["data"] == {
        "Fidelity": 0.815958,
        "Xerror": 0.184042,
        "Zerror": -0.0205033,
        "Yerror": 0.0205033,
    }


@pytest.mark.asyncio
async def test_ChannelXErrorSimpleMM():
    worker = Worker()
    await worker.run(
        config_name="ChannelXErrorSimpleMM",
        ned_file_path="simulations/simulation_test.ini",
    )
    print(worker.output)
    worker.print_results()
    assert worker.results["EndNode1<-->EndNode2"]["data"] == {
        "Fidelity": 0.905137,
        "Xerror": 0.0948629,
        "Zerror": -0.00540325,
        "Yerror": 0.00540325,
    }
    assert worker.results["EndNode2<-->EndNode1"]["data"] == {
        "Fidelity": 0.905137,
        "Xerror": 0.0948629,
        "Zerror": -0.00540325,
        "Yerror": 0.00540325,
    }
