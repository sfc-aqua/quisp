# USAGE IN COMMAND LINE USING MAKE

We are working with the following installation tree.  You are assumed
to have just come from [doc/INSTALL.md](INSTALL.md).

```
home/
├── projects/
│   └── quisp/
│       ├── .git/
│       ├── setenv*
│       └── quisp/
└── .local/
    └── lib/
        ├── omnetpp-5.6.1/
        │   ├── setenv*
        │   └── bin/
        │       └── omnetpp*
        └── eigen-source/
```

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
/home/.local/lib/omnetpp-5.6.1 λ source setenv && cd /home/projects/quisp
/home/.local/lib/omnetpp-5.6.1
/home/projects/quisp λ source setenv
(quisp) /home/projects/quisp λ echo $VIRTUAL_ENV
quisp
```

### Move the OmNET++ folder close enough to quisp

If you put the OmNET++ folder (or a symbolic link to it) close to the quisp
folder, the `setenv` script will find it and you will not need to setup the
OmNET++ environment yourself.

```sh
/home/projects λ ln -s /home/.local/lib/omnetpp-5.6.1 omnetpp
/home/projects λ cd quisp
/home/projects/quisp λ source setenv
(quisp) /home/projects/quisp λ echo $VIRTUAL_ENV
quisp
```

## Run the first build and fix errors

You can directly run the build using `make`.

```sh
(quisp) /home/projects/quisp λ make
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

## Running QUISP

### Run the GUI

You can build then run the QUISP graphical interface in normal mode.

```sh
(quisp) /home/projects/quisp λ make run
```

You can also run in debug mode. The debug mode will build QUISP in debug
mode, then run the graphical interface in gdb. This can be useful to locate
a Segmentation fault for example.

```sh
(quisp) /home/projects/quisp λ make dbg

...

Setting up Qtenv...

Loading NED files from .:  13

Loading images from './bitmaps': *: 0
Loading images from './images': *: 0
Loading images from '/tmp/tmp.home/home/.local/lib/omnetpp-5.6.1/images': *: 0  abstract/*: 90  background/*: 4  block/*: 320  device/*: 195  logo/*: 1  maps/*: 9  misc/*: 70  msg/*: 55  old/*:
111  status/*: 28

[New Thread 0x7fffe7402700 (LWP 2420)]
[New Thread 0x7fffda27a700 (LWP 2422)]
[New Thread 0x7fffd9a79700 (LWP 2423)]
[New Thread 0x7fffd9278700 (LWP 2424)]
[New Thread 0x7fffd8a77700 (LWP 2425)]
[Thread 0x7fffd9278700 (LWP 2424) exited]
[Thread 0x7fffe7402700 (LWP 2420) exited]

End.
[Thread 0x7fffd8a77700 (LWP 2425) exited]
[Thread 0x7fffd9a79700 (LWP 2423) exited]
[Thread 0x7fffda27a700 (LWP 2422) exited]
[Inferior 1 (process 2410) exited normally]
(gdb) q
```

### Run without GUI

Running without GUI can be useful to run faster when you do not need the graphics.
For example when running quantum tomography simulations we only want the
output topology with link costs.

You can run QUISP this way. Without GUI, one topology configuration will be run
directly. The Makefile specifies one by default.

```sh
(quisp) /home/projects/quisp λ make BATCH=true run
```

If you want to run another configuration, the list is available in the `omnetpp.ini`
file and you can specify it to `make`.

```sh
(quisp) /home/projects/quisp λ grep '^\[Config ' quisp/networks/omnetpp.ini
[Config Link_Tomography]
[Config Linear_Single_MM]
[Config Linear_One_MM_bufferGap]
[Config Linear_Single_MM_low_precision]
[Config Linear_Single_MSM]
[Config Linear_Single_MIM]
[Config Linear_MIM_and_MM_and_MSM]
[Config ispMap_1239_node_23_48]
[Config Simple_constant_quantum_cost]
(quisp) /home/projects/quisp λ make BATCH=true QCONFIG=Linear_Single_MM run
```

Note that you can do the exact same thing in debug mode.

```sh
(quisp) /home/projects/quisp λ make BATCH=true QCONFIG=Linear_Single_MM dbg
```

## Documenting QUISP

Do not hesitate to document your code by using the Doxygen syntax.
Then, you can generate automatic code documentation with doxygen and use your
favorite web browser to open it.

```sh
(quisp) /home/projects/quisp λ make doc
(quisp) /home/projects/quisp λ xdg-open doc/html/index.html
```
