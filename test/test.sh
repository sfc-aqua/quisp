#!/bin/sh
# run the result_test.ini in the network. This is not an unit test.
echo "test start"
cd /root/quisp/quisp/networks
make -C ../ cleanall
make -C ../ BATCH=true QCONFIG=/root/quisp/quisp/network/* -j $(nproc) all
# These are creating all simulations HACK
# if we set quisp as ./quisp/..., may be error because of existance of the same name binary 
if [ -e /root/quisp/test/testresults.txt ];then
    rm  /root/quisp/test/testresults.txt
else
    touch /root/quisp/test/testresults.txt
fi
# Actual test part
# ==== This should be iterative
echo "init" >> /root/quisp/test/testresults.txt 
/root/quisp/quisp/out/clang-release/quisp  -u Cmdenv --cmdenv-express-mode=true -c Test_Realistic_Layer2_Simple_NoError  -f /root/quisp/quisp/networks/test.ini | grep "fidelity" | tr ";" "\n">> /root/quisp/test/testresults.txt
echo " ">> /root/quisp/test/testresults.txt 
/root/quisp/quisp/out/clang-release/quisp  -u Cmdenv --cmdenv-express-mode=true -c Test_Realistic_Layer2_Simple  -f /root/quisp/quisp/networks/test.ini | grep "fidelity" | tr ";" "\n">> /root/quisp/test/testresults.txt
echo "next round">>/root/quisp/test/testresults.txt
# ==== 
# On docker
g++ -std=c++11 -o /root/quisp/test/quisp_test /root/quisp/test/quisp_test.cpp -I/rooot/omnetpp/include -I/usr/include/eigen3 -I/root/clibrary/googletest/googletest/include -L/root/clibrary/googletest/build/lib/ -pthread -lgtest_main -lgtest
# remove used results
/root/quisp/test/quisp_test
echo "test done"
