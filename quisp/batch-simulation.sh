#!/bin/bash

for i in 1 2 4 8 16 32 64;
do
    echo "Welcome $i times"
    ./quisp -n "./networks:./channels:./modules:./simulations" -i \
        ./images ./simulations/mim_generation_test.ini -u Cmdenv -c "memory_$i" --cmdenv-status-frequency=10s > "out-$i" &
done

for i in 0 1 2 3 4 5 6 7 8 9 10;
do
    alicedist="$((20 - $i))"
    echo "Welcome $i times $alicedist"
    ./quisp -n "./networks:./channels:./modules:./simulations" -i \
        ./images ./simulations/cross_validation.ini -u Cmdenv -c "mim_imbalanced_${alicedist}_${i}" --cmdenv-status-frequency=10s > "exp2-raw-${alicedist}_${i}" &
done
