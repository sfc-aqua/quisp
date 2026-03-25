#!/bin/bash

pids=()

# # echo "Running to purification sims"
# # ./quisp -n "./networks:./channels:./modules:./simulations" \
# #     -i ./images ./simulations/cross_validation_config_generated.ini -u Cmdenv \
# #     -c "purification_validation_cnot_0_meas_0_without_decoherence" --cmdenv-status-frequency=10s > "cross-validation/purification-fidelity-noerror" &
# # pids+=($!)
# # echo "waiting for base fidelity experiment"
# # for pid in ${pids[*]};
# # do
# #     echo "waiting on pid = $pid"
# #     wait $pid
# # done
# # pids=()

# # for i in 18000 55000;
# # do
# #     echo "Running purification sims with decoherence with ${i} micro seconds"
# #     ./quisp -n "./networks:./channels:./modules:./simulations" \
# #         -i ./images ./simulations/cross_validation_config_generated.ini -u Cmdenv \
# #         -c "purification_validation_cnot_0_meas_0_with_decoherence_${i}_ms" --cmdenv-status-frequency=10s > "cross-validation/purification-fidelity-no-error-decoherence-${i}-ms" &
# #     pids+=($!)
# # done
# # # wait for all pids
# # echo "waiting for first experiments"
# # for pid in ${pids[*]};
# # do
# #     echo "waiting on pid = $pid"
# #     wait $pid
# # done
# # pids=()

# # for i in $(seq 60 2 100);
# # do
# #     echo "Running purification sims without decoherence with intial fidelity = ${i}"
# #     ./quisp -n "./networks:./channels:./modules:./simulations" \
# #         -i ./images ./simulations/cross_validation_config_generated.ini -u Cmdenv \
# #         -c "short_1000_purification_validation_cnot_0_meas_0_without_decoherence_initial_fidelity_${i}" --cmdenv-status-frequency=10s > "cross-validation/short-1000-purification-fidelity-no-error-initial-fidelity-${i}" &
# #     pids+=($!)
# # done
# # # wait for all pids
# # echo "waiting for first experiments"
# # for pid in ${pids[*]};
# # do
# #     echo "waiting on pid = $pid"
# #     wait $pid
# # done
# # pids=()


# ######## No error long version

# mkdir -p cross-validation/no-error/long
# for i in $(seq 60 2 100);
# do
#     echo "Running purification sims (long; 100k shots) without decoherence with intial fidelity = ${i}"
#     ./quisp -n "./networks:./channels:./modules:./simulations" \
#         -i ./images ./simulations/cross_validation_config_generated.ini -u Cmdenv \
#         -c "purification_validation_cnot_0_meas_0_without_decoherence_initial_fidelity_${i}" --cmdenv-status-frequency=10s > "cross-validation/no-error/long/purification-fidelity-no-error-initial-fidelity-${i}" &
#     pids+=($!)
# done
# # wait for all pids
# echo "waiting for first experiments"
# for pid in ${pids[*]};
# do
#     echo "waiting on pid = $pid"
#     wait $pid
# done
# pids=()

# ######## No error short version

# mkdir -p cross-validation/no-error/short
# for i in $(seq 60 2 100);
# do
#     echo "Running purification sims (short; 500 shots) without decoherence with intial fidelity = ${i}"
#     ./quisp -n "./networks:./channels:./modules:./simulations" \
#         -i ./images ./simulations/cross_validation_config_generated.ini -u Cmdenv \
#         -c "short_500_purification_validation_cnot_0_meas_0_without_decoherence_initial_fidelity_${i}" --cmdenv-status-frequency=10s > "cross-validation/no-error/short/purification-fidelity-no-error-initial-fidelity-${i}" &
#     pids+=($!)
# done
# # wait for all pids
# echo "waiting for first experiments"
# for pid in ${pids[*]};
# do
#     echo "waiting on pid = $pid"
#     wait $pid
# done
# pids=()

# ######## With 55ms decoherence (short)

# mkdir -p cross-validation/55ms/short
# for i in $(seq 60 2 100);
# do
#     echo "Running purification sims (short; 500 shots) with decoherence 55ms with intial fidelity = ${i}"
#     ./quisp -n "./networks:./channels:./modules:./simulations" \
#         -i ./images ./simulations/cross_validation_config_generated.ini -u Cmdenv \
#         -c "short_500_purification_validation_cnot_0_meas_0_with_decoherence_55000_ms_initial_fidelity_${i}" --cmdenv-status-frequency=10s > "cross-validation/55ms/short/purification-fidelity-with-55ms-initial-fidelity-${i}" &
#     pids+=($!)
# done
# # wait for all pids
# echo "waiting for first experiments"
# for pid in ${pids[*]};
# do
#     echo "waiting on pid = $pid"
#     wait $pid
# done
# pids=()


######## With 55ms decoherence (long)

mkdir -p cross-validation/55ms/long
for i in $(seq 60 2 100);
do
    echo "Running purification sims (long; 100k shots) with decoherence 55ms with intial fidelity = ${i}"
    ./quisp -n "./networks:./channels:./modules:./simulations" \
        -i ./images ./simulations/cross_validation_config_generated.ini -u Cmdenv \
        -c "purification_validation_cnot_0_meas_0_with_decoherence_55000_ms_initial_fidelity_${i}" --cmdenv-status-frequency=10s > "cross-validation/55ms/long/purification-fidelity-with-55ms-initial-fidelity-${i}" &
    pids+=($!)
done
# wait for all pids
echo "waiting for first experiments"
for pid in ${pids[*]};
do
    echo "waiting on pid = $pid"
    wait $pid
done
pids=()

# ######## With 18ms decoherence (short)

# mkdir -p cross-validation/18ms/short
# for i in $(seq 60 2 100);
# do
#     echo "Running purification sims (short; 500 shots) with decoherence 18ms with intial fidelity = ${i}"
#     ./quisp -n "./networks:./channels:./modules:./simulations" \
#         -i ./images ./simulations/cross_validation_config_generated.ini -u Cmdenv \
#         -c "short_500_purification_validation_cnot_0_meas_0_with_decoherence_18000_ms_initial_fidelity_${i}" --cmdenv-status-frequency=10s > "cross-validation/18ms/short/purification-fidelity-with-18ms-initial-fidelity-${i}" &
#     pids+=($!)
# done
# # wait for all pids
# echo "waiting for first experiments"
# for pid in ${pids[*]};
# do
#     echo "waiting on pid = $pid"
#     wait $pid
# done
# pids=()


# ######## With 18ms decoherence (long)

# mkdir -p cross-validation/18ms/long
# for i in $(seq 60 2 100);
# do
#     echo "Running purification sims (long; 100k shots) with decoherence 18ms with intial fidelity = ${i}"
#     ./quisp -n "./networks:./channels:./modules:./simulations" \
#         -i ./images ./simulations/cross_validation_config_generated.ini -u Cmdenv \
#         -c "purification_validation_cnot_0_meas_0_with_decoherence_18000_ms_initial_fidelity_${i}" --cmdenv-status-frequency=10s > "cross-validation/18ms/long/purification-fidelity-with-18ms-initial-fidelity-${i}" &
#     pids+=($!)
# done
# # wait for all pids
# echo "waiting for first experiments"
# for pid in ${pids[*]};
# do
#     echo "waiting on pid = $pid"
#     wait $pid
# done
# pids=()


echo "All simulations finished"
