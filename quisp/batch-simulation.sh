#!/bin/bash

pids=()

echo "Running to find base Bell pair fidelity"
./quisp -n "./networks:./channels:./modules:./simulations" \
    -i ./images ./simulations/mim_generation_test.ini -u Cmdenv \
    -c "base_fidelity" --cmdenv-status-frequency=10s > "exp-base-fidelity" &
pids+=($!)
echo "waiting for base fidelity experiment"
for pid in ${pids[*]};
do
    echo "waiting on pid = $pid"
    wait $pid
done
pids=()

for i in 1 2 4 8 16 32 64;
do
    echo "Running first exp with $i memories"
    ./quisp -n "./networks:./channels:./modules:./simulations" \
        -i ./images ./simulations/mim_generation_test.ini -u Cmdenv \
        -c "memory_$i" --cmdenv-status-frequency=10s > "exp1-raw-memories-$i" &
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

for i in 0 1 2 3 4 5 6 7 8 9 10;
do
    alicedist="$((20 - $i))"
    echo "Running imbalanced BSA placement with distance $i - $alicedist"
    ./quisp -n "./networks:./channels:./modules:./simulations" \
        -i ./images ./simulations/cross_validation.ini -u Cmdenv \
        -c "mim_imbalanced_${alicedist}_${i}" --cmdenv-status-frequency=10s > "exp2-raw-${alicedist}_${i}" &
    pids+=($!)
done
# wait for all pids
echo "waiting for second experiments"
for pid in ${pids[*]};
do
    echo "waiting on pid = $pid"
    wait $pid
done
pids=()

for cnot in 0 025 05 075 1 125 15 175 2 225 25 275 3 325 35 375 4 425 45 475 5 525 55 575 6 625 65 675 7 725 75 775 8 825 85 875 9 925 95 975;
do
    echo "Running experiment 3 - CNOT error: $cnot, measurement error: 0, with decoherence"
    ./quisp -n "./networks:./channels:./modules:./simulations" \
        -i ./images ./simulations/cross_validation_config_generated.ini -u Cmdenv \
        -c "swapping_validation_cnot_${cnot}_meas_0_with_decoherence" \
        --cmdenv-status-frequency=10s > "exp3-raw-${cnot}_0_with_decoherence" &
    pids+=($!)

    echo "Running experiment 3 - CNOT error: $cnot, measurement error: 0, without decoherence"
    ./quisp -n "./networks:./channels:./modules:./simulations" \
        -i ./images ./simulations/cross_validation_config_generated.ini -u Cmdenv \
        -c "swapping_validation_cnot_${cnot}_meas_0_without_decoherence" \
        --cmdenv-status-frequency=10s > "exp3-raw-${cnot}_0_without_decoherence" &
    pids+=($!)
done
# wait for all pids
echo "waiting for third experiments (CNOT error)"
for pid in ${pids[*]};
do
    echo "waiting on pid = $pid"
    wait $pid
done
pids=()

for meas in 025 05 075 1 125 15 175 2 225 25 275 3 325 35 375 4 425 45 475 5 525 55 575 6 625 65 675 7 725 75 775 8 825 85 875 9 925 95 975;
do
    echo "Running experiment 3 - CNOT error: 0, measurement error: $meas, with decoherence"
    ./quisp -n "./networks:./channels:./modules:./simulations" \
        -i ./images ./simulations/cross_validation_config_generated.ini -u Cmdenv \
        -c "swapping_validation_cnot_0_meas_${meas}_with_decoherence" \
        --cmdenv-status-frequency=10s > "exp3-raw-0_${meas}_with_decoherence" &
    pids+=($!)

    echo "Running experiment 3 - CNOT error: 0, measurement error: $meas, without decoherence"
    ./quisp -n "./networks:./channels:./modules:./simulations" \
        -i ./images ./simulations/cross_validation_config_generated.ini -u Cmdenv \
        -c "swapping_validation_cnot_0_meas_${meas}_without_decoherence" \
        --cmdenv-status-frequency=10s > "exp3-raw-0_${meas}_without_decoherence" &
    pids+=($!)
done
# wait for all pids
echo "waiting for third experiments (measurement error)"
for pid in ${pids[*]};
do
    echo "waiting on pid = $pid"
    wait $pid
done
pids=()

echo "All simulations finished"
