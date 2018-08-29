# QUISP

**TODO** PROJECT DESCRIPTION

## Installing requirements

QUISP requires OmNET++ and external C++ libraries to work. The full installation
process is described in [doc/INSTALL.md]().

## Building and running

There are two main ways of working with QUISP. You can either use the Eclipse-like
graphical interface of OmNET++, for which you will find instructions in
[doc/USAGE-omnetpp-gui.md](), or you can use the `Makefile` and GNU make,
by looking at instructions in [doc/USAGE-makefile.md](). Some operations are
implemented in the Makefile and not explained for the graphical user interface.

## Development tools

A few tools (mainly scripts) can be used to make development a bit easier. Their
usage is described in [doc/SCRIPTS.md]().


## Building and running

### Building and cleaning binaries

The makefile is there for this.

```sh
~/work/quisp λ make
~/work/quisp λ make clean
```

### Build documentation

Documentation generation uses `doxygen`.

```sh
~/work/quisp λ make doc
```

### Running the QUISP GUI

```sh
~/work/quisp λ make run
```

## Development tools

### File-wise todos

In `*.h` and `*.cc` files, put todos as follows:

```
/** \todo <identifier> Anything describing what to do. */
```

The `todo` tool can help list, add and remove todos on every file at once.

```
λ todo ls clean
λ todo add doc Write some clear documentation.
λ todo rm clean
```

### Generate documentation blocks

```
λ doc_file quisp/modules/stationaryQubit.h
λ echo "class stationaryQubit" | doc_class quisp/modules/stationaryQubit.h
```
