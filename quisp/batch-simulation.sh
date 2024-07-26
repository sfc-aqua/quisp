#!/bin/bash

# for i in 1 2 4 8 16 32 64;
# do
#     echo "Welcome $i times"
#     ./quisp -n "./networks:./channels:./modules:./simulations" -i \
#         ./images ./simulations/mim_generation_test.ini -u Cmdenv -c "memory_$i" --cmdenv-status-frequency=10s > "out-$i" &
# done

# for i in 0 1 2 3 4 5 6 7 8 9 10;
# do
#     alicedist="$((20 - $i))"
#     echo "Welcome $i times $alicedist"
#     ./quisp -n "./networks:./channels:./modules:./simulations" -i \
#         ./images ./simulations/cross_validation.ini -u Cmdenv -c "mim_imbalanced_${alicedist}_${i}" --cmdenv-status-frequency=10s > "exp2-raw-${alicedist}_${i}" &
# done

for cnot in 0 025 05 075 1 125 15 175 2 225 25 275 3 325 35 375 4 425 45 475;
do
    echo "Welcome cnot: $cnot, meas $meas, without decoherence"
    ./quisp -n "./networks:./channels:./modules:./simulations" -i \
        ./images ./simulations/cross_validation_config_generated.ini -u Cmdenv -c "swapping_validation_cnot_${cnot}_meas_0_with_1ms_decoherence" --cmdenv-status-frequency=10s > "exp3-raw-${cnot}_0_with_1ms_decoherence" &

    echo "Welcome cnot: $cnot, meas $meas, with 1ms decoherence"
    ./quisp -n "./networks:./channels:./modules:./simulations" -i \
        ./images ./simulations/cross_validation_config_generated.ini -u Cmdenv -c "swapping_validation_cnot_${cnot}_meas_0_without_decoherence" --cmdenv-status-frequency=10s > "exp3-raw-${cnot}_0_without_decoherence" &
done

for meas in 025 05 075 1 125 15 175 2 225 25 275 3 325 35 375 4 425 45 475;
do
    echo "Welcome cnot: $cnot, meas $meas, without decoherence"
    ./quisp -n "./networks:./channels:./modules:./simulations" -i \
        ./images ./simulations/cross_validation_config_generated.ini -u Cmdenv -c "swapping_validation_cnot_0_meas_${meas}_with_1ms_decoherence" --cmdenv-status-frequency=10s > "exp3-raw-0_${meas}_with_1ms_decoherence" &

    echo "Welcome cnot: $cnot, meas $meas, with 1ms decoherence"
    ./quisp -n "./networks:./channels:./modules:./simulations" -i \
        ./images ./simulations/cross_validation_config_generated.ini -u Cmdenv -c "swapping_validation_cnot_0_meas_${meas}_without_decoherence" --cmdenv-status-frequency=10s > "exp3-raw-0_${meas}_without_decoherence" &

done
