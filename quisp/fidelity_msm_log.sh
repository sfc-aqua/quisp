#!/bin/bash

# This bash file writes in each simulation setting in the file where we write in the simtime when we obtain 100 bell pairs in the link.
output_file="fidelities"

for link in MIM MSM; do
    for type in _depolarizing_purification_one, _depolarizing_purification_two, _depolarizing_purification_three; do
        echo "${link}_depolarizing${}," >> "$output_file"
        ./quisp -u Cmdenv simulations/link_generation_test.ini -c ${link}"
        echo  >> "$output_file"
    done
done
