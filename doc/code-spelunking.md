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
based on being listed in a `.ned` file.  In `networks/QNode.ned`, you
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

## Our first RuleSet: Looking at the tomography code
