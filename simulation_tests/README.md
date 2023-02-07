# Simulation Test Suite

These simulation tests run multiple simulation scenarios and check their results like fidelity to confirm our simulator behaves appropriately. Our simulation test suite is built on pytest with xdist and asyncio plugins to support running multiple simulations in parallel.

## Usage

```
$ cd simulation_tests

# install dependencies
$ pip install -r ../requirements.txt

# run all tests in single process
$ pytest

# run all tests in parallel
$ pytest -n auto

# run all tests with 4 cores
$ pytest -n 4

# run all tests in single process with stdout for debugging
$ pytest -s

# run "NoErrorMIM" test
$ pytest -s -k NoErrorMIM

```
