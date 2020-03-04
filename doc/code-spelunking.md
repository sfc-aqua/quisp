# Code Spelunking: Your First Foray #

There are several hundred pages of documentation [available on the OMNeT++ website](https://omnetpp.org/documentation/).  You'll want to
begin finding your way around in that.

In OMNeT++, practically all of the work is triggered via `cMessage`s,
passed from object to object, and network packets are `cPacket`s (see
Ch. 5 of the OMNeT++ manual).

This document is just to get you started; more complete documentation
will be coming eventually.  There is some information on the code
structure (which naturally will gradually go out of date) in Appendix
A of [Takaaki's master's thesis](https://arxiv.org/abs/1908.10758).

## Finding the "Application" that runs

If almost all of the action is triggered a `cMessage`, almost all of
the hardware and software components are known as `module`s.  To get
oriented, see the [API for
cSimpleModule](https://doc.omnetpp.org/omnetpp/api/classomnetpp_1_1cSimpleModule.html).
See Sec. 4.4 of the OMNeT++ manual, "Adding Functionality to
cSimpleModule".

Each `module` is loaded and an instance of the object instantiated
based on being listed in a `.ned` file.  In `quisp/networks/QNode.ned`, you
will find

```
module QNode
{
...
    submodules:
        app: Application {
            parameters:
                address = address;//share the same address within all inner modules
                @display("p=30,43");
        }
```

Let's find the `initialize()` member function for that class.  There
should be one in each `module`.  For example, in
`quisp/modules/Application.cc`, you will find

```
void Application::initialize()
```

Inside that function, you will see it first checks its own node type;
if it's not an end node, it sends a message to delete itself.  (It
determines whether it's an end node by looking at whether there is a
`gate` connected to a router.)

Otherwise, assuming it's an EndNode, it proceeds and sets up the
application itself.

**One of the important open tasks is to build a better model of an
application, including both behavior of individual applications,
and an overall traffic model.**  This set of notes should help us
get started on that.

You will see, in the current implementation, that if the node's
address is 1, it picks a single other node at random and builds a
connection to it.  This is done by firing off a single
`ConnectionSetupRequest` message to that node; after that, all of the
connection setup proceeds in an event response fashion.  (At the
moment, loss of classical messages is not included, so there is no
need to monitor and retry the setup.)

## Finding the important software modules

In QuISP, there is a big, and important, distinction between the
_software_ for a quantum repeater, and the simulation of the
_hardware_.  The 

In `quisp/networks/qrsa.ned`, you'll find the definitions of the key
components:

```
simple RoutingDaemon
{
    parameters:
        int address;
    gates:
        //inout dummyQNICLink[];
}

simple HardwareMonitor
{
...
}

simple ConnectionManager
{
...
}

simple RuleEngine
{
...
}

simple RealTimeController
{
...
}
```

Those five `simple` objects are configured into one software system,

```
module quantumRoutingSoft
{
...
}
```

which is used as a `submodule` in `module QNode`, found in
`quisp/networks/QNode.ned`, as described near the top of this
document.

_(add the software architecture figure here)_

## Our first RuleSet: Looking at the tomography code

Let's follow one chain of things through the code.  Let's see how the
link-level tomography gets kicked off and executed.

You'll find some useful definitions in `quisp/classical_messages.msg`:

```
packet LinkTomographyRuleSet extends header
{
    int process_id;
    int number_of_measuring_resources;
    RuleSetField RuleSet;
}

packet LinkTomographyRequest extends header
{
}
```

(along with several others).  Those are transformed automatically into
a file called `classical_messages_m.cc`; don't edit this file!

Link tomography is enabled by a parameter called, naturally enough,
`link_tomography`, a boolean.  It's defined in
`quisp/networks/qrsa.ned`:

```
simple HardwareMonitor
{
    parameters:
...
        bool link_tomography = default(false);
...
}
```

but if you grep through the `.ini` files shipped with this, you'll
find that the default is overridden in most of them, including (unless
this changes before release), the default `omnetpp.ini` file:

```
[Config Example_run]
network= Realistic_Layer2_Simple_MIM_MM_10km
...
**.num_measure = 7000
...
**.tomography_output_filename = "Example_run"
...
**.link_tomography = true
**.initial_purification = 2
**.Purification_type = 1001
```

