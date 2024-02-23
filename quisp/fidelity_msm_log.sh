#!/bin/bash

output_file="fidelities"

for link in MIM; do
    for type in depolarizing_purification_four; do
        echo "${link}_${type}," >> "$output_file"
        ./quisp -u Cmdenv simulations/link_generation_test.ini -c Testing_${link}_eight_memory_${type}
        echo  >> "$output_file"
    done
done
