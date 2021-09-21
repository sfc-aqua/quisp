#!/bin/bash

#Linear network perfs

BENCH_ROOT=$(cd $(dirname $0); pwd)
NETWORK_ROOT=$(cd $(dirname $BENCH_ROOT); pwd)
EXEC_ROOT=$(cd $(dirname $NETWORK_ROOT); pwd)
QUISP_ROOT=$(cd $(dirname $EXEC_ROOT); pwd)
NEDPATH=$EXEC_ROOT/networks:$EXEC_ROOT/modules:$EXEC_ROOT/channels
cd $QUISP_ROOT
make exe
cd $EXEC_ROOT
make cleanall
make BATCH=true QCONFIG=$EXEC_ROOT/networks/* -j $(nproc) all
cd $BENCH_ROOT
mkdir dm_files
mkdir output_200Mes
echo "Start benchmark"
# for nsize in 50
# do
#     echo "linear $nsize nodes"
#     for r in 1
#     do
#     echo linear${nsize}nodes >> "./output_200Mes/time_perf_linear${nsize}nodes_${r}rounds_200qubits.txt"
#     time ../../quisp -c linear${nsize}_mm_pur_es -u Cmdenv -m -n ../..:../../channels:../../modules:. benchmark.ini| grep -e "** Event" -A 2 >> "./output_200Mes/time_perf_linear${nsize}nodes_${r}rounds_200qubits.txt"
    
#     mv "\"Linear${nsize}_MM_B\"_dm" "./dm_files/\"Linear${nsize}_MM\"_dm_${r}" 
#     mv "\"Linear${nsize}_MM_B\"" "./dm_files\"Linear${nsize}_MM\"_${r}"

#     echo "it took $runtime to finish round ${r}"
#     echo "Round ${r} finished. Proceeding to next simulation round"

# 	echo "Format result"
# 	python format_result.py ./output_200Mes/time_perf_linear${nsize}nodes_${r}rounds_200qubits.txt
#     done
# done

echo "Finished all benchmarks"
# ../../quisp -c linear10_mm_pur_es -u Cmdenv -m -n ../..:../../channels:../../modules:. benchmark.ini