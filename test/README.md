# Tests

## Policy of test
- In the quantum world, we can't avoid probabilistic phenomena. When we run simulations, we fix the seed value. Thus, we have to make a new simulation with adjustable seed.
- When we add new features, we should have at least ten tests. This number can be changed according to what you want and the scale of the new feature.

## Test Structure

Currently, we need *docker* to run the tests.

- **quisp/test_docker_run.sh** ... this shell script run the docker. (Before running you have to build it with quisp/docker_build.sh)
- **quisp/test/test.sh** ... this "bash" script is running all tests in test.ini, and store results to quisp/test/testresults.txt
- **quisp/test/test_result.py** ... this python script checks if the result is same as what we expected. Simulation results are loaded from quisp/test/testresults.txt.
- **quisp/test/testresults.txt** ... This text file doesn't exist at first, but when you run test.sh, this file is automatically created.
- **quisp/quisp/networks/test.ini** ... this file includes all test cases.
- **quisp/.travis.yml** ... this .yml file is for Travis CI. Travis executes all tests automatically when you push your changes.

## How to run?

If you have docker and python, you can run test,

```shell=sh
(at quisp/)
$ sh docker_build.sh
$ sh test_docker_run.sh
> this takes about 10, 20 mins or more...
$ cd test
$ python -m unittest discover
```

Python 3.6 is verified.
We intend to fix to be able to run them without docker.

If you don't like to install these tools, just commit and you can check it when you create pull requests.
