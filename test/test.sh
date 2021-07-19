#!/bin/bash
set -eu
# run the result_test.ini in the network. This is not an unit test.
echo "test start"
cd /root/quisp
make makefile-exe
cd /root/quisp/quisp/
make cleanall
make BATCH=true QCONFIG=/root/quisp/quisp/networks/* -j $(nproc) all
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
