# USAGE IN COMMAND LINE USING MAKE

Every time you want to use the Makefile, you need to setup the environment
using scripts from the quisp project.

## Setup the environment

The environment setup script is the `setenv` file in the quisp project
directory.

This script needs to know where is OmNET++. If you do not let it know, you will
get an error.

```sh
/home/projects/quisp λ source setenv
Could not find OmNET++
```

There are two ways of letting the `setenv` script know where OmNET++ is.

### Set the OmNET++ environment before

If you source the `setenv` file of OmNET++ before, the quisp script will detect
it and find OmNET++ in the PATH variable.

```sh
/home/.local/lib/omnetpp-5.2 λ source setenv && cd /home/projects/quisp
/home/.local/lib/omnetpp-5.2
/home/projects/quisp λ source setenv
(quisp) /home/projects/quisp λ echo $VIRTUAL_ENV
quisp
```

### Move the OmNET++ folder close enough to quisp

If you put the OmNET++ folder (or a symbolic link to it) close to the quisp
folder, the `setenv` script will find it and you will not need to setup the
OmNET++ environment yourself.

```sh
/home/projects λ ln -s /home/.local/lib/omnetpp-5.2 omnetpp
/home/projects λ cd quisp
/home/projects/quisp λ source setenv
(quisp) /home/projects/quisp λ echo $VIRTUAL_ENV
quisp
```

## Run the first build and fix errors

You can directly run the build using `make`.

```sh
/home/projects/quisp λ make
```

Here is a list of quickly fixed common errors that you could get.

### Unable to find Eigen

```
fatal error: unsupported/Eigen/MatrixFunctions: No such file or directory
```

This means your Eigen library is not installed in `/usr/local/include`. You do
not need to move your installation. In my example I installed it in
`/home/.local/lib/eigen-source`. Open the newly created `quisp/.oppbuildspec`
and change the path to the Eigen library.

```diff
 <?xml version="1.0" encoding="UTF-8" standalone="no"?>
 <buildspec version="4.0">
-  <dir makemake-options="--deep -O out -I. -I/usr/local/include/eigen3 --meta:recurse --meta:export-include-path --meta:use-exported-include-paths --meta:export-library --meta:use-exported-libs --meta:feature-cflags --meta:feature-ldflags" path="." type="makemake"/>
+  <dir makemake-options="--deep -O out -I. -I/home/.local/lib/eigen-source --meta:recurse --meta:export-include-path --meta:use-exported-include-paths --meta:export-library --meta:use-exported-libs --meta:feature-cflags --meta:feature-ldflags" path="." type="makemake"/>
 </buildspec>
```
