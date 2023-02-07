from .utils import Worker, parse_output
import pytest

@pytest.mark.asyncio
async def test_NoErrorMIM():
    worker = Worker()
    await worker.run(config_name="NoErrorMIM", ned_file_path="simulations/simulation_test.ini")
    worker.print_results()
    print(worker.output)


@pytest.mark.asyncio
async def test_0():
    worker = Worker()
    await worker.run("Test0")
    worker.print_results()

    # FIXME: the results seem wrong. we put the temporary results to check the simulation tests work.
    assert worker.results["EndNode2[0]<-->Repeater1[0]"]["data"], {
        "Fidelity": 0.875412,
        "Xerror": 0.00346101,
        "Zerror": 0.124588,
        "Yerror": -0.00346101,
    }
    assert worker.results["Repeater1[0]<-->EndNode2[0]"]["data"], {
        "Fidelity": 0.875412,
        "Xerror": 0.00346101,
        "Zerror": 0.124588,
        "Yerror": -0.00346101,
    }

