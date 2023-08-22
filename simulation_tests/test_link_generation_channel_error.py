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
        "Fidelity": 0.896712,
        "Xerror": 0.103288,
        "Zerror": -0.0103481,
        "Yerror": 0.0103481,
    }
    assert worker.results["EndNode2<-->EndNode1"]["data"] == {
        "Fidelity": 0.896712,
        "Xerror": 0.103288,
        "Zerror": -0.0103481,
        "Yerror": 0.0103481,
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

@pytest.mark.asyncio
async def test_ChannelXErrorSimpleMSM():
    worker = Worker()
    await worker.run(
        config_name="ChannelXErrorSimpleMSM",
        ned_file_path="simulations/simulation_test.ini",
    )
    print(worker.output)
    worker.print_results()
    assert worker.results["EndNode1<-->EndNode2"]["data"] == {
        "Fidelity": 0.900457,
        "Xerror": 0.0995426,
        "Zerror": -0.00306765,
        "Yerror": 0.00306765,
    }
    assert worker.results["EndNode2<-->EndNode1"]["data"] == {
        "Fidelity": 0.900457,
        "Xerror": 0.0995426,
        "Zerror": -0.00306765,
        "Yerror": 0.00306765,
    }

@pytest.mark.asyncio
async def test_MIM_Werner_State_Channel():
    worker = Worker()
    await worker.run(
        config_name="Channel_Error_Werner_State_MIM",
        ned_file_path="simulations/simulation_test.ini",
    )
    print(worker.output)
    worker.print_results()
    assert worker.results["EndNode1<-->EndNode2"]["data"] == {
        "Fidelity": 0.694766,
        "Xerror": 0.103959,
        "Zerror": 0.100688,
        "Yerror": 0.100587,
    }
    assert worker.results["EndNode2<-->EndNode1"]["data"] == {
        "Fidelity": 0.694766,
        "Xerror": 0.103959,
        "Zerror": 0.100688,
        "Yerror": 0.100587,
    }


@pytest.mark.asyncio
async def test_MM_Werner_State_Channel():
    worker = Worker()
    await worker.run(
        config_name="Channel_Error_Werner_State_MM",
        ned_file_path="simulations/simulation_test.ini",
    )
    print(worker.output)
    worker.print_results()
    assert worker.results["EndNode1<-->EndNode2"]["data"] == {
        "Fidelity": 0.700108,
        "Xerror": 0.104376,
        "Zerror": 0.0904865,
        "Yerror": 0.105029,
    }
    assert worker.results["EndNode2<-->EndNode1"]["data"] == {
        "Fidelity": 0.700108,
        "Xerror": 0.104376,
        "Zerror": 0.0904865,
        "Yerror": 0.105029,
    }

@pytest.mark.asyncio
async def test_MSM_Werner_State_Channel():
    worker = Worker()
    await worker.run(
        config_name="Channel_Error_Werner_State_MSM",
        ned_file_path="simulations/simulation_test.ini",
    )
    print(worker.output)
    worker.print_results()
    assert worker.results["EndNode1<-->EndNode2"]["data"] == {
        "Fidelity": 0.701657,
        "Xerror": 0.0870884,
        "Zerror": 0.101223,
        "Yerror": 0.110031,
    }
    assert worker.results["EndNode2<-->EndNode1"]["data"] == {
        "Fidelity": 0.701657,
        "Xerror": 0.0870884,
        "Zerror": 0.101223,
        "Yerror": 0.110031,
    }
