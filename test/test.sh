#!/bin/bash
set -eu

# run the result_test.ini in the network. This is not an unit test.
echo "test start"
QUISP_ROOT=`pwd`/..
NEDPATH=$QUISP_ROOT/quisp/networks:$QUISP_ROOT/quisp/modules:$QUISP_ROOT/quisp/channels
cd $QUISP_ROOT
make makefile-exe
cd $QUISP_ROOT/quisp/
make cleanall
make MODE=release

# if we set quisp as ./quisp/..., may be error because of existance of the same name binary
if [ -e $QUISP_ROOT/test/testresults.txt ];then
    rm  $QUISP_ROOT/test/testresults.txt
fi
# Actual test part
# Experiments=("Test0" "Test1" "Test2")
NUM_TEST=35
# ===
# This "init" and "next" is identifier of the experiments
# for((i=0; i<${#Experiments[@]}; i++)); do
for((i=0; i<$NUM_TEST; i++)); do
echo "start test $i"
echo "init$i" >> $QUISP_ROOT/test/testresults.txt
$QUISP_ROOT/quisp/out/clang-release/quisp -u Cmdenv --cmdenv-express-mode=true -c "Test$i" -f $QUISP_ROOT/quisp/simulations/test.ini -n $NEDPATH >> $QUISP_ROOT/test/Test$i.log
cat $QUISP_ROOT/test/Test$i.log | grep "fidelity" | tr ";" "\n" | tr "{" "\n"| tr "}" "\n"|sed s/"<-->"/"\n"/g>> $QUISP_ROOT/test/testresults.txt
echo "next">>$QUISP_ROOT/test/testresults.txt
echo "finish test $i"
done
