# Linear network perfs
BENCH_ROOT=$(cd $(dirname $0); pwd)
echo $BENCH_ROOT
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
mkdir output
echo "Starting benchmark"
echo linear10nodes>>./output/time_perf_10nodes.txt
../../quisp -c linear10_mm_pur_es -u Cmdenv -m -n ../..:../../channels:../../modules:. benchmark.ini | grep "** Event" -A 2 >> ./output/time_perf_10nodes.txt
# echo linear50nodes>>./output/time_perf_50nodes.txt
# ../../quisp -c linear50_mm_pur_es -u Cmdenv -m -n ../..:../../channels:../../modules:. benchmark.ini | grep "** Event" -A 2 >> ./output/time_perf_50nodes.txt
# echo linear100nodes>>./output/time_perf_100nodes.txt
# ../../quisp -c linear100_mm_pur_es -u Cmdenv -m -n ../..:../../channels:../../modules:. benchmark.ini | grep "** Event" -A 2 >> ./output/time_perf_100nodes.txt

# echo circle10nodes>>./output/time_perf_circle10nodes.txt
# ../../quisp -c circle10_pur_es -u Cmdenv -m -n ../..:../../channels:../../modules:. benchmark.ini | grep "** Event" -A 2 >> ./output/time_perf_circle10nodes.txt
# echo circle50nodes>>./output/time_perf_circle50nodes.txt
# ../../quisp -c circle50_pur_es -u Cmdenv -m -n ../..:../../channels:../../modules:. benchmark.ini | grep "** Event" -A 2 >> ./output/time_perf_circle50nodes.txt
# echo circle100nodes>>./output/time_perf_circle100nodes.txt
# ../../quisp -c circle100_pur_es -u Cmdenv -m -n ../..:../../channels:../../modules:. benchmark.ini | grep "** Event" -A 2 >> ./output/time_perf_circle100nodes.txt

python format_result.py ./output/time_perf_10nodes.txt
# python format_result.py ./output/time_perf_50nodes.txt
# python format_result.py ./output/time_perf_100nodes.txt

# python format_result.py ./output/time_perf_circle10nodes.txt
# python format_result.py ./output/time_perf_circle50nodes.txt
# python format_result.py ./output/time_perf_circle100nodes.txt

