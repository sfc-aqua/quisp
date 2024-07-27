#!/bin/bash

for i in 1 2 4 8 16 32 64;
do
    # sed command to print even numbered lines
    grep "sim time" "exp1-raw-memories-$i" | awk '{print $3}' | sed -n 'n;p' > "postprocess-exp1-memories-$i"
done

for i in 0 1 2 3 4 5 6 7 8 9 10;
do
    # sed command to print even numbered lines
    alicedist="$((20 - $i))"
    grep "sim time" "exp2-raw-${alicedist}_${i}" | awk '{print $3}' | sed -n 'n;p' > "postprocess-exp2-$i"
done


# TODO: complete the postprocessing
for cnot in 0 025 05 075 1 125 15 175 2 225 25 275 3 325 35 375 4 425 45 475 5;
do
    grep "fidelity" "exp3-raw-${cnot}_0_without_decoherence" | sed -n 's/.*Fidelity=\(0\.[0-9]*\).*/\1/p' | sed -n 'n;p' | cat
    grep "sim time" "exp3-raw-${cnot}_0_without_decoherence" | cat
done

for cnot in 0 025 05 075 1 125 15 175 2 225 25 275 3 325 35 375 4 425 45 475 5;
do
    grep "fidelity" "exp3-raw-${cnot}_0_with_1ms_decoherence" | sed -n 's/.*Fidelity=\(0\.[0-9]*\).*/\1/p' | sed -n 'n;p' | cat
    grep "sim time" "exp3-raw-${cnot}_0_with_1ms_decoherence" | cat
done
