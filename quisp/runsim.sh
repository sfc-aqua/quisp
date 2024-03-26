#! bin/bash

output_file="bellpairtimings"

for chain in mxm mim msm;
do
    for length in simple long
        do
            echo "${chain}_${length}" >> "$output_file"
            ./quisp -u Cmdenv simulations/heterogeneous.ini -c ${chain}_${length}
            echo >> "$output_file"
    done
done

for chain in mxm msm;
do
    for length in simple long
        do
            echo "${chain}_${length}_adaptive" >> "$output_file"
            ./quisp -u Cmdenv simulations/heterogeneous.ini -c ${chain}_${length}_adaptive
            echo >> "$output_file"
    done
done
