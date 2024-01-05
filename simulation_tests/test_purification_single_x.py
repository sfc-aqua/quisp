from .utils import Worker
import pytest


@pytest.mark.asyncio
async def test_Single_X_Purification_MIM_No_Error():
    worker = Worker()
    await worker.run(
        config_name="Single_X_Purification_MIM_No_Error",
        ned_file_path="simulations/simulation_test.ini",
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
async def test_Single_X_Purification_MM_No_Error():
    worker = Worker()
    await worker.run(
        config_name="Single_X_Purification_MM_No_Error",
        ned_file_path="simulations/simulation_test.ini",
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
async def test_Single_X_Purification_MSM_No_Error():
    worker = Worker()
    await worker.run(
        config_name="Single_X_Purification_MSM_No_Error",
        ned_file_path="simulations/simulation_test.ini",
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
async def test_Single_X_Purification_MIM_Werner_State():
    worker = Worker()
    await worker.run(
        config_name="Single_X_Purification_MIM_Werner_State",
        ned_file_path="simulations/simulation_test.ini",
    )
    print(worker.output)
    worker.print_results()
    assert worker.results["EndNode1<-->EndNode2"]["data"] == {
        "Fidelity": 0.739466,
        "Xerror": 0.052239,
        "Zerror": 0.20503,
        "Yerror": 0.00326519,
    }
    assert worker.results["EndNode2<-->EndNode1"]["data"] == {
        "Fidelity": 0.739466,
        "Xerror": 0.052239,
        "Zerror": 0.20503,
        "Yerror": 0.00326519,
    }


@pytest.mark.asyncio
async def test_Single_X_Purification_MM_Werner_State():
    worker = Worker()
    await worker.run(
        config_name="Single_X_Purification_MM_Werner_State",
        ned_file_path="simulations/simulation_test.ini",
    )
    print(worker.output)
    worker.print_results()
    assert worker.results["EndNode1<-->EndNode2"]["data"] == {
        "Fidelity": 0.742061,
        "Xerror": 0.027587,
        "Zerror": 0.192103,
        "Yerror": 0.0382493,
    }
    assert worker.results["EndNode2<-->EndNode1"]["data"] == {
        "Fidelity": 0.742061,
        "Xerror": 0.027587,
        "Zerror": 0.192103,
        "Yerror": 0.0382493,
    }

@pytest.mark.asyncio
async def test_Single_X_Purification_MSM_Werner_State():
    worker = Worker()
    await worker.run(
        config_name="Single_X_Purification_MSM_Werner_State",
        ned_file_path="simulations/simulation_test.ini",
    )
    print(worker.output)
    worker.print_results()
    assert worker.results["EndNode1<-->EndNode2"]["data"] == {
        "Fidelity": 0.745086,
        "Xerror": 0.011647,
        "Zerror": 0.186204,
        "Yerror": 0.0570624,
    }
    assert worker.results["EndNode2<-->EndNode1"]["data"] == {
        "Fidelity": 0.745086,
        "Xerror": 0.011647,
        "Zerror": 0.186204,
        "Yerror": 0.0570624,
    }
