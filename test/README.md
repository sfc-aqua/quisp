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

## Test list
Test list in test.ini file
| TEST CASE| CONTENS | REMARKS |
| -------- | -------- | -------- |
| Test0     | No error case     |      |
| Test1     | Channel X error test     |      |
| Test2     | Channel Z error test     |with hom darkcount|
| Test3     | Channel Y error test     |      |
| Test4     | Memory X error test     |purification 3003|
| Test5     | Memory Y error test     |with hom darkcount|
| Test6     | Memory Z error test     |with hom darkcount|
| Test7     | Memory energy excite error test |with hom darkcount purification 1031|
| Test8     | Memory energy relaxation error test      |      |
| Test9     | Memory completely mixed test      |      |
| Test10     | internal_hom_loss test     |purification 2002|
| Test11     | internal_hom_error test     |WARNING: This feature has not been implemented yet. If you have error with this test, you might have to change test. purification 1221|
| Test12     | hom_loss_error test     | not internal  purification 1031|
| Test13     | hom error test     |  not internal  with hom darkcount|
| Test14     | Measurement error X test     |purification 1221|
| Test15     | Measurement error Y test|purification 3003|
| Test16     | Measurement error Z test|purification 3003|
| Test17     | H gate X error test|purification 1001|
| Test18     | H gate Y error test|purification 1001|
| Test19     | H gate Z error test|purification 1011|
| Test20     | X gate X error test|purification 2002|
| Test21     | X gate Y error test|purification 2002|
| Test22     | X gate Z error test|purification 2002|
| Test23     | Z gate X error test|purification 3003|
| Test24     | Z gate Y error test|purification 3003|
| Test25     | Z gate Z error test|purification 3003|
| Test26     | CNOT gate IZ error test|purification 1221|
| Test27     | CNOT gate ZI error test|purification 1221|
| Test28     | CNOT gate ZZ error test|purification 1221|
| Test29     | CNOT gate IX error test|purification 1221|
| Test30     | CNOT gate XI error test|purification 1221|
| Test31     | CNOT gate XX error test|purification 1221|
| Test32     | CNOT gate IY error test|purification 1221|
| Test33     | CNOT gate YI error test|purification 1221|
| Test34     | CNOT gate YY error test|purification 1221|

## Notes

If you look in detail at the Travis CI test output, you may see messages like:

```$ sh docker_run_lint.sh
...
Error while processing /root/quisp/quisp/rules/example.cc.
4735/root/quisp/quisp/modules/Application.cc:9:10: error: 'classical_messages_m.h' file not found [clang-diagnostic-error]
4736#include <classical_messages_m.h>
4737         ^
...
/root/quisp/quisp/modules/stationaryQubit.h:10:10: error: 'PhotonicQubit_m.h' file not found [clang-diagnostic-error]
4789Suppressed 14962 warnings (14962 in non-user code).
4790Use -header-filter=.* to display errors from all non-system headers. Use -system-headers to display errors from system headers as well.
4791The command "sh docker_run_lint.sh" exited with 0.
```

These errors occur only during the lint phase, because the appropriate
.msg file has not been compiled.  These errors can be safely ignored
(except that they may cause lint to miss some errors in the code).
When the system is actually compiled for the functional tests in the
list above, the .msg files are compiled and incorporated properly.
