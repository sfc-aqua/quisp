#!/bin/sh
./quisp simulations/test_steane.ini -u Cmdenv  -c MIM_1km --cmdenv-express-mode=true
./quisp simulations/test_steane.ini -u Cmdenv  -c MIM_5km --cmdenv-express-mode=true
./quisp simulations/test_steane.ini -u Cmdenv  -c MIM_10km --cmdenv-express-mode=true
./quisp simulations/test_steane.ini -u Cmdenv  -c MIM_15km --cmdenv-express-mode=true
./quisp simulations/test_steane.ini -u Cmdenv  -c MIM_20km --cmdenv-express-mode=true
./quisp simulations/test_steane.ini -u Cmdenv  -c MIM_25km --cmdenv-express-mode=true
./quisp simulations/test_steane.ini -u Cmdenv  -c MIM_30km --cmdenv-express-mode=true
./quisp simulations/test_steane.ini -u Cmdenv  -c MIM_35km --cmdenv-express-mode=true