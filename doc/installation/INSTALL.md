# INSTALLATION

Welcome to the installation instructions for installing QuISP.  In
theory, QuISP runs anywhere you can get OmNET++ to run, including Mac,
Windows, and Linux.  The notes here assume you are working on Linux.
If you prefer to do this inside a container, we support working with
[Docker](https://www.docker.com/); see the instructions
[here](./Build_on_docker.md).  If you are on Windows, see the
[Windows install doc](Build_on_windows.md).

This document walks you through downloading QuISP, then installing and
building the related software.  Importing QuISP itself into OmNET++
and building and executing it can be done in two distinct ways,
documented separately (scroll down to the end of this document).

You should assume that reading the instructions, installing from
source, and getting QuISP to run will take you two to four hours the
first time.

## Notation

These installation instructions are interlaced with one example of running the
installation on Linux. Every shell sample will look like this:

```sh
/the/current/directory λ echo HELLO WORLD
HELLO WORLD
```

You type the part after the lambda character (beginning with "echo" in
the example above).

## QUISP

You can get the source for quisp and put it pretty much anywhere you want.

```sh
/home λ mkdir projects && cd projects
/home/projects λ git clone https://github.com/sfc-aqua/quisp.git
Cloning into 'quisp'...
remote: Counting objects: 1222, done.
remote: Compressing objects: 100% (1006/1006), done.
remote: Total 1222 (delta 895), reused 287 (delta 176)
Receiving objects: 100% (1222/1222), 3.79 MiB | 1.61 MiB/s, done.
Resolving deltas: 100% (895/895), done.
```

At this point your file system looks like this.

```
home/
└── projects/
    └── quisp/
        └── .git/
```

## OmNET++

Get the release of OmNET++ 5.6.1 from [their website](https://omnetpp.org/) and uncompress it in the folder of your
choice. To remain general, this example uncompresses it in a local
libraries folder, far from the quisp project and from standard
installation folders.

```
home/
├── projects/
│   └── quisp/
│       └── .git/
└── downloads/
    └── omnetpp-5.6.1-src-linux.tgz
```

```sh
/home λ mkdir -p .local/lib && cd .local/lib
/home/.local/lib λ tar -xzf /home/downloads/omnetpp-5.6.1-src-linux.tgz
```

At this point there is no `omnetpp` binary because you still need to build from
the source release.

```
home/
├── projects/
│   └── quisp/
│       └── .git/
├── downloads/
│   └── omnetpp-5.6.1-src-linux.tgz
└── .local/
    └── lib/
        └── omnetpp-5.6.1/
            ├── configure*
            ├── INSTALL
            ├── Makefile
            ├── README
            ├── setenv*
            ├── bin/
            └── doc/
```

### Building OmNET++

Building information is available in the `doc/InstallGuide.pdf` file of their
source release. Here is a quick version of it on linux.

Compiling OmNET++ takes time. Be patient.

```sh
/home/.local/lib/omnetpp-5.6.1 λ source setenv
/home/.local/lib/omnetpp-5.6.1

/home/.local/lib/omnetpp-5.6.1 λ ./configure
checking build system type... x86_64-unknown-linux-gnu
checking host system type... x86_64-unknown-linux-gnu
configure: -----------------------------------------------
configure: reading configure.user for your custom settings
configure: -----------------------------------------------
checking for clang... no
checking for icc... no
checking for gcc... gcc

...

Your PATH contains /tmp/tmp.home/home/.local/lib/omnetpp-5.6.1/bin. Good!

/home/.local/lib/omnetpp-5.6.1 λ make -j9
make -s MODE=release
***** Configuration: MODE=release, TOOLCHAIN_NAME=gcc, LIB_SUFFIX=.so ****
===== Checking environment =====

...

Creating executable: out/gcc-debug//osg-satellites_dbg

Now you can type "omnetpp" to start the IDE
```

Among other things, this gives you access to the OmNET++ IDE via the executable
file `omnetpp`.

```
home/
└── .local/
    └── lib/
        └── omnetpp-5.6.1/
            └── bin/
                └── omnetpp*
```

## Eigen

To run the simulations, you need to get Eigen, which is a library for matrix
calculation in C/C++. This is used for channel errors and memory errors.

Download Eigen (tested with version 3.3.4) from [their website][eigen].

[eigen]: http://eigen.tuxfamily.org/index.php?title=Main_Page

```
home/
├── projects/
│   └── quisp/
│       └── .git/
├── .local/
│   └── lib/
│       └── omnetpp-5.6.1/
│           ├── setenv*
│           └── bin/
│               └── omnetpp*
└── downloads/
    └── eigen-eigen-5a0156e40feb.tar.bz2
```

```sh
/home/.local/lib λ tar -xjf /home/downloads/eigen-eigen-*.tar.bz2
/home/.local/lib λ mv eigen-eigen-* eigen-source
```

```
home/
├── projects/
│   └── quisp/
│       └── .git/
├── .local/
│   └── lib/
│       ├── omnetpp-5.6.1/
│       │   ├── setenv*
│       │   └── bin/
│       │       └── omnetpp*
│       └── eigen-source/
│           ├── Eigen/
│           ├── unsupported/
│           │   └── Eigen/
│           └── INSTALL
└── downloads/
    └── eigen-eigen-5a0156e40feb.tar.bz2
```

If you want to install the library in your system instead of keeping this local
installation, you will find installation information in the `INSTALL` file of
their archive. The example follows the full system installation.

Note that by default, the `CMAKE_INSTALL_PREFIX` variable is `/usr/local`, which
is good. `make install` might require administrator privileges.

```sh
/home/.local/lib λ mkdir eigen-build && cd eigen-build
/home/.local/lib/eigen-build λ cmake -DCMAKE_INSTALL_PREFIX=/usr/local ../eigen-source
/home/.local/lib/eigen-build λ make install
```

```
home/
├── projects/
│   └── quisp/
│       └── .git/
└── .local/
    └── lib/
        ├── omnetpp-5.6.1/
        │   ├── setenv*
        │   └── bin/
        │       └── omnetpp*
        ├── eigen-build/
        └── eigen-source/
usr/
└── local/
    ├── include/
    │   └── eigen3/
    │       ├── Eigen/
    │       └── unsupported/
    │           └── Eigen/
    └── share/
        └── eigen3/
```

## Help Me!!!

If you are having trouble with the install and the answers aren't
here, you can peruse the [Frequently Asked Questions
(FAQ)](FAQ.md).

## Next Step: QuISP!

There are two main ways of working with QUISP. You can either use the
Eclipse-like graphical interface of OmNET++, for which you will find
instructions in [doc/USAGE-omnetpp-gui.md](USAGE-omnetpp-gui.md),
or you can use the `Makefile` and GNU make, by looking at instructions
in [doc/USAGE-makefile.md](USAGE-makefile.md). Some operations are
implemented in the Makefile and not explained for the graphical user
interface.
