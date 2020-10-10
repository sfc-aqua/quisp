#!/bin/bash
# run the result_test.ini in the network. This is not an unit test.
echo "test start"
cd /root/quisp/quisp/networks
make -C ../ cleanall
make -C ../ BATCH=true QCONFIG=/root/quisp/quisp/network/* -j $(nproc) all
# These are creating all simulations HACK
# if we set quisp as ./quisp/..., may be error because of existance of the same name binary 
if [ -e /root/quisp/test/testresults.txt ];then
    rm  /root/quisp/test/testresults.txt
fi
# Actual test part
# Experiments=("Test0" "Test1" "Test2")
NUM_TEST=35
# ===
# This "init" and "next" is identifier of the experiments
# for((i=0; i<${#Experiments[@]}; i++)); do
for((i=0; i<$NUM_TEST; i++)); do
echo "start test $i"
echo "init$i" >> /root/quisp/test/testresults.txt 
/root/quisp/quisp/out/clang-release/quisp  -u Cmdenv --cmdenv-express-mode=true -c "Test$i" -f /root/quisp/quisp/networks/test.ini | grep "fidelity" | tr ";" "\n" | tr "{" "\n"| tr "}" "\n"|sed s/"<-->"/"\n"/g>> /root/quisp/test/testresults.txt
echo "next">>/root/quisp/test/testresults.txt
echo "finish test $i"
done
# ==== 
# On docker
# g++ -std=c++11 -o /root/quisp/test/quisp_test /root/quisp/test/quisp_test.cpp -I/rooot/omnetpp/include -I/usr/include/eigen3 -I/root/clibrary/googletest/googletest/include -L/root/clibrary/googletest/build/lib/ -pthread -lgtest_main -lgtest
# This is just testing result! not each function!

