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
async def test_Single_X_Purification_MIM_Werner_State():
    worker = Worker()
    await worker.run(
        config_name="Single_X_Purification_MIM_Werner_State",
        ned_file_path="simulations/simulation_test.ini",
    )
    print(worker.output)
    worker.print_results()
    assert worker.results["EndNode1<-->EndNode2"]["data"] == {
        "Fidelity": 0.735104,
        "Xerror": 0.0311294,
        "Zerror": 0.197981,
        "Yerror": 0.0357851,
    }
    assert worker.results["EndNode2<-->EndNode1"]["data"] == {
        "Fidelity": 0.735104,
        "Xerror": 0.0311294,
        "Zerror": 0.197981,
        "Yerror": 0.0357851,
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
        "Fidelity": 0.747207,
        "Xerror": 0.0251512,
        "Zerror": 0.19216,
        "Yerror": 0.0354823,
    }
    assert worker.results["EndNode2<-->EndNode1"]["data"] == {
        "Fidelity": 0.747207,
        "Xerror": 0.0251512,
        "Zerror": 0.19216,
        "Yerror": 0.0354823,
    }
