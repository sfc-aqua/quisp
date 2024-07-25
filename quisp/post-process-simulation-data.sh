#!/bin/bash

for i in 1 2 4 8 16 32 64;
do
    # sed command to print even numbered lines
    grep "sim time" "out-$i" | awk '{print $3}' | sed -n 'n;p' > "postprocess-memory-$i"
done

for i in 0 1 2 3 4 5 6 7 8 9 10;
do
    # sed command to print even numbered lines
    alicedist="$((20 - $i))"
    grep "sim time" "exp2-raw-${alicedist}_${i}" | awk '{print $3}' | sed -n 'n;p' > "postprocess-exp2-$i"
done

