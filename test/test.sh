#!/bin/sh
# run the result_test.ini in the network. This is not an unit test.
pwd
cd /root/quisp/quisp/networks
make -C ../ cleanall
make -C ../ BATCH=true QCONFIG=/root/quisp/quisp/network/* all
# These are creating all simulations HACK
# if we set quisp as ./quisp/..., may be error because of existance of the same name binary 
/root/quisp/quisp/out/clang-release/quisp  -u Cmdenv -c Test_Realistic_Layer2_Simple  -f /root/quisp/quisp/networks/test.ini >> testresults.txt
echo "here at $(pwd)"
# On docker
g++ -std=c++11 -o quisp_test /root/quisp/test/quisp_test.cpp -I/rooot/omnetpp/include -I/usr/include/eigen3 -I/root/clibrary/googletest/googletest/include -L/root/clibrary/googletest/build/lib/ -pthread -lgtest_main -lgtest
# remove used results
./quisp_test
echo "test done"
