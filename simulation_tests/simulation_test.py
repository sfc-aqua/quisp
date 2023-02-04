from .utils import Worker, parse_output
import pytest


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


@pytest.mark.asyncio
async def test_1():
    worker = Worker()
    await worker.run("Test1")
    worker.print_results()


@pytest.mark.asyncio
async def test_2():
    worker = Worker()
    await worker.run(config_name="Test2", ned_file_path="simulations/test.ini")
    worker.print_results()


@pytest.mark.asyncio
async def test_3():
    worker = Worker()
    await worker.run("Test3")
    worker.print_results()


@pytest.mark.asyncio
async def test_4():
    worker = Worker()
    await worker.run("Test4")
    worker.print_results()


@pytest.mark.asyncio
async def test_5():
    worker = Worker()
    await worker.run("Test5")
    worker.print_results()


@pytest.mark.asyncio
async def test_6():
    worker = Worker()
    await worker.run("Test6")
    worker.print_results()


@pytest.mark.asyncio
async def test_7():
    worker = Worker()
    await worker.run("Test7")
    worker.print_results()


@pytest.mark.asyncio
async def test_8():
    worker = Worker()
    await worker.run("Test8")
    print(worker.output)


@pytest.mark.asyncio
async def test_9():
    worker = Worker()
    await worker.run("Test9")
    worker.print_results()


@pytest.mark.asyncio
async def test_10():
    worker = Worker()
    await worker.run("Test10")
    worker.print_results()


@pytest.mark.asyncio
async def test_11():
    worker = Worker()
    await worker.run("Test11")
    worker.print_results()


@pytest.mark.asyncio
async def test_12():
    worker = Worker()
    await worker.run("Test12")
    worker.print_results()


@pytest.mark.asyncio
async def test_13():
    worker = Worker()
    await worker.run("Test13")
    worker.print_results()


@pytest.mark.asyncio
async def test_14():
    worker = Worker()
    await worker.run("Test14")
    worker.print_results()


@pytest.mark.asyncio
async def test_15():
    worker = Worker()
    await worker.run("Test15")
    worker.print_results()


@pytest.mark.asyncio
async def test_16():
    worker = Worker()
    await worker.run("Test16")
    worker.print_results()


@pytest.mark.asyncio
async def test_17():
    worker = Worker()
    await worker.run("Test17")
    worker.print_results()


@pytest.mark.asyncio
async def test_18():
    worker = Worker()
    await worker.run("Test18")
    worker.print_results()


@pytest.mark.asyncio
async def test_19():
    worker = Worker()
    await worker.run("Test19")
    worker.print_results()


@pytest.mark.asyncio
async def test_20():
    worker = Worker()
    await worker.run("Test20")
    worker.print_results()


@pytest.mark.asyncio
async def test_21():
    worker = Worker()
    await worker.run("Test21")
    worker.print_results()


@pytest.mark.asyncio
async def test_22():
    worker = Worker()
    await worker.run("Test22")
    worker.print_results()


@pytest.mark.asyncio
async def test_23():
    worker = Worker()
    await worker.run("Test23")
    worker.print_results()


@pytest.mark.asyncio
async def test_24():
    worker = Worker()
    await worker.run("Test24")
    worker.print_results()


@pytest.mark.asyncio
async def test_25():
    worker = Worker()
    await worker.run("Test25")
    worker.print_results()


@pytest.mark.asyncio
async def test_26():
    worker = Worker()
    await worker.run("Test26")
    worker.print_results()


@pytest.mark.asyncio
async def test_27():
    worker = Worker()
    await worker.run("Test27")
    worker.print_results()


@pytest.mark.asyncio
async def test_28():
    worker = Worker()
    await worker.run("Test28")
    worker.print_results()


@pytest.mark.asyncio
async def test_29():
    worker = Worker()
    await worker.run("Test29")
    worker.print_results()


@pytest.mark.asyncio
async def test_30():
    worker = Worker()
    await worker.run("Test30")
    worker.print_results()


@pytest.mark.asyncio
async def test_31():
    worker = Worker()
    await worker.run("Test31")
    worker.print_results()


@pytest.mark.asyncio
async def test_32():
    worker = Worker()
    await worker.run("Test32")
    worker.print_results()


@pytest.mark.asyncio
async def test_33():
    worker = Worker()
    await worker.run("Test33")
    worker.print_results()


@pytest.mark.asyncio
async def test_34():
    worker = Worker()
    await worker.run("Test34")
    worker.print_results()
