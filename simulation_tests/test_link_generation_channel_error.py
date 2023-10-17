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
        "Fidelity": 0.906557,
        "Xerror": 0.0934427,
        "Zerror": -0.00237126,
        "Yerror": 0.00237126,
    }
    assert worker.results["EndNode2<-->EndNode1"]["data"] == {
        "Fidelity": 0.906557,
        "Xerror": 0.0934427,
        "Zerror": -0.00237126,
        "Yerror": 0.00237126,
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
        "Fidelity": 0.898293,
        "Xerror": 0.101707,
        "Zerror": 0.00698899,
        "Yerror": -0.00698899,
    }
    assert worker.results["EndNode2<-->EndNode1"]["data"] == {
        "Fidelity": 0.898293,
        "Xerror": 0.101707,
        "Zerror": 0.00698899,
        "Yerror": -0.00698899,
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
        "Fidelity": 0.721372,
        "Xerror": 0.083573,
        "Zerror": 0.0860698,
        "Yerror": 0.108985,
    }
    assert worker.results["EndNode2<-->EndNode1"]["data"] == {
        "Fidelity": 0.721372,
        "Xerror": 0.083573,
        "Zerror": 0.0860698,
        "Yerror": 0.108985,
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
        "Fidelity": 0.689943,
        "Xerror": 0.106828,
        "Zerror": 0.103317,
        "Yerror": 0.0999117,
    }
    assert worker.results["EndNode2<-->EndNode1"]["data"] == {
        "Fidelity": 0.689943,
        "Xerror": 0.106828,
        "Zerror": 0.103317,
        "Yerror": 0.0999117,
    }
