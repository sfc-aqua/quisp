#!/bin/bash

output_file="bellpairtimings"
for memory in one two four eight sixteen; do
    echo -n "balanced_${memory}," >> "$output_file"
    ./quisp -u Cmdenv simulations/sequencesim.ini -c balanced_${memory}
    echo  >> "$output_file"
done

echo -n "inbalanced_eleven_nine," >> "$output_file"
./quisp -u Cmdenv simulations/sequencesim.ini -c inbalanced_eleven_nine
echo  >> "$output_file"

echo -n "inbalanced_twelve_eight," >> "$output_file"
./quisp -u Cmdenv simulations/sequencesim.ini -c inbalanced_twelve_eight
echo  >> "$output_file"

echo -n "inbalanced_thirteen_seven," >> "$output_file"
./quisp -u Cmdenv simulations/sequencesim.ini -c inbalanced_thirteen_seven
echo  >> "$output_file"

echo -n "inbalanced_fourteen_six," >> "$output_file"
./quisp -u Cmdenv simulations/sequencesim.ini -c inbalanced_fourteen_six
echo  >> "$output_file"

echo -n "inbalanced_fifteen_five," >> "$output_file"
./quisp -u Cmdenv simulations/sequencesim.ini -c inbalanced_fifteen_five
echo  >> "$output_file"

echo -n "inbalanced_sixteen_four," >> "$output_file"
./quisp -u Cmdenv simulations/sequencesim.ini -c inbalanced_sixteen_four
echo  >> "$output_file"

echo -n "inbalanced_seventeen_three," >> "$output_file"
./quisp -u Cmdenv simulations/sequencesim.ini -c inbalanced_seventeen_three
echo  >> "$output_file"

echo -n "inbalanced_eighteen_two," >> "$output_file"
./quisp -u Cmdenv simulations/sequencesim.ini -c inbalanced_eighteen_two
echo  >> "$output_file"

echo -n "inbalanced_nineteen_one," >> "$output_file"
./quisp -u Cmdenv simulations/sequencesim.ini -c inbalanced_nineteen_one
echo  >> "$output_file"

echo -n "inbalanced_twenty_zero," >> "$output_file"
./quisp -u Cmdenv simulations/sequencesim.ini -c inbalanced_twenty_zero
echo  >> "$output_file"
