#! bin/bash

output_file="bellpairtimings"

# # mxm mim msm simple chains
# for chain in mxm mim msm;
# do
#     for length in simple long
#         do
#             echo "${chain}_${length}" >> "$output_file"
#             ./quisp -u Cmdenv simulations/heterogeneous.ini -c ${chain}_${length}
#             echo >> "$output_file"
#     done
# done

# for chain in mxm msm;
# do
#     for length in simple long
#         do
#             echo "${chain}_${length}_adaptive" >> "$output_file"
#             ./quisp -u Cmdenv simulations/heterogeneous.ini -c ${chain}_${length}_adaptive
#             echo >> "$output_file"
#     done
# done
output_file="bellpairtimings"
# # insertion of mim link in msm 10 node chain
# for position in zero one two three four;
# do
#     for length in simple long
#         do
#             echo "msm_ten_nodes_mim_${position}_${length}" >> "$output_file"
#             ./quisp -u Cmdenv simulations/heterogeneous.ini -c msm_ten_nodes_mim_${position}_${length}
#             echo >> "$output_file"
#     done
# done

# for position in zero one two three four;
# do
#     for length in simple long
#         do
#             echo "msm_ten_nodes_mim_${position}_${length}_adaptive" >> "$output_file"
#             ./quisp -u Cmdenv simulations/heterogeneous.ini -c msm_ten_nodes_mim_${position}_${length}_adaptive
#             echo >> "$output_file"
#     done
# done

for memory in four thirtytwo;
do
    for length in long short
        do
            echo "msm_ten_nodes_${length}_${memory}" >> "$output_file"
            ./quisp -u Cmdenv simulations/heterogeneous.ini -c msm_ten_nodes_${length}_${memory}
            echo >> "$output_file"
    done
done
for memory in four thirtytwo;
do
    for length in long short
        do
            echo "msm_ten_nodes_${length}_adaptive_${memory}" >> "$output_file"
            ./quisp -u Cmdenv simulations/heterogeneous.ini -c msm_ten_nodes_${length}_adaptive_${memory}
            echo >> "$output_file"
    done
done