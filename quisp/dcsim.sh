#! bin/bash
output_file="bellpairtimings"

for length in ten hun;
do
    for arch in mim msm;
    do
        for adaptive in na a;
        do
            for mem in one two four eight sixteen thirtytwo sixtyfour onehundredtwentyeight twohundredfiftysix fivehundredtwelve;
                do
                    echo -n "${arch}_${length}_${adaptive}_${mem}," >> "$output_file"
                    ./quisp -u Cmdenv simulations/datacentre.ini -c ${arch}_${length}_${adaptive}_${mem}
                    echo >> "$output_file"
            done
        done
    done
done

