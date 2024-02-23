#!/bin/bash

# This bash file writes in each simulation setting in the file where we write in the simtime when we obtain 100 bell pairs in the link.
output_file="hundredbellpair"

for link in MSM; do
    for memory in one; do
        echo "${link}_${memory}," >> "$output_file"
        ./quisp -u Cmdenv simulations/link_generation_test.ini -c Testing_${link}_${memory}_memory_short
        echo  >> "$output_file"
    done
done
