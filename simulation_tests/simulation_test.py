from .utils import Worker, parse_output
import pytest


def test_util():
    s = "Repeater1[0]<-->QuantumChannel{cost=0.00795483;distance=2.5km;fidelity=0.647462;bellpair_per_sec=299.875;}<-->EndNode2[0]; Fidelity=0.647462; Xerror=-0.00802559; Zerror=0.352538; Yerror=0.00802559"
    print(parse_output(s))


@pytest.mark.asyncio
async def test_1():
    worker = Worker()
    await worker.run("Test1")


@pytest.mark.asyncio
async def test_2():
    worker = Worker()
    await worker.run("Test2")
    print(worker.results)
    for name in worker.results:
        print(name, worker.results[name]["data"])


@pytest.mark.asyncio
async def test_3():
    worker = Worker()
    await worker.run("Test3")
    print(worker.results)


@pytest.mark.asyncio
async def test_4():
    worker = Worker()
    await worker.run("Test4")
    print(worker.results)


@pytest.mark.asyncio
async def test_5():
    worker = Worker()
    await worker.run("Test5")
    print(worker.results)


@pytest.mark.asyncio
async def test_6():
    worker = Worker()
    await worker.run("Test6")
    print(worker.results)


@pytest.mark.asyncio
async def test_7():
    worker = Worker()
    await worker.run("Test7")
    print(worker.results)


@pytest.mark.asyncio
async def test_8():
    worker = Worker()
    await worker.run("Test8")
    print(worker.output)


@pytest.mark.asyncio
async def test_9():
    worker = Worker()
    await worker.run("Test9")
    print(worker.results)


@pytest.mark.asyncio
async def test_10():
    worker = Worker()
    await worker.run("Test10")
    print(worker.results)


@pytest.mark.asyncio
async def test_11():
    worker = Worker()
    await worker.run("Test11")
    print(worker.results)


@pytest.mark.asyncio
async def test_12():
    worker = Worker()
    await worker.run("Test12")
    print(worker.results)


@pytest.mark.asyncio
async def test_13():
    worker = Worker()
    await worker.run("Test13")
    print(worker.results)


@pytest.mark.asyncio
async def test_14():
    worker = Worker()
    await worker.run("Test14")
    print(worker.results)
