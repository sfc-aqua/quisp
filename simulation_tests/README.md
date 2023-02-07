# Simulation Test Suite

These simulation tests run multiple simulation scenarios and check their results like fidelity to confirm our simulator behaves appropriately. Our simulation test suite is built on pytest with xdist and asyncio plugins to support running multiple simulations in parallel.

## Usage

```sh
$ cd simulation_tests

# install dependencies
$ pip install -r ../requirements.txt

# run all tests in single process
$ pytest

# run all tests in parallel
$ pytest -n auto

# run all tests with 4 cores
$ pytest -n 4

# run all tests in single process with stdout for debugging.
# you can use `print()` to check something to debug.
$ pytest -s

# run "NoErrorMIM" test
$ pytest -s -k NoErrorMIM

```

## Adding new test cases

test files should start with `test_` to be discovered by pytest. 

```python
from .utils import Worker
import pytest


# this function is async because it uses "await" to wait the simulation run
@pytest.mark.asyncio
async def test_NoErrorMIM(): # the func name must start with "test_"
    # worker manages simulator and the simulation result
    worker = Worker()
    await worker.run(
        # config name in the specified ini file
        config_name="NoErrorMIM", 
        # find relative path from where the quisp binary exists
        ned_file_path="simulations/simulation_test.ini" 
    )
    # shows all the simulator output if we run pytest with -s option
    print(worker.output)
    worker.print_results()

    # confirm whether the simulation result matches or not
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
```